#include "mainwindow.h"

#include <QDesktopServices>
#include <QInputDialog>
#include <QMessageBox>
#include <QProcess>
#include <QSettings>
#include <QUrl>

#include "config.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    QApplication::setApplicationDisplayName(tr(APP_NAME));
    setWindowTitle(tr("Login"));
    setWindowIcon(QIcon(":/icon/steam-papirus.svg"));
    QSettings setting("config.ini", QSettings::IniFormat);
    ui->auto_quit->setChecked(setting.value("auto_exit").toBool());

    reg = new QSettings(STEAM_REG, QSettings::NativeFormat);
    // Find Steam Path form reg
    steam_path = reg->value("SteamPath").toString();
    steam_exec = reg->value("SteamExe").toString();

    // load Saved User in loginusers.vdf
    users = SteamAccount::loadUsersFromFile(steam_path + R"(\config\loginusers.vdf)");

    QString recentUser = reg->value("AutoLoginUser").toString();
    size_t selection = 0;
    for (size_t i = 0; i < users.size(); ++i) {
        QString name = users.at(i).getAccountName();
        if (name == recentUser) {
            selection = i;
        }
        ui->list_account->addItem(name);
    }
    connect(ui->list_account->selectionModel(), &QItemSelectionModel::currentChanged, this, &MainWindow::onAccountChanged);

    ui->list_account->setCurrentRow(selection);
    connect(ui->btn_login, &QPushButton::released, this, [this] { login(ui->account->text()); });
    connect(ui->btn_add_user, &QToolButton::clicked, this, [this] {
        bool isConfirm = false;
        QString user_name;
        do {
            user_name =
                QInputDialog::getText(this, tr("Add User"), tr("Enter Steam Account Name.")
                    , QLineEdit::Normal, "", &isConfirm, Qt::Popup, Qt::ImhLatinOnly);
        } while (isConfirm && user_name.isEmpty()
                 && QMessageBox::critical(this, tr("Error Input"), tr("Username can not be empty")));

        if (isConfirm && !user_name.isEmpty()) {
            qDebug() << "Add New User: " << user_name;
            login(user_name);

        }
    });
}

MainWindow::~MainWindow() {
    QSettings setting("config.ini", QSettings::IniFormat);
    setting.setValue("auto_exit", ui->auto_quit->isChecked());
    delete ui;
}

bool MainWindow::killSteamProcess() {
    int choice = QMessageBox::information(this, tr("Steam is running"), tr("Kill Steam process?"), QMessageBox::Ok | QMessageBox::Cancel,
                                          QMessageBox::Cancel);
    if (choice == QMessageBox::Ok) {
        QProcess::execute("taskkill", QStringList() << "/IM"
                                            << "steam.exe"
                                            << "/T"
                                            << "/F");
    }
    return choice == QMessageBox::Ok;
}

void MainWindow::login(const QString &user_name) {
    if (!user_name.isEmpty()) {
        reg->setValue("AutoLoginUser", user_name);
    }

    // detect whether steam is running
    // tasklist /FI "imagename eq Steam.exe"
    QProcess p;
    p.start("tasklist", QStringList() << "/FI"
                                      << "imagename eq Steam.exe");
    p.waitForFinished();
    QString res = QString::fromLocal8Bit(p.readAll());
    qDebug() << res;
    p.close();

    if (!(res.contains("steam.exe") && !killSteamProcess())) {
        QDesktopServices::openUrl(QUrl::fromLocalFile(steam_exec));
        if (ui->auto_quit->isChecked()) {
            qApp->exit(0);
        }
    }
}

void MainWindow::onAccountChanged(const QModelIndex &current) {
    auto user = users.at(current.row());
    ui->account->setText(user.getAccountName());
    ui->username->setText(user.getPersonalName());
    ui->last_login->setText(user.getLastLogin().toString());
}

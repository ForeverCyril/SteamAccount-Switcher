#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QSettings>
#include <QDesktopServices>
#include <QUrl>
#include <QProcess>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->users, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &MainWindow::onAccountChanged);
    connect(ui->loginBtn, &QPushButton::clicked, this, &MainWindow::login);

    QSettings setting("config.ini", QSettings::IniFormat);
    ui->autoexit->setChecked(setting.value("auto_exit").toBool());

    reg = new QSettings(STEAM_REG, QSettings::NativeFormat);
    //Find Steam Path form reg
    steam_path = reg->value("SteamPath").toString();
    steam_exec = reg->value("SteamExe").toString();

    //load Saved User in loginusers.vdf
    users = SteamAccount::loadUsersFromFile(steam_path+R"(\config\loginusers.vdf)");

    for(auto user : users){
        ui->users->addItem(user.getAccountName());
    }

    // show recent login account
    QString recentUser = reg->value("AutoLoginUser").toString();
    for(int i=0;i<users.size();i++){
        if(users.at(i).getAccountName() == recentUser){
            ui->users->setCurrentIndex(i);
            break;
        }
    }

}

MainWindow::~MainWindow()
{
    QSettings setting("config.ini", QSettings::IniFormat);
    setting.setValue("auto_exit", ui->autoexit->isChecked());
    delete ui;
}

bool MainWindow::killSteamProcess() {
    QProcess p;
    int choice = QMessageBox::information(
            this,
            tr("Steam is running"),
            tr("Kill Steam process?"),
            QMessageBox::Ok|QMessageBox::Cancel, QMessageBox::Cancel);

    if(choice == QMessageBox::Ok){
        p.execute("taskkill",QStringList()<<"/IM"<<"steam.exe"<<"/T"<<"/F");
        p.waitForFinished();
    }
    p.close();
    return choice == QMessageBox::Ok;
}

void MainWindow::login() {
    QString id = ui->users->currentText();
    reg->setValue("AutoLoginUser", id);

    //detect whether steam is running
    //tasklist /FI "imagename eq Steam.exe"
    QProcess p;
    p.start("tasklist",QStringList()<<"/FI"<<"imagename eq Steam.exe");
    p.waitForFinished();
    QString res = QString::fromLocal8Bit(p.readAll());
    qDebug()<<res;
    p.close();
    if(!( res.contains("steam.exe") && !killSteamProcess())){
        QDesktopServices::openUrl(QUrl::fromLocalFile(steam_exec));
        if(ui->autoexit->isChecked()) this->close();
    }
}

void MainWindow::onAccountChanged(int new_index) {
    this->ui->name->setText(this->users.at(new_index).getPersonalName());
    this->ui->time->setText(this->users.at(new_index).getLastLogin().toString());
}

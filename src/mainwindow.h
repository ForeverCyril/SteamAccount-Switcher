#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSettings>

#include "steam_account.h"

constexpr const char *STEAM_REG = R"(\HKEY_CURRENT_USER\Software\Valve\Steam)";

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

public slots:
    void login(const QString &user_name = "");
    void onAccountChanged(const QModelIndex &current);

private:
    bool killSteamProcess();

    Ui::MainWindow *ui;
    QSettings *reg;
    QString steam_path;
    QString steam_exec;
    QList<SteamAccount> users;
};

#endif  // MAINWINDOW_H

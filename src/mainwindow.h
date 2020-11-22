#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSettings>
#include "steam_account.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void login();
    void onAccountChanged(int new_index);

private:
    bool killSteamProcess();

    Ui::MainWindow *ui;
    const QString STEAM_REG = R"(\HKEY_CURRENT_USER\Software\Valve\Steam)";
    QSettings *reg;
    QString steam_path;
    QString steam_exec;
    QList<SteamAccount> users;
};

#endif // MAINWINDOW_H

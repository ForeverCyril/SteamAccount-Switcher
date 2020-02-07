#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSettings>
#include "account.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    void initUI();
    bool killSteamProcess();

    Ui::MainWindow *ui;
    const QString STEAM_REG = R"(\HKEY_CURRENT_USER\Software\Valve\Steam)";
    QSettings *reg;
    QString steam_path;
    QString steam_exec;
    QList<Account> users;
};

#endif // MAINWINDOW_H

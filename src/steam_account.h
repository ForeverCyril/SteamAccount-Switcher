#ifndef STEAMACCOUNTSWITCHER_STEAM_ACCOUNT_H
#define STEAMACCOUNTSWITCHER_STEAM_ACCOUNT_H

#include <QDateTime>
#include <QDebug>
#include <QFile>
#include <QString>
#include <utility>

class SteamAccount {
private:
    QString account_name;
    QString personal_name;
    QDateTime last_login;

public:
    SteamAccount() = default;
    SteamAccount(const SteamAccount &account);
    explicit SteamAccount(QString &account, QString &name = QString());

    static QList<SteamAccount> loadUsersFromFile(const QString &filename);

    [[nodiscard]] const QString &getAccountName() const;

    void setAccountName(const QString &accountName);

    [[nodiscard]] const QString &getPersonalName() const;

    void setPersonalName(const QString &personalName);

    [[nodiscard]] const QDateTime &getLastLogin() const;

    void setLastLogin(const QDateTime &lastLogin);
};


#endif  // STEAMACCOUNTSWITCHER_STEAM_ACCOUNT_H

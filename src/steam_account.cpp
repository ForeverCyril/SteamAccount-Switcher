#include "steam_account.h"


SteamAccount::SteamAccount(const SteamAccount &account) {
    this->account_name = account.account_name;
    this->personal_name = account.personal_name;
    this->last_login = account.last_login;
}

SteamAccount::SteamAccount(QString &account, QString &name) {
    this->account_name = account;
    this->personal_name = name;
}

const QString &SteamAccount::getAccountName() const {
    return account_name;
}

void SteamAccount::setAccountName(const QString &accountName) {
    account_name = accountName;
}

const QString &SteamAccount::getPersonalName() const {
    return personal_name;
}

void SteamAccount::setPersonalName(const QString &personalName) {
    personal_name = personalName;
}

const QDateTime &SteamAccount::getLastLogin() const {
    return last_login;
}

void SteamAccount::setLastLogin(const QDateTime &lastLogin) {
    last_login = lastLogin;
}

QList<SteamAccount> SteamAccount::loadUsersFromFile(const QString &filename) {
    QFile file(filename);
    if(! file.exists()){
        qDebug()<<"loginusers.vdf is not exist.";
        return QList<SteamAccount>();
    }
    if(! file.open(QIODevice::ReadOnly)){
        qDebug()<<"can not read file";
        return QList<SteamAccount>();
    }

    QList<QStringList> data;
    while(! file.atEnd()){
        QString line = file.readLine();
        line.remove("\"");
        data.append(line.simplified().split(" "));
    }

    int index = -1;
    QList<SteamAccount> accountList;
    for(const auto& line:data){
        if(line.at(0)=="AccountName"){
            index++;
            accountList.append(SteamAccount());
            accountList[index].setAccountName(line.at(1));
        } else if(line.at(0)=="PersonaName"){
            accountList[index].setPersonalName(line.at(1));
        } else if(line.at(0)=="Timestamp"){
            accountList[index].setLastLogin(QDateTime::fromTime_t(line.at(1).toUInt()));
        }
    }
    return accountList;
}

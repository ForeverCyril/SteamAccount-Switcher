#ifndef STEAMACCOUNTSWITCHER_ACCOUNT_H
#define STEAMACCOUNTSWITCHER_ACCOUNT_H

#include <QString>
#include <QFile>
#include <QDebug>
#include <QDateTime>
#include <utility>

class Account {

private:
    QString account_name;
    QString personal_name;
    QDateTime last_login;

public:
    Account()= default;
    Account(const Account &account){
        this->account_name = account.account_name;
        this->personal_name = account.personal_name;
        this->last_login = account.last_login;
    }
    explicit Account(QString account, QString name=QString()){
        this->account_name = std::move(account);
        this->personal_name = std::move(name);
    }

    QString getAccount() const { return this->account_name;}
    QString getName() const { return this->personal_name;}
    QString getTime(Qt::DateFormat format = Qt::TextDate) const { return this->last_login.toString(format);}

    void setAccount(QString account){this->account_name = account;}
    void setName(QString name){this->personal_name = name;}
    void setTime(uint time){this->last_login = QDateTime::fromTime_t(time);}
};


#endif //STEAMACCOUNTSWITCHER_ACCOUNT_H

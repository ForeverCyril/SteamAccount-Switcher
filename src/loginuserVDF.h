#ifndef STEAMACCOUNTSWITCHER_LOGINUSERVDF_H
#define STEAMACCOUNTSWITCHER_LOGINUSERVDF_H

#include "account.h"
#include <QList>
#include <QString>

QList<Account> loadUsersFromFile(const QString& filename){
    QFile file(filename);
    if(not file.exists()){
        qDebug()<<"loginusers.vdf is not exist.";
        return QList<Account>();
    }
    if(not file.open(QIODevice::ReadOnly)){
        qDebug()<<"can not read file";
        return QList<Account>();
    }

    QList<QStringList> data;
    while(not file.atEnd()){
        QString line = file.readLine();
        line.remove("\"");
        data.append(line.simplified().split(" "));
    }

    int index = -1;
    QList<Account> accountList;
    for(const auto& line:data){
        if(line.at(0)=="AccountName"){
            index++;
            accountList.append(Account());
            accountList[index].setAccount(line.at(1));
        } else if(line.at(0)=="PersonaName"){
            accountList[index].setName(line.at(1));
        } else if(line.at(0)=="Timestamp"){
            accountList[index].setTime(line.at(1).toUInt());
        }
    }
    return accountList;
}


#endif //STEAMACCOUNTSWITCHER_LOGINUSERVDF_H

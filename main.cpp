#include "waveclient.h"
#include"wavelogin.h"
#include"waveregister.h"
#include <QApplication>
#include<QSqlDatabase>
static bool connDatabase(){
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL","conn");
    db.setHostName("localhost");
    db.setDatabaseName("wavedb");
    db.setUserName("root");
    db.setPassword("root");
    return db.open();
}
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    WaveLogin login;
    WaveClient client;
    WaveRegister reg;
    if(connDatabase()){
        login.show();
        return a.exec();
    }
}

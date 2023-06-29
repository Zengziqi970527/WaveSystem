#ifndef WAVELOGIN_H
#define WAVELOGIN_H

#include <QDialog>
#include<QSqlDatabase>
#include<QSqlQuery>
#include<QCryptographicHash>
#include<QMessageBox>
#include<QHostInfo>
#include<QHostAddress>
namespace Ui {
class WaveLogin;
}

class WaveLogin : public QDialog
{
    Q_OBJECT

public:
    explicit WaveLogin(QWidget *parent = nullptr);
    ~WaveLogin();
    void checkLogin();
    void loginInfo();
signals:
    void toRegister();
    void openClient(QString username);
private slots:
    void on_btnRegister_clicked();

    void on_btnLogin_clicked();

private:
    Ui::WaveLogin *ui;
};

#endif // WAVELOGIN_H

#ifndef WAVEREGISTER_H
#define WAVEREGISTER_H

#include <QDialog>
#include<QSqlDatabase>
#include<QSqlQuery>
#include<QMessageBox>
#include<QCryptographicHash>
#include<QHostInfo>
#include<QHostAddress>
namespace Ui {
class WaveRegister;
}

class WaveRegister : public QDialog
{
    Q_OBJECT

public:
    explicit WaveRegister(QWidget *parent = nullptr);
    ~WaveRegister();
    void insertUser();
    bool userisin();
signals:
    void backToLogin();
private slots:
    void on_btnClear_clicked();

    void on_btnRegister_clicked();
    void on_btnBack_clicked();

private:
    Ui::WaveRegister *ui;
};

#endif // WAVEREGISTER_H

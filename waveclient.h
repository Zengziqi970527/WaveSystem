#ifndef WAVECLIENT_H
#define WAVECLIENT_H

#include <QWidget>
#include<QSqlDatabase>
#include<QSqlQuery>
QT_BEGIN_NAMESPACE
namespace Ui { class WaveClient; }
QT_END_NAMESPACE

class WaveClient : public QWidget
{
    Q_OBJECT

public:
    WaveClient(QWidget *parent = nullptr);
    ~WaveClient();
public:
    QString username;
public slots:
    void getusername(QString username);
private:
    Ui::WaveClient *ui;
};
#endif // WAVECLIENT_H

#include "waveregister.h"
#include "ui_waveregister.h"
#include<QDebug>
WaveRegister::WaveRegister(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::WaveRegister)
{
    ui->setupUi(this);
}

WaveRegister::~WaveRegister()
{
    delete ui;
}

void WaveRegister::insertUser()
{
    QSqlDatabase db = QSqlDatabase::database("conn");
    QSqlQuery *query = new QSqlQuery(db);
    QString sql = "INSERT INTO userinfo(userName,passWords) VALUES('%1','%2')";
    if(!ui->lineUsername->text().isEmpty()&&!ui->linePwd->text().isEmpty()){
        if(ui->linePwd->text()==ui->lineConfigPwd->text()){
            QString username = ui->lineUsername->text();
            QByteArray qba = QCryptographicHash::hash(ui->linePwd->text().toLatin1(),QCryptographicHash::Md5);
            QString pwd = qba.toHex();
            query->exec(sql.arg(username,pwd));
            QString hostname = QHostInfo::localHostName();
            QHostInfo hostinfo = QHostInfo::fromName(hostname);
            QList<QHostAddress> list = hostinfo.addresses();
            QString localip = list.at(1).toString();
            QString insert = "INSERT INTO logininfo VALUES('%1','%2',0)";
            query->exec(insert.arg(username,localip));
            int choose = QMessageBox::question(this,tr("注册成功"),tr("注册成功，点击确认返回登录窗口"),QMessageBox::Yes);
            if(choose==QMessageBox::Yes){
                this->close();
            }
        }
        else{
            QMessageBox::warning(this,tr("注册失败"),tr("两次密码不一致,请重新输入"),QMessageBox::Ok);
            ui->linePwd->clear();
            ui->lineConfigPwd->clear();
        }

    }
    else
        QMessageBox::warning(this,tr("注册失败"),tr("用户名密码不可为空"),QMessageBox::Ok);
}

bool WaveRegister::userisin()
{
    bool flag = false;
    QSqlDatabase db = QSqlDatabase::database("conn");
    QSqlQuery *query = new QSqlQuery(db);
    QString sql = "select * from userinfo";
    query->exec(sql);
    while(query->next()){
        if(ui->lineUsername->text()==query->value("userName")){
            QMessageBox::warning(this,tr("注册失败"),tr("用户名已被使用"),QMessageBox::Ok);
            ui->lineUsername->clear();
            ui->linePwd->clear();
            ui->lineConfigPwd->clear();
            return flag;
        }
    }
    flag = true;
    return flag;
}

void WaveRegister::on_btnClear_clicked()
{
    ui->lineUsername->clear();
    ui->linePwd->clear();
    ui->lineConfigPwd->clear();
}


void WaveRegister::on_btnRegister_clicked()
{
    if(userisin())
        insertUser();
}


void WaveRegister::on_btnBack_clicked()
{
    emit this->backToLogin();
    this->close();
}


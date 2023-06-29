#include "wavelogin.h"
#include "ui_wavelogin.h"
#include"waveregister.h"
#include"waveclient.h"
WaveLogin::WaveLogin(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::WaveLogin)
{
    ui->setupUi(this);
    WaveRegister *reg = new WaveRegister();
    WaveClient *client = new WaveClient();
    connect(this,&WaveLogin::toRegister,reg,&WaveRegister::show);
    connect(reg,&WaveRegister::backToLogin,this,&WaveLogin::show);
    connect(this,SIGNAL(openClient(QString)),client,SLOT(getusername(QString)));
    connect(this,&WaveLogin::openClient,client,[=](){
        client->show();
        this->close();
    });
}

WaveLogin::~WaveLogin()
{
    delete ui;
}

void WaveLogin::checkLogin()
{
    QSqlDatabase db = QSqlDatabase::database("conn");
    QSqlQuery *query  = new QSqlQuery(db);
    QString sql = "SELECT * FROM userinfo WHERE userName = '%1'";
    bool flag = false;
    if(!ui->lineUsername->text().isEmpty()&&!ui->linePwd->text().isEmpty()){
        query->exec(sql.arg(ui->lineUsername->text()));
        QByteArray qba = QCryptographicHash::hash(ui->linePwd->text().toLatin1(),QCryptographicHash::Md5);
        QString pwd = qba.toHex();
        while(query->next()){
            if(pwd==query->value("passWords")){
                flag = true;
                break;
//                if(choose==1)
//                    return true;
            }
        }
        if(flag){
            loginInfo();
            emit this->openClient(ui->lineUsername->text());
        }
        else
            QMessageBox::warning(this,tr("登录失败"),tr("请检查用户名或密码是否正确"),QMessageBox::Ok);
    }
    else{
        QMessageBox::warning(this,tr("登录失败"),tr("用户名或密码不可为空"),QMessageBox::Ok);
    }
}

void WaveLogin::loginInfo()
{
    QSqlDatabase db = QSqlDatabase::database("conn");
    QSqlQuery *query = new QSqlQuery(db);
    QString sql = "SELECT * FROM logininfo WHERE userName='%1'";
    query->exec(sql.arg(ui->lineUsername->text()));
    if(query->next()){
        QString update = "UPDATE logininfo SET state=1,userIp='%1' WHERE userName = '%2'";
        QString username = ui->lineUsername->text();
        QString hostname = QHostInfo::localHostName();
        QHostInfo hostinfo = QHostInfo::fromName(hostname);
        QList<QHostAddress> addlist = hostinfo.addresses();
        QString localip = addlist.at(1).toString();
        query->exec(update.arg(localip,username));
    }
    else{
        QString hostname = QHostInfo::localHostName();
        QHostInfo hostinfo = QHostInfo::fromName(hostname);
        QList<QHostAddress> addlist = hostinfo.addresses();
        QString localip = addlist.at(1).toString();
        QString insert = "INSERT INTO logininfo VALUES('%1','%2',1)";
        query->exec(insert.arg(ui->lineUsername->text(),localip));
    }
}

void WaveLogin::on_btnRegister_clicked()
{
    emit this->toRegister();
}


void WaveLogin::on_btnLogin_clicked()
{
    checkLogin();
}


#include "waveclient.h"
#include "ui_waveclient.h"
#include<QDebug>
WaveClient::WaveClient(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::WaveClient)
{
    ui->setupUi(this);
}

WaveClient::~WaveClient()
{
    delete ui;
}

void WaveClient::getusername(QString name)
{
    username=name;
}


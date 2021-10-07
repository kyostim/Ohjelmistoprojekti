#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    _qNetworkAccessManager = new QNetworkAccessManager();
    connect(_qNetworkAccessManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(managerFinished(QNetworkReply*)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::managerFinished(QNetworkReply *qNetworkReply)
{
    if(!qNetworkReply->error())
    {
        QString responseContent = qNetworkReply->readAll();
        ui->textEditXMLContent->setText(responseContent);
    }
}


void MainWindow::on_pushButtonGetConfiguration_clicked()
{
    if(_qNetworkAccessManager != nullptr)
    {
        QString ipAddress = ui->lineEditIPAddress->text();
        int port = ui->spinBoxPort->value();

        QString getConfigurationRequest(QString("http://%1:%2/config").arg(ipAddress).arg(port));

        _qNetworkRequest.setUrl(QUrl(getConfigurationRequest));
        _qNetworkAccessManager->get(_qNetworkRequest);
    }


}

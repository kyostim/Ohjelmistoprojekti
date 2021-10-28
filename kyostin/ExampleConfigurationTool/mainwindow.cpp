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
    if(_qNetworkAccessManager != nullptr)
    {
        delete _qNetworkAccessManager;
        _qNetworkAccessManager = nullptr;
    }
    delete ui;
}

void MainWindow::managerFinished(QNetworkReply *qNetworkReply)
{
    if(!qNetworkReply->error())
    {
        if(_getState == 1)
        {
            QString responseContent = qNetworkReply->readAll();
            ui->textEditXMLContent->setText(responseContent);
            QMap<QString, QString> configurationTags = CentriaXMLParser::ParseXMLContent("OCR_CONFIGURATION", responseContent);
            PopulateGrid(configurationTags);
        }
        else if(_getState == 2)
        {
            QByteArray imageData = qNetworkReply->readAll();
            QImage image;
            image.loadFromData(imageData, "JPG");
            ui->labelImage->setPixmap(QPixmap::fromImage(image));
        }
    }
    else
    {
        ui->textEditXMLContent->setText(qNetworkReply->errorString());
    }
    _getState = 0;
}

void MainWindow::on_pushButtonGetConfiguration_clicked()
{
    if(_qNetworkAccessManager != nullptr)
    {
        QString ipAddress = ui->lineEditIPAddress->text();
        int port = ui->spinBoxPort->value();

        QString getConfigurationRequest(QString("http://%1:%2/configuration").arg(ipAddress).arg(port));

        _getState = 1;
        _qNetworkRequest.setUrl(QUrl(getConfigurationRequest));
        _qNetworkAccessManager->get(_qNetworkRequest);
    }
}

void MainWindow::on_pushButtonSetConfiguration_clicked()
{
    if(_qNetworkAccessManager != nullptr)
    {
        QString ipAddress = ui->lineEditIPAddress->text();
        int port = ui->spinBoxPort->value();

        QString putConfigurationRequest(QString("http://%1:%2/configuration?xmlFileContent=").arg(ipAddress).arg(port));
        putConfigurationRequest.append(ui->textEditXMLContent->toPlainText());
        _qNetworkRequest.setUrl(QUrl(putConfigurationRequest));

        QByteArray xmlContent;
        xmlContent.append(ui->textEditXMLContent->toPlainText());
        _qNetworkAccessManager->put(_qNetworkRequest,xmlContent);
    }
}

void MainWindow::PopulateGrid(QMap<QString, QString> &configurationTags)
{
    QList<QString> keys = configurationTags.keys();
    ui->tableWidgetConfigurations->setColumnCount(2);
    ui->tableWidgetConfigurations->setRowCount(keys.size());
    QStringList headers;
    headers.append("Property");
    headers.append("Value");
    ui->tableWidgetConfigurations->setHorizontalHeaderLabels(headers);

    int row = 0;
    foreach(QString key, keys)
    {
        QString value = configurationTags[key];
        QTableWidgetItem* keyItem = new QTableWidgetItem();
        keyItem->setText(key);
        ui->tableWidgetConfigurations->setItem(row, 0, keyItem);

        QTableWidgetItem* valueItem = new QTableWidgetItem();
        valueItem->setText(value);
        ui->tableWidgetConfigurations->setItem(row, 1, valueItem);



        row++;
    }
}

void MainWindow::on_pushButtonGetImage_clicked()
{
    if(_qNetworkAccessManager != nullptr)
    {
        QString ipAddress = ui->lineEditIPAddress->text();
        int port = ui->spinBoxPort->value();

        QString getConfigurationRequest(QString("http://%1:%2/image").arg(ipAddress).arg(port));

        _getState = 2;
        _qNetworkRequest.setUrl(QUrl(getConfigurationRequest));
        _qNetworkAccessManager->get(_qNetworkRequest);
    }
}

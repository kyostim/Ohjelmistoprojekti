#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QImage>

#include "centriaxmlparser.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void managerFinished(QNetworkReply * qNetworkReply);

    void on_pushButtonGetConfiguration_clicked();

    void on_pushButtonSetConfiguration_clicked();

    void on_pushButtonGetImage_clicked();

private:
    Ui::MainWindow *ui;

    int _getState = 0;

    QNetworkAccessManager *_qNetworkAccessManager = nullptr;
    QNetworkRequest _qNetworkRequest;

    void PopulateGrid(QMap<QString, QString> &configurationTags);
};
#endif // MAINWINDOW_H

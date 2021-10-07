#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>


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

private:
    Ui::MainWindow *ui;

    QNetworkAccessManager *_qNetworkAccessManager = nullptr;
    QNetworkRequest _qNetworkRequest;
};
#endif // MAINWINDOW_H

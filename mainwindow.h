#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QNetworkAccessManager> /*не забывать добавлять network в файле проекта*/
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrl>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    QNetworkAccessManager * nam;
    ~MainWindow();

private slots:
    //void on_pushButton_clicked();
    void replyFinished(QNetworkReply* rply); // вручную прописанный слот-обработчик
    
    void on_btnReq_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H

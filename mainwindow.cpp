#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QNetworkAccessManager> /*не забывать добавлять network в файле проекта*/
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrl>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::replyFinished(QNetworkReply *rply)
{

        QString htmlPage(rply->readAll());
   // ui->edtReply->setPlainText(rply->rawHeader());
    ui->edtReply->setPlainText(
                htmlPage
                ); // запись текста в большое поле
    // qDebug() << "*** replyFinished ***";

    QString value = ui->ValueBox->currentText();

    qDebug() << value;
    if (value == "Rubles per Dollar")
    {
        // курс валюты ищем по тегу
        QString search = "<ins class=\"rubl\">руб.</ins>&nbsp;";


        // поиск по тегам indexOf
        int tag_position =
                htmlPage.indexOf(search); //57,0188</td>"

        qDebug() << tag_position;

        // mid() - извлечь подстроку из строки
       QString price =  htmlPage.mid(tag_position + search.length(),5); // выделение подстроки (Mid) с цифрами

        qDebug() << price;


        ui->lbExRatio->setText(price); // вывод строки с цифрами в label
    }
    else if (value == "Rubles per Euro")
    {
        // курс валюты ищем по тегу
        QString search = "<ins>€</ins>";

        // поиск по тегам indexOf
        int tag_position =
                htmlPage.indexOf(search); //57,0188</td>"

        qDebug() << tag_position;

        // mid() - извлечь подстроку из строки
       QString price =  htmlPage.mid(tag_position + search.length() + 118,5); // выделение подстроки (Mid) с цифрами

        qDebug() << price;


        ui->lbExRatio->setText(price); // вывод строки с цифрами в label
    }
    else
    {
        QString answer = "Please, choose the currency";
        ui->edtReply->setPlainText(
                    answer
                    );
    }


}

void MainWindow::on_btnReq_clicked()
{
    /*
    QNetworkAccessManager; // класс для отправки запросов HTTP
            // 1. методы get, post, put для отправки
            // 2. свойства и методы для работы с прокси, куками и кешем
            // 3. сигнал о приходе ответа от сервера

    QNetworkRequest; // - класс инкапсулирующий запрос и автоматизирующий его составление
                        // 1. Хранение всех полей
                        // 2. Заполнение (вручную или автоматически) заголовков

    QNetworkReply; // - класс инкапсулирующий ответ и автоматизирующий его разбор

    QUrl;

    */

   nam =    new QNetworkAccessManager(this);

    connect(nam, SIGNAL(finished(QNetworkReply*)), // сигнал возникает при поступлении ответа сервера
            this, SLOT(replyFinished(QNetworkReply*))); // надо создать

    QUrl url = ui->edtURL->text();

    QNetworkRequest  request(url);

    // request->setHeader(); // - если бы захотели, что-то отправить

    nam->get(request);
}

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QTextStream>
#include <QMessageBox>
#include <cmath>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

float bad_log=0;
float suc_log=0;
float percent_suc_log;
float percent_bad_log;
void MainWindow::on_pushButton_clicked()
{
    QTextStream out(stdout);
    QString login = ui->login->text();
    QString pass= ui->pass->text();

    int key[]={4,1,2,3};
    QString mas_start_pass[3][4];
    QString crypt_pass;
    QString saved_crypt_pass="____";
    QMessageBox auth;
    int b;


    b=0;
    if (login =="Admin" && pass.size() == 12){
        for (int i=0;i<3;i++){
            for (int j=0;j<4;j++){
                mas_start_pass[i][j]=pass[b];
                        b++;
            }
           }

        //b=0;
        for (int j=0;j<4;j++) {
            for (int i=0;i<3;i++){
                crypt_pass+=mas_start_pass[i][key[j]-1];
                //b++;
            }
        }

        if (crypt_pass==saved_crypt_pass) {
            suc_log++;
            percent_suc_log=round(((suc_log/(bad_log+suc_log))*100)*10)/10;
            percent_bad_log=round(((bad_log/(bad_log+suc_log))*100)*10)/10;
            QPixmap pixmap("C:/Users/Egor/Documents/Lightshot/Dostup.png");
            pixmap=pixmap.scaled(850, 900, Qt::KeepAspectRatio, Qt::SmoothTransformation);
            auth.setIconPixmap(pixmap);
            QString status = QString("Успешных входов: %1 \n Неуспешных попыток: %2 \n Процент успешных входов: %3 \n Процент неуспешных попыток: %4").arg(suc_log).arg(bad_log).arg(percent_suc_log).arg(percent_bad_log);
            auth.setText(status);
            auth.exec();

        }
        else{
            QMessageBox::information(this,"Уведомление","Логин или пароль неверен");
            bad_log++;
        }

      }
    else {
        QMessageBox::information(this,"Уведомление","Логин или пароль неверен");
        bad_log++;
    }
}

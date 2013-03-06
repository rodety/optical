#include "configprogram.h"
#include "ui_configprogram.h"
#include <fstream>
#include <QFile>
#include<QMessageBox>
#include<QDir>
#include<QDebug>
using namespace std;

ConfigProgram::ConfigProgram(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ConfigProgram)
{
    ui->setupUi(this);
    //login = NULL;
}

ConfigProgram::~ConfigProgram()
{
    delete ui;
}

void ConfigProgram::setWidgetLogin(QWidget *w)
{
    //login = w;
}

void ConfigProgram::setHostName(QString str)
{
    ui->lineEdit_hostName->setText(str);
}
void ConfigProgram::setDatabase(QString str)
{
    ui->lineEdit_databaseName->setText(str);
}
void ConfigProgram::setName(QString str)
{
    ui->lineEdit_userName->setText(str);
}
void ConfigProgram::setPass(QString str)
{
    ui->lineEdit_password->setText(str);
}

void ConfigProgram::on_pushButton_clicked()
{
    int ret = 0;
    if(ui->lineEdit_hostName->text().size() == 0)
    {
        ret = QMessageBox::warning(this, tr("Warning"), tr("Escriba la dirección IP %1"),
                                                   QMessageBox::Close);

    }
    if(ui->lineEdit_databaseName->text().size() == 0)
        {
            ret = QMessageBox::warning(this, tr("Warning"), tr("Escriba el nombre de la base de datos"),
                                                       QMessageBox::Close);
        }
    if(ui->lineEdit_userName->text().size() == 0)
        {
            ret = QMessageBox::warning(this, tr("Warning"), tr("Escriba el nombre de usuario de la base de datos"),
                                                       QMessageBox::Close);
        }
    if(ui->lineEdit_password->text().size() == 0)
        {
            ret = QMessageBox::warning(this, tr("Warning"), tr("Escriba la contaseña de la base de datos"),
                                                       QMessageBox::Close);
        }
    if(ui->lineEdit_port->text().size() == 0)
        {
            ret = QMessageBox::warning(this, tr("Warning"), tr("Escriba el  numero de puerto de la base de datos"),
                                                       QMessageBox::Close);
        }

    if(ret == 0)
    {
        QFile file("config.ini");
        file.open(QIODevice::WriteOnly|QIODevice::Text);
        QString str=
                ui->lineEdit_hostName->text()+"#"
                +ui->lineEdit_databaseName->text()+"#"
                +ui->lineEdit_userName->text()+"#"
                +ui->lineEdit_password->text()+"#"
                +ui->lineEdit_port->text()+"#";

        file.write(str.toStdString().data());
        file.close();
        this->close();
        QString path = "start OpticalManager.exe";
        system(path.toStdString().c_str());
    }
}

void ConfigProgram::on_pushButton_2_clicked()
{
    this->close();
}

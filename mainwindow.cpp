#include "mainwindow.h"
#include "ui_mainwindow.h"

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

void MainWindow::on_actionProducto_triggered()
{
    ui_producto* form=new ui_producto;
    setCentralWidget(form);
}

void MainWindow::on_actionUsuario_triggered()
{

}

void MainWindow::on_actionCliente_triggered()
{
    ui_cliente* form=new ui_cliente;
    setCentralWidget(form);
}

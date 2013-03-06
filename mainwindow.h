#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <producto/ui_producto.h>
#include <cliente/ui_cliente.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
private slots:
    void on_actionProducto_triggered();
    void on_actionUsuario_triggered();
    void on_actionCliente_triggered();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H

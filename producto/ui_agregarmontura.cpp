#include "ui_agregarmontura.h"
#include "ui_ui_agregarmontura.h"

ui_agregarMontura::ui_agregarMontura(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ui_agregarMontura)
{
    ui->setupUi(this);

    ui->comboBox_marca->setTipo("marca");
    ui->comboBox_marca->ActualizarItems(marca::mostrar());
    ui->comboBox_tamanio->setTipo("tamanio");
    ui->comboBox_tamanio->ActualizarItems(tamanio::mostrar());
    ui->comboBox_forma->setTipo("forma");
    ui->comboBox_forma->ActualizarItems(forma::mostrar());
    ui->comboBox_calidad->setTipo("calidad");
    ui->comboBox_calidad->ActualizarItems(calidad::mostrar());
    ui->comboBox_color->setTipo("color");
    ui->comboBox_color->ActualizarItems(color::mostrar());
    ui->comboBox_estado->setTipo("estado");
    ui->comboBox_estado->ActualizarItems(estado::mostrar());
    modo=0;
}

ui_agregarMontura::~ui_agregarMontura()
{
    delete ui;
}

void ui_agregarMontura::setModo(bool m)
{
    modo=m;
}

void ui_agregarMontura::setMontura(montura* m)
{
    pMontura=*m;
    ui->lineEdit_codigo->setText(pMontura.getCodigo());
    ui->lineEdit_descripcion->setText(pMontura.getDescripcion());
    ui->lineEdit_precioCompra->setText(pMontura.getPrecioCompra());
    ui->lineEdit_precioVenta->setText(pMontura.getPrecioVenta());
    ui->lineEdit_precioDescuento->setText(pMontura.getPrecioDescuento());
    ui->lineEdit_accesorios->setText(pMontura.getAccesorios());
    ui->spinBox_stock->setValue(pMontura.getStock().toInt());
    ui->lineEdit_observaciones->setText(pMontura.getObservaciones());
    ui->comboBox_estado->buscarValor(pMontura.getEstado().getNombre());
    ui->comboBox_marca->buscarValor(pMontura.getMarca().getNombre());
    ui->comboBox_forma->buscarValor(pMontura.getForma().getNombre());
    ui->comboBox_color->buscarValor(pMontura.getColor().getNombre());
    ui->comboBox_tamanio->buscarValor(pMontura.getTamanio().getNombre());
    ui->comboBox_calidad->buscarValor(pMontura.getCalidad().getNombre());
}

bool ui_agregarMontura::verificarRestricciones()
{
    QRegExp noNumeros("[a-zA-Z]");
    QRegExp noAlfabeto("[0-9\.\,\@]");

    QMessageBox box;
    box.setIcon(QMessageBox::Warning);
    box.setWindowTitle("Error de Escritura");

    if(ui->lineEdit_codigo->text().size() == 0)
    {
        box.setText("El Codigo es obligatorio");
        box.exec();
        ui->lineEdit_codigo->setFocus();
        return false;
    }
    if(ui->lineEdit_descripcion->text().size() == 0)
    {
        box.setText("La Descripcion es obligatoria");
        box.exec();
        ui->lineEdit_descripcion->setFocus();
        return false;
    }
    if(ui->lineEdit_precioCompra->text().contains(noNumeros))
    {
        box.setText("El Precio de Compra solo puede contener numeros");
        box.exec();
        ui->lineEdit_precioCompra->setFocus();
        return false;
    }
    if(ui->lineEdit_precioCompra->text().size() == 0)
    {
        box.setText("El Precio de Compra es obligatorio");
        box.exec();
        ui->lineEdit_precioCompra->setFocus();
        return false;
    }
    if(ui->lineEdit_precioVenta->text().contains(noNumeros))
    {
        box.setText("El Precio de Venta solo puede contener numeros");
        box.exec();
        ui->lineEdit_precioVenta->setFocus();
        return false;
    }
    if(ui->lineEdit_precioVenta->text().size() == 0)
    {
        box.setText("El Precio de Venta es obligatorio");
        box.exec();
        ui->lineEdit_precioVenta->setFocus();
        return false;
    }
    if(ui->lineEdit_precioDescuento->text().contains(noNumeros))
    {
        box.setText("El Precio de Descuento solo puede contener numeros");
        box.exec();
        ui->lineEdit_precioDescuento->setFocus();
        return false;
    }
    if(ui->lineEdit_precioDescuento->text().size() == 0)
    {
        box.setText("El Precio de Descuento es obligatorio");
        box.exec();
        ui->lineEdit_precioDescuento->setFocus();
        return false;
    }
    if(!ui->comboBox_marca->selecciono())
    {
        box.setText("Seleccione alguna Marca");
        box.exec();
        ui->comboBox_marca->setFocus();
        return false;
    }
    if(!ui->comboBox_tamanio->selecciono())
    {
        box.setText("Seleccione algun Tamaño");
        box.exec();
        ui->comboBox_tamanio->setFocus();
        return false;
    }
    if(!ui->comboBox_forma->selecciono())
    {
        box.setText("Seleccione alguna Forma");
        box.exec();
        ui->comboBox_forma->setFocus();
        return false;
    }
    if(!ui->comboBox_calidad->selecciono())
    {
        box.setText("Seleccione alguna Calidad");
        box.exec();
        ui->comboBox_calidad->setFocus();
        return false;
    }
    if(!ui->comboBox_color->selecciono())
    {
        box.setText("Seleccione algun Color");
        box.exec();
        ui->comboBox_color->setFocus();
        return false;
    }
    if(!ui->comboBox_estado->selecciono())
    {
        box.setText("Seleccione algun Estado");
        box.exec();
        ui->comboBox_estado->setFocus();
        return false;
    }
    return true;
}

void ui_agregarMontura::on_pushButton_agregar_clicked()
{
    if(!verificarRestricciones())
        return;
    pMontura.setCodigo(ui->lineEdit_codigo->text());
    pMontura.setDescripcion(ui->lineEdit_descripcion->text());
    pMontura.setPrecioCompra(ui->lineEdit_precioCompra->text());
    pMontura.setPrecioVenta(ui->lineEdit_precioVenta->text());
    pMontura.setPrecioDescuento(ui->lineEdit_precioDescuento->text());
    pMontura.setAccesorios(ui->lineEdit_accesorios->text());
    pMontura.setStock(ui->spinBox_stock->text());
    pMontura.setObservaciones(ui->lineEdit_observaciones->text());
    estado pEstado;pEstado.setNombre(ui->comboBox_estado->currentText());pEstado.completar();
    marca pMarca;pMarca.setNombre(ui->comboBox_marca->currentText());pMarca.completar();
    //colaborador
    forma pForma;pForma.setNombre(ui->comboBox_forma->currentText());pForma.completar();
    color pColor;pColor.setNombre(ui->comboBox_color->currentText());pColor.completar();
    tamanio pTamanio;pTamanio.setNombre(ui->comboBox_tamanio->currentText());pTamanio.completar();
    calidad pCalidad;pCalidad.setNombre(ui->comboBox_calidad->currentText());pCalidad.completar();
    pMontura.setEstado(pEstado);
    pMontura.setMarca(pMarca);
    //colaborador
    pMontura.setForma(pForma);
    pMontura.setColor(pColor);
    pMontura.setTamanio(pTamanio);
    pMontura.setCalidad(pCalidad);
    if(modo==0)//agrego
    {
        if(pMontura.agregar())
        {
            this->close();
            emit guardado();
        }
        else
        {
            QMessageBox box;
            box.setIcon(QMessageBox::Critical);
            box.setWindowTitle("Error");
            box.setText("El producto no se pudo agregar!");
            box.setStandardButtons(QMessageBox::Ok);
            box.setDefaultButton(QMessageBox::Ok);
            box.exec();
        }
    }
    else//actualizo
    {
        if(pMontura.actualizar())
        {
            this->close();
            emit guardado();
        }
        else
        {
            QMessageBox box;
            box.setIcon(QMessageBox::Critical);
            box.setWindowTitle("Error");
            box.setText("El producto no se pudo actualizar!");
            box.setStandardButtons(QMessageBox::Ok);
            box.setDefaultButton(QMessageBox::Ok);
            box.exec();
        }
    }
}

void ui_agregarMontura::on_pushButton_xmarca_clicked()
{
    ui->comboBox_marca->eliminar();
}

void ui_agregarMontura::on_pushButton_xtamanio_clicked()
{
    ui->comboBox_tamanio->eliminar();
}

void ui_agregarMontura::on_pushButton_xforma_clicked()
{
    ui->comboBox_forma->eliminar();
}

void ui_agregarMontura::on_pushButton_xcalidad_clicked()
{
    ui->comboBox_calidad->eliminar();
}

void ui_agregarMontura::on_pushButton_xcolor_clicked()
{
    ui->comboBox_color->eliminar();
}

void ui_agregarMontura::on_pushButton_xestado_clicked()
{
    ui->comboBox_estado->eliminar();
}

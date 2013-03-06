#include "ui_agregarluna.h"
#include "ui_ui_agregarluna.h"

ui_agregarLuna::ui_agregarLuna(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ui_agregarLuna)
{
    ui->setupUi(this);

    ui->comboBox_marca->setTipo("marca");
    ui->comboBox_marca->ActualizarItems(marca::mostrar());
    ui->comboBox_diametro->setTipo("diametro");
    ui->comboBox_diametro->ActualizarItems(diametro::mostrar());
    ui->comboBox_calidad->setTipo("calidad");
    ui->comboBox_calidad->ActualizarItems(calidad::mostrar());
    ui->comboBox_tipoLuna->setTipo("tipoLuna");
    ui->comboBox_tipoLuna->ActualizarItems(tipoLuna::mostrar());
    ui->comboBox_tratamiento->setTipo("tratamiento");
    ui->comboBox_tratamiento->ActualizarItems(tratamiento::mostrar());
    ui->comboBox_estado->setTipo("estado");
    ui->comboBox_estado->ActualizarItems(estado::mostrar());
    modo=0;
}

ui_agregarLuna::~ui_agregarLuna()
{
    delete ui;
}

void ui_agregarLuna::setModo(bool m)
{
    modo=m;
}

void ui_agregarLuna::setLuna(luna *l)
{
    pLuna=*l;
    ui->lineEdit_codigo->setText(pLuna.getCodigo());
    ui->lineEdit_descripcion->setText(pLuna.getDescripcion());
    ui->lineEdit_precioCompra->setText(pLuna.getPrecioCompra());
    ui->lineEdit_precioVenta->setText(pLuna.getPrecioVenta());
    ui->lineEdit_precioDescuento->setText(pLuna.getPrecioDescuento());
    ui->lineEdit_accesorios->setText(pLuna.getAccesorios());
    ui->spinBox_stock->setValue(pLuna.getStock().toInt());
    ui->lineEdit_observaciones->setText(pLuna.getObservaciones());
    ui->comboBox_estado->buscarValor(pLuna.getEstado().getNombre());
    ui->comboBox_marca->buscarValor(pLuna.getMarca().getNombre());
    ui->comboBox_diametro->buscarValor(pLuna.getDiametro().getValor());
    ui->comboBox_calidad->buscarValor(pLuna.getCalidad().getNombre());
    ui->comboBox_tipoLuna->buscarValor(pLuna.getTipoLuna().getNombre());
    ui->comboBox_tratamiento->buscarValor(pLuna.getTratamiento().getNombre());
    ui->lineEdit_vInicial->setText(pLuna.getValorInicial());
    ui->lineEdit_vFinal->setText(pLuna.getValorFinal());
    if(pLuna.getLado()=="Derecho")
        ui->comboBox_lado->setCurrentIndex(2);
    else if(pLuna.getLado()=="Izquierdo")
        ui->comboBox_lado->setCurrentIndex(3);
    else
        ui->comboBox_lado->setCurrentIndex(1);
    ui->checkBox_precio->setChecked(pLuna.getPrecio().toInt());
}

bool ui_agregarLuna::verificarRestricciones()
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
    if(!ui->comboBox_estado->selecciono())
    {
        box.setText("Seleccione algun Estado");
        box.exec();
        ui->comboBox_estado->setFocus();
        return false;
    }
    if(!ui->comboBox_diametro->selecciono())
    {
        box.setText("Seleccione algun Diametro");
        box.exec();
        ui->comboBox_diametro->setFocus();
        return false;
    }
    if(!ui->comboBox_calidad->selecciono())
    {
        box.setText("Seleccione alguna Calidad");
        box.exec();
        ui->comboBox_calidad->setFocus();
        return false;
    }
    if(!ui->comboBox_tipoLuna->selecciono())
    {
        box.setText("Seleccione algun Tipo de Luna");
        box.exec();
        ui->comboBox_tipoLuna->setFocus();
        return false;
    }
    if(!ui->comboBox_tratamiento->selecciono())
    {
        box.setText("Seleccione algun tratamiento");
        box.exec();
        ui->comboBox_tratamiento->setFocus();
        return false;
    }
    if(ui->lineEdit_vInicial->text().contains(noNumeros))
    {
        box.setText("El Valor Inicial solo puede contener numeros");
        box.exec();
        ui->lineEdit_vInicial->setFocus();
        return false;
    }
    if(ui->lineEdit_vInicial->text().size() == 0)
    {
        box.setText("El Valor Inicial es obligatorio");
        box.exec();
        ui->lineEdit_vInicial->setFocus();
        return false;
    }
    if(ui->lineEdit_vFinal->text().contains(noNumeros))
    {
        box.setText("El Valor Final solo puede contener numeros");
        box.exec();
        ui->lineEdit_vFinal->setFocus();
        return false;
    }
    if(ui->lineEdit_vFinal->text().size() == 0)
    {
        box.setText("El Valor Final es obligatorio");
        box.exec();
        ui->lineEdit_vFinal->setFocus();
        return false;
    }
    if(ui->comboBox_lado->currentIndex()==0)
    {
        box.setText("Seleccione un Lado");
        box.exec();
        ui->comboBox_lado->setFocus();
        return false;
    }
    return true;
}

void ui_agregarLuna::on_pushButton_aceptar_clicked()
{
    if(!verificarRestricciones())
        return;
    pLuna.setCodigo(ui->lineEdit_codigo->text());
    pLuna.setDescripcion(ui->lineEdit_descripcion->text());
    pLuna.setPrecioCompra(ui->lineEdit_precioCompra->text());
    pLuna.setPrecioVenta(ui->lineEdit_precioVenta->text());
    pLuna.setPrecioDescuento(ui->lineEdit_precioDescuento->text());
    pLuna.setAccesorios(ui->lineEdit_accesorios->text());
    pLuna.setStock(ui->spinBox_stock->text());
    pLuna.setObservaciones(ui->lineEdit_observaciones->text());
    estado pEstado;pEstado.setNombre(ui->comboBox_estado->currentText());pEstado.completar();
    marca pMarca;pMarca.setNombre(ui->comboBox_marca->currentText());pMarca.completar();
    //colaborador
    diametro pDiametro;pDiametro.setValor(ui->comboBox_diametro->currentText());pDiametro.completar();
    calidad pCalidad;pCalidad.setNombre(ui->comboBox_calidad->currentText());pCalidad.completar();
    tipoLuna pTipoLuna;pTipoLuna.setNombre(ui->comboBox_tipoLuna->currentText());pTipoLuna.completar();
    tratamiento pTratamiento;pTratamiento.setNombre(ui->comboBox_tratamiento->currentText());pTratamiento.completar();
    pLuna.setValorInicial(ui->lineEdit_vInicial->text());
    pLuna.setValorFinal(ui->lineEdit_vFinal->text());
    pLuna.setLado(ui->comboBox_lado->currentText());
    if(ui->checkBox_precio->isChecked())
        pLuna.setPrecio("1");
    else
        pLuna.setPrecio("0");
    pLuna.setEstado(pEstado);
    pLuna.setMarca(pMarca);
    //colaborador
    pLuna.setDiametro(pDiametro);
    pLuna.setCalidad(pCalidad);
    pLuna.setTipoLuna(pTipoLuna);
    pLuna.setTratamiento(pTratamiento);
    if(modo==0)//agrego
    {
        if(pLuna.agregar())
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
        if(pLuna.actualizar())
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

void ui_agregarLuna::on_pushButton_xMarca_clicked()
{
    ui->comboBox_marca->eliminar();
}

void ui_agregarLuna::on_pushButton_xDiametro_clicked()
{
    ui->comboBox_diametro->eliminar();
}

void ui_agregarLuna::on_pushButton_xCalidad_clicked()
{
    ui->comboBox_calidad->eliminar();
}

void ui_agregarLuna::on_pushButton_xTipoLuna_clicked()
{
    ui->comboBox_tipoLuna->eliminar();
}

void ui_agregarLuna::on_pushButton_xTratamiento_clicked()
{
    ui->comboBox_tratamiento->eliminar();
}

void ui_agregarLuna::on_pushButton_xEstado_clicked()
{
    ui->comboBox_estado->eliminar();
}

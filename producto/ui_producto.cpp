#include "ui_producto.h"
#include "ui_ui_producto.h"
#include <QPrinter>
#include <QPainter>
#include <QPixmap>

ui_producto::ui_producto(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ui_producto)
{
    ui->setupUi(this);
    ui->tabWidget->setCurrentIndex(0);
    posicion=0;
    cambiarModeloLuna();

    /// #etiquetas/////////
    system("mkdir -p etiquetas");
    system("mkdir -p etiquetas/imagenes");
    act=-1;
    pag=0;
    connect(ui->tableView_productos, SIGNAL (doubleClicked (const QModelIndex & )), this, SLOT (agregar_etiqueta(const QModelIndex & )));
    connect(ui->tableView_etiquetas, SIGNAL(doubleClicked(const QModelIndex & )), this, SLOT(eliminar_etiqueta(const QModelIndex &)));
    reporte=new NCReport();
}


ui_producto::~ui_producto()
{
    delete ui;
}

void ui_producto::cambiarModeloLuna()
{
    ui->tableView_productos->setModel(luna::mostrar());
}
void ui_producto::cambiarModeloMontura()
{
    ui->tableView_productos->setModel(montura::mostrar());
}
void ui_producto::cambiarModeloLenteContacto()
{
    ui->tableView_productos->setModel(lenteContacto::mostrar());
}
void ui_producto::cambiarModeloOtros()
{
    ui->tableView_productos->setModel(otros::mostrar());
}

void ui_producto::on_comboBox_tipoProducto_currentIndexChanged(int index)
{
    posicion=index;
    if(posicion==0)
        cambiarModeloLuna();
    if(posicion==1)
        cambiarModeloMontura();
    if(posicion==2)
        cambiarModeloLenteContacto();
    if(posicion==3)
        cambiarModeloOtros();
}

void ui_producto::on_pushButton_agregar_2_clicked()
{
    if(posicion==0)
    {
        ui_agregarLuna* form=new ui_agregarLuna;
        form->setWindowTitle("Nueva Luna");
        form->show();
        connect(form,SIGNAL(guardado()),this,SLOT(cambiarModeloLuna()));
    }
    if(posicion==1)
    {
        ui_agregarMontura* form=new ui_agregarMontura;
        form->setWindowTitle("Nueva Montura");
        form->show();
        connect(form,SIGNAL(guardado()),this,SLOT(cambiarModeloMontura()));
    }
    if(posicion==2)
    {
        ui_agregarLente* form=new ui_agregarLente;
        form->setWindowTitle("Nuevo Lente de Contacto");
        form->show();
        connect(form,SIGNAL(guardado()),this,SLOT(cambiarModeloLenteContacto()));
    }
    if(posicion==3)
    {
        ui_agregarOtros* form=new ui_agregarOtros;
        form->setWindowTitle("Nuevo Producto");
        form->show();
        connect(form,SIGNAL(guardado()),this,SLOT(cambiarModeloOtros()));
    }
}

void ui_producto::on_pushButton_editar_clicked()
{
    int fila=ui->tableView_productos->currentIndex().row();
    if(fila!=-1)
    {
        if(posicion==0)
        {
            luna productoActual;
            productoActual.setCodigo(ui->tableView_productos->model()->data(ui->tableView_productos->model()->index(fila,0)).toString());
            productoActual.setDescripcion(ui->tableView_productos->model()->data(ui->tableView_productos->model()->index(fila,1)).toString());
            estado pEstado;pEstado.setNombre(ui->tableView_productos->model()->data(ui->tableView_productos->model()->index(fila,2)).toString());pEstado.completar();
            productoActual.setPrecioCompra(ui->tableView_productos->model()->data(ui->tableView_productos->model()->index(fila,3)).toString());
            productoActual.setPrecioVenta(ui->tableView_productos->model()->data(ui->tableView_productos->model()->index(fila,4)).toString());
            productoActual.setPrecioDescuento(ui->tableView_productos->model()->data(ui->tableView_productos->model()->index(fila,5)).toString());
            productoActual.setStock(ui->tableView_productos->model()->data(ui->tableView_productos->model()->index(fila,6)).toString());
            marca pMarca;pMarca.setNombre(ui->tableView_productos->model()->data(ui->tableView_productos->model()->index(fila,7)).toString());pMarca.completar();
            diametro pDiametro;pDiametro.setValor(ui->tableView_productos->model()->data(ui->tableView_productos->model()->index(fila,8)).toString());pDiametro.completar();
            calidad pCalidad;pCalidad.setNombre(ui->tableView_productos->model()->data(ui->tableView_productos->model()->index(fila,9)).toString());pCalidad.completar();
            tipoLuna pTipoLuna;pTipoLuna.setNombre(ui->tableView_productos->model()->data(ui->tableView_productos->model()->index(fila,10)).toString());pTipoLuna.completar();
            tratamiento pTratamiento;pTratamiento.setNombre(ui->tableView_productos->model()->data(ui->tableView_productos->model()->index(fila,11)).toString());pTratamiento.completar();
            productoActual.setValorInicial(ui->tableView_productos->model()->data(ui->tableView_productos->model()->index(fila,12)).toString());
            productoActual.setValorFinal(ui->tableView_productos->model()->data(ui->tableView_productos->model()->index(fila,13)).toString());
            productoActual.setLado(ui->tableView_productos->model()->data(ui->tableView_productos->model()->index(fila,14)).toString());
            productoActual.setPrecio(ui->tableView_productos->model()->data(ui->tableView_productos->model()->index(fila,15)).toString());
            productoActual.setEstado(pEstado);
            productoActual.setMarca(pMarca);
            productoActual.setDiametro(pDiametro);
            productoActual.setCalidad(pCalidad);
            productoActual.setTipoLuna(pTipoLuna);
            productoActual.setTratamiento(pTratamiento);
            productoActual.completar();

            ui_agregarLuna* form=new ui_agregarLuna;
            form->setLuna(&productoActual);
            form->setModo(true);
            form->setWindowTitle("Editar Luna");
            form->show();
            connect(form,SIGNAL(guardado()),this,SLOT(cambiarModeloLuna()));
        }
        if(posicion==1)
        {
            montura productoActual;
            productoActual.setCodigo(ui->tableView_productos->model()->data(ui->tableView_productos->model()->index(fila,0)).toString());
            productoActual.setDescripcion(ui->tableView_productos->model()->data(ui->tableView_productos->model()->index(fila,1)).toString());
            estado pEstado;pEstado.setNombre(ui->tableView_productos->model()->data(ui->tableView_productos->model()->index(fila,2)).toString());pEstado.completar();
            productoActual.setPrecioCompra(ui->tableView_productos->model()->data(ui->tableView_productos->model()->index(fila,3)).toString());
            productoActual.setPrecioVenta(ui->tableView_productos->model()->data(ui->tableView_productos->model()->index(fila,4)).toString());
            productoActual.setPrecioDescuento(ui->tableView_productos->model()->data(ui->tableView_productos->model()->index(fila,5)).toString());
            productoActual.setStock(ui->tableView_productos->model()->data(ui->tableView_productos->model()->index(fila,6)).toString());
            marca pMarca;pMarca.setNombre(ui->tableView_productos->model()->data(ui->tableView_productos->model()->index(fila,7)).toString());pMarca.completar();
            forma pForma;pForma.setNombre(ui->tableView_productos->model()->data(ui->tableView_productos->model()->index(fila,8)).toString());pForma.completar();
            color pColor;pColor.setNombre(ui->tableView_productos->model()->data(ui->tableView_productos->model()->index(fila,9)).toString());pColor.completar();
            tamanio pTamanio;pTamanio.setNombre(ui->tableView_productos->model()->data(ui->tableView_productos->model()->index(fila,10)).toString());pTamanio.completar();
            calidad pCalidad;pCalidad.setNombre(ui->tableView_productos->model()->data(ui->tableView_productos->model()->index(fila,11)).toString());pCalidad.completar();
            productoActual.setEstado(pEstado);
            productoActual.setMarca(pMarca);
            productoActual.setForma(pForma);
            productoActual.setColor(pColor);
            productoActual.setTamanio(pTamanio);
            productoActual.setCalidad(pCalidad);
            productoActual.completar();

            ui_agregarMontura* form=new ui_agregarMontura;
            form->setMontura(&productoActual);
            form->setModo(true);
            form->setWindowTitle("Editar Montura");
            form->show();
            connect(form,SIGNAL(guardado()),this,SLOT(cambiarModeloMontura()));
        }
        if(posicion==2)
        {
            lenteContacto productoActual;
            productoActual.setCodigo(ui->tableView_productos->model()->data(ui->tableView_productos->model()->index(fila,0)).toString());
            productoActual.setDescripcion(ui->tableView_productos->model()->data(ui->tableView_productos->model()->index(fila,1)).toString());
            estado pEstado;pEstado.setNombre(ui->tableView_productos->model()->data(ui->tableView_productos->model()->index(fila,2)).toString());pEstado.completar();
            productoActual.setPrecioCompra(ui->tableView_productos->model()->data(ui->tableView_productos->model()->index(fila,3)).toString());
            productoActual.setPrecioVenta(ui->tableView_productos->model()->data(ui->tableView_productos->model()->index(fila,4)).toString());
            productoActual.setPrecioDescuento(ui->tableView_productos->model()->data(ui->tableView_productos->model()->index(fila,5)).toString());
            productoActual.setStock(ui->tableView_productos->model()->data(ui->tableView_productos->model()->index(fila,6)).toString());
            marca pMarca;pMarca.setNombre(ui->tableView_productos->model()->data(ui->tableView_productos->model()->index(fila,7)).toString());pMarca.completar();
            productoActual.setPresentacion(ui->tableView_productos->model()->data(ui->tableView_productos->model()->index(fila,8)).toString());
            productoActual.setTinteVisibilidad(ui->tableView_productos->model()->data(ui->tableView_productos->model()->index(fila,9)).toString());
            productoActual.setContenidoAcuoso(ui->tableView_productos->model()->data(ui->tableView_productos->model()->index(fila,10)).toString());
            productoActual.setDiseno(ui->tableView_productos->model()->data(ui->tableView_productos->model()->index(fila,11)).toString());
            tipoLente pTipoLente;pTipoLente.setNombre(ui->tableView_productos->model()->data(ui->tableView_productos->model()->index(fila,12)).toString());pTipoLente.completar();
            potencia pPotencia;pPotencia.setNombre(ui->tableView_productos->model()->data(ui->tableView_productos->model()->index(fila,13)).toString());pPotencia.completar();
            curvaBase pCurvaBase;pCurvaBase.setValor(ui->tableView_productos->model()->data(ui->tableView_productos->model()->index(fila,14)).toString());pCurvaBase.completar();
            diametro pDiametro;pDiametro.setValor(ui->tableView_productos->model()->data(ui->tableView_productos->model()->index(fila,15)).toString());pDiametro.completar();
            tiempoUso pTiempoUso;pTiempoUso.setValor(ui->tableView_productos->model()->data(ui->tableView_productos->model()->index(fila,16)).toString());pTiempoUso.completar();
            material pMaterial;pMaterial.setNombre(ui->tableView_productos->model()->data(ui->tableView_productos->model()->index(fila,17)).toString());pMaterial.completar();
            productoActual.setEstado(pEstado);
            productoActual.setMarca(pMarca);
            productoActual.setTipoLente(pTipoLente);
            productoActual.setPotencia(pPotencia);
            productoActual.setCurvaBase(pCurvaBase);
            productoActual.setDiametro(pDiametro);
            productoActual.setTiempoUso(pTiempoUso);
            productoActual.setMaterial(pMaterial);
            productoActual.completar();

            ui_agregarLente* form=new ui_agregarLente;
            form->setLenteContacto(&productoActual);
            form->setModo(true);
            form->setWindowTitle("Editar Lente de Contacto");
            form->show();
            connect(form,SIGNAL(guardado()),this,SLOT(cambiarModeloLenteContacto()));
        }
        if(posicion==3)
        {
            otros productoActual;
            productoActual.setCodigo(ui->tableView_productos->model()->data(ui->tableView_productos->model()->index(fila,0)).toString());
            productoActual.setDescripcion(ui->tableView_productos->model()->data(ui->tableView_productos->model()->index(fila,1)).toString());
            estado pEstado;pEstado.setNombre(ui->tableView_productos->model()->data(ui->tableView_productos->model()->index(fila,2)).toString());pEstado.completar();
            productoActual.setPrecioCompra(ui->tableView_productos->model()->data(ui->tableView_productos->model()->index(fila,3)).toString());
            productoActual.setPrecioVenta(ui->tableView_productos->model()->data(ui->tableView_productos->model()->index(fila,4)).toString());
            productoActual.setPrecioDescuento(ui->tableView_productos->model()->data(ui->tableView_productos->model()->index(fila,5)).toString());
            productoActual.setStock(ui->tableView_productos->model()->data(ui->tableView_productos->model()->index(fila,6)).toString());
            marca pMarca;pMarca.setNombre(ui->tableView_productos->model()->data(ui->tableView_productos->model()->index(fila,7)).toString());pMarca.completar();
            color pColor;pColor.setNombre(ui->tableView_productos->model()->data(ui->tableView_productos->model()->index(fila,8)).toString());pColor.completar();
            talla pTalla;pTalla.setNombre(ui->tableView_productos->model()->data(ui->tableView_productos->model()->index(fila,9)).toString());pTalla.completar();
            calidad pCalidad;pCalidad.setNombre(ui->tableView_productos->model()->data(ui->tableView_productos->model()->index(fila,10)).toString());pCalidad.completar();
            productoActual.setEstado(pEstado);
            productoActual.setMarca(pMarca);
            productoActual.setColor(pColor);
            productoActual.setTalla(pTalla);
            productoActual.setCalidad(pCalidad);
            productoActual.completar();

            ui_agregarOtros* form=new ui_agregarOtros;
            form->setOtros(&productoActual);
            form->setModo(true);
            form->setWindowTitle("Editar Producto");
            form->show();
            connect(form,SIGNAL(guardado()),this,SLOT(cambiarModeloOtros()));
        }
    }
}

void ui_producto::on_pushButton_eliminar_clicked()
{
    int fila=ui->tableView_productos->currentIndex().row();
    if(fila!=-1)
    {
        QMessageBox box;
        box.setIcon(QMessageBox::Question);
        box.setWindowTitle("Advertencia");
        box.setText("Esta seguro de eliminar este producto?");
        box.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
        box.setDefaultButton(QMessageBox::Ok);
        int ret=box.exec();
        switch(ret)
        {
            case QMessageBox::Ok:
            {
                if(posicion==0)
                {
                    luna productoActual;
                    productoActual.setCodigo(ui->tableView_productos->model()->data(ui->tableView_productos->model()->index(fila,0)).toString());
                    productoActual.setDescripcion(ui->tableView_productos->model()->data(ui->tableView_productos->model()->index(fila,1)).toString());
                    estado pEstado;pEstado.setNombre(ui->tableView_productos->model()->data(ui->tableView_productos->model()->index(fila,2)).toString());pEstado.completar();
                    productoActual.setPrecioCompra(ui->tableView_productos->model()->data(ui->tableView_productos->model()->index(fila,3)).toString());
                    productoActual.setPrecioVenta(ui->tableView_productos->model()->data(ui->tableView_productos->model()->index(fila,4)).toString());
                    productoActual.setPrecioDescuento(ui->tableView_productos->model()->data(ui->tableView_productos->model()->index(fila,5)).toString());
                    productoActual.setStock(ui->tableView_productos->model()->data(ui->tableView_productos->model()->index(fila,6)).toString());
                    marca pMarca;pMarca.setNombre(ui->tableView_productos->model()->data(ui->tableView_productos->model()->index(fila,7)).toString());pMarca.completar();
                    diametro pDiametro;pDiametro.setValor(ui->tableView_productos->model()->data(ui->tableView_productos->model()->index(fila,8)).toString());pDiametro.completar();
                    calidad pCalidad;pCalidad.setNombre(ui->tableView_productos->model()->data(ui->tableView_productos->model()->index(fila,9)).toString());pCalidad.completar();
                    tipoLuna pTipoLuna;pTipoLuna.setNombre(ui->tableView_productos->model()->data(ui->tableView_productos->model()->index(fila,10)).toString());pTipoLuna.completar();
                    tratamiento pTratamiento;pTratamiento.setNombre(ui->tableView_productos->model()->data(ui->tableView_productos->model()->index(fila,11)).toString());pTratamiento.completar();
                    productoActual.setValorInicial(ui->tableView_productos->model()->data(ui->tableView_productos->model()->index(fila,12)).toString());
                    productoActual.setValorFinal(ui->tableView_productos->model()->data(ui->tableView_productos->model()->index(fila,13)).toString());
                    productoActual.setLado(ui->tableView_productos->model()->data(ui->tableView_productos->model()->index(fila,14)).toString());
                    productoActual.setPrecio(ui->tableView_productos->model()->data(ui->tableView_productos->model()->index(fila,15)).toString());
                    productoActual.setEstado(pEstado);
                    productoActual.setMarca(pMarca);
                    productoActual.setDiametro(pDiametro);
                    productoActual.setCalidad(pCalidad);
                    productoActual.setTipoLuna(pTipoLuna);
                    productoActual.setTratamiento(pTratamiento);
                    productoActual.completar();

                    productoActual.eliminar();
                    cambiarModeloLuna();
                }
                if(posicion==1)
                {
                    montura productoActual;
                    productoActual.setCodigo(ui->tableView_productos->model()->data(ui->tableView_productos->model()->index(fila,0)).toString());
                    productoActual.setDescripcion(ui->tableView_productos->model()->data(ui->tableView_productos->model()->index(fila,1)).toString());
                    estado pEstado;pEstado.setNombre(ui->tableView_productos->model()->data(ui->tableView_productos->model()->index(fila,2)).toString());pEstado.completar();
                    productoActual.setPrecioCompra(ui->tableView_productos->model()->data(ui->tableView_productos->model()->index(fila,3)).toString());
                    productoActual.setPrecioVenta(ui->tableView_productos->model()->data(ui->tableView_productos->model()->index(fila,4)).toString());
                    productoActual.setPrecioDescuento(ui->tableView_productos->model()->data(ui->tableView_productos->model()->index(fila,5)).toString());
                    productoActual.setStock(ui->tableView_productos->model()->data(ui->tableView_productos->model()->index(fila,6)).toString());
                    marca pMarca;pMarca.setNombre(ui->tableView_productos->model()->data(ui->tableView_productos->model()->index(fila,7)).toString());pMarca.completar();
                    forma pForma;pForma.setNombre(ui->tableView_productos->model()->data(ui->tableView_productos->model()->index(fila,8)).toString());pForma.completar();
                    color pColor;pColor.setNombre(ui->tableView_productos->model()->data(ui->tableView_productos->model()->index(fila,9)).toString());pColor.completar();
                    tamanio pTamanio;pTamanio.setNombre(ui->tableView_productos->model()->data(ui->tableView_productos->model()->index(fila,10)).toString());pTamanio.completar();
                    calidad pCalidad;pCalidad.setNombre(ui->tableView_productos->model()->data(ui->tableView_productos->model()->index(fila,11)).toString());pCalidad.completar();
                    productoActual.setEstado(pEstado);
                    productoActual.setMarca(pMarca);
                    productoActual.setForma(pForma);
                    productoActual.setColor(pColor);
                    productoActual.setTamanio(pTamanio);
                    productoActual.setCalidad(pCalidad);
                    productoActual.completar();

                    productoActual.eliminar();
                    cambiarModeloMontura();
                }
                if(posicion==2)
                {
                    lenteContacto productoActual;
                    productoActual.setCodigo(ui->tableView_productos->model()->data(ui->tableView_productos->model()->index(fila,0)).toString());
                    productoActual.setDescripcion(ui->tableView_productos->model()->data(ui->tableView_productos->model()->index(fila,1)).toString());
                    estado pEstado;pEstado.setNombre(ui->tableView_productos->model()->data(ui->tableView_productos->model()->index(fila,2)).toString());pEstado.completar();
                    productoActual.setPrecioCompra(ui->tableView_productos->model()->data(ui->tableView_productos->model()->index(fila,3)).toString());
                    productoActual.setPrecioVenta(ui->tableView_productos->model()->data(ui->tableView_productos->model()->index(fila,4)).toString());
                    productoActual.setPrecioDescuento(ui->tableView_productos->model()->data(ui->tableView_productos->model()->index(fila,5)).toString());
                    productoActual.setStock(ui->tableView_productos->model()->data(ui->tableView_productos->model()->index(fila,6)).toString());
                    marca pMarca;pMarca.setNombre(ui->tableView_productos->model()->data(ui->tableView_productos->model()->index(fila,7)).toString());pMarca.completar();
                    productoActual.setPresentacion(ui->tableView_productos->model()->data(ui->tableView_productos->model()->index(fila,8)).toString());
                    productoActual.setTinteVisibilidad(ui->tableView_productos->model()->data(ui->tableView_productos->model()->index(fila,9)).toString());
                    productoActual.setContenidoAcuoso(ui->tableView_productos->model()->data(ui->tableView_productos->model()->index(fila,10)).toString());
                    productoActual.setDiseno(ui->tableView_productos->model()->data(ui->tableView_productos->model()->index(fila,11)).toString());
                    tipoLente pTipoLente;pTipoLente.setNombre(ui->tableView_productos->model()->data(ui->tableView_productos->model()->index(fila,12)).toString());pTipoLente.completar();
                    potencia pPotencia;pPotencia.setNombre(ui->tableView_productos->model()->data(ui->tableView_productos->model()->index(fila,13)).toString());pPotencia.completar();
                    curvaBase pCurvaBase;pCurvaBase.setValor(ui->tableView_productos->model()->data(ui->tableView_productos->model()->index(fila,14)).toString());pCurvaBase.completar();
                    diametro pDiametro;pDiametro.setValor(ui->tableView_productos->model()->data(ui->tableView_productos->model()->index(fila,15)).toString());pDiametro.completar();
                    tiempoUso pTiempoUso;pTiempoUso.setValor(ui->tableView_productos->model()->data(ui->tableView_productos->model()->index(fila,16)).toString());pTiempoUso.completar();
                    material pMaterial;pMaterial.setNombre(ui->tableView_productos->model()->data(ui->tableView_productos->model()->index(fila,17)).toString());pMaterial.completar();
                    productoActual.setEstado(pEstado);
                    productoActual.setMarca(pMarca);
                    productoActual.setTipoLente(pTipoLente);
                    productoActual.setPotencia(pPotencia);
                    productoActual.setCurvaBase(pCurvaBase);
                    productoActual.setDiametro(pDiametro);
                    productoActual.setTiempoUso(pTiempoUso);
                    productoActual.setMaterial(pMaterial);
                    productoActual.completar();

                    productoActual.eliminar();
                    cambiarModeloLenteContacto();
                }
                if(posicion==3)
                {
                    otros productoActual;
                    productoActual.setCodigo(ui->tableView_productos->model()->data(ui->tableView_productos->model()->index(fila,0)).toString());
                    productoActual.setDescripcion(ui->tableView_productos->model()->data(ui->tableView_productos->model()->index(fila,1)).toString());
                    estado pEstado;pEstado.setNombre(ui->tableView_productos->model()->data(ui->tableView_productos->model()->index(fila,2)).toString());pEstado.completar();
                    productoActual.setPrecioCompra(ui->tableView_productos->model()->data(ui->tableView_productos->model()->index(fila,3)).toString());
                    productoActual.setPrecioVenta(ui->tableView_productos->model()->data(ui->tableView_productos->model()->index(fila,4)).toString());
                    productoActual.setPrecioDescuento(ui->tableView_productos->model()->data(ui->tableView_productos->model()->index(fila,5)).toString());
                    productoActual.setStock(ui->tableView_productos->model()->data(ui->tableView_productos->model()->index(fila,6)).toString());
                    marca pMarca;pMarca.setNombre(ui->tableView_productos->model()->data(ui->tableView_productos->model()->index(fila,7)).toString());pMarca.completar();
                    color pColor;pColor.setNombre(ui->tableView_productos->model()->data(ui->tableView_productos->model()->index(fila,8)).toString());pColor.completar();
                    talla pTalla;pTalla.setNombre(ui->tableView_productos->model()->data(ui->tableView_productos->model()->index(fila,9)).toString());pTalla.completar();
                    calidad pCalidad;pCalidad.setNombre(ui->tableView_productos->model()->data(ui->tableView_productos->model()->index(fila,10)).toString());pCalidad.completar();
                    productoActual.setEstado(pEstado);
                    productoActual.setMarca(pMarca);
                    productoActual.setColor(pColor);
                    productoActual.setTalla(pTalla);
                    productoActual.setCalidad(pCalidad);
                    productoActual.completar();

                    productoActual.eliminar();
                    cambiarModeloOtros();
                }
            }
            case QMessageBox::Cancel:
                break;
            default:
                break;
        }
    }
}


/// #etiquetas ////////////////////////////////////////

void ui_producto::agregar_etiqueta(const QModelIndex &model)
{
    int fila=model.row();
    if(fila!=-1)
    {
        etiqueta t;
        QString codigo,color,calidad,precio;
        codigo=ui->tableView_productos->model()->data(ui->tableView_productos->model()->index(fila,0)).toString();
        for(int i=0;i<etiquetas.size();i++)
            if(etiquetas[i].getCodigo()==codigo)
            {
                QMessageBox box;
                box.setIcon(QMessageBox::Question);
                box.setWindowTitle("Advertencia");
                box.setText("Ya existe este producto!\nDesea etiquetarlo de igual manera?");
                box.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
                box.setDefaultButton(QMessageBox::Ok);
                int ret=box.exec();
                switch(ret)
                {
                    case QMessageBox::Ok:
                        break;
                    case QMessageBox::Cancel:
                        return;
                    default:
                        break;
                }
                break;
            }
        if(codigo.size()==0)
            return;
        if(posicion==0)
        {
            color=ui->tableView_productos->model()->data(ui->tableView_productos->model()->index(fila,10)).toString();//tipo luna
            calidad=ui->tableView_productos->model()->data(ui->tableView_productos->model()->index(fila,11)).toString();
            precio=ui->tableView_productos->model()->data(ui->tableView_productos->model()->index(fila,3)).toString();
        }
        if(posicion==1)
        {
            color=ui->tableView_productos->model()->data(ui->tableView_productos->model()->index(fila,9)).toString();
            calidad=ui->tableView_productos->model()->data(ui->tableView_productos->model()->index(fila,11)).toString();
            precio=ui->tableView_productos->model()->data(ui->tableView_productos->model()->index(fila,3)).toString();
        }
        if(posicion==2)
        {
            color=ui->tableView_productos->model()->data(ui->tableView_productos->model()->index(fila,9)).toString();//tinte visibilidad
            calidad=ui->tableView_productos->model()->data(ui->tableView_productos->model()->index(fila,7)).toString();//marca
            precio=ui->tableView_productos->model()->data(ui->tableView_productos->model()->index(fila,3)).toString();
        }
        if(posicion==3)
        {
            color=ui->tableView_productos->model()->data(ui->tableView_productos->model()->index(fila,8)).toString();
            calidad=ui->tableView_productos->model()->data(ui->tableView_productos->model()->index(fila,10)).toString();
            precio=ui->tableView_productos->model()->data(ui->tableView_productos->model()->index(fila,3)).toString();
        }
        t.setCodigo(codigo);
        t.setColor(color);
        t.setCalidad(calidad);
        t.setPrecio(precio);
        t.buscarUbicacion();
        etiquetas.append(t);
        ui->tableView_etiquetas->insertRow(ui->tableView_etiquetas->rowCount());
        ui->tableView_etiquetas->setItem(ui->tableView_etiquetas->rowCount()-1,0,new QTableWidgetItem(codigo));
        ui->tableView_etiquetas->setItem(ui->tableView_etiquetas->rowCount()-1,1,new QTableWidgetItem(color));
        ui->tableView_etiquetas->setItem(ui->tableView_etiquetas->rowCount()-1,2,new QTableWidgetItem(calidad));
        ui->tableView_etiquetas->setItem(ui->tableView_etiquetas->rowCount()-1,4,new QTableWidgetItem(precio));
        ui->tableView_etiquetas->setItem(ui->tableView_etiquetas->rowCount()-1,3,new QTableWidgetItem(t.getUbicacion()));
    }
}

void ui_producto::eliminar_etiqueta(const QModelIndex &model)
{
    int fila=model.row();
    ui->tableView_etiquetas->removeRow(fila);
    etiquetas.removeAt(fila);
}

void ui_producto::on_pushButton_previsualizar_clicked()
{
    for(int i=0;i<etiquetas.size();i++)
        etiquetas[i].etiquetar();
    QPixmap pm(ui->draw_label->width()*4,ui->draw_label->height()*4);
    pm.fill(Qt::white);
    QPainter p;
    //QFont font("times",16);
    QFont font("times",12);
    p.begin(&pm);
    p.setFont(font);

    int j=0;
    int k=0;
    pag=0;
    QString num;

    for(int i=0;i<etiquetas.size();i++)
    {
        QImage tmp("etiquetas/imagenes/"+etiquetas[i].getCodigo()+".png");
        //QImage imagen=tmp.scaledToHeight(100);
        QImage imagen=tmp.scaledToHeight(60);
        p.drawImage((200*k)+60,(100*j)+30,imagen);
        p.drawText((200*k)+60,(100*j)+105,etiquetas[i].getColor());
        p.drawText((200*k)+130,(100*j)+105,etiquetas[i].getCalidad());
        p.drawText((200*k)+60,(100*j)+121,etiquetas[i].getUbicacion());
        p.drawText((200*k)+130,(100*j)+121,"S/."+etiquetas[i].getPrecio());

        if(k==5)
        {
            k=-1;
            j++;
        }
        k++;
        if(j==17 || (i+1)==etiquetas.size())
        {
            j=0;
            pm.save("etiquetas/"+num.setNum(pag)+".png");
            pm.fill(Qt::white);
            pag++;
        }
    }

    if(pag!=0)
    {
        ui->lineEdit_pag->setText("1/"+num.setNum(pag));
        this->act=0;
        ui->pushButton_siguiente->setEnabled(1);
        if(this->act==0)
            ui->pushButton_anterior->setDisabled(1);
        if(this->act+1==pag)
            ui->pushButton_siguiente->setDisabled(1);
        QImage act("etiquetas/0.png");
        p.drawImage(0,0,act);
    }
    else
    {
        ui->lineEdit_pag->setText("0/0");
        ui->pushButton_anterior->setDisabled(1);
        ui->pushButton_anterior->setDisabled(1);
        pm.fill(Qt::white);
    }
    ui->draw_label->setPixmap(pm.scaled(ui->draw_label->width(),ui->draw_label->height()));
}

void ui_producto::on_pushButton_imprimir_clicked()
{
    reporte->reset(true);
    QString filename("etiquetas");
    reporte->setReportFile(filename);
    reporte->addParameter("id",QVariant("value"));
}

void ui_producto::on_pushButton_anterior_clicked()
{
    if(pag!=0 && act>0)
    {
        QPixmap pm(ui->draw_label->width()*4,ui->draw_label->height()*4);
        pm.fill(Qt::white);
        QPainter p;
        p.begin(&pm);
        QString num;
        QImage act("etiquetas/"+num.setNum(--this->act)+".png");
        ui->lineEdit_pag->setText(num.setNum(this->act+1)+"/"+num.setNum(pag));
        p.drawImage(0,0,act);
        ui->draw_label->setPixmap(pm.scaled(ui->draw_label->width(),ui->draw_label->height()));

        ui->pushButton_siguiente->setEnabled(1);
        if(this->act==0)
            ui->pushButton_anterior->setDisabled(1);
    }
}

void ui_producto::on_pushButton_siguiente_clicked()
{
    if(pag!=0 && (act+1)<pag)
    {
        QPixmap pm(ui->draw_label->width()*4,ui->draw_label->height()*4);
        pm.fill(Qt::white);
        QPainter p;
        p.begin(&pm);
        QString num;
        QImage act("etiquetas/"+num.setNum(++this->act)+".png");
        ui->lineEdit_pag->setText(num.setNum(this->act+1)+"/"+num.setNum(pag));
        p.drawImage(0,0,act);
        ui->draw_label->setPixmap(pm.scaled(ui->draw_label->width(),ui->draw_label->height()));

        ui->pushButton_anterior->setEnabled(1);
        if(this->act+1==pag)
            ui->pushButton_siguiente->setDisabled(1);
    }
}

void ui_producto::on_tabWidget_currentChanged(int index)
{
    if(index==1)
    {
        ui->lineEdit_buscar->setDisabled(1);
        ui->pushButton_buscar->setDisabled(1);
        ui->pushButton_busquedaAvanzada->setDisabled(1);
    }
    else
    {
        ui->lineEdit_buscar->setEnabled(1);
        ui->pushButton_buscar->setEnabled(1);
        ui->pushButton_busquedaAvanzada->setEnabled(1);
    }
}


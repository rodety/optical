#include "luna.h"

luna::luna()
{
}


diametro luna::getDiametro()
{
    return pDiametro;
}
calidad luna::getCalidad()
{
    return pCalidad;
}
tipoLuna luna::getTipoLuna()
{
    return pTipoLuna;
}
tratamiento luna::getTratamiento()
{
    return pTratamiento;
}
QString luna::getValorInicial()
{
    return valorInicial;
}
QString luna::getValorFinal()
{
    return valorFinal;
}
QString luna::getLado()
{
    return lado;
}
QString luna::getPrecio()
{
    return precio;
}


void luna::setDiametro(diametro tmp)
{
    pDiametro=tmp;
}
void luna::setCalidad(calidad tmp)
{
    pCalidad=tmp;
}
void luna::setTipoLuna(tipoLuna tmp)
{
    pTipoLuna=tmp;
}
void luna::setTratamiento(tratamiento tmp)
{
    pTratamiento=tmp;
}
void luna::setValorInicial(QString tmp)
{
    valorInicial=tmp;
}
void luna::setValorFinal(QString tmp)
{
    valorFinal=tmp;
}
void luna::setLado(QString tmp)
{
    lado=tmp;
}
void luna::setPrecio(QString tmp)
{
    precio=tmp;
}


bool luna::agregar()
{
    QSqlQuery query;
    query.prepare("INSERT INTO Producto(codigo,descripcion,precioCompra,precioVenta,precioDescuento,accesorios,stock,observaciones,Estado_idEstado,Marca_idMarca) VALUES(?,?,?,?,?,?,?,?,?,?)");//falta colaborador
    query.bindValue(0,codigo);
    query.bindValue(1,descripcion);
    query.bindValue(2,precioCompra);
    query.bindValue(3,precioVenta);
    query.bindValue(4,precioDescuento);
    query.bindValue(5,accesorios);
    query.bindValue(6,stock);
    query.bindValue(7,observaciones);
    query.bindValue(8,pEstado.getIdEstado());
    query.bindValue(9,pMarca.getIdMarca());
    if(query.exec())
    {
        query.clear();
        query.prepare("SELECT @@identity AS id;");
        query.exec();
        if(query.size()!=0)
        {
            query.first();
            idProducto=query.value(0).toString();
        }
        query.clear();
        query.prepare("INSERT INTO Luna(Producto_idProducto,Diametro_idDiametro,Calidad_idCalidad,TipoLuna_idTipoLuna,Tratamiento_idTratamiento,valorInicial,valorFinal,lado,precio) VALUES(?,?,?,?,?,?,?,?,?)");
        query.bindValue(0,idProducto);
        query.bindValue(1,pDiametro.getIdDiametro());
        query.bindValue(2,pCalidad.getIdCalidad());
        query.bindValue(3,pTipoLuna.getIdTipoLuna());
        query.bindValue(4,pTratamiento.getIdTratamiento());
        query.bindValue(5,valorInicial);
        query.bindValue(6,valorFinal);
        query.bindValue(7,lado);
        query.bindValue(8,precio);
        if(query.exec())
            return true;
        else
            return false;
    }
    else
        return false;
}

bool luna::actualizar()
{
    QSqlQuery query;
    query.prepare("UPDATE Producto SET codigo=?,descripcion=?,precioCompra=?,precioVenta=?,precioDescuento=?,accesorios=?,stock=?,observaciones=?,Estado_idEstado=?,Marca_idMarca=? WHERE idProducto=?");//falta colaborador
    query.bindValue(0,codigo);
    query.bindValue(1,descripcion);
    query.bindValue(2,precioCompra);
    query.bindValue(3,precioVenta);
    query.bindValue(4,precioDescuento);
    query.bindValue(5,accesorios);
    query.bindValue(6,stock);
    query.bindValue(7,observaciones);
    query.bindValue(8,pEstado.getIdEstado());
    query.bindValue(9,pMarca.getIdMarca());
    query.bindValue(10,idProducto);
    if(query.exec())
    {
        query.clear();
        query.prepare("UPDATE Luna SET Diametro_idDiametro=?,Calidad_idCalidad=?,TipoLuna_idTipoLuna=?,Tratamiento_idTratamiento=?,valorInicial=?,valorFinal=?,lado=?,precio=? WHERE Producto_idProducto=?");
        query.bindValue(0,pDiametro.getIdDiametro());
        query.bindValue(1,pCalidad.getIdCalidad());
        query.bindValue(2,pTipoLuna.getIdTipoLuna());
        query.bindValue(3,pTratamiento.getIdTratamiento());
        query.bindValue(4,valorInicial);
        query.bindValue(5,valorFinal);
        query.bindValue(6,lado);
        query.bindValue(7,precio);
        query.bindValue(8,idProducto);
        if(query.exec())
            return true;
        else
            return false;
    }
    else
        return false;
}

bool luna::eliminar()
{
    QSqlQuery query;
    query.prepare("DELETE FROM Luna WHERE Producto_idProducto=?");
    query.bindValue(0,idProducto);
    if(query.exec())
    {
        query.clear();
        query.prepare("DELETE FROM Producto WHERE idProducto=?");
        query.bindValue(0,idProducto);
        if(query.exec())
            return true;
        else
            return false;
    }
    else
        return false;
}

QSqlQueryModel* luna::mostrar()
{
    QSqlQueryModel* model=new QSqlQueryModel;
    model->setQuery("SELECT codigo,descripcion,e.nombre as 'Estado',precioCompra,precioVenta,precioDescuento,stock,m.nombre as 'Marca',d.valor as 'Diametro',c.nombre as 'Calidad',tl.nombre as 'Tipo de Luna',t.nombre as 'Tratamiento',l.valorInicial,l.valorFinal,l.lado,l.precio FROM Producto p,Estado e,Luna l,Marca m,Diametro d,Calidad c,TipoLuna tl,Tratamiento t WHERE p.Estado_idEstado=e.idEstado AND p.Marca_idMarca=m.idMarca AND p.idProducto=l.Producto_idProducto AND l.Diametro_idDiametro=d.idDiametro AND l.Calidad_idCalidad=c.idCalidad AND l.TipoLuna_idTipoLuna=tl.idTipoLuna AND l.Tratamiento_idTratamiento=t.idTratamiento");
    return model;
}

bool luna::completar()
{
    QSqlQuery query;
    query.prepare("SELECT p.idProducto,p.accesorios,p.observaciones FROM Producto p,Luna l WHERE p.idProducto=l.Producto_idProducto AND p.codigo=? AND p.descripcion=? AND p.precioCompra=? AND p.precioVenta=? AND p.precioDescuento=? AND p.stock=? AND p.Estado_idEstado=? AND p.Marca_idMarca=? AND l.Diametro_idDiametro=? AND l.Calidad_idCalidad=? AND l.TipoLuna_idTipoLuna=? AND l.Tratamiento_idTratamiento=? AND l.valorInicial=? AND l.valorFinal=? AND l.lado=? AND l.precio=?");//falta seleccionar colaborador
    query.bindValue(0,codigo);
    query.bindValue(1,descripcion);
    query.bindValue(2,precioCompra);
    query.bindValue(3,precioVenta);
    query.bindValue(4,precioDescuento);
    query.bindValue(5,stock);
    query.bindValue(6,pEstado.getIdEstado());
    query.bindValue(7,pMarca.getIdMarca());
    query.bindValue(8,pDiametro.getIdDiametro());
    query.bindValue(9,pCalidad.getIdCalidad());
    query.bindValue(10,pTipoLuna.getIdTipoLuna());
    query.bindValue(11,pTratamiento.getIdTratamiento());
    query.bindValue(12,valorInicial);
    query.bindValue(13,valorFinal);
    query.bindValue(14,lado);
    query.bindValue(15,precio);
    if(query.exec())
    {
        if(query.size()!=0)
        {
            query.first();
            idProducto=query.value(0).toString();
            accesorios=query.value(1).toString();
            observaciones=query.value(2).toString();
            return true;
        }
        else
            return false;
    }
    else
        return false;
}

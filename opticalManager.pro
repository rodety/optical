#-------------------------------------------------
#
# Project created by QtCreator 2013-02-16T12:40:56
#
#-------------------------------------------------

QT       += core gui
QT      += sql
QT      += network

TARGET = opticalManager
TEMPLATE = app
DEFINES += NCREPORT_IMPORT
unix {
    LIBS += -lncreport -Llib -L/usr/local/bin
    LIBS += -lzint
    target.path = /usr/local/bin
}
win32-g++: {
    release: LIBS += nc/libncreport2.a
    debug: LIBS += nc/libncreportd2.a
    target.path = bin
} else {
  win32: LIBS += ncreport2.lib
  target.path = bin
}

INCLUDEPATH += include

SOURCES += main.cpp\
        mainwindow.cpp \
    configuracion/ui_login.cpp \
    configuracion/sesion.cpp \
    configuracion/configurador.cpp \
    configuracion/configprogram.cpp \
    configuracion/conexionbd.cpp \
    configuracion/usuario.cpp \
    configuracion/ui_cambiarpassdialog.cpp \
    producto/ui_producto.cpp \
    objetopersistente.cpp \
    producto/producto.cpp \
    producto/montura.cpp \
    producto/estado.cpp \
    producto/marca.cpp \
    producto/forma.cpp \
    producto/color.cpp \
    producto/tamanio.cpp \
    producto/calidad.cpp \
    mycombobox.cpp \
    producto/ui_agregarmontura.cpp \
    producto/luna.cpp \
    producto/diametro.cpp \
    producto/tipoluna.cpp \
    producto/tratamiento.cpp \
    producto/ui_agregarluna.cpp \
    persona/persona.cpp \
    cliente/ui_medidas_historial.cpp \
    cliente/ui_historial_clinico.cpp \
    cliente/ui_cliente_datos.cpp \
    cliente/ui_cliente.cpp \
    cliente/medidashistorial.cpp \
    cliente/historialclinico.cpp \
    cliente/cliente.cpp \
    persona/documento.cpp \
    producto/tipolente.cpp \
    producto/potencia.cpp \
    producto/curvabase.cpp \
    producto/tiempouso.cpp \
    producto/material.cpp \
    producto/lentecontacto.cpp \
    producto/ui_agregarlente.cpp \
    producto/talla.cpp \
    producto/otros.cpp \
    producto/ui_agregarotros.cpp \
    etiqueta.cpp

HEADERS  += mainwindow.h \
    configuracion/ui_login.h \
    configuracion/sesion.h \
    configuracion/configurador.h \
    configuracion/configprogram.h \
    configuracion/conexionbd.h \
    configuracion/usuario.h \
    configuracion/ui_cambiarpassdialog.h \
    producto/ui_producto.h \
    objetopersistente.h \
    producto/producto.h \
    producto/montura.h \
    producto/estado.h \
    producto/marca.h \
    producto/forma.h \
    producto/color.h \
    producto/tamanio.h \
    producto/calidad.h \
    mycombobox.h \
    producto/ui_agregarmontura.h \
    producto/luna.h \
    producto/diametro.h \
    producto/tipoluna.h \
    producto/tratamiento.h \
    producto/ui_agregarluna.h \
    persona/persona.h \
    cliente/ui_medidas_historial.h \
    cliente/ui_historial_clinico.h \
    cliente/ui_cliente_datos.h \
    cliente/ui_cliente.h \
    cliente/medidashistorial.h \
    cliente/historialclinico.h \
    cliente/cliente.h \
    persona/documento.h \
    producto/tipolente.h \
    producto/potencia.h \
    producto/curvabase.h \
    producto/tiempouso.h \
    producto/material.h \
    producto/lentecontacto.h \
    producto/ui_agregarlente.h \
    producto/talla.h \
    producto/otros.h \
    producto/ui_agregarotros.h \
    etiqueta.h

FORMS    += mainwindow.ui \
    configuracion/ui_login.ui \
    configuracion/configprogram.ui \
    configuracion/ui_cambiarpassdialog.ui \
    producto/ui_producto.ui \
    producto/ui_agregarmontura.ui \
    producto/ui_agregarluna.ui \
    cliente/ui_medidas_historial.ui \
    cliente/ui_historial_clinico.ui \
    cliente/ui_cliente_datos.ui \
    cliente/ui_cliente.ui \
    producto/ui_agregarlente.ui \
    producto/ui_agregarotros.ui

RESOURCES += \
    Icons/Icons.qrc

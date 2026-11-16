#include "ProyectoProgramacionArreglado.h"
#include "Inventario.h"
#include "Carrito.h"
#include "HistorialVentas.h"
#include <QDebug>

ProyectoProgramacionArreglado::ProyectoProgramacionArreglado(QWidget* parent)
    : QMainWindow(parent)
{
    ui.setupUI(this);

    // --- PRUEBA RÁPIDA DE CONEXIÓN PARA EL RESPALDO ---
    Inventario inv;
    inv.agregarProducto(Producto(1, "Arroz", 1500.0, 5));

    Carrito carrito;
    Producto* p = &inv.getProductos()[0];
    carrito.agregarItem(*p, 2);

    HistorialVentas historial;
    historial.registrarVenta(1, carrito.getTotal(), "15/11/2026");

    qDebug() << "=== PRUEBA DE RESPALDO EXITOSA ===";
    qDebug() << "Total en carrito:" << carrito.getTotal();
}

ProyectoProgramacionArreglado::~ProyectoProgramacionArreglado() {}

#pragma once

#ifndef HISTORIAL_VENTAS_H
#define HISTORIAL_VENTAS_H

#include <QVector>
#include <QString>
#include <memory>
#include "Transaccion.h"

// Guarda los datos de un producto vendido
struct DetalleProducto {
    QString nombre;
    int cantidad;
    double precioUnitario;
};
// Estructura para registrar los datos de una venta
struct RegistroVenta {
    int idVenta;
    double total;
    QString fecha;
    double efectivoRecibido = 0.0;
    double cambio = 0.0;

    // Productos comprados en esta venta
    QVector<DetalleProducto> productos;
};

class HistorialVentas {

private:
    // Almacena las transacciones completas
    QVector<std::shared_ptr<Transaccion>> registroTransacciones;

    // Almacena los datos básicos de las ventas
    QVector<RegistroVenta> ventas;

public:

    // Registrar una venta con ID, total y fecha
void registrarVenta(int id, double total, QString fecha) {
    ventas.append({ id, total, fecha, 0.0, 0.0, {} });
}

    // Registrar una venta con efectivo recibido y cambio
    void registrarVenta(int id, double total, QString fecha,
        double efectivo, double vuelto)
    {
        ventas.append({ id, total, fecha, efectivo, vuelto });
    }

    // Obtener todas las ventas registradas
    QVector<RegistroVenta> getVentas() const {
        return ventas;
    }

    // Agregar una transacción completa
    void agregarTransaccion(std::shared_ptr<Transaccion> transaccion) {
        registroTransacciones.append(transaccion);
    }

    // Obtener las transacciones registradas
    QVector<std::shared_ptr<Transaccion>> obtenerHistorial() const {
        return registroTransacciones;
    }

    // Obtener la cantidad de ventas
    int obtenerCantidadVentas() const {
        return ventas.size();
    }

    // Limpiar todo el historial
    void limpiarHistorial() {
        registroTransacciones.clear();
        ventas.clear();
    }
    bool buscarVenta(int id, RegistroVenta& resultado) const {
        for (const RegistroVenta& venta : ventas) {
            if (venta.idVenta == id) {
                resultado = venta;
                return true;
            }
        }

        return false;
    }
    void registrarVenta(int id, double total, QString fecha,
        double efectivo, double vuelto,
        const QVector<DetalleProducto>& productos)
    {
        ventas.append({ id, total, fecha, efectivo, vuelto, {} });
    }
};

#endif // HISTORIAL_VENTAS_H

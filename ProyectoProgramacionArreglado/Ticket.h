#pragma once
// Ticket.h
#ifndef TICKET_H
#define TICKET_H

#include "Transaccion.h"
#include <QStringList>

class Ticket : public Transaccion {
private:
    QString cliente;
    QStringList resumenProductos;

public:
    Ticket(int id, double total, const QString& clienteNombre, const QStringList& productos)
        : Transaccion(id, total), cliente(clienteNombre), resumenProductos(productos) {
    }

    // Sobrescribimos el método virtual
    QString obtenerDetalle() const override {
        QString detalle = "==========================\n";
        detalle += "       LA PULPE - TICKET   \n";
        detalle += "==========================\n";
        detalle += "ID Ticket: " + QString::number(idTransaccion) + "\n";
        detalle += "Fecha: " + fechaHora.toString("yyyy-MM-dd hh:mm:ss") + "\n";
        detalle += "Cliente: " + cliente + "\n";
        detalle += "--------------------------\n";
        detalle += "Productos:\n";
        for (const QString& prod : resumenProductos) {
            detalle += " - " + prod + "\n";
        }
        detalle += "--------------------------\n";
        detalle += "TOTAL A PAGAR: ₡" + QString::number(montoTotal, 'f', 2) + "\n";
        detalle += "==========================\n";
        return detalle;
    }
};

#endif // TICKET_H
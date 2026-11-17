#pragma once
// Transaccion.h
#ifndef TRANSACCION_H
#define TRANSACCION_H

#include <QString>
#include <QDateTime>

class Transaccion {
protected:
    int idTransaccion;
    QDateTime fechaHora;
    double montoTotal;

public:
    Transaccion(int id, double total) : idTransaccion(id), montoTotal(total), fechaHora(QDateTime::currentDateTime()) {}
    virtual ~Transaccion() {}

    // Métodos virtuales para polimorfismo
    virtual QString obtenerDetalle() const = 0;

    int getId() const { return idTransaccion; }
    QDateTime getFechaHora() const { return fechaHora; }
    double getMontoTotal() const { return montoTotal; }
};

#endif // TRANSACCION_H
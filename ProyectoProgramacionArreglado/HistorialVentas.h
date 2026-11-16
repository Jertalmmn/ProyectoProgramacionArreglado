#pragma once
#ifndef HISTORIAL_VENTAS_H
#define HISTORIAL_VENTAS_H

#include <QVector>
#include <QString>

struct RegistroVenta {
    int idVenta;
    double total;
    QString fecha;
};

class HistorialVentas {
private:
    QVector<RegistroVenta> ventas;

public:
    void registrarVenta(int id, double total, QString fecha) {
        ventas.append({ id, total, fecha });
    }

    QVector<RegistroVenta> getVentas() const {
        return ventas;
    }
};

#endif // HISTORIAL_VENTAS_H
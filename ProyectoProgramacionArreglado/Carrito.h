#pragma once
#ifndef CARRITO_H
#define CARRITO_H

#include <QVector>
#include <QString>
#include "Producto.h"

struct ItemVenta {
    int idProducto;
    QString nombre;
    double precioUnitario;
    int cantidad;
};

class Carrito {
private:
    QVector<ItemVenta> items;
    double total;

public:
    Carrito() : total(0.0) {}

    void agregarItem(const Producto& p, int cantidad) {
        items.append({ p.getId(), p.getNombre(), p.getPrecio(), cantidad });
        total += p.getPrecio() * cantidad;
    }

    double getTotal() const { return total; }
    QVector<ItemVenta> getItems() const { return items; }

    void limpiar() {
        items.clear();
        total = 0.0;
    }
};

#endif // CARRITO_H
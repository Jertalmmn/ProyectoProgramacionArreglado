#pragma once
#ifndef INVENTARIO_H
#define INVENTARIO_H

#include <QVector>
#include "Producto.h"

class Inventario {
private:
    QVector<Producto> productos;

public:
    void agregarProducto(const Producto& p);
    QVector<Producto>& getProductos();
    Producto* buscarProducto(int id);
};

#endif // INVENTARIO_H
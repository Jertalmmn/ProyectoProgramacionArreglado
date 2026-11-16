#pragma once
#include "Inventario.h"

void Inventario::agregarProducto(const Producto& p) {
    productos.append(p);
}

QVector<Producto>& Inventario::getProductos() {
    return productos;
}

Producto* Inventario::buscarProducto(int id) {
    for (int i = 0; i < productos.size(); ++i) {
        if (productos[i].getId() == id) {
            return &productos[i];
        }
    }
    return nullptr;
}
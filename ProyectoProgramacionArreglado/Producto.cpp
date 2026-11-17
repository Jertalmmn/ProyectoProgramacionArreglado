#include "Producto.h"

Producto::Producto(int id, QString nombre, double precio, int stock)
    : id(id), nombre(nombre), precio(precio), stock(stock) {
}

int Producto::getId() const {
    return id;
}

QString Producto::getNombre() const {
    return nombre;
}

double Producto::getPrecio() const {
    return precio;
}

int Producto::getStock() const {
    return stock;
}

void Producto::reducirStock(int cantidad) {
    if (cantidad <= stock) {
        stock -= cantidad;
    }
    else {
        stock = 0;
    }
}
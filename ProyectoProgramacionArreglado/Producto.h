#ifndef PRODUCTO_H
#define PRODUCTO_H

#include <QString>

class Producto {
private:
    int id;
    QString nombre;
    double precio;
    int stock;

public:
    // Constructor
    Producto(int id, QString nombre, double precio, int stock);

    // Getters
    int getId() const;
    QString getNombre() const;
    double getPrecio() const;
    int getStock() const;

    // Métodos de acción
    void reducirStock(int cantidad);
};

#endif // PRODUCTO_H
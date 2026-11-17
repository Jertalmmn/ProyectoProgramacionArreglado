#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_ProyectoProgramacionArreglado.h"
#include <vector>
#include <utility>
#include "Producto.h"

class ProyectoProgramacionArreglado : public QMainWindow
{
    Q_OBJECT

public:
    ProyectoProgramacionArreglado(QWidget* parent = nullptr);
    ~ProyectoProgramacionArreglado();

private slots:
    void on_pushButton_clicked(); // Conexión automática con el botón "Añadir Producto"
    void on_pushButton_2_clicked();

private:
    Ui::ProyectoProgramacionArregladoClass ui;
    std::vector<Producto> listaInventario; // Vector para almacenar los productos en memoria
    int contadorId = 1; // ID autoincrementable para cada producto nuevo

    double subtotalVenta = 0.0;
    double totalVenta = 0.0;
    std::vector<std::pair<Producto, int>> productosEnVenta;
};
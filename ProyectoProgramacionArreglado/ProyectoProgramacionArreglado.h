#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_ProyectoProgramacionArreglado.h"
#include <vector>
#include "Producto.h"

class ProyectoProgramacionArreglado : public QMainWindow
{
    Q_OBJECT

public:
    ProyectoProgramacionArreglado(QWidget* parent = nullptr);
    ~ProyectoProgramacionArreglado();

private slots:
    void on_pushButton_clicked(); // Conexión automática con el botón "Añadir Producto"

private:
    Ui::ProyectoProgramacionArregladoClass ui;
    std::vector<Producto> listaInventario; // Vector para almacenar los productos en memoria
    int contadorId = 1; // ID autoincrementable para cada producto nuevo
};
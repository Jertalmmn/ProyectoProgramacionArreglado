
#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_ProyectoProgramacionArreglado.h"
#include <vector>
#include <utility>

#include "Producto.h"
#include "HistorialVentas.h"
#include "Ticket.h"

class ProyectoProgramacionArreglado : public QMainWindow
{
    Q_OBJECT

public:
    ProyectoProgramacionArreglado(QWidget* parent = nullptr);
    ~ProyectoProgramacionArreglado();

private slots:
    // Botones del inventario y ventas
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();

    // Botón de historial de ventas
    void on_ConsultarHistorial_clicked();

private:
    // Interfaz gráfica
    Ui::ProyectoProgramacionArregladoClass ui;

    // Inventario
    std::vector<Producto> listaInventario;
    int contadorId = 1;

    // Ventas
    double subtotalVenta = 0.0;
    double totalVenta = 0.0;
    std::vector<std::pair<Producto, int>> productosEnVenta;

    // Historial de ventas y tickets (David)
    HistorialVentas historialGeneral;
    int contadorTickets = 1;
};

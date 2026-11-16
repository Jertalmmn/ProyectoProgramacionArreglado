#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_ProyectoProgramacionArreglado.h"

class ProyectoProgramacionArreglado : public QMainWindow
{
    Q_OBJECT

public:
    ProyectoProgramacionArreglado(QWidget *parent = nullptr);
    ~ProyectoProgramacionArreglado();

private:
    Ui::ProyectoProgramacionArregladoClass ui;
};


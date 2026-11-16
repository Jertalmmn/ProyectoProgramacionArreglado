#include "ProyectoProgramacionArreglado.h"
#include <QMessageBox>

ProyectoProgramacionArreglado::ProyectoProgramacionArreglado(QWidget* parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
}

ProyectoProgramacionArreglado::~ProyectoProgramacionArreglado() {}

void ProyectoProgramacionArreglado::on_pushButton_clicked()
{
    // 1. Obtener los textos de los QLineEdit usando los nombres exactos de tu UI
    QString nombre = ui.lnNombre->text().trimmed();
    QString precioStr = ui.lnPrecio->text().trimmed();
    QString stockStr = ui.lnStock->text().trimmed();

    // 2. Validar que no estén vacíos
    if (nombre.isEmpty() || precioStr.isEmpty() || stockStr.isEmpty()) {
        QMessageBox::warning(this, "Campos Vacíos", "Por favor, completa todos los campos (Nombre, Precio y Stock).");
        return;
    }

    // 3. Validar conversión numérica segura
    bool okPrecio, okStock;
    double precio = precioStr.toDouble(&okPrecio);
    int stock = stockStr.toInt(&okStock);

    if (!okPrecio || precio < 0 || !okStock || stock < 0) {
        QMessageBox::warning(this, "Datos Inválidos", "El precio y el stock deben ser números válidos mayores o iguales a 0.");
        return;
    }

    // 4. Crear el objeto Producto utilizando tu constructor (con ID automático)
    Producto nuevoProducto(contadorId, nombre, precio, stock);
    listaInventario.push_back(nuevoProducto);
    contadorId++; // Incrementamos el ID para el siguiente producto

    // 5. Mostrar el producto visualmente en el listWidget_2 de tu pestaña
    QString itemText = QString("ID: %1 | Producto: %2 | Precio: ₡%3 | Stock: %4")
        .arg(nuevoProducto.getId())
        .arg(nuevoProducto.getNombre())
        .arg(nuevoProducto.getPrecio())
        .arg(nuevoProducto.getStock());

    ui.listWidget_2->addItem(itemText);

    // 6. Mensaje de éxito y limpieza de los inputs para el siguiente registro
    QMessageBox::information(this, "Éxito", "¡Producto añadido al inventario correctamente!");

    ui.lnNombre->clear();
    ui.lnPrecio->clear();
    ui.lnStock->clear();
    ui.lnNombre->setFocus();
}
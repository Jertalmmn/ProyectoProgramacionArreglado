#include "ProyectoProgramacionArreglado.h"
#include <QMessageBox>
#include <QInputDialog>

ProyectoProgramacionArreglado::ProyectoProgramacionArreglado(QWidget* parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

    ui.lineEdit->setPlaceholderText("ingrese el id o nombre del producto");
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

void ProyectoProgramacionArreglado::on_pushButton_2_clicked()
{
    QString textoIngresado = ui.lineEdit->text().trimmed();

    if (textoIngresado.isEmpty()) {
        if (productosEnVenta.empty()) {
            QMessageBox::warning(this, "Venta Vacía", "Escribe el ID o nombre de un producto, o procesa una venta con elementos.");
            return;
        }

        
        bool okPago = false;
        double dineroEntregado = QInputDialog::getDouble(
            this,
            "Cobrar",
            QString("Total a pagar: ₡%1\nIngrese con cuánto dinero paga el cliente:").arg(totalVenta),
            totalVenta, 
            totalVenta, 
            1000000.0,  
            2,          
            &okPago
        );

        if (!okPago) {
            return; 
        }

        double cambio = dineroEntregado - totalVenta;

        
        for (auto& itemVenta : productosEnVenta) {
            Producto& prodVenta = itemVenta.first;
            int cantidadComprada = itemVenta.second;

            for (auto& prodInventario : listaInventario) {
                if (prodInventario.getId() == prodVenta.getId()) {
                    prodInventario.reducirStock(cantidadComprada);
                }
            }
        }

        
        QMessageBox::information(
            this,
            "Pago Exitoso",
            QString("¡Venta procesada con éxito!\n\nDinero recibido: ₡%1\nCambio a devolver: ₡%2\n\nStock actualizado en inventario.")
            .arg(dineroEntregado, 0, 'f', 2)
            .arg(cambio, 0, 'f', 2)
        );

        
        ui.listWidget->clear();
        productosEnVenta.clear();
        subtotalVenta = 0.0;
        totalVenta = 0.0;
        ui.label->setText("Subtotal: ₡0.00");
        ui.label_2->setText("Total: ₡0.00");
        ui.lineEdit->clear();
        ui.lineEdit->setFocus();
        return;
    }

    bool esNumero = false;
    int idBuscado = textoIngresado.toInt(&esNumero);

    bool encontrado = false;
    for (auto& prod : listaInventario) {
        bool coincide = false;

        if (esNumero) {
            coincide = (prod.getId() == idBuscado);
        }
        else {
            coincide = (prod.getNombre().compare(textoIngresado, Qt::CaseInsensitive) == 0);
        }

        if (coincide) {
            if (prod.getStock() > 0) {
                bool ok = false;
                int cantidadDeseada = QInputDialog::getInt(
                    this,
                    "Cantidad de producto",
                    QString("¿Cuántas unidades de '%1' desea llevar?\n(Disponibles en stock: %2)")
                    .arg(prod.getNombre())
                    .arg(prod.getStock()),
                    1, 1, prod.getStock(), 1, &ok
                );

                if (!ok) {
                    return;
                }

                productosEnVenta.push_back(std::make_pair(prod, cantidadDeseada));

                double subtotalItem = prod.getPrecio() * cantidadDeseada;
                subtotalVenta += subtotalItem;
                totalVenta = subtotalVenta;

                QString itemStr = QString("ID: %1 | %2 (x%3) - ₡%4")
                    .arg(prod.getId())
                    .arg(prod.getNombre())
                    .arg(cantidadDeseada)
                    .arg(subtotalItem);

                ui.listWidget->addItem(itemStr);

                ui.label->setText("Subtotal: ₡" + QString::number(subtotalVenta, 'f', 2));
                ui.label_2->setText("Total: ₡" + QString::number(totalVenta, 'f', 2));

                encontrado = true;
                ui.lineEdit->clear();
                ui.lineEdit->setFocus();
                break;
            }
            else {
                QMessageBox::warning(this, "Sin Stock", "Lo sentimos, este producto se encuentra agotado.");
                return;
            }
        }
    }

    if (!encontrado) {
        QMessageBox::warning(this, "No encontrado", "No se encontró ningún producto con ese ID o nombre.");
    }
}
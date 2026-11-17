
#include "ProyectoProgramacionArreglado.h"

#include <QMessageBox>
#include <QInputDialog>
#include <QDateTime>

// ==========================================
// CONSTRUCTOR Y DESTRUCTOR
// ==========================================

ProyectoProgramacionArreglado::ProyectoProgramacionArreglado(QWidget* parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

    ui.lineEdit->setPlaceholderText(
        "ingrese el id o nombre del producto"
    );
}

ProyectoProgramacionArreglado::~ProyectoProgramacionArreglado()
{
}


// ==========================================
// INVENTARIO - AÑADIR PRODUCTOS
// ==========================================

void ProyectoProgramacionArreglado::on_pushButton_clicked()
{
    // 1. Obtener los datos ingresados
    QString nombre = ui.lnNombre->text().trimmed();
    QString precioStr = ui.lnPrecio->text().trimmed();
    QString stockStr = ui.lnStock->text().trimmed();

    // 2. Validar campos vacíos
    if (nombre.isEmpty() || precioStr.isEmpty() || stockStr.isEmpty()) {

        QMessageBox::warning(
            this,
            "Campos Vacíos",
            "Por favor, completa todos los campos (Nombre, Precio y Stock)."
        );

        return;
    }

    // 3. Validar datos numéricos
    bool okPrecio = false;
    bool okStock = false;

    double precio = precioStr.toDouble(&okPrecio);
    int stock = stockStr.toInt(&okStock);

    if (!okPrecio || precio < 0 || !okStock || stock < 0) {

        QMessageBox::warning(
            this,
            "Datos Inválidos",
            "El precio y el stock deben ser números válidos mayores o iguales a 0."
        );

        return;
    }

    // 4. Crear el producto
    Producto nuevoProducto(contadorId, nombre, precio, stock);

    listaInventario.push_back(nuevoProducto);

    contadorId++;

    // 5. Mostrar el producto en el inventario
    QString itemText = QString(
        "ID: %1 | Producto: %2 | Precio: ₡%3 | Stock: %4"
    )
        .arg(nuevoProducto.getId())
        .arg(nuevoProducto.getNombre())
        .arg(nuevoProducto.getPrecio())
        .arg(nuevoProducto.getStock());

    ui.listWidget_2->addItem(itemText);

    // 6. Confirmar y limpiar campos
    QMessageBox::information(
        this,
        "Éxito",
        "¡Producto añadido al inventario correctamente!"
    );

    ui.lnNombre->clear();
    ui.lnPrecio->clear();
    ui.lnStock->clear();

    ui.lnNombre->setFocus();
}


// ==========================================
// VENTAS - AGREGAR PRODUCTOS Y COBRAR
// ==========================================

void ProyectoProgramacionArreglado::on_pushButton_2_clicked()
{
    QString textoIngresado = ui.lineEdit->text().trimmed();

    // ======================================
    // PROCESAR EL COBRO
    // ======================================

    if (textoIngresado.isEmpty()) {

        // 1. Comprobar si existen productos en venta
        if (productosEnVenta.empty()) {

            QMessageBox::warning(
                this,
                "Venta Vacía",
                "Escribe el ID o nombre de un producto, o procesa una venta con elementos."
            );

            return;
        }

        // 2. Solicitar el dinero entregado
        bool okPago = false;

        double dineroEntregado = QInputDialog::getDouble(
            this,
            "Cobrar",
            QString(
                "Total a pagar: ₡%1\nIngrese con cuánto dinero paga el cliente:"
            ).arg(totalVenta, 0, 'f', 2),
            totalVenta,
            totalVenta,
            1000000.0,
            2,
            &okPago
        );

        if (!okPago) {
            return;
        }

        // 3. Calcular el cambio
        double cambio = dineroEntregado - totalVenta;

        // 4. Actualizar el stock del inventario
        for (auto& itemVenta : productosEnVenta) {

            Producto& prodVenta = itemVenta.first;
            int cantidadComprada = itemVenta.second;

            for (auto& prodInventario : listaInventario) {

                if (prodInventario.getId() == prodVenta.getId()) {

                    prodInventario.reducirStock(cantidadComprada);
                    break;
                }
            }
        }

        // ======================================
        // HISTORIAL DE VENTAS - DAVID
        // ======================================

        // 5. Obtener la fecha y hora de la venta
        QString fechaActual = QDateTime::currentDateTime()
            .toString("dd/MM/yyyy hh:mm:ss");

        // 6. Registrar la venta en el historial
        historialGeneral.registrarVenta(
            contadorTickets,
            totalVenta,
            fechaActual
        );

        // 7. Incrementar el ID del siguiente ticket
        contadorTickets++;

        // ======================================
        // CONFIRMAR LA VENTA
        // ======================================

        QMessageBox::information(
            this,
            "Pago Exitoso",
            QString(
                "¡Venta procesada con éxito!\n\n"
                "Dinero recibido: ₡%1\n"
                "Cambio a devolver: ₡%2\n\n"
                "Stock actualizado en inventario."
            )
            .arg(dineroEntregado, 0, 'f', 2)
            .arg(cambio, 0, 'f', 2)
        );

        // 8. Limpiar los datos de la venta
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

    // ======================================
    // BUSCAR PRODUCTO PARA AGREGAR A VENTA
    // ======================================

    bool esNumero = false;

    int idBuscado = textoIngresado.toInt(&esNumero);

    bool encontrado = false;

    for (auto& prod : listaInventario) {

        bool coincide = false;

        // Buscar por ID o nombre
        if (esNumero) {
            coincide = (prod.getId() == idBuscado);
        }
        else {
            coincide = (
                prod.getNombre().compare(
                    textoIngresado,
                    Qt::CaseInsensitive
                ) == 0
                );
        }

        if (coincide) {

            // Verificar disponibilidad
            if (prod.getStock() > 0) {

                bool ok = false;

                int cantidadDeseada = QInputDialog::getInt(
                    this,
                    "Cantidad de producto",
                    QString(
                        "¿Cuántas unidades de '%1' desea llevar?\n"
                        "(Disponibles en stock: %2)"
                    )
                    .arg(prod.getNombre())
                    .arg(prod.getStock()),
                    1,
                    1,
                    prod.getStock(),
                    1,
                    &ok
                );

                if (!ok) {
                    return;
                }

                // Agregar el producto a la venta
                productosEnVenta.push_back(
                    std::make_pair(prod, cantidadDeseada)
                );

                // Calcular subtotal
                double subtotalItem =
                    prod.getPrecio() * cantidadDeseada;

                subtotalVenta += subtotalItem;
                totalVenta = subtotalVenta;

                // Mostrar el producto en el carrito
                QString itemStr = QString(
                    "ID: %1 | %2 (x%3) - ₡%4"
                )
                    .arg(prod.getId())
                    .arg(prod.getNombre())
                    .arg(cantidadDeseada)
                    .arg(subtotalItem, 0, 'f', 2);

                ui.listWidget->addItem(itemStr);

                // Actualizar los totales visuales
                ui.label->setText(
                    "Subtotal: ₡" +
                    QString::number(subtotalVenta, 'f', 2)
                );

                ui.label_2->setText(
                    "Total: ₡" +
                    QString::number(totalVenta, 'f', 2)
                );

                encontrado = true;

                ui.lineEdit->clear();
                ui.lineEdit->setFocus();

                break;
            }
            else {

                QMessageBox::warning(
                    this,
                    "Sin Stock",
                    "Lo sentimos, este producto se encuentra agotado."
                );

                return;
            }
        }
    }

    // Mostrar advertencia si no existe el producto
    if (!encontrado) {

        QMessageBox::warning(
            this,
            "No encontrado",
            "No se encontró ningún producto con ese ID o nombre."
        );
    }
}


// ==========================================
// HISTORIAL DE VENTAS - DAVID
// BOTÓN CONSULTAR HISTORIAL
// ==========================================


void ProyectoProgramacionArreglado::on_ConsultarHistorial_clicked()
{
    // 1. Limpiar el cuadro de texto
    ui.Factura->clear();

    // 2. Obtener las ventas registradas
    QVector<RegistroVenta> ventas = historialGeneral.getVentas();

    // 3. Verificar si existen ventas
    if (ventas.isEmpty()) {
        ui.Factura->setPlainText(
            "No hay ventas registradas en el historial."
        );
        return;
    }

    // 4. Preparar el encabezado del historial
    QString textoHistorial =
        "             SUPER LA CARACUCHA\n"
        "========================================\n\n";

    double totalRecaudado = 0.0;

    // 5. Recorrer las ventas registradas
    for (const RegistroVenta& venta : ventas) {

        textoHistorial += QString(
            "Venta #%1\n"
        ).arg(venta.idVenta);

        textoHistorial += QString(
            "Fecha: %1\n"
        ).arg(venta.fecha);

        textoHistorial +=
            "----------------------------------------\n";

        textoHistorial += QString(
            "TOTAL DE COMPRA: ₡%1\n"
        ).arg(venta.total, 0, 'f', 2);

        textoHistorial += QString(
            "Efectivo recibido: ₡%1\n"
        ).arg(venta.efectivoRecibido, 0, 'f', 2);

        textoHistorial += QString(
            "CAMBIO ENTREGADO: ₡%1\n"
        ).arg(venta.cambio, 0, 'f', 2);

        textoHistorial +=
            "========================================\n"
            "        ¡GRACIAS POR SU COMPRA!\n\n";

        totalRecaudado += venta.total;
    }

    // 7. Mostrar todo el historial en Factura
    ui.Factura->setPlainText(textoHistorial);
}

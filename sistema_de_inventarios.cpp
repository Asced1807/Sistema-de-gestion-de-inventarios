// Elvin Coronado Reyes (Asce)
#include <iostream>
#include <string>
#include <limits> // Para limpiar el buffer de entrada

class Producto {
public:
    std::string codigo;
    std::string nombre;
    std::string descripcion;
    int cantidad;
};

const int MAX_PRODUCTOS = 100;
Producto inventario[MAX_PRODUCTOS];
int totalProductos = 0;

void limpiarBuffer() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}


// Función para agregar un producto al inventario
void agregarProducto(std::string &codigo, const std::string &nombre, const std::string &descripcion, int cantidad) {
    // Verificar si el código ya existe en el inventario
    for (int i = 0; i < totalProductos; i++) {
        if (inventario[i].codigo == codigo) {
            std::cout << "Ya existe un producto con el mismo codigo en el inventario." << std::endl;
            return;
        }
    }

    // Agregar el producto si no existe el código repetido
    if (totalProductos < MAX_PRODUCTOS) {
        inventario[totalProductos].codigo = codigo;
        inventario[totalProductos].nombre = nombre;
        inventario[totalProductos].descripcion = descripcion;
        inventario[totalProductos].cantidad = cantidad;
        totalProductos++;
        std::cout << "Producto agregado al inventario." << std::endl;
    } else {
        std::cout << "El inventario esta lleno, no se pueden agregar mas productos." << std::endl;
    }
}


// Función para vender un producto
void venderProducto() {
    std::string codigoVender;
    std::cout << "Ingrese el codigo del producto a vender: ";
    std::getline(std::cin, codigoVender);

    // Buscar el producto en el inventario
    int indiceProducto = -1;
    for (int i = 0; i < totalProductos; i++) {
        if (inventario[i].codigo == codigoVender) {
            indiceProducto = i;
            break;
        }
    }

    if (indiceProducto != -1) {
        std::cout << "Producto encontrado en el inventario." << std::endl;
        
        int cantidadVender;
        std::cout << "Ingrese la cantidad a vender: ";
        std::cin >> cantidadVender;
        limpiarBuffer();

        // Verificar si hay suficiente stock
        if (inventario[indiceProducto].cantidad >= cantidadVender) {
            // Realizar la venta y actualizar el inventario
            inventario[indiceProducto].cantidad -= cantidadVender;
            std::cout << "Venta realizada con exito. Stock actualizado: " << inventario[indiceProducto].cantidad << " unidades quedan de ese producto." << std::endl;
        } else {
            std::cout << "No hay suficiente stock para realizar la venta." << std::endl;
        }
    } else {
        std::cout << "Producto no encontrado en el inventario." << std::endl;
    }
}

void verInventario() {
    std::cout << "\nInventario:" << std::endl;
    std::cout << "---------------------------------------------" << std::endl;
    std::cout << "Codigo\t| Nombre\t| Descripcion\t| Cantidad" << std::endl;
    std::cout << "---------------------------------------------" << std::endl;

    for (int i = 0; i < totalProductos; i++) {
        std::cout << inventario[i].codigo << "\t| " << inventario[i].nombre << "\t| " << inventario[i].descripcion << "\t| " << inventario[i].cantidad << std::endl;
    }

    std::cout << "---------------------------------------------" << std::endl;
}

// Función para actualizar un producto en el inventario
void actualizarProducto(std::string codigo, int nuevaCantidad) {
    for (int i = 0; i < totalProductos; i++) {
        if (inventario[i].codigo == codigo) {
            inventario[i].cantidad += nuevaCantidad; // Sumar la nueva cantidad a la existente
            std::cout << "Producto actualizado en el inventario. Nueva cantidad: " << inventario[i].cantidad << " unidades." << std::endl;
            return;
        }
    }
    std::cout << "Producto no encontrado en el inventario." << std::endl;
}


// Función para eliminar un producto del inventario
void eliminarProducto(std::string codigo) {
    for (int i = 0; i < totalProductos; i++) {
        if (inventario[i].codigo == codigo) {
            // Mover los productos siguientes hacia atrás para llenar el espacio vacío
            for (int j = i; j < totalProductos - 1; j++) {
                inventario[j] = inventario[j + 1];
            }
            totalProductos--;
            std::cout << "Producto eliminado del inventario." << std::endl;
            return;
        }
    }
    std::cout << "Producto no encontrado en el inventario." << std::endl;
}


// Función para buscar y mostrar información de un producto por código o nombre
void consultarProducto() {
    int opcion;
    std::cout << "Seleccione una opcion de busqueda:" << std::endl;
    std::cout << "1. Buscar por codigo" << std::endl;
    std::cout << "2. Buscar por nombre" << std::endl;
    std::cin >> opcion;
    limpiarBuffer(); // Limpiar el buffer después de capturar la opción

    if (opcion == 1) {
        std::string codigoBusqueda;
        std::cout << "Ingrese el codigo del producto: ";
        std::getline(std::cin, codigoBusqueda);

        for (int i = 0; i < totalProductos; i++) {
            if (inventario[i].codigo == codigoBusqueda) {
                std::cout << "\nInformacion del producto:" << std::endl;
                std::cout << "\nCodigo: " << inventario[i].codigo << std::endl;
                std::cout << "Nombre: " << inventario[i].nombre << std::endl;
                std::cout << "Descripcion: " << inventario[i].descripcion << std::endl;
                std::cout << "Cantidad disponible en inventario: " << inventario[i].cantidad << " unidades" << std::endl;
                return;
            }
        }
        std::cout << "Producto no encontrado en el inventario." << std::endl;
    } else if (opcion == 2) {
        std::string nombreBusqueda;
        std::cout << "Ingrese el nombre del producto: ";
        std::getline(std::cin, nombreBusqueda);

        for (int i = 0; i < totalProductos; i++) {
            if (inventario[i].nombre == nombreBusqueda) {
                std::cout << "\nInformacion del producto:" << std::endl;
                std::cout << "\nCodigo: " << inventario[i].codigo << std::endl;
                std::cout << "Nombre: " << inventario[i].nombre << std::endl;
                std::cout << "Descripcion: " << inventario[i].descripcion << std::endl;
                std::cout << "Cantidad disponible en inventario: " << inventario[i].cantidad << " unidades" << std::endl;
                return;
            }
        }
        std::cout << "Producto no encontrado en el inventario." << std::endl;
    } else {
        std::cout << "Opcion no valida." << std::endl;
    }
}

// Función para mostrar el menú y procesar la opción seleccionada
void mostrarMenu() {
    int opcion;
    while (true) {
        std::cout << "\nBienvenidos a sistemas de inventarios ElvinDEV" << std::endl;
        std::cout << "\n1. Agregar Producto" << std::endl;
        std::cout << "2. Vender Producto" << std::endl;
        std::cout << "3. Ver Inventario" << std::endl;
        std::cout << "4. Consultar Producto" << std::endl;
        std::cout << "5. Actualizar Producto" << std::endl;
        std::cout << "6. Eliminar Producto" << std::endl;
        std::cout << "7. Salir" << std::endl;

        std::cout << "\nSeleccione una opcion: ";
        std::cin >> opcion;
        limpiarBuffer();

        switch (opcion) {
            case 1: {
                // Agregar Producto
                int cantidadAgregar;
                std::string codigoAgregar, nombreAgregar, descripcionAgregar;

                std::cout << "\nIngrese el codigo del producto: ";
                std::getline(std::cin, codigoAgregar);
                std::cout << "Ingrese el nombre del producto: ";
                std::getline(std::cin, nombreAgregar);
                std::cout << "Ingrese la descripcion del producto: ";
                std::getline(std::cin, descripcionAgregar);
                std::cout << "Ingrese la cantidad a agregar: ";
                std::cin >> cantidadAgregar;
                limpiarBuffer();

                agregarProducto(codigoAgregar, nombreAgregar, descripcionAgregar, cantidadAgregar);
                break;
            }

            case 2:
                venderProducto();
                break;

            case 3:
                // Ver Inventario
                verInventario();
                break;

            case 4:
                // Consultar Producto
                consultarProducto();
                break;

            case 5: {
    std::string codigoActualizar;
    int nuevaCantidad;

    std::cout << "Ingrese el codigo del producto a actualizar: ";
    std::getline(std::cin, codigoActualizar);
    std::cout << "Ingrese la cantidad: ";
    std::cin >> nuevaCantidad;
    limpiarBuffer();

    actualizarProducto(codigoActualizar, nuevaCantidad);
    break;
}

case 6: {
    std::string codigoEliminar;
    std::cout << "Ingrese el codigo del producto a eliminar: ";
    std::getline(std::cin, codigoEliminar);

    eliminarProducto(codigoEliminar);
    break;
}
            case 7:
                std::cout << "Saliendo del programa." << std::endl;
                return;

            default:
                std::cout << "Opcion no valida." << std::endl;
                break;
        }
    }
}

int main() {
    mostrarMenu();
    return 0;
}

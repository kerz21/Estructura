#include <iostream>
#include <string>
#include <iomanip>
#include <conio.h> 
#include <cstdlib> // Para system("cls")
#include <cstdio> // Para manejo de archivos
#include <fstream> // Para exportar a Excel (CSV)
#include <locale> // Para configuración regional

using namespace std;

struct Producto {
    int codigo;
    char categoria[50];
    double precioPorUnidad;
    int stock;
};

const int MAX_PRODUCTOS = 100;
Producto productos[MAX_PRODUCTOS];
int numProductos = 0;

bool validarAdmin(const string& usuario, const string& contrasena) {
    string adminUsuario = "admin";
    string adminContrasena = "admin123";
    return (usuario == adminUsuario && contrasena == adminContrasena);
}

bool validarEmpleado(const string& usuario, const string& contrasena) {
    string empleadoUsuario = "empleado";
    string empleadoContrasena = "empleado123";
    return (usuario == empleadoUsuario && contrasena == empleadoContrasena);
}

void limpiarPantalla() {
    system("cls");
}

void mostrarMenuAdmin() {
    cout << "----- Menú Administrador -----" << endl;
    cout << "1) Insertar producto" << endl;
    cout << "2) Buscar producto" << endl;
    cout << "3) Actualizar producto" << endl;
    cout << "4) Eliminar producto" << endl;
    cout << "5) Mostrar productos" << endl;
    cout << "6) Exportar a Excel (CSV)" << endl; // Nueva opción
    cout << "7) Salir" << endl;
    cout << "-----------------------------" << endl;
    cout << "Seleccione una opción: ";
}

void mostrarMenuEmpleado() {
    cout << "----- Menú Empleado -----" << endl;
    cout << "1) Buscar producto" << endl;
    cout << "2) Salir" << endl;
    cout << "------------------------" << endl;
    cout << "Seleccione una opción: ";
}

void cargarProductosDesdeArchivo() {
    FILE *fich = fopen("productos.txt", "r");
    if (fich == NULL) {
        cout << "Error al abrir el archivo para lectura." << endl;
        return;
    }

    Producto producto;
    while (fscanf(fich, "%d %49s %lf %d", &producto.codigo, producto.categoria, &producto.precioPorUnidad, &producto.stock) != EOF) {
        if (numProductos < MAX_PRODUCTOS) {
            productos[numProductos++] = producto;
        }
    }

    fclose(fich);
}

void insertar() {
    if (numProductos < MAX_PRODUCTOS) {
        Producto nuevoProducto;

        cout << "Ingrese el código del producto: ";
        cin >> nuevoProducto.codigo;
        
        cin.ignore(); // Limpiar el buffer de entrada
        
        cout << "Ingrese la categoría del producto: ";
        cin.getline(nuevoProducto.categoria, 50);

        cout << "Ingrese el precio por unidad del producto: ";
        cin >> nuevoProducto.precioPorUnidad;

        cout << "Ingrese el stock del producto: ";
        cin >> nuevoProducto.stock;

        // Guardar el nuevo producto en el archivo
        FILE *fich = fopen("productos.txt", "a");
        if (fich == NULL) {
            cout << "Error al abrir el archivo para escritura." << endl;
        } else {
            fprintf(fich, "%d %s %lf %d\n", nuevoProducto.codigo, nuevoProducto.categoria, nuevoProducto.precioPorUnidad, nuevoProducto.stock);
            fclose(fich);
            productos[numProductos++] = nuevoProducto;
            cout << "Producto ingresado correctamente.\n";
        }
    } else {
        cout << "No es posible agregar más productos. Límite alcanzado.\n";
    }
}

void buscar() {
    if (numProductos == 0) {
        cout << "No hay productos para buscar." << endl;
        return;
    }

    int codigoBuscar;
    cout << "Ingrese el código del producto a buscar: ";
    cin >> codigoBuscar;

    bool encontrado = false;
    for (int i = 0; i < numProductos; ++i) {
        if (productos[i].codigo == codigoBuscar) {
            cout << "\nProducto encontrado:\n";
            cout << "Código: " << productos[i].codigo << endl;
            cout << "Categoría: " << productos[i].categoria << endl;
            cout << "Precio por unidad: $" << productos[i].precioPorUnidad << endl;
            cout << "Stock disponible: " << productos[i].stock << " unidades\n";
            encontrado = true;
            break;
        }
    }

    if (!encontrado) {
        cout << "Producto no encontrado.\n";
    }
}

void actualizar() {
    if (numProductos == 0) {
        cout << "No hay productos para actualizar." << endl;
        return;
    }

    int codigoActualizar;
    cout << "Ingrese el código del producto a actualizar: ";
    cin >> codigoActualizar;

    bool encontrado = false;
    for (int i = 0; i < numProductos; ++i) {
        if (productos[i].codigo == codigoActualizar) {
            cout << "\nActualización de producto:\n";
            cout << "Categoría actual: " << productos[i].categoria << endl;
            cout << "Nuevo precio por unidad: ";
            cin >> productos[i].precioPorUnidad;
            cout << "Nuevo stock del producto: ";
            cin >> productos[i].stock;

            // Actualizar el producto en el archivo
            FILE *fich = fopen("productos.txt", "w");
            if (fich == NULL) {
                cout << "Error al abrir el archivo para escritura." << endl;
            } else {
                for (int j = 0; j < numProductos; ++j) {
                    fprintf(fich, "%d %s %lf %d\n", productos[j].codigo, productos[j].categoria, productos[j].precioPorUnidad, productos[j].stock);
                }
                fclose(fich);
            }

            encontrado = true;
            cout << "Producto actualizado correctamente.\n";
            break;
        }
    }

    if (!encontrado) {
        cout << "Producto no encontrado.\n";
    }
}

void eliminar() {
    if (numProductos == 0) {
        cout << "No hay productos para eliminar." << endl;
        return;
    }

    int codigoEliminar;
    cout << "Ingrese el código del producto a eliminar: ";
    cin >> codigoEliminar;

    bool encontrado = false;
    for (int i = 0; i < numProductos; ++i) {
        if (productos[i].codigo == codigoEliminar) {
            encontrado = true;
            for (int j = i; j < numProductos - 1; ++j) {
                productos[j] = productos[j + 1];
            }
            numProductos--;

            // Actualizar el archivo
            FILE *fich = fopen("productos.txt", "w");
            if (fich == NULL) {
                cout << "Error al abrir el archivo para escritura." << endl;
            } else {
                for (int j = 0; j < numProductos; ++j) {
                    fprintf(fich, "%d %s %lf %d\n", productos[j].codigo, productos[j].categoria, productos[j].precioPorUnidad, productos[j].stock);
                }
                fclose(fich);
            }

            cout << "Producto eliminado correctamente.\n";
            break;
        }
    }

    if (!encontrado) {
        cout << "Producto no encontrado.\n";
    }
}

void mostrarProductos() {
    if (numProductos == 0) {
        cout << "No hay productos para mostrar." << endl;
        return;
    }

    cout << "\nListado de Productos:\n";
    for (int i = 0; i < numProductos; ++i) {
        cout << "Código: " << productos[i].codigo << endl;
        cout << "Categoría: " << productos[i].categoria << endl;
        cout << "Precio por unidad: $" << productos[i].precioPorUnidad << endl;
        cout << "Stock disponible: " << productos[i].stock << " unidades\n";
        cout << "---------------------------\n";
    }
}

void exportarAExcel() {
    ofstream archivo("productos.csv");
    if (!archivo.is_open()) {
        cout << "Error al crear el archivo CSV." << endl;
        return;
    }

    archivo << "Código,Categoría,Precio por Unidad,Stock\n";
    for (int i = 0; i < numProductos; ++i) {
        archivo << productos[i].codigo << "," 
                << productos[i].categoria << "," 
                << productos[i].precioPorUnidad << "," 
                << productos[i].stock << "\n";
    }

    archivo.close();
    cout << "Datos exportados correctamente a productos.csv\n";
}

void obtenerContrasena(string& contrasena) {
    char caracter;
    contrasena = "";
    while ((caracter = getch()) != 13) { // 13 es el código ASCII para Enter
        if (caracter == 8) { // 8 es el código ASCII para Backspace
            if (!contrasena.empty()) {
                cout << "\b \b"; // Borra el último carácter en la pantalla
                contrasena = contrasena.substr(0, contrasena.length() - 1);
            }
        } else {
            contrasena.push_back(caracter);
            cout << "*";
        }
    }
    cout << endl;
}

int main() {
    system("chcp 65001 > nul"); // Cambiar la página de códigos a UTF-8
    setlocale(LC_ALL, "es_ES.UTF-8"); // Configuración regional para mostrar caracteres en español
    system("color e0");

    string usuario;
    string contrasena;

    // Cargar productos desde el archivo al iniciar el programa
    cargarProductosDesdeArchivo();

    bool salir = false; // Variable para controlar la salida del programa

    do {
        cout << setw(82) << "+.-------------INGRESE EL USUARIO-------------.+" << endl;
        cin >> usuario;
        cin.ignore(); // Limpiar el buffer de entrada
        cout << setw(84) << "+.-------------INGRESE LA CONTRASEÑA-------------.+" << endl;
        obtenerContrasena(contrasena);
        cin.get(); // Espera a que el usuario presione la tecla enter para poder ejecutar la función de limpiar pantalla
        limpiarPantalla();

        if (validarAdmin(usuario, contrasena)) {
            do {
                mostrarMenuAdmin();
                int opcion;
                cin >> opcion;

                switch (opcion) {
                    case 1:
                        insertar();
                        break;
                    case 2:
                        buscar();
                        break;
                    case 3:
                        actualizar();
                        break;
                    case 4:
                        eliminar();
                        break;
                    case 5:
                        mostrarProductos();
                        break;
                    case 6:
                        exportarAExcel(); // Nueva opción para exportar a Excel
                        break;
                    case 7:
                        cout << "Saliendo del programa..." << endl;
                        salir = true; // Salir del bucle principal
                        break;
                    default:
                        cout << "Opción inválida. Intente de nuevo." << endl;
                }
            } while (!salir);
        } else if (validarEmpleado(usuario, contrasena)) {
            do {
                mostrarMenuEmpleado();
                int opcion;
                cin >> opcion;
                switch (opcion) {
                    case 1:
                        buscar();
                        break;
                    case 2:
                        cout << "Saliendo del programa..." << endl;
                        salir = true; // Salir del bucle principal
                        break;
                    default:
                        cout << "Opción inválida. Intente de nuevo." << endl;
                }
            } while (!salir);
        } else {
            cout << "Usuario o contraseña incorrectos. Intente de nuevo." << endl;
        }

        // Reiniciar la variable salir para el siguiente ciclo
        salir = false;

    } while (true);

    return 0;
}


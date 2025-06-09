#include <algorithm>
#include <iostream>
#include "Librerias/Lista/Lista.h"
#include "Librerias/Cola/Cola.h"
#include "Librerias/Pila/Pila.h"
#include "Librerias/HashMap/HashMap.h"
#include "Librerias/Arbol/ArbolBinario.h"
#include "Librerias/Arbol/ArbolBinarioAVL.h"
#include <sstream>
#include <fstream>
#include <vector>
#include <map>
#include <chrono>


using namespace std;
namespace fs = std::filesystem;

struct Venta {
    int idVenta;
    string fecha;
    string pais;
    string ciudad;
    string cliente;
    string producto;
    string categoria;
    int cantidad;
    double precioUnitario;
    double montoTotal;
    string medioEnvio;
    string estadoEnvio;
};


// Lee las ventas desde un archivo CSV y las almacena en un VECTOR.
// Utiliza ifstream para leer línea por línea y stringstream para separar los campos.
// Cada venta se guarda como un struct Venta y se agrega al vector.
vector<Venta> leerVentasDesdeCSV(const string& archivoCSV) {
    vector<Venta> ventas;
    ifstream archivo(archivoCSV);

    if (!archivo.is_open()) {
        cerr << "Error: No se pudo abrir el archivo: ventas_sudamerica.csv" << endl;
        return ventas;
    }

    string linea;
    getline(archivo, linea);

    while (getline(archivo, linea)) {
        stringstream ss(linea);
        string campo;
        Venta venta;

        getline(ss, campo, ','); venta.idVenta = stoi(campo);
        getline(ss, venta.fecha, ',');
        getline(ss, venta.pais, ',');
        getline(ss, venta.ciudad, ',');
        getline(ss, venta.cliente, ',');
        getline(ss, venta.producto, ',');
        getline(ss, venta.categoria, ',');
        getline(ss, campo, ','); venta.cantidad = stoi(campo);
        getline(ss, campo, ','); venta.precioUnitario = stod(campo);
        getline(ss, campo, ','); venta.montoTotal = stod(campo);
        getline(ss, venta.medioEnvio, ',');
        getline(ss, venta.estadoEnvio, ',');

        ventas.push_back(venta);
    }

    return ventas;
}

// Muestra las primeras n ventas del VECTOR de ventas.
// Utiliza un bucle for y accede a los elementos por índice.
void mostrarVentas(const vector<Venta>& ventas, int n = 5) {
    if (ventas.empty()) {
        cout << "No hay ventas para mostrar." << endl;
        return;
    }
    for (int i = 0; i < min(n, static_cast<int>(ventas.size())); i++) {
        const Venta& v = ventas[i];
        cout << v.idVenta << " | " << v.fecha << " | " << v.pais << " | " << v.ciudad
             << " | " << v.producto << " | $" << v.montoTotal << endl;
    }
}

// Muestra todas las ventas del VECTOR de forma RECURSIVA.
// Llama a sí misma incrementando el índice hasta recorrer todo el vector.
void mostrarVentasRecursivo(const vector<Venta>& ventas, int idx = 0) {
    if (idx >= ventas.size()) return;
    const Venta& v = ventas[idx];
    cout << v.idVenta << " | " << v.fecha << " | " << v.pais << " | " << v.ciudad
         << " | " << v.producto << " | $" << v.montoTotal << endl;
    mostrarVentasRecursivo(ventas, idx + 1);
}

// Busca una venta por ID usando un HASHMAP (HashMap<int, Venta*>).
void buscarVentaPorIDHashMap(HashMap<int, Venta*>& ventasPorID) {
    int id;
    cout << "Ingrese el ID de la venta a buscar: ";
    cin >> id;
    try {
        Venta* v = ventasPorID.get(id);
        cout << "Venta encontrada: " << v->idVenta << " | " << v->fecha<<" | "<<v->pais<<" | "<<v->ciudad<<" | "<<v->cliente <<
            " | "<<v->producto<<" | "<<v->categoria <<" | "<<v->cantidad <<" | "<<v->precioUnitario<<" | "<<v->montoTotal<<" | "
        <<v->medioEnvio<<" | "<<v->estadoEnvio<<endl;
    } catch (...) {
        cout << "No se encontró una venta con el ID: " << id << endl;
    }
}

// Obtiene el siguiente ID disponible recorriendo el archivo CSV.
// Utiliza ifstream y stringstream para encontrar el máximo ID y sumar uno.
int obtenerSiguienteID(const string& archivoCSV) {
    ifstream archivo(archivoCSV);
    string linea;
    int maxID = 0;

    getline(archivo, linea);

    while (getline(archivo, linea)) {
        stringstream ss(linea);
        string campo;
        getline(ss, campo, ',');
        int id = stoi(campo);
        if (id > maxID) {
            maxID = id;
        }
    }
    return maxID + 1;
}

// Carga una venta desde la entrada del usuario y la devuelve como struct Venta.
// No utiliza estructura de datos, solo variables locales.
Venta cargarVentaDeUsuario(int idVenta) {
    Venta v;
    v.idVenta = idVenta;

    cout << "Ingrese fecha (DD/MM/AAAA): ";
    getline(cin, v.fecha);

    // País
    int opcion;
    cout << "Seleccione el país:\n";
    cout << " 1) Argentina\n 2) Brasil\n 3) Chile\n 4) Colombia\n 5) Venezuela\n 6) Bolivia\n 7) Uruguay\n 8) Paraguay\n 9) Ecuador\n 10) Perú\n";
    cout << "Opción: ";
    cin >> opcion; cin.ignore();
    switch (opcion) {
        case 1: v.pais = "Argentina"; break;
        case 2: v.pais = "Brasil"; break;
        case 3: v.pais = "Chile"; break;
        case 4: v.pais = "Colombia"; break;
        case 5: v.pais = "Venezuela"; break;
        case 6: v.pais = "Bolivia";break;
        case 7: v.pais = "Uruguay"; break;
        case 8: v.pais = "Paraguay"; break;
        case 9: v.pais = "Ecuador"; break;
        case 10: v.pais = "Perú"; break;
        default: cout << "Opcion invalida"; break;
    }

    // Ciudad (texto libre)
    cout << "Ingrese ciudad: ";
    getline(cin, v.ciudad);

    // Cliente
    cout << "Ingrese nombre del cliente: ";
    getline(cin, v.cliente);

    // Producto (ingresado por nombre, como pediste)
    cout << "Ingrese nombre del producto: ";
    getline(cin, v.producto);

    // Categoría
    cout << "Seleccione categoría:\n";
    cout << " 1) Electrónica\n 2)Oficina\n 3)Accesorios\n 4)Muebles\n 5)Otro\n" ;
    cout << "Opción: ";
    cin >> opcion; cin.ignore();
    switch (opcion) {
        case 1: v.categoria = "Electrónica"; break;
        case 2: v.categoria = "Oficina"; break;
        case 3: v.categoria = "Accesorios"; break;
        case 4: v.categoria = "Muebles"; break;
        default: v.categoria = "Otra"; break;
    }

    // Cantidad y precio
    cout << "Ingrese cantidad: ";
    cin >> v.cantidad;
    cout << "Ingrese precio unitario ($): ";
    cin >> v.precioUnitario;
    cin.ignore();

    v.montoTotal = v.cantidad * v.precioUnitario;
    cout << "Monto total calculado: $" << v.montoTotal << endl;

    // Medio de envío
    cout << "Seleccione medio de envío:\n";
    cout << " 1) Aéreo\n 2) Terrestre\n 3) Marítimo\n 4)Otro\n" ;
    cout << "Opción: ";
    cin >> opcion; cin.ignore();
    switch (opcion) {
        case 1: v.medioEnvio = "Aéreo"; break;
        case 2: v.medioEnvio = "Terrestre"; break;
        case 3: v.medioEnvio = "Marítimo"; break;
        default: v.medioEnvio = "Otro"; break;
    }

    // Estado de envío
    cout << "Seleccione estado de envío:\n";
    cout << " 1) Entregado\n 2) En tránsito\n 3) Cancelado\n";
    cout << "Opción: ";
    cin >> opcion; cin.ignore();
    switch (opcion) {
        case 1: v.estadoEnvio = "Entregado"; break;
        case 2: v.estadoEnvio = "En tránsito"; break;
        case 3: v.estadoEnvio = "Cancelado"; break;
        default: v.estadoEnvio = "Desconocido"; break;
    }

    return v;
}

// Guarda todas las ventas del VECTOR en un archivo CSV.
// Utiliza ofstream y recorre el vector para escribir cada venta.
void guardarVentasEnCSV(const vector<Venta>& ventas, const string& archivoCSV) {
    ofstream archivo(archivoCSV);
    if (!archivo.is_open()) {
        cerr << " No se pudo abrir el archivo para guardar." << endl;
        return;
    }

    archivo << "idVenta,fecha,pais,ciudad,cliente,producto,categoria,cantidad,precioUnitario,montoTotal,medioEnvio,estadoEnvio\n";

    for (const auto& v : ventas) {
        archivo << v.idVenta << ","
                << v.fecha << ","
                << v.pais << ","
                << v.ciudad << ","
                << v.cliente << ","
                << v.producto << ","
                << v.categoria << ","
                << v.cantidad << ","
                << v.precioUnitario << ","
                << v.montoTotal << ","
                << v.medioEnvio << ","
                << v.estadoEnvio << "\n";
    }

    archivo.close();
}

// Carga una nueva venta al VECTOR y la guarda en el archivo CSV.
// Utiliza el vector para almacenar y actualizar las ventas.
void cargarNuevaVenta(vector<Venta>& ventas, const string& archivoCSV) {
    int nuevoID = 1;
    if (!ventas.empty()) {
        for (const auto& v : ventas) {
            if (v.idVenta >= nuevoID) nuevoID = v.idVenta + 1;
        }
    }


    Venta nuevaVenta = cargarVentaDeUsuario(nuevoID);
    ventas.push_back(nuevaVenta);
    guardarVentasEnCSV(ventas, archivoCSV);

    cout << "\033[32m✅ Venta cargada correctamente.\033[0m" << endl;
}

// Agrega una venta a una LISTA enlazada y la guarda en el archivo CSV.
// Utiliza la estructura Lista<Venta> para insertar al principio.
void agregarVenta(Lista<Venta>& lista, const Venta& v, const string& archivoCSV) {
    lista.insertarPrimero(v);

    ofstream archivo(archivoCSV, ios::app);
    if (archivo.is_open()) {
        archivo << v.idVenta << ","
        << v.fecha << ","
        << v.pais << ","
        << v.ciudad << ","
        << v.cliente << ","
        << v.producto << ","
        << v.categoria << ","
        << v.cantidad << ","
        << v.precioUnitario << ","
        << v.montoTotal << ","
        << v.medioEnvio << ","
        << v.estadoEnvio << endl;

        archivo.close();
        cout << "Venta agregada con exito" << endl;
    } else {
        cout << "No se pudo abrir el archivo" << endl;
    }
}

// Calcula el top 5 de ciudades por país usando MAP de MAP y VECTOR.
// Agrupa por país y ciudad, suma montos y ordena usando vector de pares.
void Top5CiudadesPorPais(const vector<Venta>& ventas) {
    map<string, map<string, double>> datos;
    for (auto& v : ventas)
        datos[v.pais][v.ciudad] += v.montoTotal;

    for (auto it = datos.begin(); it != datos.end(); ++it) {
        string pais = it->first;
        map<string, double>& ciudades = it->second;
        vector<pair<string, double>> vec(ciudades.begin(), ciudades.end());
        sort(vec.begin(), vec.end(), [](const pair<string, double>& a, const pair<string, double>& b) { return a.second > b.second; });

        cout << "Top 5 ciudades con mayor monto de venta en " << pais << ":" << endl;
        for (int i = 0; i < min(5, (int)vec.size()); i++) {
            cout << vec[i].first << " : $" << vec[i].second << endl;
        }
    }
}

// Calcula el monto total por producto y país usando MAP de MAP.
// Agrupa por país y producto, suma montos y muestra resultados.
void montoTotalPorProductoPorPais(const vector<Venta>& ventas) {
    map<string, map<string, double>> datos;

    for (auto& v : ventas)
        datos[v.pais][v.producto] += v.montoTotal;

    for (auto it = datos.begin(); it != datos.end(); ++it) {
        string pais = it->first;
        map<string, double>& productos = it->second;
        cout << "Monto total por producto en " << pais << ":" << endl;
        for (auto jt = productos.begin(); jt != productos.end(); ++jt)
            cout << " " << jt->first << " : $" << jt->second << endl;
    }
}

// Determina el medio de envío más frecuente por país y categoría usando MAP anidados.
// Cuenta ocurrencias y usa max_element para encontrar el más frecuente.
void medioDeEnvioMasFrecuentePorPais(const vector<Venta>& ventas) {
    map<string, map<string, map<string, int>>> datos;
    for (auto& v : ventas)
        datos[v.pais][v.categoria][v.medioEnvio]++;

    for (auto it = datos.begin(); it != datos.end(); ++it) {
        string pais = it->first;
        map<string, map<string, int>>& categorias = it->second;
        cout << "Medios de envio más usados en " << pais << endl;

        for (auto jt = categorias.begin(); jt != categorias.end(); ++jt) {
            string categoria = jt->first;
            map<string, int>& medios = jt->second;
            auto maxIt = max_element(medios.begin(), medios.end(), [](const pair<string, int>& a, const pair<string, int>& b) { return a.second < b.second; });
            cout << " " << categoria << " : " << maxIt->first << " (" << maxIt->second << " veces)" << endl;
        }
    }
}

// Encuentra el estado de envío más frecuente por país usando MAP anidados.
// Cuenta ocurrencias y usa max_element para mostrar el más común.
void estadoMasFrecuentePorPais(const vector<Venta>& ventas) {
    map<string, map<string, int>> datos;
    for (auto& v : ventas)
        datos[v.pais][v.estadoEnvio]++;

    for (auto it = datos.begin(); it != datos.end(); ++it) {
        string pais = it->first;
        map<string, int>& estados = it->second;
        auto maxIt = max_element(estados.begin(), estados.end(), [](const pair<string, int>& a, const pair<string, int>& b) { return a.second < b.second; });
        cout << "Estado de envio más frecuente en " << pais << " : " << maxIt->first << " (" << maxIt->second << " veces)" << endl;
    }
}

// Busca el producto más y menos vendido usando MAP.
// Suma cantidades por producto y usa max_element/min_element.
void productoMasYMenosVendido(const vector<Venta>& ventas) {
    map<string, int> cantidades;

    for (auto& v : ventas)
        cantidades[v.producto] += v.cantidad;

    auto maxIt = max_element(cantidades.begin(), cantidades.end(), [](const pair<string, int>& a, const pair<string, int>& b) { return a.second < b.second; });
    auto minIt = min_element(cantidades.begin(), cantidades.end(), [](const pair<string, int>& a, const pair<string, int>& b) { return a.second < b.second; });

    cout << "Elemento más vendido: " << maxIt->first << " (" << maxIt->second << " unidades)" << endl;
    cout << "Elemento menos vendido: " << minIt->first << " (" << minIt->second << " unidades)" << endl;
}

// Calcula el promedio de monto total por categoría y país usando MAP anidados.
// Suma montos y cuenta ocurrencias para calcular el promedio.
void promedioCategoriaPorPais(const vector<Venta>& ventas) {
    map<string, map<string, pair<double, int>>> datos;
    for (auto& v : ventas) {
        datos[v.pais][v.categoria].first += v.montoTotal;
        datos[v.pais][v.categoria].second++;
    }
    for (auto it = datos.begin(); it != datos.end(); ++it) {
        string pais = it->first;
        map<string, pair<double, int>>& categorias = it->second;
        cout << "Promedio por categoria en " << pais << endl;
        for (auto jt = categorias.begin(); jt != categorias.end(); ++jt)
            cout << " " << jt->first << " : $" << jt->second.first / jt->second.second << endl;
    }
}

// Busca el día con más ventas usando MAP.
// Suma montos por fecha y usa max_element para encontrar el máximo.
void diaConMasVentas(const vector<Venta>& ventas) {
    map<string, double> totales;
    for (auto& v : ventas)
        totales[v.fecha] += v.montoTotal;

    auto maxIt = max_element(totales.begin(), totales.end(), [](const pair<string, double>& a, const pair<string, double>& b) { return a.second < b.second; });
    cout << "Día con más ventas: " << maxIt->first << " ($" << maxIt->second << ")" << endl;
}

// Elimina una venta del VECTOR según país o ciudad.
// Utiliza COLA para almacenar filtrados y LISTA para historial de eliminadas.
void eliminarVenta(vector<Venta>& ventas, const string& archivoCSV) {
    if (ventas.empty()) {
        cout << "⚠ No hay ventas registradas." << endl;
        return;
    }

    int modoBusqueda;
    cout << "¿Cómo desea buscar las ventas?\n";
    cout << " 1) Por país\n";
    cout << " 2) Por ciudad\n";
    cout << "Opción: ";
    cin >> modoBusqueda;
    cin.ignore();

    string filtro;
    if (modoBusqueda == 1) {
        cout << "Seleccione el país:\n";
        cout << " 1) Argentina\n 2) Brasil\n 3) Chile\n 4) Colombia\n 5) Venezuela\n 6) Bolivia\n 7) Uruguay\n 8) Paraguay\n 9) Ecuador\n 10)Perú\n";
        int opcionPais;
        cout << "Opción: ";
        cin >> opcionPais;
        cin.ignore();
        switch (opcionPais) {
        case 1: filtro = "Argentina"; break;
        case 2: filtro = "Brasil"; break;
        case 3: filtro = "Chile"; break;
        case 4: filtro = "Colombia"; break;
        case 5: filtro = "Venezuela"; break;
        case 6: filtro = "Bolivia";break;
        case 7: filtro = "Uruguay"; break;
        case 8: filtro = "Paraguay"; break;
        case 9: filtro = "Ecuador"; break;
        case 10: filtro = "Perú"; break;
        default: cout << "❌ Opción inválida. Solo 1 (Argentina) a 10 (Perú).\n"; return;
    }
    } else if (modoBusqueda == 2) {
        cout << "Ingrese el nombre exacto de la ciudad: ";
        getline(cin, filtro);
    } else {
        cout << "❌ Opción inválida. Solo 1 (país) o 2 (ciudad).\n";
        return;
    }

    Cola<Venta> colaFiltrados;
    Lista<Venta> historialEliminadas;
    vector<int> indicesFiltrados;

    for (size_t i = 0; i < ventas.size(); i++) {
        if ((modoBusqueda == 1 && ventas[i].pais == filtro) ||
            (modoBusqueda == 2 && ventas[i].ciudad == filtro)) {
            indicesFiltrados.push_back(i);
            colaFiltrados.encolar(ventas[i]);
        }
    }

    if (indicesFiltrados.empty()) {
        cout << "❌ No se encontraron ventas con ese filtro.\n";
        return;
    }

    // Mostrar ventas encontradas usando el vector de índices
    cout << "\nVentas encontradas:\n";
    for (size_t j = 0; j < indicesFiltrados.size(); ++j) {
        const Venta& v = ventas[indicesFiltrados[j]];
        cout << (j+1) << ") ID: " << v.idVenta << ", Cliente: " << v.cliente
             << ", Producto: " << v.producto << ", Ciudad: " << v.ciudad
             << ", País: " << v.pais << ", Monto: $" << v.montoTotal << endl;
    }

    int opcionEliminar;
    cout << "\nIngrese el número de la venta que desea eliminar (1 a "
         << indicesFiltrados.size() << "): ";
    cin >> opcionEliminar;

    if (opcionEliminar < 1 || opcionEliminar > static_cast<int>(indicesFiltrados.size())) {
        cout << "❌ Opción inválida.\n";
        return;
    }

    int idxAEliminar = indicesFiltrados[opcionEliminar - 1];
    // Mantener la cola para historial de eliminadas
    historialEliminadas.insertarUltimo(ventas[idxAEliminar]);
    ventas.erase(ventas.begin() + idxAEliminar);
    guardarVentasEnCSV(ventas, archivoCSV);

    cout << "\033[32m✅ Venta eliminada correctamente y archivo actualizado.\033[0m\n";
}

// Convierte una fecha de formato DD/MM/AAAA a YYYY-MM-DD.
// Solo manipula strings, sin estructura de datos.
string fechaDDMMAAAA_a_YYYYMMDD(const string& fecha) {
    if (fecha.size() < 10) return fecha;
    return fecha.substr(6,4) + "-" + fecha.substr(3,2) + "-" + fecha.substr(0,2);
}

// Modifica una venta del VECTOR por ID.
// Utiliza PILA para historial de cambios y recorre el vector para buscar la venta.
void modificarVenta(vector<Venta>& ventas, const string& archivoCSV) {
    if (ventas.empty()) {
        cout << "⚠ No hay ventas registradas." << endl;
        return;
    }

    int id;
    cout << "Ingrese el ID de la venta que desea modificar: ";
    cin >> id;
    cin.ignore();

    Pila<Venta> pilaCambios;  // historial por si se quiere deshacer después
    bool encontrada = false;

    for (Venta& v : ventas) {
        if (v.idVenta == id) {
            encontrada = true;
            pilaCambios.push(v);
            string entrada;

            // Cliente - texto libre
            cout << "Cliente [" << v.cliente << "]: ";
            getline(cin, entrada);
            if (!entrada.empty()) v.cliente = entrada;

            // Producto - texto libre
            cout << "Producto [" << v.producto << "]: ";
            getline(cin, entrada);
            if (!entrada.empty()) v.producto = entrada;

            // Ciudad - texto libre
            cout << "Ciudad [" << v.ciudad << "]: ";
            getline(cin, entrada);
            if (!entrada.empty()) v.ciudad = entrada;

            // País - opciones fijas
            cout << "País actual: " << v.pais << endl;
            cout << "Seleccione país (ENTER para mantener):\n";
            cout << " 1) Argentina\n 2) Brasil\n 3) Chile\n 4) Colombia\n 5) Venezuela\n 6) Bolivia\n 7) Uruguay\n 8) Paraguay\n 9) Ecuador\n 10)Perú\n";
            cout << "Opción: ";
            getline(cin, entrada);
            if (!entrada.empty()) {
                int op = stoi(entrada);
                switch (op) {
                    case 1: v.pais = "Argentina"; break;
                    case 2: v.pais = "Brasil"; break;
                    case 3: v.pais = "Chile"; break;
                    case 4: v.pais = "Colombia"; break;
                    case 5: v.pais = "Venezuela"; break;
                    case 6: v.pais = "Bolivia";break;
                    case 7: v.pais = "Uruguay"; break;
                    case 8: v.pais = "Paraguay"; break;
                    case 9: v.pais = "Ecuador"; break;
                    case 10: v.pais = "Perú"; break;
                    default: cout<< "Se mantiene el pais\n"; break;
                }
            }

            // Estado de envío - opciones fijas
            cout << "Estado de envío actual: " << v.estadoEnvio << endl;
            cout << "Seleccione estado de envío (ENTER para mantener):\n";
            cout << " 1) Pendiente\n 2) Enviado\n 3) Entregado\n 4) Cancelado\n";
            cout << "Opción: ";
            getline(cin, entrada);
            if (!entrada.empty()) {
                int op = stoi(entrada);
                switch (op) {
                    case 1: v.estadoEnvio = "Pendiente"; break;
                    case 2: v.estadoEnvio = "Enviado"; break;
                    case 3: v.estadoEnvio = "Entregado"; break;
                    case 4: v.estadoEnvio = "Cancelado"; break;
                    default: cout << "Opción inválida, se mantiene el estado actual.\n"; break;
                }
            }

            // Categoría - opciones fijas
            cout << "Categoría actual: " << v.categoria << endl;
            cout << "Seleccione categoría (ENTER para mantener):\n";
            cout << " 1) Electrónica\n 2) Accesorios\n 3) Oficina\n 4) Muebles\n 5) Otros\n";
            cout << "Opción: ";
            getline(cin, entrada);
            if (!entrada.empty()) {
                int op = stoi(entrada);
                switch (op) {
                    case 1: v.categoria = "Electrónica"; break;
                    case 2: v.categoria = "Accesorios"; break;
                    case 3: v.categoria = "Oficina"; break;
                    case 4: v.categoria = "Muebles"; break;
                    case 5: cout<< "Opcion Invalida"; break;
                    default: cout << "Opción inválida, se mantiene la categoría actual.\n"; break;
                }
            }

            // Medio de envío - opciones fijas
            cout << "Medio de envío actual: " << v.medioEnvio << endl;
            cout << "Seleccione medio de envío (ENTER para mantener):\n";
            cout << " 1) Terrestre\n 2) Marítimo\n 3) Aéreo\n";
            cout << "Opción: ";
            getline(cin, entrada);
            if (!entrada.empty()) {
                int op = stoi(entrada);
                switch (op) {
                    case 1: v.medioEnvio = "Terrestre"; break;
                    case 2: v.medioEnvio = "Marítimo"; break;
                    case 3: v.medioEnvio = "Aéreo"; break;
                    default: cout << "Opción inválida, se mantiene el medio actual.\n"; break;
                }
            }

            // Fecha - texto libre (o puedes poner validación aparte)
            cout << "Fecha [" << v.fecha << "]: ";
            getline(cin, entrada);
            if (!entrada.empty()) v.fecha = entrada;

            // Cantidad - numérico
            cout << "Cantidad [" << v.cantidad << "]: ";
            getline(cin, entrada);
            if (!entrada.empty()) {
                try {
                    v.cantidad = stof(entrada);
                } catch (...) {
                    cout << "Entrada inválida para cantidad, se mantiene el valor actual.\n";
                }
            }

            // Precio Unitario - numérico
            cout << "Precio Unitario [" << v.precioUnitario << "]: ";
            getline(cin, entrada);
            if (!entrada.empty()) {
                try {
                    v.precioUnitario = stof(entrada);
                } catch (...) {
                    cout << "Entrada inválida para precio, se mantiene el valor actual.\n";
                }
            }

            v.montoTotal = v.precioUnitario * v.cantidad;

            guardarVentasEnCSV(ventas, archivoCSV);

            cout << "✅ Venta modificada correctamente.\n";

            return;
        }
    }

    if (!encontrada) {
        cout << "❌ No se encontró una venta con ese ID.\n";
    }
}

//caso 6:

// Muestra todas las ventas de una ciudad específica usando VECTOR.
// Recorre el vector y filtra por ciudad.
void ventasPorCiudad(const vector<Venta>& ventas) {
    string ciudad;
    cout << "Ingrese la ciudad: ";
    getline(cin, ciudad);
    for (const auto& v : ventas) {
        if (v.ciudad == ciudad) {
            cout << v.idVenta << ", " << v.producto << ", " << v.categoria << ", " << v.pais << ", " << v.ciudad << ", " << v.fecha << endl;
        }
    }
}

// Muestra ventas en un rango de fechas y país usando VECTOR.
// Convierte fechas y filtra por país y rango.
void ventasPorRangoDeFechasYpais(const vector<Venta>& ventas) {
    string pais, fechaInicio, fechaFin;
    int opcion;
    cout << "Seleccione el país:\n";
    cout << " 1) Argentina\n 2) Brasil\n 3) Chile\n 4) Colombia\n 5) Venezuela\n 6) Bolivia\n 7) Uruguay\n 8) Paraguay\n 9) Ecuador\n 10) Perú\n";
    cout << "Opción: ";
    cin >> opcion; cin.ignore();
    switch (opcion) {
        case 1: pais = "Argentina"; break;
        case 2: pais = "Brasil"; break;
        case 3: pais = "Chile"; break;
        case 4: pais = "Colombia"; break;
        case 5: pais = "Venezuela"; break;
        case 6: pais = "Bolivia";break;
        case 7: pais = "Uruguay"; break;
        case 8: pais = "Paraguay"; break;
        case 9: pais = "Ecuador"; break;
        case 10: pais = "Perú"; break;
        default: pais = "Otro"; break;
    }
    cout << "Ingrese la fecha de inicio (DD/MM/AAAA): "; cin >> fechaInicio;
    cout << "Ingrese la fecha de fin (DD/MM/AAAA): "; cin >> fechaFin;

    string fechaInicioISO = fechaDDMMAAAA_a_YYYYMMDD(fechaInicio);
    string fechaFinISO = fechaDDMMAAAA_a_YYYYMMDD(fechaFin);

    for (const auto& v : ventas) {
        string fechaVentaISO = fechaDDMMAAAA_a_YYYYMMDD(v.fecha);
        if (v.pais == pais && fechaVentaISO >= fechaInicioISO && fechaVentaISO <= fechaFinISO) {
            cout << v.idVenta << ", " << v.producto << ", " << v.fecha << ", " << v.cantidad << endl;
        }
    }
}

// Compara dos países usando MAP para acumular totales, productos y medios de envío.
// Agrupa y muestra estadísticas por país.
void compararPaises(const vector<Venta>& ventas) {
    string pais1, pais2;
    int opcion1;int opcion2;
    cout << "Seleccione el primer país:\n";
    cout << " 1) Argentina\n 2) Brasil\n 3) Chile\n 4) Colombia\n 5) Venezuela\n 6) Bolivia\n 7) Uruguay\n 8) Paraguay\n 9) Ecuador\n 10) Perú\n";
    cout << "Opción: ";
    cin >> opcion1; cin.ignore();
    switch (opcion1) {
        case 1: pais1 = "Argentina"; break;
        case 2: pais1 = "Brasil"; break;
        case 3: pais1 = "Chile"; break;
        case 4: pais1 = "Colombia"; break;
        case 5: pais1 = "Venezuela"; break;
        case 6: pais1 = "Bolivia";break;
        case 7: pais1 = "Uruguay"; break;
        case 8: pais1 = "Paraguay"; break;
        case 9: pais1 = "Ecuador"; break;
        case 10: pais1 = "Perú"; break;
        default: cout<<"Opcion Invalida"; break;
    }

    cout << "Seleccione el segundo país:\n";
    cout << " 1) Argentina\n 2) Brasil\n 3) Chile\n 4) Colombia\n 5) Venezuela\n 6) Bolivia\n 7) Uruguay\n 8) Paraguay\n 9) Ecuador\n 10) Perú\n";
    cout << "Opción: ";
    cin >> opcion2; cin.ignore();
    switch (opcion2) {
        case 1: pais2 = "Argentina"; break;
        case 2: pais2 = "Brasil"; break;
        case 3: pais2 = "Chile"; break;
        case 4: pais2 = "Colombia"; break;
        case 5: pais2 = "Venezuela"; break;
        case 6: pais2 = "Bolivia";break;
        case 7: pais2 = "Uruguay"; break;
        case 8: pais2 = "Paraguay"; break;
        case 9: pais2 = "Ecuador"; break;
        case 10: pais2 = "Perú"; break;
        default: cout<<"Seleccion invalida"; break;
    }

    map<string, float> totalVentas;
        map<string, map<string, int>> productosVendidos;
        map<string, map<string, int>> mediosEnvio;

        for (const auto& v : ventas) {
            if (v.pais == pais1 || v.pais == pais2) {
                totalVentas[v.pais] += v.precioUnitario * v.cantidad;
                productosVendidos[v.pais][v.producto] += v.cantidad;
                mediosEnvio[v.pais][v.medioEnvio]++;
            }
        }

        for (const string& pais : {pais1, pais2}) {
            cout << "\nPais: " << pais;
            cout << "\nMonto total de ventas: $" << totalVentas[pais];

            string masVendido;
            int maxCantidad = 0;
            for (auto& [producto, cant] : productosVendidos[pais]) {
                if (cant > maxCantidad) {
                    masVendido = producto;
                    maxCantidad = cant;
                }
            }
            cout << "\nProducto mas vendido: " << masVendido;

            string medioMasUsado;
            int maxUso = 0;
            for (auto& [medio, cantidad] : mediosEnvio[pais]) {
                if (cantidad > maxUso) {
                    medioMasUsado = medio;
                    maxUso = cantidad;
                }
            }
            cout << "\nMedio de envio mas usado: " << medioMasUsado << endl;
        }
    }

// Compara dos productos por país usando MAP anidados.
// Acumula cantidad y monto por producto y país.
void compararProductos(const vector<Venta>& ventas) {
    string prod1, prod2;
    cout << "\033[36mIngrese el primer producto:\033[0m ";
    cin >> ws;
    getline(cin, prod1);
    cout << "\033[36mIngrese el segundo producto:\033[0m ";
    getline(cin, prod2);

    // Mapa de país -> producto -> cantidad y monto
    map<string, map<string, pair<int, float>>> estadisticas;

    for (const auto& v : ventas) {
        if (v.producto == prod1 || v.producto == prod2) {
            estadisticas[v.pais][v.producto].first += v.cantidad;
            estadisticas[v.pais][v.producto].second += v.cantidad * v.precioUnitario;
        }
    }

    cout << "\n\033[35m--- Comparación de productos por país ---\033[0m\n";

    for (const auto& [pais, productos] : estadisticas) {
        cout << "\n\033[33mPaís: " << pais << "\033[0m\n";

        for (const string& prod : {prod1, prod2}) {
            int cantidad = productos.count(prod) ? productos.at(prod).first : 0;
            float monto = productos.count(prod) ? productos.at(prod).second : 0.0;

            cout << "  Producto: " << prod << endl;
            cout << "    Cantidad total: " << cantidad << endl;
            cout << "    Monto total: $" << monto << endl;
        }
    }
}

// Muestra productos por debajo de un umbral de precio promedio usando MAP.
// Agrupa por producto y país, calcula promedios y filtra.
void productosPorDebajoDeUmbral(const vector<Venta>& ventas) {
    string pais;
    float umbral;
    int opcion;
    cout << "Seleccione el país:\n";
    cout << " 1) Argentina\n 2) Brasil\n 3) Chile\n 4) Colombia\n 5) Venezuela\n 6) Bolivia\n 7) Uruguay\n 8) Paraguay\n 9) Ecuador\n 10)Perú\n";
    cout << "Opción: ";
    cin >> opcion; cin.ignore();
    switch (opcion) {
        case 1: pais = "Argentina"; break;
        case 2: pais = "Brasil"; break;
        case 3: pais = "Chile"; break;
        case 4: pais = "Colombia"; break;
        case 5: pais = "Venezuela"; break;
        case 6: pais = "Bolivia";break;
        case 7: pais = "Uruguay"; break;
        case 8: pais = "Paraguay"; break;
        case 9: pais = "Ecuador"; break;
        case 10: pais = "Perú"; break;
        default: cout<<"Opcion incorrecta"; break;
    }
    cout << "Ingrese el umbral en $: "; cin >> umbral;

    map<string, pair<float, int>> acumulados; // producto -> {suma, cantidad total}

    for (const auto& v : ventas) {
        if (v.pais == pais) {
            acumulados[v.producto].first += v.precioUnitario * v.cantidad;
            acumulados[v.producto].second += v.cantidad;
        }
    }

    cout << "Productos con promedio por unidad menor a $" << umbral << " en " << pais << ":\n";
    for (auto& [producto, datos] : acumulados) {
        float promedio = datos.first / datos.second;
        if (promedio < umbral) {
            cout << producto << ", promedio: $" << promedio << endl;
        }
    }
}

// Muestra productos por encima de un umbral de precio promedio usando MAP.
// Agrupa por producto y país, calcula promedios y filtra.
void productosPorEncimaDeUmbral(const vector<Venta>& ventas) {
    string pais;
int opcion;
    float umbral;
    switch (opcion) {
        case 1: pais = "Argentina"; break;
        case 2: pais = "Brasil"; break;
        case 3: pais = "Chile"; break;
        case 4: pais = "Colombia"; break;
        case 5: pais = "Venezuela"; break;
        case 6: pais = "Bolivia";break;
        case 7: pais = "Uruguay"; break;
        case 8: pais = "Paraguay"; break;
        case 9: pais = "Ecuador"; break;
        case 10: pais = "Perú"; break;
        default: cout<<"Opcion incorrecta"; break;
    }
    cout << "Ingrese el umbral en $: "; cin >> umbral;

    map<string, pair<float, int>> acumulados; // producto -> {suma, cantidad total}

    for (const auto& v : ventas) {
        if (v.pais == pais) {
            acumulados[v.producto].first += v.precioUnitario * v.cantidad;
            acumulados[v.producto].second += v.cantidad;
        }
    }

    cout << "Productos con promedio por unidad mayor a $" << umbral << " en " << pais << ":\n";
    for (auto& [producto, datos] : acumulados) {
        float promedio = datos.first / datos.second;
        if (promedio > umbral) {
            cout << producto << ", promedio: $" << promedio << endl;
        }
    }
}

// Lee un entero de forma segura desde la entrada.
// Utiliza bucle y manejo de excepciones para validar la entrada.
int leerEnteroSeguro(const string& mensaje) {
    string entrada;
    int numero;
    while (true) {
        cout << mensaje;
        cin>>entrada;
cin.ignore();

        try {
            numero = stoi(entrada);
            return numero;
        } catch (...) {
            cout << "\033[31mEntrada inválida. Por favor, ingrese un número válido.\033[0m\n";
        }
    }
}

int main() {
    using namespace std::chrono;

    system("chcp 65001");
    int opcion;
    Venta nuevaVenta;
    Lista<Venta> listaVentas;

    string archivoCSV = "C:/POO/ventas_sudamerica.csv";

    auto start = high_resolution_clock::now();
    vector<Venta> ventas = leerVentasDesdeCSV(archivoCSV);
    auto end = high_resolution_clock::now();
        auto duration = duration_cast<milliseconds>(end - start);
        std::cout << "Tiempo de carga (ms): " << duration.count() << std::endl;

        std::cout << "Se leyeron " << ventas.size() << " ventas.\n\n";
        std::cout << "Primeras ventas leídas desde el archivo:\n";
        mostrarVentas(ventas);

        HashMap<int, Venta*> ventasPorID(ventas.size() * 2);
        for (auto& v : ventas) {
            ventasPorID.put(v.idVenta, &v);
        }

        do {
            std::cout << "\n\033[1;34m====== MENU PRINCIPAL ======\033[0m\n";
            std::cout << "\033[32m1. Buscar venta por ID\033[0m\n";
            std::cout << "\033[33m2. Cargar nueva venta\033[0m\n";
            std::cout << "\033[35m3. Eliminar venta\033[0m\n";
            std::cout << "\033[36m4. Modificar una venta\033[0m\n";
            std::cout << "\033[34m5. Mostrar estadisticas generales (sin eliminar)\033[0m\n";
            std::cout << "\033[36m6. Consultas dinamicas solicitadas por el usuario\033[0m\n";
            std::cout << "\033[31m7. Salir del programa\033[0m\n";

            opcion = leerEnteroSeguro("\033[36mSeleccione una opción: \033[0m");

            switch (opcion) {
                case 1:
                    buscarVentaPorIDHashMap(ventasPorID);
                    std::cout << "\033[32mBúsqueda completada.\033[0m\n";
                    break;
                case 2:
                    cargarNuevaVenta(ventas, archivoCSV);
                    ventasPorID.put(ventas.back().idVenta, &ventas.back());
                    break;
                case 3:
                    eliminarVenta(ventas, archivoCSV);
                    ventasPorID = HashMap<int, Venta*>(ventas.size() * 2);
                    for (auto& v : ventas) ventasPorID.put(v.idVenta, &v);
                    break;
                case 4:
                    modificarVenta(ventas, archivoCSV);
                    ventasPorID = HashMap<int, Venta*>(ventas.size() * 2);
                    for (auto& v : ventas) ventasPorID.put(v.idVenta, &v);
                    break;
                case 5:
                    int subopcionEstadisticas;
                    do {
                        std::cout << "\n\033[1;34m--- ESTADISTICAS GENERALES ---\033[0m\n";
                        std::cout << "1. Top 5 ciudades por país\n";
                        std::cout << "2. Monto total por producto por país\n";
                        std::cout << "3. Promedio por categoría por país\n";
                        std::cout << "4. Estado de envío más frecuente por país\n";
                        std::cout << "5. Producto más y menos vendido\n";
                        std::cout << "6. Día con más ventas\n";
                        std::cout << "7. Medio de envío más frecuente por país\n";
                        std::cout << "8. Volver al menú principal\n";
                        subopcionEstadisticas = leerEnteroSeguro("Seleccione una opción (1-8): ");
                        switch (subopcionEstadisticas) {
                            case 1:
                                Top5CiudadesPorPais(ventas);
                                cout << "\033[34mLa estructura utilizada fue: HASHMAP\033[0m" << endl;
                                break;
                            case 2:
                                montoTotalPorProductoPorPais(ventas);
                                cout << "\033[34mLa estructura utilizada fue: HASHMAP\033[0m" << endl;
                                break;
                            case 3:
                                promedioCategoriaPorPais(ventas);
                                cout << "\033[34mLa estructura utilizada fue: HASHMAP\033[0m" << endl;
                                break;
                            case 4:
                                estadoMasFrecuentePorPais(ventas);
                                cout << "\033[34mLa estructura utilizada fue: HASHMAP\033[0m" << endl;
                                break;
                            case 5:
                                productoMasYMenosVendido(ventas);
                                cout << "\033[34mLa estructura utilizada fue: HASHMAP\033[0m" << endl;
                                break;
                            case 6:
                                diaConMasVentas(ventas);
                                cout << "\033[34mLa estructura utilizada fue: HASHMAP\033[0m" << endl;
                                break;
                            case 7:
                                medioDeEnvioMasFrecuentePorPais(ventas);
                                cout << "\033[34mLa estructura utilizada fue: HASHMAP\033[0m" << endl;
                                break;
                            case 8:
                                std::cout << "Volviendo al menú principal...\n";
                                break;
                            default:
                                std::cout << "\033[31mOpción inválida.\033[0m\n";
                                break;
                        }
                    } while (subopcionEstadisticas != 8);
                    break;
                case 6: {
                    int subopcion;
                    do {
                        std::cout << "\n\033[1;34m--- CONSULTAS DINÁMICAS ---\033[0m\n";
                        std::cout << "\033[32m1. Ventas en una ciudad específica\033[0m\n";
                        std::cout << "\033[33m2. Ventas en rango de fechas por país\033[0m\n";
                        std::cout << "\033[35m3. Comparar dos países\033[0m\n";
                        std::cout << "\033[36m4. Comparar dos productos por cada país\033[0m\n";
                        std::cout << "\033[31m5. Productos por debajo de un umbral (por país)\033[0m\n";
                        std::cout << "\033[31m6. Productos por encima de un umbral (por país)\033[0m\n";
                        std::cout << "\033[31m7. Volver al menú principal\033[0m\n";

                        subopcion = leerEnteroSeguro("\033[36mSeleccione una opción: \033[0m");

                        switch (subopcion) {
                            case 1: 
                                ventasPorCiudad(ventas); 
                                cout << "\033[34mLa estructura utilizada fue: VECTOR\033[0m" << endl;
                                break;
                            case 2: 
                                ventasPorRangoDeFechasYpais(ventas); 
                                cout << "\033[34mLa estructura utilizada fue: VECTOR\033[0m" << endl;
                                break;
                            case 3: 
                                compararPaises(ventas); 
                                cout << "\033[34mLa estructura utilizada fue: MAP\033[0m" << endl;
                                break;
                            case 4: 
                                compararProductos(ventas); 
                                cout << "\033[34mLa estructura utilizada fue: MAP\033[0m" << endl;
                                break;
                            case 5: 
                                productosPorDebajoDeUmbral(ventas); 
                                cout << "\033[34mLa estructura utilizada fue: MAP\033[0m" << endl;
                                break;
                            case 6: 
                                productosPorEncimaDeUmbral(ventas); 
                                cout << "\033[34mLa estructura utilizada fue: MAP\033[0m" << endl;
                                break;
                            case 7: 
                                std::cout << "\033[33mVolviendo al menú principal...\033[0m\n"; 
                                break;
                            default: 
                                std::cout << "\033[31mOpción inválida.\033[0m\n"; 
                                break;
                        }
                    } while (subopcion != 7);
                    break;
                }
                case 7:
                    std::cout << "\033[31mSaliendo del programa...\033[0m\n";
                    break;
                default:
                    std::cout << "\033[31mOpción inválida.\033[0m\n";
                    break;
            }

        } while (opcion != 7);

    return 0;
}

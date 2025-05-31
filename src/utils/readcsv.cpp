#include "../classes/enemigo.h"
#include "../classes/jefe.h"
#include "../classes/mazmorra.h"
#include <fstream>
#include <sstream>
#include <iostream>
using namespace std;


struct EnemigosInfo {
    vector<Enemigo> enemigosIniciales;
    Jefe jefe;
    vector<Enemigo> enemigosJefe;
};

bool esNumeroValido(const string& str) {
    try {
        size_t pos;
        stoi(str, &pos);
        return pos == str.length();
    } catch (...) {
        return false;
    }
}

EnemigosInfo leerEnemigosDeLinea(const string& linea) {
    vector<Enemigo> enemigosIniciales;
    vector<Enemigo> enemigosJefe;
    Jefe jefe("default", 0, 0, 1, vector<pair<int, int> > (), 1, 1, 1);
    
    stringstream ss(linea);
    string token;
    vector<string> datos;
    

    while (getline(ss, token, ',')) {
        datos.push_back(token);
    }
    
    size_t i = 0;
    bool encontradoJefe = false;
    
    // Leer datos mientras 
    while (i < datos.size()) {

        if (i + 2 >= datos.size()) break;
        
        try {

            if (!esNumeroValido(datos[i])) {
                if (i + 3 >= datos.size()) {
                    i++;
                    continue;
                }
                
                int numMovimientosJefe;
                try {
                    numMovimientosJefe = stoi(datos[i + 3]);
                    int datosNecesariosJefe = 4 + (2 * numMovimientosJefe) + 4;
                    
                    if (i + datosNecesariosJefe <= datos.size()) {
                        stringstream jefeStr;
                        for (int j = 0; j < datosNecesariosJefe; j++) {
                            if (j > 0) jefeStr << ",";
                            jefeStr << datos[i + j];
                        }
                        
                        jefe = Jefe::leerDesdeStream(jefeStr);
                        encontradoJefe = true;
                        i += datosNecesariosJefe;
                        continue;
                    }
                } catch (...) {
                    i++;
                    continue;
                }
            }
            
            // Enemigo normal
            int numMovimientos;
            try {
                numMovimientos = stoi(datos[i + 2]);
                int datosNecesarios = 3 + (2 * numMovimientos) + 4;
                
                if (i + datosNecesarios > datos.size()) {
                    i++;
                    continue;
                }
                
                stringstream enemigoStr;
                for (int j = 0; j < datosNecesarios; j++) {
                    if (j > 0) enemigoStr << ",";
                    enemigoStr << datos[i + j];
                }
                
                Enemigo enemigo = Enemigo::leerDesdeStream(enemigoStr);
                
                if (!encontradoJefe) {
                    enemigosIniciales.push_back(enemigo);
                } else {
                    enemigosJefe.push_back(enemigo);
                }
                
                i += datosNecesarios;
                
            } catch (const exception& e) {
                i++;
            }
            
        } catch (const exception& e) {
            i++;
        }
    }
    
    return {enemigosIniciales, jefe, enemigosJefe};
}

vector<Mazmorra> leerMazmorras(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        throw runtime_error("No se pudo abrir el archivo de mazmorras: " + filename);
    }

    string line;
    vector<Mazmorra> mazmorras;


    string enemigos_path = "data/enemigos.csv";
    size_t pos = filename.find_last_of("/\\");
    if (pos != string::npos) {
        enemigos_path = filename.substr(0, pos + 1) + "enemigos.csv";
    }

    ifstream enemigosFile(enemigos_path);
    if (!enemigosFile.is_open()) {
        throw runtime_error("No se pudo abrir el archivo de enemigos: " + enemigos_path);
    }

    string lineaEnemigos;
    vector<string> lineasEnemigos;
    

    while (getline(enemigosFile, lineaEnemigos)) {
        if (!lineaEnemigos.empty()) {
            lineasEnemigos.push_back(lineaEnemigos);
        }
    }

    size_t indiceEnemigos = 0;
    // Leer cada mazmorra
    while (getline(file, line)) {
        try {
            istringstream ss(line);
            string token;
            vector<string> datos;
            while (getline(ss, token, ',')) {
                datos.push_back(token);
            }

            if (datos.size() < 2) {
                throw runtime_error("Datos insuficientes para crear mazmorra");
            }

            // Leer los enemigos de la mazmorra
            if (indiceEnemigos >= lineasEnemigos.size()) {
                throw runtime_error("No hay suficientes líneas de enemigos para esta mazmorra");
            }
            
            EnemigosInfo enemigos = leerEnemigosDeLinea(lineasEnemigos[indiceEnemigos++]);

            int altoPrincipal = stoi(datos[0]);
            int anchoPrincipal = stoi(datos[1]);
            vector<vector<string> > salaPrincipal(altoPrincipal, vector<string>(anchoPrincipal));
            size_t idx = 2;

            if (idx + (altoPrincipal * anchoPrincipal) > datos.size()) {
                throw runtime_error("Datos insuficientes para sala principal");
            }

            for (int y = 0; y < altoPrincipal; ++y)
                for (int x = 0; x < anchoPrincipal; ++x)
                    salaPrincipal[y][x] = datos[idx++] + " ";

            if (idx + 1 >= datos.size()) {
                throw runtime_error("Datos insuficientes para sala del jefe");
            }

            int altoJefe = stoi(datos[idx++]);
            int anchoJefe = stoi(datos[idx++]);
            vector<vector<string> > salaJefe(altoJefe, vector<string>(anchoJefe));

            if (idx + (altoJefe * anchoJefe) > datos.size()) {
                throw runtime_error("Datos insuficientes para sala del jefe");
            }

            for (int y = 0; y < altoJefe; ++y)
                for (int x = 0; x < anchoJefe; ++x)
                    salaJefe[y][x] = datos[idx++] + " ";

            mazmorras.push_back(Mazmorra(
                anchoPrincipal, altoPrincipal,
                anchoJefe, altoJefe,
                salaPrincipal, salaJefe,
                enemigos.enemigosIniciales, enemigos.jefe, enemigos.enemigosJefe
            ));
        } catch (const exception& e) {
            cerr << "Error al leer mazmorra: " << e.what() << endl;
            continue;
        }
    }

    if (mazmorras.empty()) {
        throw runtime_error("No se pudieron cargar mazmorras del archivo");
    }

    return mazmorras;
}

void mostrarEnemigos(const Mazmorra& mazmorra) {
    cout << "Enemigos en esta mazmora:\n";
    for (size_t i = 0; i < mazmorra.getEnemigosIniciales().size(); ++i) {
        const auto& e = mazmorra.getEnemigosIniciales()[i];
        cout << "  Enemigo " << i + 1 << " -> Posición: (" << e.getY() << ", " << e.getX()
             << "), Vida: " << e.getVida() << ", Daño: " << e.getDaño()
             << ", Rango: " << e.getRango() << ", Frecuencia: " << e.getFrecuencia()
             << ", Número de movimientos: " << e.getNumeroMovimientos() << "\n";
    }

    const auto& j = mazmorra.getJefe();
    cout << "  Jefe: " << j.getNombre() << " -> Posición: (" << j.getY() << ", " << j.getX()
         << "), Vida: " << j.getVida() << ", Daño: " << j.getDaño()
         << ", Rango: " << j.getRango() << ", Frecuencia: " << j.getFrecuencia()
         << ", Número de movimientos: " << j.getNumeroMovimientos() << "\n";

    if (!mazmorra.getEnemigosJefe().empty()) {
        cout << "  Enemigos en la sala del jefe:\n";
        for (size_t i = 0; i < mazmorra.getEnemigosJefe().size(); ++i) {
            const auto& e = mazmorra.getEnemigosJefe()[i];
            cout << "    Enemigo " << i + 1 << " -> Posición: (" << e.getY() << ", " << e.getX()
                 << "), Vida: " << e.getVida() << ", Daño: " << e.getDaño()
                 << ", Rango: " << e.getRango() << ", Frecuencia: " << e.getFrecuencia()
                 << ", Número de movimientos: " << e.getNumeroMovimientos() << "\n";
        }
    } else {
        cout << "  (No hay enemigos adicionales en la sala del jefe)\n";
    }
}

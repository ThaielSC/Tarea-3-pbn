#include "game.h"
#include <iostream>
#include <cctype>
#include "../utils/readcsv.h"

// Constructor para el menú
Game::Game(string dungeon_path, string enemys_path) 
    : mazmorra(nullptr), jugador(nullptr), gameOver(false), llaves(0), llavejefe(false) {
    dungeons = leerMazmorras(dungeon_path);
    if (dungeons.empty()) {
        throw runtime_error("No se pudieron cargar las mazmorras");
    }
    this->enemys_path = enemys_path;
}

// Constructor para el juego
Game::Game(Mazmorra* maz, Jugador* jug) 
    : mazmorra(maz), jugador(jug), gameOver(false), llaves(0), llavejefe(false) {}

vector<Mazmorra>& Game::get_dungeons() {
    if (dungeons.empty()) {
        throw runtime_error("No hay mazmorras cargadas");
    }
    return dungeons;
}

void Game::limpiarPantalla() const {
    system("clear");
}

void Game::mostrarEstado() const {
    std::cout << "=============================" << std::endl;
    std::cout << "Mapa:" << std::endl;
    mazmorra->mostrar();
    std::cout << std::endl << std::endl;
    
    std::cout << "=============================" << std::endl;
    std::cout << std::endl;
    
    // Mostrar información del jugador
    std::cout << "Dirección actual: ";
    switch(jugador->getDireccionActual()) {
        case 'N': std::cout << "ARRIBA"; break;
        case 'S': std::cout << "ABAJO"; break;
        case 'E': std::cout << "DERECHA"; break;
        case 'O': std::cout << "IZQUIERDA"; break;
    }
    std::cout << std::endl;
    
    std::cout << "Vida: " << jugador->getVida() << std::endl;
    std::cout << "Llaves: " << llaves << std::endl;
    std::cout << "Llave del jefe: " << (llavejefe ? "Sí" : "No") << std::endl;
    std::cout << "Habilidad (Z): Salto" << std::endl;
    std::cout << "Atacar (X): " << jugador->getDaño() << " daño, solo frente a enemigos" << std::endl;
    std::cout << "Actuar (C): Solo frente a puertas y cofres" << std::endl;
    std::cout << std::endl;
    std::cout << "Comando (WASD/Z/X/C, P para salir): ";
}

void Game::procesarComando(char comando) {
    comando = std::tolower(comando);
    
    switch(comando) {
        case 'w':
        case 'a':
        case 's':
        case 'd':
            jugador->procesarEntrada(comando);
            jugador->mover();
            break;
            
        case 'z':
            std::cout << "Habilidad no implementada aún" << std::endl;
            break;
            
        case 'x':
            jugador->procesarEntrada(comando);
            {
                std::string resultado = jugador->atacar();
                if (!resultado.empty()) {
                    std::cout << resultado << std::endl;
                }
            }
    break;
            
        case 'c':
            std::cout << "Interacción no implementada aún" << std::endl;
            break;
            
        case 'p':
            gameOver = true;
            break;
            
        default:
            std::cout << "Comando no válido" << std::endl;
    }
}

void Game::run() {
    if (!mazmorra || !jugador) {
        throw runtime_error("No se ha inicializado correctamente el juego");
    }

    char comando;
    while (!gameOver) {
        limpiarPantalla();
        mostrarEstado();
        
        if (!(std::cin >> comando)) {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            continue;
        }
        
        procesarComando(comando);
    }
}

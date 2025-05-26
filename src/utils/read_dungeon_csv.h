// src/utils/read_dungeon_csv.h
#ifndef READ_DUNGEON_CSV_H
#define READ_DUNGEON_CSV_H

#include "../classes/dungeon.h" // Ajusta la ruta si es necesario
#include <string>
#include <vector>

// Lee una lista de Dungeons desde un archivo CSV
std::vector<Dungeon> leerDungeonsDesdeCSV(const std::string &filePath);

#endif // READ_DUNGEON_CSV_H

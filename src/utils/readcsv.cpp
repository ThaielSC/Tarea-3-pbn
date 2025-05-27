#include "readcsv.h"
#include <fstream>
#include <iostream>
#include <string>

vector<string> read_csv(string filename) {
  ifstream file(filename);
  if (file.is_open()) {
    cout << "[INFO] Se abrio el archivo: " << filename << endl;
  } else {
    cerr << "[ERROR] No se pudo abrir el archivo: \n" << filename << endl;
  }

  string line;
  vector<string> lines;

  while (getline(file, line)) {
    lines.push_back(line);
  }

  file.close();
  return lines;
}

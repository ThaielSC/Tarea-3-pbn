#include "../src/utils/readcsv.h"
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

vector<vector<vector<string>>> parse_matrices(const string &line) {
  vector<vector<vector<string>>> result;
  vector<string> tokens;
  string token;

  // Tokenizamos la línea por comas
  stringstream ss(line);
  while (getline(ss, token, ',')) {
    if (!token.empty()) {
      tokens.push_back(token);
    }
  }

  size_t index = 0;
  while (index + 1 < tokens.size()) {
    // Paso 1: Leer n y m
    int n = stoi(tokens[index]);
    int m = stoi(tokens[index + 1]);
    index += 2;

    // Paso 2: Validar que hay suficientes elementos
    if (index + n * m > tokens.size()) {
      cerr << "[ERROR] Datos insuficientes para una matriz de " << n << "x" << m
           << endl;
      break;
    }

    // Paso 3: Construir la matriz
    vector<vector<string>> matrix;
    for (int i = 0; i < n; ++i) {
      vector<string> row;
      for (int j = 0; j < m; ++j) {
        row.push_back(tokens[index++]);
      }
      matrix.push_back(row);
    }

    result.push_back(matrix);
  }

  return result;
}

int main() {
  vector<string> lines = read_csv("./data/mazmorras.csv");

  cout << "[INFO] Total de líneas: " << lines.size() << endl;

  for (const string &line : lines) {
    // cout << "Línea: " << line << endl;
    auto matrices = parse_matrices(line);
    for (size_t i = 0; i < matrices.size(); ++i) {
      cout << "Matriz #" << i + 1 << ":\n";
      for (const auto &fila : matrices[i]) {
        for (const auto &valor : fila) {
          cout << valor << " ";
        }
        cout << endl;
      }
      cout << endl;
    }
  }

  return 0;
}

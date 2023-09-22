#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>

using namespace std;

// Función para realizar las sustituciones
string sustituciones(string texto) {
    replace(texto.begin(), texto.end(), 'j', 'i');
    replace(texto.begin(), texto.end(), 'h', 'i');
    replace(texto.begin(), texto.end(), '~', 'n');
    replace(texto.begin(), texto.end(), 'k', 'l');
    replace(texto.begin(), texto.end(), 'u', 'v');
    replace(texto.begin(), texto.end(), 'w', 'v');
    replace(texto.begin(), texto.end(), 'y', 'z');
    return texto;
}

// Función para eliminar las tildes
string eliminar_tildes(string texto) {
    string resultado;
    for (char c : texto) {
        if (static_cast<unsigned char>(c) <= 127) {
            resultado += c;
        }
    }
    return resultado;
}

// Función para convertir a mayúsculas
string convertir_mayusculas(string texto) {
    transform(texto.begin(), texto.end(), texto.begin(), ::toupper);
    return texto;
}

// Función para eliminar espacios en blanco y signos de puntuación
string eliminar_espacios_puntuacion(string texto) {
    string resultado;
    for (char c : texto) {
        if (isalnum(c)) {
            resultado += c;
        }
    }
    return resultado;
}

// Función para guardar el resultado en un archivo
void guardar_resultado(string texto, string nombre_archivo) {
    ofstream archivo(nombre_archivo);
    if (archivo.is_open()) {
        archivo << texto;
        archivo.close();
    } else {
        cerr << "Error al abrir el archivo." << endl;
    }
}

// Función para calcular las frecuencias de las letras
map<char, int> frecuencias(string archivo) {
    ifstream archivo_entrada(archivo);
    map<char, int> frecuencia_letras;
    char caracter;

    while (archivo_entrada >> caracter) {
        if (isalpha(caracter)) {
            caracter = toupper(caracter);
            frecuencia_letras[caracter]++;
        }
    }
    
    archivo_entrada.close();
    return frecuencia_letras;
}

// Función para obtener los cinco caracteres de mayor frecuencia
vector<pair<char, int>> obtener_top_cinco(map<char, int> frecuencias) {
    vector<pair<char, int>> frecuencias_vector(frecuencias.begin(), frecuencias.end());
    sort(frecuencias_vector.begin(), frecuencias_vector.end(),
         [](const pair<char, int>& a, const pair<char, int>& b) {
             return a.second > b.second;
         });
    return vector<pair<char, int>>(frecuencias_vector.begin(), frecuencias_vector.begin() + 5);
}

int main() {
    string texto_original = "Hay golpes en la vida, tan fuertes... ¡Yo no sé! Golpes como del odio de Dios; como si ante ellos, la resaca de todo lo sufrido se empozara en el alma... ¡Yo no sé! Son pocos; pero son... Abren zanjas oscuras en el rostro más fiero y en el lomo más fuerte. Serán tal vez los potros de bárbaros Atilas; o los heraldos negros que nos manda la Muerte. Son las caídas hondas de los Cristos del alma de alguna fe adorable que el Destino blasfema. Esos golpes sangrientos son las crepitaciones de algún pan que en la puerta del horno se nos quema. Y el hombre. . . Pobre. . . ¡pobre! Vuelve los ojos, como cuando por sobre el hombro nos llama una palmada; vuelve los ojos locos, y todo lo vivido se empoza, como charco de culpa, en la mirada. Hay golpes en la vida, tan fuertes. . . ¡Yo no sé!";

    // Aplicar preprocesamiento
    string resultado = sustituciones(texto_original);
    resultado = eliminar_tildes(resultado);
    resultado = convertir_mayusculas(resultado);
    resultado = eliminar_espacios_puntuacion(resultado);

    // Guardar el resultado en un archivo
    guardar_resultado(resultado, "HERALDOSNEGROS_pre.txt");

    // Calcular las frecuencias de las letras
    map<char, int> frecuencia_letras = frecuencias("HERALDOSNEGROS_pre.txt");

    // Obtener los cinco caracteres de mayor frecuencia
    vector<pair<char, int>> top_cinco = obtener_top_cinco(frecuencia_letras);

    cout << "Caracteres de mayor frecuencia:" << endl;
    for (const auto& par : top_cinco) {
        cout << par.first << ": " << par.second << " veces" << endl;
    }

    return 0;
}

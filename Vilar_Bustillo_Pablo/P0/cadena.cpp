#include "cadena.hpp"
using namespace std;

// CONSTRUCTORES
/**
 * @brief Constructor de la clase Cadena
 * @param tam Tamaño de la cadena
 * @param c Carácter con el que se rellenará la cadena
 * @post Se crea una cadena con el tamaño y el carácter especificados
 */
Cadena::Cadena(size_t tam, char c) : s_(new char[c+1]), tam_(tam)
{
    while(tam --> 0)
        s_[tam] = c;
    s_[tam_] = '\0';
}

/**
 * @brief Constructor de copia de la clase Cadena
 * @param c Cadena a copiar
 * @post Se crea una cadena con el tamaño y el contenido de la cadena a copiar
 */
Cadena::Cadena(const Cadena& c) : s_(new char[c.tam_+1]), tam_(c.tam_) {
    copiar(c);
}
/**
 * @brief Constructor de conversión de la clase Cadena
 * @param c Cadena de caracteres
 * @post Se crea una cadena con el tamaño de la cadena de caracteres
 */
Cadena::Cadena(const char* c) : s_(new char[length(c)+1]), tam_(length(c)){
    copiar(c);
}

/**
 * @brief Constructor de movimiento de la clase Cadena
 * @param c Cadena a mover
 * @post Se crea una cadena con el tamaño y el contenido de la cadena a mover
 */
Cadena::Cadena(Cadena && c)  noexcept : s_(c.s_), tam_(c.tam_) {
    c.s_ = nullptr;
    c.tam_ = 0;
}

// DESTRUCTOR
/**
 * @brief Destructor de la clase Cadena
 * @post Se libera la memoria reservada para la cadena
 */
Cadena::~Cadena() {
    tam_ = 0;
    delete[] s_;
}

/**
 * @brief Operador de la clase Cadena
 * @return devuelve la cadena de caracteres
 */
Cadena::operator const char *() const {return s_;}

// FUNCIONES
/**
 * @brief Calcula el tamaño de una cadena
 * @param c Cadena de caracteres
 * @return Tamaño de la cadena
 */
size_t Cadena::length(const char *c) noexcept {
    size_t i = 0;
    while(c[i]) i++;
    return i;
}

/**
 * @brief Calcula el tamaño de una cadena
 * @param c Cadena de caracteres
 * @return Tamaño de la cadena
 */
size_t Cadena::length(const char *c) const noexcept {
    size_t i = 0;
    while(c[i]) i++;
    return i;
}

// OPERADORES ARITMÉTICOS
/**
 * @brief Concatenacion de 2 cadenas, copia en la primera
 * @param c Cadena a concatenar
 * @return Cadena concatenada
 */
Cadena Cadena::operator+=(const Cadena &c) {
    char *cad_aux = new char[tam_ + 1];
    strcpy(cad_aux, s_);
    tam_ += c.tam_;
    delete[] s_;

    s_ = new char[tam_ + 1];
    strcpy(s_, cad_aux);
    strcat(s_, c.s_);
    s_[tam_] = '\0';
    delete[] cad_aux;
    return *this;
}

/**
 * @brief Concatenacion de una cadena y una cadena de caracteres, copia en la primera
 * @param c Cadena de caracteres a concatenar
 * @return Cadena concatenada
 */
Cadena Cadena::operator+=(const char* c) {
    char *cad_aux = new char[tam_ + 1];
    strcpy(cad_aux, s_);
    tam_ += length(c);
    delete[] s_;

    s_ = new char[tam_ + 1];
    strcpy(s_, cad_aux);
    strcat(s_, c);
    s_[tam_] = '\0';
    delete[] cad_aux;
    return *this;
}

// OPERADORES DE ASIGNACIÓN
/**
 * @brief Asignación de una cadena a otra
 * @param c Cadena a asignar
 * @return Cadena asignada
 */
 Cadena& Cadena::operator=(const Cadena &c) {
     if(*this != c) copiar(c);
     return *this;
 }

/**
 * @brief Asignación de una cadena de caracteres a una cadena
 * @param c Cadena de caracteres a asignar
 * @return Cadena asignada
 */
 Cadena& Cadena::operator=(const char* c) {
     Cadena aux(c);
     if (*this != aux) copiar(c);
     return *this;
 }

/**
 * @brief Asignación de una cadena de caracteres a una cadena
 * @param c Cadena de caracteres a asignar
 * @return Cadena asignada
 */
Cadena& Cadena::operator=(Cadena&& c) {
    tam_ = c.tam_;
    delete[] s_;
    s_ = c.s_;
    c.s_ = nullptr;
    c.tam_ = 0;
    return *this;
}

// OPERADORES DE INDICE
/**
 * @brief Operador de acceso a un elemento de la cadena
 * @param i Posición del elemento
 * @return Elemento de la cadena
 */
char& Cadena::operator[](size_t i) noexcept {
    return s_[i];
}

/**
 * @brief Operador de acceso a un elemento de la cadena
 * @param i Posición del elemento
 * @return Elemento de la cadena
 */
const char& Cadena::operator[](size_t i) const noexcept {
    return s_[i];
}

/**
 * @brief Operador de acceso a un elemento de la cadena con comprobación de rango
 * @param i Posición del elemento
 * @return Elemento de la cadena
 * @throw std::out_of_range Indice fuera de rango
 */
char& Cadena::at(size_t i) {
    if(i >= tam_) throw std::out_of_range("Indice fuera de rango");
    return s_[i];
}

/**
 * @brief Operador de acceso a un elemento de la cadena con comprobación de rango
 * @param i Posición del elemento
 * @return Elemento de la cadena
 * @throw std::out_of_range Indice fuera de rango
 */
const char& Cadena::at(size_t i) const {
    if(i >= tam_) throw std::out_of_range("Indice fuera de rango");
    return s_[i];
}

/**
 * @brief Operador de subcadena de la cadena
 * @param i
 * @param fin
 * @return Subcadena de la cadena comprendida entre i y fin
 */
Cadena Cadena::substr(size_t i, size_t fin) const {
    if(i > tam_ || fin > tam_ || (i + fin) > tam_)
        throw std::out_of_range("Indice fuera de rango");

    char* aux = new char[fin + 1];
    size_t j = 0;
    while (j < fin) {
        aux[j] = s_[i + j];
        j++;
    }
    aux[fin] = '\0';
    Cadena cad_res(aux);
    delete []aux;
    return cad_res;
}

// FUNCIONES AUXILIARES PRIVADAS
/**
 * @brief Copia una cadena en otra
 * @param c Cadena a copiar
 * @post Se copia la cadena en la cadena actual
 */
void Cadena::copiar(const Cadena& c) {
    tam_ = c.tam_;
    delete[] s_;
    s_ = new char[tam_ + 1];
    strcpy(s_, c.s_);
}

/**
 * @brief Copia una cadena de caracteres en una cadena
 * @param c Cadena de caracteres a copiar
 * @post Se copia la cadena de caracteres en la cadena actual
 */
void Cadena::copiar(const char* c) {
    tam_ = length(c);
    delete[] s_;
    s_ = new char[tam_ + 1];
    strcpy(s_, c);
}

// OPERADORES ARITMÉTICOS
/**
 * @brief Concatenación de 2 cadenas
 * @param c1 Cadena a concatenar
 * @param c2 Cadena a concatenar
 * @return Cadena concatenada
 */
Cadena operator+(const Cadena& c1, const Cadena& c2) {
    Cadena aux(c1);
    aux += c2;
    return aux;
}

// OPERADORES LÓGICOS
/**
 * @brief Comprueba si 2 cadenas de la Clase Cadena son iguales
 * @param c1 Cadena a comparar de tipo Cadena
 * @param c2 Cadena a comparar de tipo Cadena
 * @return true si las cadenas son iguales, false en caso contrario
 */
bool operator==(const Cadena& c1, const Cadena& c2) {
    return (strcmp(c1.c_str(), c2.c_str()) == 0);
}

/**
 * @brief Comprueba si 1 cadena de la Clase Cadena y otra de tipo char* son iguales
 * @param c1 Cadena a comparar de tipo Cadena
 * @param c2 Cadena a comparar de tipo char*
 * @return true si las cadenas son iguales, false en caso contrario
 */

bool operator==(const Cadena& c1, const char* c2) {
    return (strcmp(c1.c_str(), c2) == 0);
}

/**
 * @brief Comprueba si 1 cadena de la Clase Cadena y otra de tipo char* son iguales
 * @param c1 Cadena a comparar de tipo char*
 * @param c2 Cadena a comparar de tipo Cadena
 * @return true si las cadenas son iguales, false en caso contrario
 */

bool operator==(const char* c1, const Cadena& c2) {
    return (strcmp(c1, c2.c_str()) == 0);
}

/**
 * @brief Comprueba si 2 cadenas de la Clase Cadena son distintas
 * @param c1 Cadena de tipo Cadena a comparar
 * @param c2 Cadena de tipo Cadena a comparar
 * @return true si las cadenas son distintas, false en caso contrario
 */
bool operator!=(const Cadena& c1, const Cadena& c2) {
    return !(c1 == c2);
}

/**
 * @brief Comprueba si 1 cadena de la Clase Cadena y otra de tipo char* son distintas
 * @param c1 Cadena de tipo Cadena a comparar
 * @param c2 Cadena de tipo char* a comparar
 * @return true si las cadenas son distintas, false en caso contrario
 */
bool operator!=(const Cadena& c1, const char* c2) {
    return !(c1 == c2);
}

/**
 * @brief Comprueba si 1 cadena de la Clase Cadena y otra de tipo char* son distintas
 * @param c1 Cadena de tipo char* a comparar
 * @param c2 Cadena de tipo Cadena a comparar
 * @return true si las cadenas son distintas, false en caso contrario
 */
bool operator!=(const char* c1, const Cadena& c2) {
    return !(c1 == c2);
}

/**
 * @brief Comprueba si una cadena de la Clase Cadena es menor que otra de la misma Clase
 * @param c1 Cadena a comparar de tipo Cadena
 * @param c2 Cadena a comparar de tipo Cadena
 * @return true si la cadena c1 es menor que la cadena c2, false en caso contrario
 */
bool operator<(const Cadena& c1, const Cadena& c2) {
    if (c1.length() < c2.length()) return true;
    else if (c1.length() > c2.length()) return false;
    else return (strcmp(c1.c_str(), c2.c_str()) < 0);
}

/**
 * @brief Comprueba si una cadena de la Clase Cadena es menor que otra de tipo char*
 * @param c1 Cadena a comparar de tipo Cadena
 * @param c2 Cadena a comparar de tipo char*
 * @return true si la cadena c1 es menor que la cadena c2, false en caso contrario
 */
bool operator<(const Cadena& c1, const char* c2) {
    if (c1.length() < strlen(c2)) return true;
    else if (c1.length() > strlen(c2)) return false;
    else return (strcmp(c1.c_str(), c2) < 0);
}

/**
 * @brief Comprueba si una cadena de tipo char* es menor que otra de la Clase Cadena
 * @param c1 Cadena a comparar de tipo char*
 * @param c2 Cadena a comparar de tipo Cadena
 * @return true si la cadena c1 es menor que la cadena c2, false en caso contrario
 */
bool operator<(const char* c1, const Cadena& c2) {
    if (strlen(c1) < c2.length()) return true;
    else if (strlen(c1) > c2.length()) return false;
    else return (strcmp(c1, c2.c_str()) < 0);
}

/**
 * @brief Comprueba si una cadena de la Clase Cadena es mayor que otra de la misma Clase
 * @param c1 Cadena a comparar de tipo Cadena
 * @param c2 Cadena a comparar de tipo Cadena
 * @return true si la cadena c1 es mayor que la cadena c2, false en caso contrario
 */
bool operator>(const Cadena& c1, const Cadena& c2) {
    return c2 < c1;
}

/**
 * @brief Comprueba si una cadena de la Clase Cadena es mayor que otra de tipo char*
 * @param c1 Cadena a comparar de tipo Cadena
 * @param c2 Cadena a comparar de tipo char*
 * @return true si la cadena c1 es mayor que la cadena c2, false en caso contrario
 */
bool operator>(const Cadena& c1, const char* c2) {
    return c2 < c1;
}

/**
 * @brief Comprueba si una cadena de tipo char* es mayor que otra de la Clase Cadena
 * @param c1 Cadena a comparar de tipo char*
 * @param c2 Cadena a comparar de tipo Cadena
 * @return true si la cadena c1 es mayor que la cadena c2, false en caso contrario
 */
bool operator>(const char* c1, const Cadena& c2) {
    return c2 < c1;
}

/**
 * @brief Comprueba si una cadena de la Clase Cadena es menor o igual que otra de la misma Clase
 * @param c1 Cadena a comparar de tipo Cadena
 * @param c2 Cadena a comparar de tipo Cadena
 * @return true si la cadena c1 es menor o igual que la cadena c2, false en caso contrario
 */

bool operator<=(const Cadena& c1, const Cadena& c2) {
    return !(c2 < c1);
}

/**
 * @brief Comprueba si una cadena de la Clase Cadena es menor o igual que otra de tipo char*
 * @param c1 Cadena a comparar de tipo Cadena
 * @param c2 Cadena a comparar de tipo char*
 * @return true si la cadena c1 es menor o igual que la cadena c2, false en caso contrario
 */
bool operator<=(const Cadena& c1, const char* c2) {
    return !(c2 < c1);
}

/**
 * @brief Comprueba si una cadena de tipo char* es menor o igual que otra de la Clase Cadena
 * @param c1 Cadena a comparar de tipo char*
 * @param c2 Cadena a comparar de tipo Cadena
 * @return true si la cadena c1 es menor o igual que la cadena c2, false en caso contrario
 */
bool operator<=(const char* c1, const Cadena& c2) {
    return !(c2 < c1);
}

/**
 * @brief Comprueba si una cadena de la Clase Cadena es mayor o igual que otra de la misma Clase
 * @param c1 Cadena a comparar de tipo Cadena
 * @param c2 Cadena a comparar de tipo Cadena
 * @return true si la cadena c1 es mayor o igual que la cadena c2, false en caso contrario
 */
bool operator>=(const Cadena& c1, const Cadena& c2) {
    return !(c1 < c2);
}

/**
 * @brief Comprueba si una cadena de la Clase Cadena es mayor o igual que otra de tipo char*
 * @param c1 Cadena a comparar de tipo Cadena
 * @param c2 Cadena a comparar de tipo char*
 * @return true si la cadena c1 es mayor o igual que la cadena c2, false en caso contrario
 */
bool operator>=(const Cadena& c1, const char* c2) {
    return !(c1 < c2);
}

/**
 * @brief Comprueba si una cadena de tipo char* es mayor o igual que otra de la Clase Cadena
 * @param c1 Cadena a comparar de tipo char*
 * @param c2 Cadena a comparar de tipo Cadena
 * @return true si la cadena c1 es mayor o igual que la cadena c2, false en caso contrario
 */
bool operator>=(const char* c1, const Cadena& c2) {
    return !(c1 < c2);
}
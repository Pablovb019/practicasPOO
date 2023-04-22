#ifndef CADENA_HPP
#define CADENA_HPP

#include <functional>
#include <iterator>
#include <iostream>
#include <cstring>
#include <stdexcept>

class Cadena{
public:
    // CONSTRUCTORES
    explicit Cadena(size_t tam = 0, char c = ' ');
    Cadena(const Cadena& c); // Constructor de copia
    Cadena(const char* c); // Constructor de conversión
    Cadena(Cadena&& c) noexcept;  // Constructor de movimiento
    operator const char* () const;

    // DESTRUCTOR
    ~Cadena();

    // OBSERVADORES
    const char* puts() { return s_; };
    const char* puts() const { return s_; };

    // FUNCIONES
    size_t length() noexcept { return tam_; };
    size_t length() const noexcept { return tam_; };
    size_t length(const char* c) noexcept;
    size_t length(const char* c) const noexcept;
    const char* c_str() const noexcept { return s_; };

    // OPERADORES ARITMÉTICOS
    Cadena operator+=(const Cadena& c);
    Cadena operator+=(const char* c);

    // OPERADORES DE ASIGNACIÓN
    Cadena& operator=(const Cadena& c);
    Cadena& operator=(const char* c);
    Cadena& operator= (Cadena&& c);

    // OPERADORES DE INDICE
    char& operator[](size_t i) noexcept;
    const char& operator[](size_t i) const noexcept;
    char& at(size_t i);
    const char& at(size_t i) const;
    Cadena substr(size_t i, size_t fin) const;


private:
    char * s_;
    size_t tam_;

    // FUNCIONES AUXILIARES
    void copiar(const Cadena& c);
    void copiar(const char* c);
};

// OPERADORES ARITMÉTICOS
Cadena operator+(const Cadena& c1, const Cadena& c2);

// OPERADORES LÓGICOS
bool operator==(const Cadena& c1, const Cadena& c2);
bool operator==(const Cadena& c1, const char* c2);
bool operator==(const char* c1, const Cadena& c2);

bool operator!=(const Cadena& c1, const Cadena& c2);
bool operator!=(const Cadena& c1, const char* c2);
bool operator!=(const char* c1, const Cadena& c2);

bool operator<(const Cadena& c1, const Cadena& c2);
bool operator<(const Cadena& c1, const char* c2);
bool operator<(const char* c1, const Cadena& c2);

bool operator>(const Cadena& c1, const Cadena& c2);
bool operator>(const Cadena& c1, const char* c2);
bool operator>(const char* c1, const Cadena& c2);

bool operator<=(const Cadena& c1, const Cadena& c2);
bool operator<=(const Cadena& c1, const char* c2);
bool operator<=(const char* c1, const Cadena& c2);

bool operator>=(const Cadena& c1, const Cadena& c2);
bool operator>=(const Cadena& c1, const char* c2);
bool operator>=(const char* c1, const Cadena& c2);

#endif
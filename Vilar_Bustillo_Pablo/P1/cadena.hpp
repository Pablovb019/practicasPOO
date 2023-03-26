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
    explicit Cadena(const char* c); // Constructor de conversión
    Cadena(Cadena&& c);  // Constructor de movimiento
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

    // ITERADORES
    typedef char* iterator;
    typedef const char* const_iterator;
    typedef std::reverse_iterator<iterator> reverse_iterator;
    typedef std::reverse_iterator<const_iterator> const_reverse_iterator;

    // FUNCIONES ITERADORES
    iterator begin() noexcept { return s_; };
    const_iterator begin() const noexcept { return const_iterator(s_); };
    const_iterator cbegin() const noexcept { return const_iterator(s_); };
    reverse_iterator rbegin() noexcept { return reverse_iterator(end()); };
    const_reverse_iterator rbegin() const noexcept { return const_reverse_iterator(end()); };
    const_reverse_iterator crbegin() const noexcept { return const_reverse_iterator(end()); };
    iterator end() noexcept { return s_ + tam_; };
    const_iterator end() const noexcept { return const_iterator(s_ + tam_); };
    const_iterator cend() const noexcept { return const_iterator(s_ + tam_); };
    reverse_iterator rend() noexcept { return reverse_iterator(begin()); };
    const_reverse_iterator rend() const noexcept { return const_reverse_iterator(begin()); };
    const_reverse_iterator crend() const noexcept { return const_reverse_iterator(begin()); };

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

// OPERADORES DE FLUJO
std::ostream& operator<<(std::ostream& os, const Cadena& c);
std::istream& operator>>(std::istream& is, Cadena& c);
#endif
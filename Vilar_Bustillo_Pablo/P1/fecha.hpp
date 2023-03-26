#ifndef FECHA_HPP
#define FECHA_HPP

#include <iostream>
#include <iomanip>
#include <cstdio>
#include <ctime>

class Fecha{
public:
    // CONSTANTES
    static const int AnnoMinimo = 1902;
    static const int AnnoMaximo = 2037;

    // CLASE DE EXCEPCION 'INVALIDA'
    class Invalida: public std::exception{
    public:
        Invalida(const char* error) : error_(error) {}
        const char* por_que() const { return error_; }
    private:
        const char* error_;
    };

    // CONSTRUCTORES
    explicit Fecha(int dia = 0, int mes = 0, int anno = 0);
    Fecha(const char* c);
    const char* cadena() const; // Conversion a cadena

    // OBSERVADORES
    int dia() const noexcept { return dia_; }
    int mes() const noexcept { return mes_; }
    int anno() const noexcept { return anno_; }

    // OPERADORES
    Fecha& operator +=(int dias); // suma de días
    Fecha& operator -=(int dias); // resta de días
    Fecha& operator ++(); // preincremento
    Fecha operator ++(int); // postincremento
    Fecha& operator --(); // predecremento
    const Fecha operator --(int); // postdecremento

    //OPERADORES ARITMÉTICOS
    Fecha operator+ (int dias) const; // suma de días con const
    Fecha operator- (int dias) const; // resta de días con const

private:
    int dia_, mes_, anno_;

    // FUNCIONES PRIVADAS
    bool comprobar() const;
    void actualizarFecha();
    int diasMes(int mes) const;
};

// OPERADORES LÓGICOS
bool operator ==(const Fecha& f1, const Fecha& f2) noexcept; // Operador de igualdad
bool operator !=(const Fecha& f1, const Fecha& f2) noexcept; // Operador de desigualdad
bool operator <(const Fecha& f1, const Fecha& f2) noexcept; // Operador de menor que
bool operator >(const Fecha& f1, const Fecha& f2) noexcept; // Operador de mayor que
bool operator <=(const Fecha& f1, const Fecha& f2) noexcept; // Operador de menor o igual que
bool operator >=(const Fecha& f1, const Fecha& f2) noexcept; // Operador de mayor o igual que

// OPERADORES DE FLUJO
std::ostream& operator <<(std::ostream& os, const Fecha& f);
std::istream& operator >>(std::istream& is, Fecha& f);

#endif
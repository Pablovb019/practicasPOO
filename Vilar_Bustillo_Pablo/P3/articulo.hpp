#ifndef ARTICULO_HPP
#define ARTICULO_HPP

#include "../P1/fecha.hpp"
#include "../P1/cadena.hpp"

class Articulo{
public:
    // CONSTRUCTOR
    Articulo(const Cadena& referencia, const Cadena& titulo, const Fecha& f_publi, double precio, unsigned stock);

    // OBSERVADORES
    const Cadena& referencia() const { return referencia_; }
    const Cadena& titulo() const { return titulo_; }
    const Fecha& f_publi() const { return f_publi_; }
    double precio() const { return precio_; }
    unsigned stock() const { return stock_; }

    double& precio() { return precio_; } // Sobrecarga para permitir modificación del precio
    unsigned& stock() { return stock_; } // Sobrecarga para permitir modificación del stock
private:
    Cadena referencia_;
    Cadena titulo_;
    Fecha f_publi_;
    double precio_;
    unsigned stock_;
};

std::ostream &operator<<(std::ostream &os, const Articulo& a);
#endif

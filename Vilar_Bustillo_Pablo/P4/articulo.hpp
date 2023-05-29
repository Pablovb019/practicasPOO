#ifndef ARTICULO_HPP
#define ARTICULO_HPP

#include "../P1/fecha.hpp"
#include "../P1/cadena.hpp"
#include <set>

class Autor{
public:
    // CONSTRUCTOR
    Autor(const Cadena& nombre, const Cadena& apellidos, const Cadena& direccion);

    // OBSERVADORES
    const Cadena& nombre() const noexcept { return nombre_; }
    const Cadena& apellidos() const noexcept { return apellidos_; }
    const Cadena& direccion() const noexcept { return direccion_; }
private:
    Cadena nombre_;
    Cadena apellidos_;
    Cadena direccion_;
};

class Articulo{
public:
    typedef std::set<Autor*> Autores;
    // CONSTRUCTOR
    Articulo(const Autores& autor,const Cadena& referencia, const Cadena& titulo, const Fecha& f_publi, double precio);

    // OBSERVADORES
    const Autores& autores() const { return autores_; }
    const Cadena& referencia() const { return referencia_; }
    const Cadena& titulo() const { return titulo_; }
    const Fecha& f_publi() const { return f_publi_; }
    double precio() const { return precio_; }
    double& precio() { return precio_; } // Sobrecarga para permitir modificación del precio

    // CLASE DE EXCEPCION 'AUTORES_VACIOS'
    class Autores_vacios: public std::exception {};

    // MÉTODOS VIRUTALES
    virtual void impresion_especifica(std::ostream& os) const = 0;
    virtual ~Articulo() {}

private:
    const Autores autores_;
    Cadena referencia_;
    Cadena titulo_;
    Fecha f_publi_;
    double precio_;
};

class ArticuloAlmacenable:public Articulo{
public:
    // CONSTRUCTOR
    ArticuloAlmacenable(const Autores& autor,const Cadena& referencia, const Cadena& titulo, const Fecha& f_publi, double precio, unsigned int stock = 0);

    // OBSERVADORES
    unsigned int stock() const { return stock_; }
    unsigned int& stock() { return stock_; }
protected:
    unsigned int stock_;
};

class LibroDigital:public Articulo{
public:
    // CONSTUCTOR
    LibroDigital(const Autores& autor,const Cadena& referencia, const Cadena& titulo, const Fecha& f_publi, double precio, const Fecha& f_expir);

    // OBSERVADORES
    const Fecha& f_expir() const { return f_expir_; }

    // MÉTODOS VIRTUALES
    void impresion_especifica(std::ostream& os) const;
private:
    const Fecha f_expir_;
};

class Libro:public ArticuloAlmacenable{
public:
    // CONSTRUCTOR
    Libro(const Autores& autor,const Cadena& referencia, const Cadena& titulo, const Fecha& f_publi, double precio, unsigned int n_pag, unsigned int stock = 0);

    // OBSERVADORES
    unsigned int n_pag() const { return n_pag_; }

    // MÉTODOS VIRTUALES
    void impresion_especifica(std::ostream& os) const;
private:
    const unsigned int n_pag_;
};

class Revista:public ArticuloAlmacenable{
public:
    // CONSTRUCTOR
    Revista(const Autores& autor,const Cadena& referencia, const Cadena& titulo, const Fecha& f_publi, double precio, unsigned int numero, unsigned int periodicidad, unsigned int stock = 0);

    // OBSERVADORES
    unsigned int numero() const { return numero_; }
    unsigned int periodicidad() const { return periodicidad_; }

    // MÉTODOS VIRTUALES
    void impresion_especifica(std::ostream& os) const;
private:
    const unsigned int numero_;
    const unsigned int periodicidad_;
};

std::ostream &operator<<(std::ostream &os, const Articulo& a);
#endif

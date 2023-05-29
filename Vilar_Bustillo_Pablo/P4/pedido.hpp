#ifndef PEDIDO_HPP
#define PEDIDO_HPP


#include "tarjeta.hpp"
#include "usuario-pedido.hpp"
#include "pedido-articulo.hpp"

class Pedido_Articulo;
class Tarjeta;
class Usuario_Pedido;

#include <iomanip>
#include <iostream>

class Pedido {
public:
    // CONSTRUCTOR
    Pedido(Usuario_Pedido& up, Pedido_Articulo& pa, Usuario& u, const Tarjeta& t, const Fecha& f = Fecha());

    // OBSERVADORES
    unsigned int numero() const { return num_pedido_; }
    const Tarjeta* tarjeta() const { return tarjeta_; }
    Fecha fecha() const { return f_pedido_; }
    double total() const { return importe_; }
    static unsigned n_total_pedidos() { return N_pedidos_; }

    // CLASE DE EXCEPCION 'VACIO'

    class Vacio: public std::exception {
    public:
        Vacio(Usuario* u) : usuario_(u) {}
        Usuario& usuario() const { return *usuario_; }
    private:
        Usuario* usuario_;
    };

    // CLASE DE EXCEPCION 'IMPOSTOR'
    class Impostor: public std::exception {
    public:
        Impostor(Usuario* u) : usuario_(u) {}
        Usuario& usuario() const { return *usuario_; }
    private:
        Usuario* usuario_;
    };

    // CLASE DE EXCEPCION 'SIN_STOCK'
    class SinStock: public std::exception {
    public:
        SinStock(Articulo* a) : articulo_(a) {}
        Articulo& articulo() const { return *articulo_; }
    private:
        Articulo* articulo_;
    };

private:
    int num_pedido_;
    const Tarjeta* tarjeta_;
    Fecha f_pedido_;
    double importe_;
    static unsigned N_pedidos_;
};

std::ostream& operator <<(std::ostream& os, const Pedido& p);

#endif

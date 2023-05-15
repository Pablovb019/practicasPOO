#ifndef PEDIDO_ARTICULO_HPP
#define PEDIDO_ARTICULO_HPP

#include "articulo.hpp"
#include "pedido.hpp"

#include <iostream>
#include <iomanip>

class LineaPedido {
public:
    // CONSTRUCTOR
    explicit LineaPedido(double precio_venta, unsigned cantidad=1) : precio_venta_(precio_venta), cantidad_(cantidad) {}

    // OBSERVADORES
    double precio_venta() const noexcept { return precio_venta_; }
    unsigned cantidad() const noexcept { return cantidad_; }
private:
    double precio_venta_;
    unsigned cantidad_;
};

std::ostream& operator<<(std::ostream& os, const LineaPedido& lp);

class Pedido;
class Articulo;

class OrdenaPedidos: public std::binary_function<Pedido*, Pedido*, bool> {
public:
    bool operator()(const Pedido* p1, const Pedido* p2) const;
};

class OrdenaArticulos: public std::binary_function<Articulo*, Articulo*, bool> {
public:
    bool operator()(const Articulo* a1, const Articulo* a2) const { return a1->referencia() < a2->referencia(); }
};

class Pedido_Articulo {
public:
    // LIBRERIAS
    typedef std::map<Articulo*, LineaPedido, OrdenaArticulos> ItemsPedido;
    typedef std::map<Pedido*, LineaPedido, OrdenaPedidos> Pedidos;
    typedef std::map<Pedido*, ItemsPedido, OrdenaPedidos> PedArt;
    typedef std::map<Articulo*, Pedidos, OrdenaArticulos> ArtPed;

    // OBSERVADORES

    // SUBORSERVADOR 'PEDIR'
    void pedir(Pedido& p, Articulo& a, double precio, unsigned cantidad = 1);
    void pedir(Articulo& a, Pedido& p, double precio, unsigned cantidad = 1);

    // SUBOBSERVADOR 'DETALLE'
    ItemsPedido detalle(const Pedido& p) const;

    // SUBOBSERVADOR 'VENTAS'
    Pedidos ventas(const Articulo& a) const;

    std::ostream& mostrarDetallePedidos(std::ostream& os) const noexcept;
    std::ostream& mostrarVentasArticulos(std::ostream& os) const noexcept;

private:
    PedArt ped_art_;
    ArtPed art_ped_;
};

std::ostream& operator<<(std::ostream& os, const Pedido_Articulo::ItemsPedido& ip);
std::ostream& operator<<(std::ostream& os, const Pedido_Articulo::Pedidos& p);

#endif

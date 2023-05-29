#include "pedido-articulo.hpp"
using namespace std;

/**
 * @brief Operador de la clase OrdenaPedidos
 * @param p1 Pedido 1
 * @param p2 Pedido 2
 * @return Devuelve true si el numero del pedido 1 es menor que el numero del pedido 2
 */
bool OrdenaPedidos::operator()(const Pedido *p1, const Pedido *p2) const {
    return p1->numero() < p2->numero();
}

/**
 * @brief Operador de insercion de flujo
 * @details Muestra el detalle de los pedidos
 * @param os Flujo de salida
 * @param lp Linea de pedido
 * @return Flujo de salida
 */
std::ostream &operator<<(std::ostream &os, const LineaPedido &lp) {
    os << fixed << setprecision(2) << lp.precio_venta() << " €\t" << lp.cantidad();
    return os;
}

/**
 * @brief Subobservador 'PEDIR'
 * @details Añade un articulo a un pedido
 * @param p Pedido
 * @param a Articulo
 * @param precio Precio del articulo
 * @param cantidad Cantidad de articulos
 */
 void Pedido_Articulo::pedir(Pedido &p, Articulo &a, double precio, unsigned cantidad) {
    ped_art_[&p].insert(make_pair(&a, LineaPedido(precio, cantidad)));
    art_ped_[&a].insert(make_pair(&p, LineaPedido(precio, cantidad)));
 }

 /**
  * @brief Subobservador 'PEDIR'
  * @details Añade un articulo a un pedido
  * @param a Articulo
  * @param p Pedido
  * @param precio Precio del articulo
  * @param cantidad Cantidad de articulos
  */

 void Pedido_Articulo::pedir(Articulo &a, Pedido &p, double precio, unsigned cantidad) {
     pedir(p, a, precio, cantidad);
 }

 /**
  * @brief Subobservador 'DETALLE'
  * @details Muestra el detalle de un pedido
  * @param p Pedido
  * @return Devuelve el detalle de un pedido
  */
Pedido_Articulo::ItemsPedido Pedido_Articulo::detalle(const Pedido &p) const {
    auto it = ped_art_.find((Pedido*) &p);
    if(it != ped_art_.end()) {
        return it->second;
    } else {
        Pedido_Articulo::ItemsPedido vacio;
        return vacio;
    }
}

/**
 * @brief Subobservador 'VENTAS'
 * @details Muestra las ventas de un articulo
 * @param a Articulo
 * @return Devuelve las ventas de un articulo
 */
Pedido_Articulo::Pedidos Pedido_Articulo::ventas(const Articulo &a) const {
    auto it = art_ped_.find((Articulo*) &a);
    if(it != art_ped_.end()) {
        return it->second;
    } else {
        Pedido_Articulo::Pedidos vacio;
        return vacio;
    }
}

/**
 * @brief Operador de insercion de flujo
 * @details Muestra el detalle de los pedidos
 * @param os Flujo de salida
 * @param pa Pedido_Articulo
 * @return Flujo de salida
 */
ostream &Pedido_Articulo::mostrarDetallePedidos(ostream &os) const noexcept {
    double total = 0.0;
    for (auto &it: ped_art_) {
        os << "Pedido núm. " << it.first->numero();
        os << "\tCliente: " << it.first->tarjeta()->titular()->nombre() << " \n";
        os << "Fecha: " << it.first->fecha() << endl;
        os << detalle(*it.first);
        total += it.first->total();
    }

    os << "TOTAL VENTAS\t" << fixed << setprecision(2) << total << " €" << endl;
    return os;
}

/**
 * @brief Operador de insercion de flujo
 * @details Muestra las ventas de los articulos
 * @param os Flujo de salida
 * @param pa Pedido_Articulo
 * @return Flujo de salida
 */
ostream &Pedido_Articulo::mostrarVentasArticulos(ostream &os) const noexcept {
    for (auto &it: art_ped_) {
        os << "Ventas de [" << it.first->referencia() << "]";
        os << " \"" << it.first->titulo() << endl;
        os << ventas(*it.first);
    }
    return os;
}

/**
 * @brief Operador de insercion de flujo
 * @details Muestra el detalle de los pedidos
 * @param os Flujo de salida
 * @param lp Linea de pedido
 * @return Flujo de salida
 */
ostream& operator <<(ostream& os, const Pedido_Articulo::ItemsPedido& ip){
    double total = 0.0;

    os << endl << "====================================================\n" << endl;
    os << " PVP\tCantidad\tArticulo\n" << endl;
    os << "====================================================\n" << endl;

    for (auto& cit: ip) {
        os << fixed << setprecision(2) << cit.second.precio_venta() << " €\t" << cit.second.cantidad() << "\t\t";
        os << "[" << cit.first->referencia() << "] " << cit.first->titulo() << endl;
        total += (cit.second.precio_venta() * cit.second.cantidad());
    }

    os << "====================================================\n" << endl;
    os << "Total\t" << fixed << setprecision(2) << total << " €" << endl;

    return os;
 }

 /**
  * @brief Operador de insercion de flujo
  * @details Muestra las ventas de los articulos
  * @param os Flujo de salida
  * @param p Pedido
  * @return Flujo de salida
  */
ostream& operator <<(ostream& os, const Pedido_Articulo::Pedidos& p){
    double precio = 0.0;
    unsigned cantidad = 0;

    os << endl << "====================================================\n" << endl;
    os << " PVP\tCantidad\tFecha de venta\n";
    os << "====================================================\n" << endl;

    for(auto cit: p){
        os << fixed << setprecision(2) << cit.second.precio_venta() << " €\t" << cit.second.cantidad() << "\t\t";
        os << cit.first->fecha() << endl;
        precio += cit.second.precio_venta() * cit.second.cantidad();
        cantidad += cit.second.cantidad();
    }

    os << "====================================================\n" << endl;
    os << fixed << setprecision(2) << precio << " €\t" << cantidad << endl;

    return os;
}
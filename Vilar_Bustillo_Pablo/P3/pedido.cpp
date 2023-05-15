#include "pedido.hpp"

unsigned Pedido::N_pedidos_ = 0;

/**
 * @brief Constructor de Pedido
 * @details Crea un pedido a partir de un usuario, una tarjeta, una fecha y un pedido
 * @param up Usuario_Pedido (clase de asociacion)
 * @param pa Pedido_Articulo (clase de asociacion)
 * @param u Usuario al que pertenece el pedido
 * @param t Tarjeta con la que se va a pagar el pedido
 * @param f Fecha en la que se realiza el pedido
 */
Pedido::Pedido(Usuario_Pedido &usuario_pedido, Pedido_Articulo &pedido_articulo, Usuario &usuario, const Tarjeta &tarjeta, const Fecha &fecha): num_pedido_(N_pedidos_ + 1), tarjeta_(&tarjeta), f_pedido_(fecha), importe_(0.) {
    if (usuario.compra().empty()) { throw Pedido::Vacio(&usuario); }
    if (tarjeta.titular() != &usuario) { throw Pedido::Impostor(&usuario); }
    if (tarjeta.caducidad() < fecha) { throw Tarjeta::Caducada(tarjeta.caducidad()); }
    if (!tarjeta.activa()) { throw Tarjeta::Desactivada(); }

    auto carrito = usuario.compra();
    for (auto& i: carrito) {
        if (i.first->stock() < i.second) {
            for(auto& it: carrito) {
                usuario.compra(*it.first, 0);
            }
            throw Pedido::SinStock(i.first);
        }
    }

    usuario_pedido.asocia(*this, usuario);
    for (auto& i: carrito) {
        importe_ += i.first->precio() * i.second;
        pedido_articulo.pedir(*i.first, *this, i.first->precio(), i.second);
        i.first->stock() -= i.second;
    }

    const_cast<Usuario::Articulos&>(usuario.compra()).clear();
    num_pedido_ = ++N_pedidos_;
}

/**
* @brief Sobrecarga del operador de insercion
 * @details Imprime un pedido
 * @param os Flujo de salida
 * @param p Pedido a imprimir
*/

std::ostream& operator<<(std::ostream& os, const Pedido& p){
    os << "Núm. pedido: " << p.numero() << std::endl;
    os << "Fecha:       " << p.fecha() << std::endl;
    os << "Pagado con:  " << p.tarjeta()->tipo() << " n.º: " << p.tarjeta()->numero() << std::endl;
    os << "Importe:     " << std::fixed << std::setprecision(2) << p.total() << " €" << std::endl;

    return os;
}
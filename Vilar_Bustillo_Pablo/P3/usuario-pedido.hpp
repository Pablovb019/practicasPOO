#ifndef USUARIO_PEDIDO_HPP
#define USUARIO_PEDIDO_HPP

#include <map>
#include <set>

class Pedido;
class Usuario;

class Usuario_Pedido {
public:
    // LIBRERIAS
    typedef std::set<Pedido*> Pedidos;
    typedef std::map<Usuario*, Pedidos> UsPed;
    typedef std::map<Pedido*, Usuario*> PedUs;

    // OBSERVADORES

    // SUBOBSERVADOR 'ASOCIA'
    void asocia(Usuario& u, Pedido& p) { us_ped_[&u].insert(&p); ped_us_[&p] = &u; }
    void asocia(Pedido& p, Usuario& u) { asocia(u, p); }

    // SUBOBSERVADOR 'PEDIDOS'
    Pedidos& pedidos(Usuario& u) { return us_ped_.find(&u)->second; }

    // SUBOBSERVADOR 'CLIENTE'
    Usuario* cliente(Pedido& p) { return ped_us_.find(&p)->second; }
private:
    UsPed us_ped_;
    PedUs ped_us_;
};


#endif

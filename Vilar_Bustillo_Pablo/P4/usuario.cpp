#include <random>
#include <unistd.h>
#include "usuario.hpp"

using namespace std;
/**
 * @brief Constructor de la clase Clave
 * @details Constructor de la clase Clave que recibe una cadena de caracteres y la encripta
 * @param clear_pass Contraseña en claro
 * @throw Incorrecta::CORTA Si la contraseña es menor de 5 caracteres
 * @throw Incorrecta::ERROR_CRYPT Si se produce un error al encriptar la contraseña
 */
Clave::Clave(const char* clear_pass) {
    if (strlen(clear_pass) < 5) {
        throw Incorrecta(CORTA);
    }
    const char* MD5Chars = "./ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
    random_device rd;
    uniform_int_distribution<size_t> dist(0, 63);

    char salt[2] = {MD5Chars[dist(rd)], MD5Chars[dist(rd)]};

    if (crypt(clear_pass, salt) == nullptr) {
        throw Incorrecta(ERROR_CRYPT);
    }

    encrypted_pass_ = crypt(clear_pass, salt);
}

/**
 * @brief Verificación de la contraseña
 * @details Función que verifica si una contraseña en claro es igual a la contraseña encriptada
 * @param clear_pass Contraseña en claro
 * @return true Si la contraseña en claro es igual a la contraseña encriptada
 * @return false Si la contraseña en claro no es igual a la contraseña encriptada
 */
bool Clave::verifica(const char* clear_pass) const {
    return encrypted_pass_ == crypt(clear_pass, encrypted_pass_.c_str());
}


Usuario::Usuarios Usuario::usuarios_;
/**
 * @brief Constructor de la clase Usuario
 * @details Constructor de la clase Usuario que recibe los datos del usuario y los almacena
 * @param id Identificador del usuario
 * @param nombre Nombre del usuario
 * @param apellidos Apellidos del usuario
 * @param direccion Dirección del usuario
 * @param password Contraseña del usuario encriptada
 * @throw Id_duplicado Si el identificador del usuario ya existe
 */
Usuario::Usuario(const Cadena &id, const Cadena &nombre, const Cadena &apellidos, const Cadena &direccion, const Clave &password):
id_(id), nombre_(nombre), apellidos_(apellidos), direccion_(direccion), password_(password){
    if(!usuarios_.insert(id).second){
        throw Id_duplicado(id);
    }
}

/**
 * @brief Destructor de la clase Usuario
 * @details Destructor de la clase Usuario que elimina el usuario de la lista de usuarios y anula el titular de las tarjetas del usuario
 */
Usuario::~Usuario() {
    for(auto & tarjeta : tarjetas_){
        tarjeta.second->anula_titular();
    }
    usuarios_.erase(id_);
}

/**
 * @brief Asignar Titular a una Tarjeta
 * @details Función que asigna el titular de una tarjeta al usuario
 * @param t Tarjeta a añadir
 * @throw Tarjeta::Titular_duplicado Si el titular de la tarjeta ya existe
 */
void Usuario::es_titular_de(const Tarjeta &t) {
    if(t.titular() == this){
        tarjetas_[t.numero()] = const_cast<Tarjeta*>(&t);
    }
}

/**
 * @brief Eliminar Titular de una Tarjeta
 * @details Función que elimina el titular de una tarjeta del usuario
 * @param t Tarjeta a eliminar
 */
void Usuario::no_es_titular_de(Tarjeta& t) {
    t.anula_titular();
    tarjetas_.erase(t.numero());
}

/**
 * @brief Añadir Artículo al Carrito
 * @details Función que añade una cantidad concreta de un artículo al carrito del usuario
 * @param a Artículo a añadir
 * @param cantidad Cantidad del artículo a añadir
 */
void Usuario::compra(const Articulo &a, unsigned int cantidad) {
    if(cantidad == 0){
        articulos_.erase(const_cast<Articulo*>(&a));
    }else{
        articulos_[const_cast<Articulo*>(&a)] = cantidad;
    }
}

/**
 * @brief Vaciar Carrito
 * @details Función que vacía el carrito del usuario
 */
void Usuario::vaciar_carro() {
    articulos_.clear();
}

std::ostream &operator<<(std::ostream &os, const Usuario &u) {
    os << u.id() << " [" << u.password_.clave() << "] " << u.nombre() << " " << u.apellidos() << endl;
    os << u.direccion() << endl;
    os << "Tarjetas:" << endl;
    for(auto & tarjeta : u.tarjetas()){
        os << *tarjeta.second << endl;
    }
    return os;
}

std::ostream &mostrar_carro(std::ostream &os, const Usuario &u) {
    os << "Carrito de compra de " << u.id() << " [Artículos: " << u.n_articulos() << "]" << endl;
    os << " Cant. Artículo" << endl;
    os << "===========================================================" << endl;

    for(auto & articulo : u.compra()){
        os << articulo.second << "   [" << articulo.first->referencia() << "] \"" << articulo.first->titulo() << "\", " << articulo.first->f_publi().anno() << ". " << fixed << setprecision(2) << articulo.first->precio() << " €" << endl;
    }

    return os;
}
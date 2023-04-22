#ifndef USUARIO_HPP
#define USUARIO_HPP

#include <map>
#include <unordered_map>
#include <unordered_set>

#include "../P1/cadena.hpp"
#include "articulo.hpp"
#include "tarjeta.hpp"

class Numero;
class Tarjeta;

class Clave{
public:
    // CONSTRUCTOREES
    Clave(const char* clear_pass);

    // ENUMERADOS
    enum Razon { CORTA, ERROR_CRYPT };

    // CLASE DE EXCEPCIÓN 'INCORRECTA'
    class Incorrecta: public std::exception{
    public:
        // Constructor
        /**
         * @brief Constructor de la clase Incorrecta
         * @details Constructor de la clase Incorrecta que recibe la razón por la que se ha lanzado la excepción
         * @param razon Razon por la que se ha lanzado la excepción
         */
        Incorrecta(const Razon& razon) : razon_(razon) {};

        // OBSEVADORES
        const Razon& razon() const { return razon_; };
    private:
        Razon razon_;
    };

    // OBSERVADORES
    const Cadena& clave() const { return encrypted_pass_; };

    // FUNCIONES PÚBLICAS
    bool verifica(const char* clear_pass) const;

private:
    Cadena encrypted_pass_;
};



class Usuario{
public:
    // CONSTANTES
    typedef std::map<Numero, Tarjeta*> Tarjetas;
    typedef std::unordered_map<Articulo*, unsigned int> Articulos;
    typedef std::unordered_set<Cadena> Usuarios;

    // CONSTRUCTORES
    Usuario(const Cadena& id, const Cadena& nombre, const Cadena& apellidos, const Cadena& direccion, const Clave& password);
    Usuario(const Usuario& u) = delete; // eliminamos el constructor de copia
    Usuario& operator =(const Usuario& u) = delete; // eliminamos el operador de asignación

    // DESTUCTOR
    ~Usuario();

    // OBSERVADORES
    const Cadena& id() const { return id_; };
    const Cadena& nombre() const { return nombre_; };
    const Cadena& apellidos() const { return apellidos_; };
    const Cadena& direccion() const { return direccion_; };
    const Tarjetas& tarjetas() const { return tarjetas_; };
    const Articulos& compra() const { return articulos_; };

    // FUNCIONES PÚBLICAS
    void es_titular_de(const Tarjeta& t);
    void no_es_titular_de(Tarjeta& t);

    void compra(const Articulo& a, unsigned int cantidad = 1);
    void vaciar_carro();

    unsigned n_articulos() const { return articulos_.size(); };
    friend std::ostream& operator <<(std::ostream& os, const Usuario& u);

    // CLASE DE EXCEPCIÓN 'ID_DUPLICADO'
    class Id_duplicado: public std::exception{
    public:
        // Constructor
        /**
         * @brief Constructor de la clase Id_duplicado
         * @details Constructor de la clase Id_duplicado que recibe el id que se ha intentado introducir
         * @param id Id que se ha intentado introducir
         */
        Id_duplicado(const Cadena& id) : id_(id) {};

        // OBSERVADORES
        const Cadena& idd() const { return id_; };
    private:
        Cadena id_;
    };

private:
    Cadena id_;
    Cadena nombre_;
    Cadena apellidos_;
    Cadena direccion_;
    Clave password_;
    Tarjetas tarjetas_;
    Articulos articulos_;
    static Usuarios usuarios_;
};

std::ostream& mostrar_carro(std::ostream& os, const Usuario& u);
#endif
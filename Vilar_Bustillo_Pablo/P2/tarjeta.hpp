#ifndef TARJETA_HPP
#define TARJETA_HPP

#include "../P1/cadena.hpp"
#include "../P1/fecha.hpp"
#include "usuario.hpp"

class Usuario;
class Clave;

class Numero{
public:
    // CONSTANTES
    enum Razon { LONGITUD, DIGITOS, NO_VALIDO };

    // CONSTRUCTORES
    Numero (const Cadena& numero);

    // OPERADORES
    operator const char* () const { return numero_.c_str(); };

    // OBSERVADORES
    const Cadena& numero() const { return numero_; };

    // CLASE DE EXCEPCIÓN 'INCORRECTO'
    class Incorrecto: public std::exception{
    public:
        // CONSTRUCTORES
        /**
         * @brief Constructor de la clase Incorrecto
         * @details Constructor de la clase Incorrecto que recibe la razón por la que se ha lanzado la excepción
         * @param razon Razon por la que se ha lanzado la excepción
         */
        Incorrecto(const Razon razon) : razon_(razon) {};

        // OBSEVADORES
        Razon razon() const { return razon_; };
    private:
        Razon razon_;
    };

private:
    Cadena numero_;
};

class Tarjeta{
public:
    // CONSTRUCTORES
    Tarjeta(const Numero& numero, Usuario& usuario, const Fecha& fecha);
    Tarjeta(const Tarjeta& t) = delete; // eliminamos el constructor de copia
    Tarjeta& operator =(const Tarjeta& t) = delete; // eliminamos el operador de asignación

    // DESTRUCTOR
    ~Tarjeta();

    // ENUMERADOS
    enum Tipo { Otro, VISA, Mastercard, Maestro, JCB, AmericanExpress };

    // OBSERVADORES
    const Numero& numero() const { return numero_; };
    const Usuario* titular() const { return titular_; };
    const Fecha& caducidad() const { return caducidad_; };
    Tipo tipo() const;
    bool activa() const { return activa_; };

    bool& activa(bool estado); // Para poder cambiar el estado de la tarjeta

    // FUNCIONES PÚBLICAS
    friend class Usuario; // Para hacer anula_titular exclusiva de la clase Usuario

    // CLASE DE EXCEPCIÓN 'CADUCADA'
    class Caducada: public std::exception{
    public:
        // CONSTRUCTORES
        /**
         * @brief Constructor de la clase Caducada
         * @details Constructor de la clase Caducada que recibe la fecha de caducidad de la tarjeta
         * @param fecha_caducada Fecha de caducidad de la tarjeta
         */
        Caducada(const Fecha& fecha_caducada) : fecha_caducada_(fecha_caducada) {};

        // OBSEVADORES
        const Fecha& cuando() const { return fecha_caducada_; };
    private:
        Fecha fecha_caducada_;
    };

    // CLASE DE EXCEPCIÓN 'NUM_DUPLICADO'
    class Num_duplicado: public std::exception{
    public:
        // CONSTRUCTORES
        /**
         * @brief Constructor de la clase Num_duplicado
         * @details Constructor de la clase Num_duplicado que recibe el número de la tarjeta duplicada
         * @param numero Número de la tarjeta duplicada
         */
        Num_duplicado(const Numero& numero) : numero_(numero) {};

        // OBSEVADORES
        const Numero& que() const { return numero_; };
    private:
        Numero numero_;
    };

private:
    const Numero numero_;
    Usuario* const titular_;
    const Fecha caducidad_;
    Tipo tipo_;
    bool activa_;

    // FUNCIONES PRIVADAS
    void anula_titular();
};

std::ostream &operator <<(std::ostream& os, const Tarjeta& t);
std::ostream &operator <<(std::ostream& os, const Tarjeta::Tipo& tipo);

// OPERADORES LÓGICOS
bool operator <(const Numero& n1, const Numero& n2);
bool operator <(const Tarjeta& t1, const Tarjeta& t2);
#endif

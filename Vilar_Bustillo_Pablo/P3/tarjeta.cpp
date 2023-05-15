#include "tarjeta.hpp"
#include <algorithm>

using namespace std;
bool luhn(const Cadena&);

/**
 * @brief Clase EsDigito
 * @details Clase que comprueba si un caracter es un digito
 */
class EsDigito: public unary_function<char, bool> {
    public:
        bool operator()(char c) const { return isdigit(c); }
};

/**
 * @brief Constructor de Numero
 * @details Constructor de la clase Numero
 * @param numero Cadena con el número de la tarjeta
 */
Numero::Numero(const Cadena& numero) {
    Cadena cad_num(numero);
    Cadena::iterator it = remove_if(cad_num.begin(), cad_num.end(), [](char c) { return isspace(c); });

    if (it != cad_num.end()) {
        *it = '\0';
        cad_num = Cadena(cad_num.c_str());
    }

    unary_negate<EsDigito> not_digit((EsDigito()));
    Cadena::const_iterator cit = find_if(cad_num.begin(), cad_num.end(), not_digit);

    if (cit != cad_num.end()) { throw Incorrecto(DIGITOS); }
    if (cad_num.length() < 13 || cad_num.length() > 19) { throw Incorrecto(LONGITUD); }
    if (!luhn(cad_num)) { throw Incorrecto(NO_VALIDO); }

    numero_ = cad_num;
}

bool operator <(const Numero& n1, const Numero& n2) {
    return strcmp(n1, n2) < 0;
}

/**
 * @brief Constructor de Tarjeta
 * @details Constructor de la clase Tarjeta
 * @param numero Numero de la tarjeta
 * @param usuario Usuario titular de la tarjeta
 * @param fecha Fecha de caducidad de la tarjeta
 */
 Tarjeta::Tarjeta(const Numero &numero, Usuario &usuario, const Fecha &fecha)
 : numero_(numero), titular_(&usuario), caducidad_(fecha), activa_(true){
    if (fecha < Fecha()){
        throw Caducada(fecha);
    }

    if (usuario.tarjetas().find(numero) != usuario.tarjetas().end()){
        throw Num_duplicado(numero);
    }

    titular_ -> es_titular_de(*this);
}

/**
 * @brief Destructor de Tarjeta
 * @details Destructor de la clase Tarjeta
 */
Tarjeta::~Tarjeta() {
    if (titular_ != nullptr) {
        titular_ -> no_es_titular_de(*this);
    }
}

/**
 * @brief Funcion Anula titular
 * @details Funcion que anula el titular de la tarjeta
 */
void Tarjeta::anula_titular() {
    activa_ = false;
    const_cast<Usuario*&>(titular_) = nullptr;
}

/**
 * @brief Funcion Tipo
 * @details Funcion que devuelve el tipo de tarjeta
 * @return Tipo de tarjeta
 */
Tarjeta::Tipo Tarjeta::tipo() const {
    int digitos = atoi(numero_.numero().substr(0, 2).c_str());
    switch (digitos/10) {
        case 3:
            if (digitos == 34 || digitos == 37) return Tipo::AmericanExpress;
            else return Tipo::JCB;
            break;

        case 4:
            return Tipo::VISA;
            break;

        case 5:
            return Tipo::Mastercard;
            break;

        case 6:
            return Tipo::Maestro;
            break;

        default:
            return Tipo::Otro;
    }
}

/**
 * @brief Operador de insercion de flujo
 * @details Operador de insercion de flujo para la clase Tarjeta
 * @param os Flujo de salida
 * @param t Tarjeta a insertar en el flujo
 * @return Flujo de salida
 */
ostream& operator <<(ostream& os, const Tarjeta& t) {
    Cadena nombre = t.titular() -> nombre();
    Cadena apellidos = t.titular() -> apellidos();

    // Nombre y apellidos en mayusculas
    for (size_t i = 0; i < nombre.length(); i++) {
        nombre[i] = toupper(nombre[i]);
    }

    for (size_t i = 0; i < apellidos.length(); i++) {
        apellidos[i] = toupper(apellidos[i]);
    }

    os << t.tipo() << endl;
    os << t.numero() << endl;
    os << nombre << " " << apellidos << endl;
    os << "Caduca: " << setfill('0') << setw(2) << t.caducidad().mes() << "/" << (t.caducidad().anno() % 100) << endl;
    return os;
}

/**
 * @brief Operador de insercion de flujo
 * @details Operador de insercion de flujo para la clase Tarjeta::Tipo
 * @param os Flujo de salida
 * @param t Tipo de tarjeta a insertar en el flujo
 * @return Flujo de salida
 */
std::ostream &operator <<(std::ostream &os, const Tarjeta::Tipo &t) {
    switch (t) {
        case Tarjeta::Tipo::VISA:
            os << "VISA";
            break;

        case Tarjeta::Tipo::Mastercard:
            os << "Mastercard";
            break;

        case Tarjeta::Tipo::Maestro:
            os << "Maestro";
            break;

        case Tarjeta::Tipo::JCB:
            os << "JCB";
            break;

        case Tarjeta::Tipo::AmericanExpress:
            os << "AmericanExpress";
            break;

        case Tarjeta::Tipo::Otro:
            os << "Tipo indeterminado";
            break;
        default:
            os << "Error";
    }
    return os;
}

bool operator <(const Tarjeta& t1, const Tarjeta& t2) {
    return t1.numero() < t2.numero();
}

bool& Tarjeta::activa(bool activa) {
    activa_ = activa;
    return activa_;
}
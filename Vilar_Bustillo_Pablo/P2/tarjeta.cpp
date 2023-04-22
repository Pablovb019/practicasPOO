#include "tarjeta.hpp"

using namespace std;
bool luhn(const Cadena&);

/**
 * @brief Constructor de Numero
 * @details Constructor de la clase Numero
 * @param numero Cadena con el número de la tarjeta
 */
Numero::Numero(const Cadena& numero) {
    char no_validos[] = "./ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz"; // Caracteres no válidos en el número de tarjeta
    size_t num_tarjeta = strcspn(numero.c_str(), no_validos); // Guarda en num_tarjeta la cadena sin los caracteres no válidos (falta eliminar lo que no sean digitos, aqui solo se eliminan los caracteres no válidos almacenados en la variable no_validos)
    if (num_tarjeta < numero.length()) throw Incorrecto(Razon::DIGITOS);

    char* pch;
    char* aux = new char[30];
    pch = strpbrk(const_cast<char*>(numero.c_str()), "0123456789"); // Elimina los caracteres no válidos

    int i = 0;
    while (pch != NULL) {
        aux[i++] = *pch;
        pch = strpbrk(pch + 1, "0123456789");
    }

    aux[i] = '\0';
    Cadena aux2(aux);
    delete[] aux;

    if (aux2.length() < 13 || aux2.length() > 19) throw Incorrecto(Razon::LONGITUD);
    if (!luhn(aux2)) throw Incorrecto(Razon::NO_VALIDO);
    numero_ = aux;
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
    os << t.tipo() << endl;
    os << t.numero() << endl;
    os << t.titular() << endl;
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
            os << "Otro";
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
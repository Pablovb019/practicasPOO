#include "fecha.hpp"

// Funciones privadas
/**
 * @brief Actualiza la fecha para que sea correcta
 * @details Si la fecha no es correcta, salta una excepción de tipo Fecha::Invalida
 * @return void
 * @throw Fecha::Invalida si la fecha actualizada no es correcta
 */
void Fecha::actualizarFecha() {
    while (mes_ > 12) {
        mes_ -= 12;
        anno_++;
    }

    while (dia_ > diasMes(mes_)) {
        dia_ -= diasMes(mes_);
        if (++mes_ > 12) {
            mes_ = 1;
            anno_++;
        }
    }

    while (dia_ < 1) {
        if (--mes_ < 1) {
            mes_ = 12;
            anno_--;
        }
        dia_ += diasMes(mes_);
    }
    if (!comprobar()) throw Fecha::Invalida("Fecha no válida");
}

/**
 * @brief Comprueba si la fecha es correcta
 * @details Comprueba si la fecha es correcta
 * @return bool
 */
bool Fecha::comprobar() const {
    if (anno_ < AnnoMinimo || anno_ > AnnoMaximo) return false;
    if (mes_ < 1 || mes_ > 12) return false;
    if (dia_ < 1 || dia_ > diasMes(mes_)) return false;
    return true;
}

/**
 * @brief Devuelve el número de días que tiene un mes
 * @details Devuelve el número de días que tiene un mes
 * @param mes Mes del que se quiere saber el número de días
 * @return int
 * @throw Fecha::Invalida si el mes no es válido
 */
int Fecha::diasMes(int mes) const {
    if (mes == 1 || mes == 3 || mes == 5 || mes == 7 || mes == 8 || mes == 10 || mes == 12) return 31; // meses de 31 días
    else if (mes == 4 || mes == 6 || mes == 9 || mes == 11) return 30; // meses de 30 días
    else if (mes == 2) { // febrero
        if (anno_ % 4 == 0 && (anno_ % 400 == 0 || anno_ % 100 != 0)) return 29; // bisiesto
        else return 28; // no bisiesto
    }
    else { throw Fecha::Invalida("Mes no válido"); }
}

// Constructores

/**
 * @brief Constructor de la clase Fecha
 * @details Constructor de la clase Fecha
 * @param dia Día de la fecha, en caso de ser 0, se toma el día actual
 * @param mes Mes de la fecha, en caso de ser 0, se toma el mes actual
 * @param anno Año de la fecha, en caso de ser 0, se toma el año actual
 * @throw Fecha::Invalida si la fecha no es correcta
 */
Fecha::Fecha(int dia, int mes, int anno) : dia_(dia), mes_(mes), anno_(anno) {
    std::time_t tiempo_calendario = std::time(nullptr);
    std::tm* tiempo_descompuesto = std::localtime(&tiempo_calendario);

    if (dia == 0) { dia_ = tiempo_descompuesto->tm_mday; }
    if (mes == 0) { mes_ = tiempo_descompuesto->tm_mon + 1; }
    if (anno == 0) { anno_ = tiempo_descompuesto->tm_year + 1900; }

    if (!comprobar()) throw Fecha::Invalida("Fecha no válida");

}

/**
 * @brief Constructor de la clase Fecha
 * @details Constructor de la clase Fecha
 * @param fecha Cadena de caracteres con la fecha
 * @return void
 * @throw Fecha::Invalida si la fecha no es correcta
 */
Fecha::Fecha(const char *c) {
    if(sscanf(c, "%d/%d/%d", &dia_, &mes_, &anno_) != 3) throw Fecha::Invalida("Fecha no válida");

    std::time_t tiempo_calendario = std::time(nullptr);
    tm* tiempo_descompuesto = std::localtime(&tiempo_calendario);

    if (dia_ == 0) { dia_ = tiempo_descompuesto->tm_mday; }
    if (mes_ == 0) { mes_ = tiempo_descompuesto->tm_mon + 1; }
    if (anno_ == 0) { anno_ = tiempo_descompuesto->tm_year + 1900; }

    if (!comprobar()) throw Fecha::Invalida("Fecha no válida");
}

/**
 * @brief Operador de asignación de la clase Fecha
 * @details Operador de asignación de la clase Fecha
 * @return Fecha& Referencia a la fecha actualizada
 */
Fecha::operator const char *() const {
    setlocale(LC_ALL, "es_ES.UTF-8"); // Para que muestre los meses y días en español
    static char *aux=new char[40];
    tm f={};
    f.tm_mday=dia_;
    f.tm_mon=mes_-1;
    f.tm_year=anno_-1900;

    mktime(&f);
    strftime(aux,40,"%A %d de %B de %Y",&f);

    return aux;
}

// Operadores

/**
 * @brief Operador de asignación de la clase Fecha
 * @details Incrementa la fecha en el número de días indicado
 * @param dias Número de días a incrementar
 * @return Fecha& Referencia a la fecha actualizada
 * @throw Fecha::Invalida si la fecha actualizada no es correcta
 */
Fecha Fecha::operator+=(int dias) {
    this->dia_ += dias;
    actualizarFecha();
    return *this;
}

/**
 * @brief Operador de asignación de la clase Fecha
 * @details Decrementa la fecha en el número de días indicado
 * @param dias Número de días a decrementar
 * @return Fecha& Referencia a la fecha actualizada
 * @throw Fecha::Invalida si la fecha actualizada no es correcta
 */
Fecha &Fecha::operator-=(int dias) {
    *this += -dias;
    actualizarFecha();
    return *this;
}

/**
 * @brief Operador de asignación de la clase Fecha
 * @details Incrementa la fecha en un día
 * @return Fecha& Referencia a la fecha actualizada
 */
Fecha &Fecha::operator++() {
    *this += 1;
    actualizarFecha();
    return *this;
}

/**
 * @brief Operador de asignación de la clase Fecha
 * @details Incrementa la fecha en un día
 * @return Fecha& Referencia a la fecha actualizada
 */
Fecha Fecha::operator++(int) {
    Fecha aux = *this;
    *this += 1;
    actualizarFecha();
    return aux;
}

/**
 * @brief Operador de asignación de la clase Fecha
 * @details Decrementa la fecha en un día
 * @return Fecha& Referencia a la fecha actualizada
 */
Fecha &Fecha::operator--() {
    *this += -1;
    actualizarFecha();
    return *this;
}

/**
 * @brief Operador de asignación de la clase Fecha
 * @details Decrementa la fecha en un día
 * @return Fecha& Referencia a la fecha actualizada
 */
const Fecha Fecha::operator--(int) {
    Fecha aux = *this;
    *this += -1;
    actualizarFecha();
    return aux;
}

// Operadores aritméticos
/**
 * @brief Operador aritmético de la clase Fecha
 * @details Incrementa la fecha en el número de días indicado
 * @param dias Número de días a incrementar
 * @return Fecha Fecha actualizada
 * @throw Fecha::Invalida si la fecha actualizada no es correcta
 */
Fecha Fecha::operator+(int dias) const {
    Fecha aux(*this);
    aux += dias;
    return aux;
}

/**
 * @brief Operador aritmético de la clase Fecha
 * @details Decrementa la fecha en el número de días indicado
 * @param dias Número de días a decrementar
 * @return Fecha Fecha actualizada
 * @throw Fecha::Invalida si la fecha actualizada no es correcta
 */
Fecha Fecha::operator-(int dias) const {
    Fecha aux(*this);
    aux += -dias;
    return aux;
}

// Operadores Logicos
/**
 * @brief Operador lógico de la clase Fecha
 * @details Comprueba si dos fechas son iguales
 * @param f1 Fecha 1
 * @param f2 Fecha 2
 * @return bool true si las fechas son iguales, false en caso contrario
 */
bool operator==(const Fecha &f1, const Fecha &f2) noexcept {
    return f1.dia() == f2.dia() && f1.mes() == f2.mes() && f1.anno() == f2.anno();
}

/**
 * @brief Operador lógico de la clase Fecha
 * @details Comprueba si dos fechas son distintas
 * @param f1 Fecha 1
 * @param f2 Fecha 2
 * @return bool true si las fechas son distintas, false en caso contrario
 */
bool operator!=(const Fecha &f1, const Fecha &f2) noexcept {
    return !(f1 == f2);
}

/**
 * @brief Operador lógico de la clase Fecha
 * @details Comprueba si una fecha es menor que otra
 * @param f1
 * @param f2
 * @return bool true si la fecha 1 es menor que la fecha 2, false en caso contrario
 */
bool operator<(const Fecha &f1, const Fecha &f2) noexcept {
    if (f1.anno() < f2.anno()) return true;
    else if (f1.anno() == f2.anno()) {
        if (f1.mes() < f2.mes()) return true;
        else if (f1.mes() == f2.mes()) {
            if (f1.dia() < f2.dia()) return true;
            else return false;
        }
        else return false;
    }
    else return false;
}

/**
 * @brief Operador lógico de la clase Fecha
 * @details Comprueba si una fecha es mayor que otra
 * @param f1
 * @param f2
 * @return bool true si la fecha 1 es mayor que la fecha 2, false en caso contrario
 */
bool operator>(const Fecha &f1, const Fecha &f2) noexcept {
    return f2 < f1;
}

/**
 * @brief Operador lógico de la clase Fecha
 * @details Comprueba si una fecha es menor que otra
 * @param f1
 * @param f2
 * @return bool true si la fecha 1 es menor o igual que la fecha 2, false en caso contrario
 */
bool operator<=(const Fecha &f1, const Fecha &f2) noexcept {
    return !(f2 < f1);
}

/**
 * @brief Operador lógico de la clase Fecha
 * @details Comprueba si una fecha es mayor que otra
 * @param f1
 * @param f2
 * @return bool true si la fecha 1 es mayor o igual que la fecha 2, false en caso contrario
 */
bool operator>=(const Fecha &f1, const Fecha &f2) noexcept {
    return !(f1 < f2);
}
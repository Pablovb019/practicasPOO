#include "articulo.hpp"

using namespace std;

/**
 * @brief Constructor de Articulo
 * @details Constructor de la clase Articulo
 * @param referencia
 * @param titulo
 * @param f_publi
 * @param precio
 * @param stock
 */
Articulo::Articulo(const Cadena &referencia, const Cadena &titulo, const Fecha &f_publi, double precio, unsigned int stock):
referencia_(referencia), titulo_(titulo), f_publi_(f_publi), precio_(precio), stock_(stock) {}

/**
 * @brief Operador de inserción de la clase Articulo
 * @details Imprime los datos de un Articulo
 * @param os Flujo de salida
 * @param a Articulo a imprimir
 * @return &ostream Flujo de salida
 */
ostream &operator<<(ostream &os, const Articulo &a) {
    os << "[" << a.referencia() << "] \"" << a.titulo() << "\", " << a.f_publi().anno() << ". " << fixed << setprecision(2) << a.precio() << " €";
    return os;
}
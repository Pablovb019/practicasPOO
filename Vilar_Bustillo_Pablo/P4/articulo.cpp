#include "articulo.hpp"

using namespace std;
/**
 * @brief Constructor de Autor
 * @details Constructor de la clase Autor
 * @param nombre Nombre del autor
 * @param apellidos Apellidos del autor
 * @param direccion Dirección del autor
 */
Autor::Autor(const Cadena &nombre, const Cadena &apellidos, const Cadena &direccion):
nombre_(nombre), apellidos_(apellidos), direccion_(direccion) {}

/**
 * @brief Constructor de Articulo
 * @details Constructor de la clase Articulo
 * @param autor Autor del articulo
 * @param referencia Referencia del articulo
 * @param titulo Titulo del articulo
 * @param f_publi Fecha de publicación del articulo
 * @param precio Precio del articulo
 */
Articulo::Articulo(const Autores &autor, const Cadena &referencia, const Cadena &titulo, const Fecha &f_publi, double precio):
autores_(autor), referencia_(referencia), titulo_(titulo), f_publi_(f_publi), precio_(precio){
    if(autor.empty()) throw Autores_vacios();
}

/**
 * @brief Constructor de Articulo Almacenable
 * @param autor Autor del Articulo Almacenable
 * @param referencia Referencia del Articulo Almacenable
 * @param titulo Titulo del Articulo Almacenable
 * @param f_publi Fecha de publicación del Articulo Almacenable
 * @param precio Precio del Articulo Almacenable
 * @param stock Stock del Articulo Almacenable
 */
ArticuloAlmacenable::ArticuloAlmacenable(const Articulo::Autores &autor, const Cadena &referencia, const Cadena &titulo, const Fecha &f_publi, double precio, unsigned int stock):
Articulo(autor, referencia, titulo, f_publi, precio), stock_(stock) {}

/**
 * @brief Constructor de LibroDigital
 * @param autor Autor del Libro Digital
 * @param referencia Referencia del Libro Digital
 * @param titulo Titulo del Libro Digital
 * @param f_publi Fecha de publicación del Libro Digital
 * @param precio Precio del Libro Digital
 * @param f_expir Fecha de expiración del Libro Digital
 */
LibroDigital::LibroDigital(const Articulo::Autores &autor, const Cadena &referencia, const Cadena &titulo, const Fecha &f_publi, double precio, const Fecha &f_expir):
Articulo(autor, referencia, titulo, f_publi, precio), f_expir_(f_expir) {}

/**
 * @brief Constructor de Libro
 * @param autor Autor del Libro
 * @param referencia Referencia del Libro
 * @param titulo Titulo del Libro
 * @param f_publi Fecha de publicación del Libro
 * @param precio Precio del Libro
 * @param n_pag Número de páginas del Libro
 * @param stock Stock del Libro
 */
Libro::Libro(const Articulo::Autores &autor, const Cadena &referencia, const Cadena &titulo, const Fecha &f_publi, double precio, unsigned int n_pag, unsigned int stock):
ArticuloAlmacenable(autor, referencia, titulo, f_publi, precio, stock), n_pag_(n_pag) {}

/**
 * @brief Constructor de Revista
 * @param autor Autor de la Revista
 * @param referencia Referencia de la Revista
 * @param titulo Titulo de la Revista
 * @param f_publi Fecha de publicación de la Revista
 * @param precio Precio de la Revista
 * @param numero Número de la Revista
 * @param periodicidad Días de periodicidad de la Revista
 * @param stock Stock de la Revista
 */
Revista::Revista(const Articulo::Autores &autor, const Cadena &referencia, const Cadena &titulo, const Fecha &f_publi, double precio, unsigned int numero, unsigned int periodicidad, unsigned int stock):
ArticuloAlmacenable(autor, referencia, titulo, f_publi, precio, stock), numero_(numero), periodicidad_(periodicidad) {}

/**
 * @brief Operador de inserción de la clase Articulo
 * @details Imprime los datos de un Articulo
 * @param os Flujo de salida
 * @param a Articulo a imprimir
 * @return &ostream Flujo de salida
 */
ostream &operator<<(ostream &os, const Articulo &a) {
    os << "[" << a.referencia() << "] \"" << a.titulo() << "\", de ";

    auto it = a.autores().begin();
    os << (*it)->apellidos();

    for(++it; it != a.autores().end(); ++it) {
        os << ", " << (*it)->apellidos();
    }
    os << ". ";

    os << a.f_publi().anno() << ". " << fixed << setprecision(2) << a.precio() << " €" << endl;
    os << "\t";

    a.impresion_especifica(os);
    return os;
}

/**
 * @brief Impresión específica de Libro Digital
 * @details Imprime la fecha de expiración de un Libro Digital
 * @param os Flujo de salidaç
 * @return &ostream Flujo de salida
 */
void LibroDigital::impresion_especifica(std::ostream &os) const {
    os << "A la venta hasta el " << f_expir_ << ".";
}

/**
 * @brief Impresión específica de Articulo Almacenable
 * @details Imprime el numero de páginas y el stock de un Articulo Almacenable
 * @param os Flujo de salida
 * @return &ostream Flujo de salida
 */
void Libro::impresion_especifica(std::ostream &os) const {
    os << n_pag_ << " págs., " << stock_ << " unidades.";
}

/**
 * @brief Impresión específica de Revista
 * @details Imprime el número y la periodicidad de una Revista
 * @param os Flujo de salida
 * @return &ostream Flujo de salida
 */

void Revista::impresion_especifica(std::ostream &os) const {
    Fecha f = f_publi() + periodicidad_;

    os << "Número: " << numero_ << ", Periodicidad: " << periodicidad_ << " días." << endl;
    os << "\tPróximo número a partir de: " << f << ".";
}
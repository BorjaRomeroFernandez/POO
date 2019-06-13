#include "articulo.hpp"
#include <iomanip>

Autor::Autor(const Cadena &n, const Cadena &a, const Cadena &d) : nombre_(n),
                                                                  apellidos_(a),
                                                                  direccion_(d)
{
}

Articulo::Articulo(Autores &a, const Cadena &r, const Cadena &t, const Fecha &f, double p) : autores_(a),
                                                                                             referencia_(r),
                                                                                             titulo_(t),
                                                                                             f_publi_(f),
                                                                                             precio_(p)
{
    if (autores_.empty())
        throw Autores_vacios();
}

ArticuloAlmacenable::ArticuloAlmacenable(Autores &a, const Cadena &r, const Cadena &t, const Fecha &f, double p, unsigned s) : Articulo(a, r, t, f, p),
                                                                                                                               stock_(s)
{
}

Libro::Libro(Autores &a, const Cadena &r, const Cadena &t, const Fecha &f, double p, unsigned pa, unsigned s) : ArticuloAlmacenable(a, r, t, f, p, s),
                                                                                                                paginas_(pa)

{
}

void Libro::impresion_especifica(std::ostream &os) const noexcept
{
    os << n_pag() << " págs., " << stock() << " unidades.";
}
Cederron::Cederron(Autores &a, const Cadena &r, const Cadena &t, const Fecha &f, double p, unsigned ta, unsigned s) : ArticuloAlmacenable(a, r, t, f, p, s),
                                                                                                                      tamano_(ta)

{
}

void Cederron::impresion_especifica(std::ostream &os) const noexcept
{
    os << tam() << " MB, " << stock() << " unidades.";
}

LibroDigital::LibroDigital(Autores &a, const Cadena &r, const Cadena &t, const Fecha &f, double p, const Fecha &e) : Articulo(a, r, t, f, p),
                                                                                                                     expiracion_(e)

{
}

void LibroDigital::impresion_especifica(std::ostream &os) const noexcept
{
    os << "A la venta hasta el " << f_expir() << '.';
}

std::ostream &operator<<(std::ostream &os, const Articulo &A) noexcept
{
    os << "[" << A.referencia() << "] \"" << A.titulo() << "\", de ";

    for (auto autor = A.autores().begin(); autor != A.autores().end(); ++autor)
        (autor == A.autores().begin()) ? (os << (*autor)->apellidos()) : (os << ", " << (*autor)->apellidos());

    os << ". " << A.f_publi().anno();
    os << ". " << std::fixed << std::setprecision(2) << A.precio() << " €\n\t";

    A.impresion_especifica(os);

    return os;
}
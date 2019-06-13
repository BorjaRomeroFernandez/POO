#include "articulo.hpp"
#include <iomanip>

Articulo::Articulo(const Cadena &r, const Cadena &t, const Fecha &f, double p, unsigned s) : referencia_(r),
                                                                                             titulo_(t),
                                                                                             f_publi_(f),
                                                                                             precio_(p),
                                                                                             stock_(s)
{
}

std::ostream &operator<<(std::ostream &os, const Articulo &A)
{
    os
        << "[" << A.referencia() << "] \"" << A.titulo() << "\", "
        << A.f_publi().anno() << ". " << A.precio() << " €";

    return os;
}
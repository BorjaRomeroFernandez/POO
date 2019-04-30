#include "articulo.hpp"

Articulo::Articulo(Cadena r, Cadena t, Fecha &f, double p, unsigned e) : referencia_(r),
                                                                         titulo_(t),
                                                                         publicacion_(f),
                                                                         precio_(p),
                                                                         ejemplares_(e)
{
}

std::ostream &operator<<(std::ostream &os, const Articulo &A)
{
    os
        << "[" << A.referencia() << "] \"" << A.titulo() << "\", "
        << A.f_publi().anno() << ". " << A.precio() << " €";

    return os;
}
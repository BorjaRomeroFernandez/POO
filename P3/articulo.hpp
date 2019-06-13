#ifndef ARTICULO_HPP_
#define ARTICULO_HPP_

#include "cadena.hpp"
#include "fecha.hpp"
#include <iostream>

class Articulo
{
public:
    Articulo(const Cadena &r, const Cadena &t, const Fecha &f, double p, unsigned s);

    const Cadena referencia() const noexcept { return referencia_; };
    const Cadena titulo() const noexcept { return titulo_; };
    const Fecha f_publi() const noexcept { return f_publi_; };
    double precio() const noexcept { return precio_; };
    double &precio() noexcept { return precio_; };
    unsigned stock() const noexcept { return stock_; };
    unsigned &stock() noexcept { return stock_; };

private:
    Cadena referencia_;
    Cadena titulo_;
    Fecha f_publi_;
    double precio_;
    unsigned stock_;
};

std::ostream &operator<<(std::ostream &os, const Articulo &A);

#endif
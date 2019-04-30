#ifndef ARTICULO_HPP_
#define ARTICULO_HPP_

#include <iostream>
#include "cadena.hpp"
#include "fecha.hpp"

class Articulo
{
public:
  Articulo(Cadena r, Cadena t, Fecha &f, double p, unsigned e);

  Cadena referencia() const noexcept { return referencia_; };
  Cadena titulo() const noexcept { return titulo_; };
  Fecha f_publi() const noexcept { return publicacion_; };
  double precio() const noexcept { return precio_; };
  double &precio() noexcept { return precio_; }
  unsigned stock() const noexcept { return ejemplares_; };
  unsigned &stock() noexcept { return ejemplares_; }

private:
  Cadena referencia_;
  Cadena titulo_;
  Fecha publicacion_;
  double precio_;
  unsigned ejemplares_;
};

std::ostream &operator<<(std::ostream &os, const Articulo &A);

#endif
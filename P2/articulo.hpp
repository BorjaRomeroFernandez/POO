#ifndef ARTICULO_HPP_
#define ARTICULO_HPP_

#include <iostream>
#include "cadena.hpp"
#include "fecha.hpp"

class Articulo
{
public:
  Articulo(Cadena r, Cadena t, Fecha &f, double p, unsigned e);

  Cadena referencia() const { return referencia_; };
  Cadena titulo() const { return titulo_; };
  Fecha f_publi() const { return publicacion_; };
  double precio() const { return precio_; };
  double &precio() { return precio_; }
  unsigned stock() const { return ejemplares_; };
  unsigned &stock() { return ejemplares_; }

private:
  Cadena referencia_;
  Cadena titulo_;
  Fecha publicacion_;
  double precio_;
  unsigned ejemplares_;
};

std::ostream &operator<<(std::ostream &os, const Articulo &A);

#endif
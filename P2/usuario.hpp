#ifndef USUARIO_HPP_
#define USUARIO_HPP_

#include <map>
#include <iostream>
#include "cadena.hpp"
#include "tarjeta.hpp"

class Clave
{
public:
  enum Razon
  {
    CORTA,
    ERROR_CRYPT
  };

  Clave(const char *c);

  class Incorrecta
  {
  public:
    Incorrecta(Razon r) : razon_(r) {}
    Razon razon() const noexcept { return razon_; }

  private:
    Razon razon_;
  };

  Cadena clave() const noexcept { return password_; }

  bool verifica(const char *c);

private:
  Cadena password_;
};

/////////////////////////////////////////////////////////////////////////////

class Usuario
{
public:
  typedef std::map<Numero, Tarjeta *> Tarjetas;
  typedef std::unordered_map<Articulo *, unsigned int> Articulos;

  Usuario(Cadena i, Cadena n, Cadena a, Cadena d, Clave c);
  Usuario(Usuario &u) = delete;

  Usuario &operator=(Usuario &u) = delete;

  class Id_duplicado
  {
  public:
    Id_duplicado(Cadena id) : id_(id) {}
    Cadena idd() const { return id_; }

  private:
    Cadena id_;
  };

  void es_titular_de(const Tarjeta &t);
  void no_es_titular_de(const Tarjeta &t);
  void compra(const Articulo &A, unsigned c = 1);

  Cadena &id() const { return identificador_; }
  Cadena &nombre() const { return nombre_; }
  Cadena &apellidos() const { return apellidos_; }
  Cadena &direccion() const { return direccion_; }
  Tarjetas &tarjetas() const { return tarjetas_; }
  Articulos &compra() const;
  unsigned n_articulos() const;

  ~Usuario();

private:
  Cadena identificador_;
  Cadena nombre_;
  Cadena apellidos_;
  Cadena direccion_;
  Clave contrasena_;
  Tarjetas tarjetas_;
  Articulos articulos_;
};

void mostrar_carro(const Usuario::Articulos &a, const Usuario &U);

std::ostream &operator<<(std::ostream &os, const Usuario &U);

#endif
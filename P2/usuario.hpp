#ifndef USUARIO_HPP_
#define USUARIO_HPP_

#include "cadena.hpp"
#include "tarjeta.hpp"
#include "articulo.hpp"
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <iostream>

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

  bool verifica(const char *c) const;

private:
  Cadena password_;
};

class Numero;
class Tarjeta;

class Usuario
{
public:
  typedef std::map<Numero, Tarjeta *> Tarjetas;
  typedef std::unordered_map<Articulo *, unsigned int> Articulos;
  typedef std::unordered_set<Cadena> Usuarios;

  Usuario(const Cadena &i, const Cadena &n, const Cadena &a, const Cadena &d, const Clave &c);
  Usuario(const Usuario &U) = delete;

  Usuario &operator=(const Usuario &U) = delete;

  class Id_duplicado
  {
  public:
    Id_duplicado(Cadena id) : id_(id) {}
    Cadena idd() const noexcept { return id_; }

  private:
    Cadena id_;
  };

  void es_titular_de(Tarjeta &t);
  void no_es_titular_de(Tarjeta &t);
  void compra(Articulo &A, unsigned c = 1);

  Cadena id() const noexcept { return identificador_; }
  Cadena nombre() const noexcept { return nombre_; }
  Cadena apellidos() const noexcept { return apellidos_; }
  Cadena direccion() const noexcept { return direccion_; }
  Tarjetas tarjetas() const noexcept { return tarjetas_; }
  Articulos compra() const noexcept { return articulos_; }
  unsigned n_articulos() const;

  friend std::ostream &operator<<(std::ostream &os, const Usuario &U);

  ~Usuario();

private:
  Cadena identificador_;
  Cadena nombre_;
  Cadena apellidos_;
  Cadena direccion_;
  Clave contrasena_;
  Tarjetas tarjetas_;
  Articulos articulos_;
  static Usuarios usuarios_;
};

void mostrar_carro(std::ostream &os, const Usuario &U);

#endif
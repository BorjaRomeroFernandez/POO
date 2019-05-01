#ifndef TARJETA_HPP_
#define TARJETA_HPP_

#include <iostream>
#include <set>
#include "cadena.hpp"
#include "fecha.hpp"
#include "usuario.hpp"

class Numero
{
public:
  enum Razon
  {
    LONGITUD,
    DIGITOS,
    NO_VALIDO
  };

  Numero(Cadena n);

  operator const char *() const noexcept { return numero_.c_str(); }

  class Incorrecto
  {
  public:
    Incorrecto(Numero::Razon r) : razon_(r) {}

    Numero::Razon razon() const noexcept { return razon_; }

  private:
    Numero::Razon razon_;
  };

  friend bool operator<(const Numero &N1, const Numero &N2);

private:
  Cadena numero_;
};

////////////////////////////////////////////////////////////////

class Tarjeta
{
public:
  typedef std::set<Numero> Numeros;

  enum Tipo
  {
    Otro,
    VISA,
    Mastercard,
    Maestro,
    JCB,
    AmericanExpress
  };

  Tarjeta(Numero n, Usuario &u, Fecha c);
  Tarjeta(const Tarjeta &T) = delete;

  Tarjeta &operator=(const Tarjeta &T) = delete;

  class Caducada
  {
  public:
    Caducada(Fecha c) : caduca_(c) {}

    Fecha cuando() const { return caduca_; };

  private:
    Fecha caduca_;
  };

  class Num_duplicado
  {
  public:
    Num_duplicado(Numero n) : numero_(n) {}

    Numero que() const { return numero_; }

  private:
    Numero numero_;
  };

  class Desactivada
  {
  };

  bool activa(bool a = true) noexcept;
  void anula_titular();

  Tipo tipo() const noexcept { return tipo_; }
  Numero numero() const noexcept { return numero_; }
  const Usuario &titular() const noexcept { return usuario_; }
  Fecha caducidad() const noexcept { return caducidad_; }
  bool activa() const noexcept { return activa_; }

  ~Tarjeta();

private:
  Tipo tipo_;
  Numero numero_;
  const Usuario *usuario_;
  Fecha caducidad_;
  bool activa_;

  static Numeros numeros_;
};

std::ostream &operator<<(std::ostream &os, const Tarjeta &T);
std::ostream &operator<<(std::ostream &os, const Tarjeta::Tipo &T);

bool operator<(const Tarjeta &T1, const Tarjeta &T2);

#endif
#ifndef TARJETA_HPP_
#define TARJETA_HPP_

#include <ostream>
#include "cadena.hpp"
#include "fecha.hpp"
#include "usuario.hpp"

class Usuario;

struct EsDigito : public std::unary_function<char, bool>
{
    bool operator()(char c) const { return isdigit(c); }
};

struct EsBlanco : public std::unary_function<char, bool>
{
    bool operator()(char c) const { return isspace(c); }
};

class Numero
{
public:
    enum Razon
    {
        LONGITUD,
        DIGITOS,
        NO_VALIDO
    };

    Numero(const Cadena &c);

    operator const char *() const;

    friend bool operator<(const Numero &N1, const Numero &N2);

    class Incorrecto
    {
    public:
        Incorrecto(Razon r) : razon_(r) {}
        const Razon &razon() const noexcept { return razon_; }

    private:
        Razon razon_;
    };

private:
    Cadena cad_;
};

class Tarjeta
{
public:
    enum Tipo
    {
        Otro,
        VISA,
        Mastercard,
        Maestro,
        JCB,
        AmericanExpress
    };

    Tarjeta(Numero N, Usuario &U, Fecha F);
    Tarjeta(const Tarjeta &T) = delete;
    Tarjeta &operator=(const Tarjeta &T) = delete;

    class Caducada
    {
    public:
        Caducada(const Fecha &f) : caducidad_(f) {}
        Fecha cuando() const noexcept { return caducidad_; }

    private:
        Fecha caducidad_;
    };

    class Num_duplicado
    {
    public:
        explicit Num_duplicado(const Numero &n) : numero_(n) {}
        Numero que() const noexcept { return numero_; }

    private:
        Numero numero_;
    };

    class Desactivada
    {
    };

    Tipo tipo() const noexcept { return t_; };
    Numero numero() const noexcept { return num_; };
    const Usuario *titular() const noexcept { return user_; };
    Fecha caducidad() const noexcept { return caducidad_; };
    bool activa() const noexcept { return estado_; }
    Cadena titular_facial() const;

    void anula_titular();
    bool activa(bool est = true);

    ~Tarjeta();

private:
    Tipo t_;
    Numero num_;
    const Usuario *user_;
    Fecha caducidad_;
    bool estado_;
};

std::ostream &operator<<(std::ostream &os, const Tarjeta &T);
std::ostream &operator<<(std::ostream &os, const Tarjeta::Tipo &t);
bool operator<(const Tarjeta &T1, const Tarjeta &T2);

#endif
#ifndef TARJETA_HPP_
#define TARJETA_HPP_
 
#include <ostream>
#include <set>
#include "cadena.hpp"
#include "fecha.hpp"
#include "usuario.hpp"

class Usuario;

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
    Cadena numero_;
};

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

    Tipo tipo() const noexcept { return tipo_; };
    Numero numero() const noexcept { return numero_; };
    const Usuario *titular() const noexcept { return usuario_; };
    Fecha caducidad() const noexcept { return caducidad_; };
    bool activa() const noexcept { return estado_; }
    Cadena titular_facial() const;

    void anula_titular();
    bool activa(bool est = true);

    ~Tarjeta();

private:
    Tipo tipo_;
    Numero numero_;
    const Usuario *usuario_;
    Fecha caducidad_;
    bool estado_;
    static Numeros numeros_;
};

std::ostream &operator<<(std::ostream &os, const Tarjeta &T);
std::ostream &operator<<(std::ostream &os, const Tarjeta::Tipo &t);
bool operator<(const Tarjeta &T1, const Tarjeta &T2);

#endif
#include "tarjeta.hpp"
#include <cstring>
#include <algorithm>
#include <iomanip>

struct Digito : public std::unary_function<const unsigned char, bool>
{
    bool operator()(const unsigned char &x) const { return std::isdigit(x); }
};

bool luhn(const Cadena &cad);

static Cadena str_toupper(Cadena s)
{
    std::transform(s.begin(), s.end(), s.begin(),
                   [](unsigned char c) { return std::toupper(c); });
    return s;
}

Numero::Numero(const Cadena &n)
{
    Cadena aux = n;

    if (aux.length() == 0)
        throw Incorrecto(Razon::LONGITUD);

    aux = aux.substr(0, std::remove_if(aux.begin(), aux.end(), [](unsigned char x) { return std::isspace(x); }) - aux.begin());

    if (std::find_if(aux.begin(), aux.end(), std::not1(Digito())) != aux.end())
        throw Incorrecto(Razon::DIGITOS);

    if (aux.length() < 13 || aux.length() > 19)
        throw Incorrecto(Razon::LONGITUD);

    if (!luhn(aux))
        throw Incorrecto(Razon::NO_VALIDO);

    numero_ = aux;
}

bool operator<(const Numero &N1, const Numero &N2)
{
    return N1.numero_ < N2.numero_;
}

Tarjeta::Numeros Tarjeta::numeros_;

Tarjeta::Tarjeta(Numero n, Usuario &u, Fecha c) : numero_(n),
                                                  titular_(&u),
                                                  caducidad_(c),
                                                  activa_(true)
{
    if (Fecha() > c)
        throw Tarjeta::Caducada(c);

    numeros_.insert(n).second;

    char f = numero_[0];

    switch (f)
    {
    case '3':
    {
        char s = numero_[1];

        (s == '4' || s == '7') ? tipo_ = Tarjeta::AmericanExpress : tipo_ = Tarjeta::JCB;
    }
    break;

    case '4':
        tipo_ = Tarjeta::VISA;
        break;

    case '5':
        tipo_ = Tarjeta::Mastercard;
        break;

    case '6':
        tipo_ = Tarjeta::Maestro;
        break;

    default:
        tipo_ = Tarjeta::Otro;
        break;
    }

    u.es_titular_de(*this);
}

bool Tarjeta::activa(bool a) noexcept
{
    activa_ = a;

    return activa_;
}

void Tarjeta::anula_titular()
{
    titular_ = nullptr;
    activa_ = false;
}

Tarjeta::~Tarjeta()
{
    if (Usuario *u = const_cast<Usuario *>(titular_))
        u->no_es_titular_de(*this);
}

std::ostream &operator<<(std::ostream &os, const Tarjeta &T)
{
    os
        << T.tipo() << std::endl
        << T.numero() << std::endl
        << str_toupper(T.titular()->nombre()) << " " << str_toupper(T.titular()->apellidos()) << std::endl
        << std::uppercase << T.titular()->nombre() << " " << T.titular()->apellidos() << std::nouppercase << std::endl
        << "Caduca: " << std::setfill('0') << std::setw(2)
        << T.caducidad().mes() << '/' << std::setw(2)
        << (T.caducidad().anno() % 100);

    return os;
}

std::ostream &operator<<(std::ostream &os, const Tarjeta::Tipo &T)
{
    switch (T)
    {
    case Tarjeta::AmericanExpress:
        os << "AmericanExpress";
        break;

    case Tarjeta::JCB:
        os << "JCB";
        break;

    case Tarjeta::VISA:
        os << "VISA";
        break;

    case Tarjeta::Mastercard:
        os << "Mastercard";
        break;

    case Tarjeta::Maestro:
        os << "Maestro";
        break;

    case Tarjeta::Otro:
        os << "Otro";
        break;
    }

    return os;
}

bool operator<(const Tarjeta &T1, const Tarjeta &T2)
{
    return T1.numero() < T2.numero();
}
#include <cstring>
#include <algorithm>
#include <iomanip>
#include "tarjeta.hpp"
#include "../luhn.cpp"

Numero::Numero(Cadena c)
{
    Cadena num = c;

    std::remove_if(num.begin(), num.end() + 1, [](char c) { return isspace(c); });

    if (std::count_if(num.begin(), num.end(), static_cast<int (*)(int)>(std::isdigit)) != num.length())
        throw Numero::Incorrecto(Numero::DIGITOS);

    if (num.length() < 13 || num.length() > 19)
        throw Numero::Incorrecto(Numero::LONGITUD);

    if (!luhn(c))
        throw Numero::Incorrecto(Numero::NO_VALIDO);

    numero_ = num;
}

bool operator<(const Numero &N1, const Numero &N2)
{
    return N1.numero_ < N2.numero_;
}

/////////////////////////////////////////////////////////////////

Tarjeta::Tarjeta(Numero n, Usuario &u, Fecha c) : usuario_(&u),
                                                  numero_(n),
                                                  caducidad_(c),
                                                  activa_(true)
{
    if (c < Fecha())
        throw Tarjeta::Caducada(c);

    if (!numeros_.insert(n).second)
        throw Tarjeta::Num_duplicado(n);

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

    u.es_titular_de(this);
}

bool Tarjeta::activa(bool a) noexcept
{
    activa_ = a;

    return activa_;
}

void Tarjeta::anula_titular()
{
    activa_ = false;
    usuario_ = nullptr;
}

Tarjeta::~Tarjeta()
{
    Usuario *u = const_cast<Usuario *>(usuario_);

    if (u != nullptr)
        u->no_es_titular_de(this);
}

std::ostream &operator<<(std::ostream &os, const Tarjeta &T)
{
    os
        << T.tipo() << std::endl
        << T.numero() << std::endl
        << std::uppercase << T.titular().nombre() << " " << T.titular().apellidos() << std::nouppercase << std::endl
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
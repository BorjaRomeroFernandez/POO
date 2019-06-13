#include <algorithm>
#include <cctype>
#include <cstring>
#include <iomanip>
#include "tarjeta.hpp"
#include "usuario.hpp"
 
struct Digito : public std::unary_function<const unsigned char, bool>
{
    bool operator()(const unsigned char &x) const { return std::isdigit(x); }
};

struct Blanco : public std::unary_function<char, bool>
{
    bool operator()(char c) const { return isspace(c); }
};

bool luhn(const Cadena &cad);

static Cadena str_toupper(Cadena s)
{
    std::transform(s.begin(), s.end(), s.begin(), [](unsigned char c) { return std::toupper(c); });

    return s;
}

Numero::Numero(const Cadena &n)
{
    Cadena aux(n);

    Cadena::iterator end = std::remove_if(aux.begin(), aux.end(), Blanco());

    if (end != aux.end())
    {
        *end = '\0';
        Cadena tmp(aux.c_str());
        numero_ = tmp;
    }

    if (aux.length() < 13 || aux.length() > 19 || aux.length() == 0)
        throw Incorrecto(Razon::LONGITUD);

    numero_ = aux.c_str();

    if (std::find_if(numero_.begin(), numero_.end(), std::not1(Digito())) != numero_.end())
        throw Incorrecto(Razon::DIGITOS);

    if (!luhn(numero_))
        throw Incorrecto(Razon::NO_VALIDO);
}

Numero::operator const char *() const
{
    return numero_.c_str();
}

bool operator<(const Numero &N1, const Numero &N2)
{
    return N1.numero_ < N2.numero_;
}

///////////////////////////////////////////////////////////////////

Tarjeta::Numeros Tarjeta::numeros_;

Tarjeta::Tarjeta(Numero N, Usuario &U, Fecha F) : numero_(N),
                                                  usuario_(&U),
                                                  caducidad_(F),
                                                  estado_(true)
{
    if (Fecha() > caducidad_)
        throw Caducada(caducidad_);

    numeros_.insert(numero_);

    switch (N[0])
    {
    case '3':
        switch (N[1])
        {
        case '4':
        case '7':
            tipo_ = JCB;
            break;

        default:
            tipo_ = AmericanExpress;
            break;
        }
        break;

    case '4':
        tipo_ = VISA;
        break;

    case '5':
        tipo_ = Mastercard;
        break;

    case '6':
        tipo_ = Maestro;
        break;

    default:
        tipo_ = Otro;
        break;
    }

    U.es_titular_de(*this);
}

Cadena Tarjeta::titular_facial() const
{
    return str_toupper(usuario_->nombre()) + " " + str_toupper(usuario_->apellidos());
}

void Tarjeta::anula_titular()
{
    usuario_ = nullptr;
    estado_ = false;
}

bool Tarjeta::activa(bool est)
{
    estado_ = est;
    return estado_;
}

Tarjeta::~Tarjeta()
{
    if (Usuario *U = const_cast<Usuario *>(usuario_))
        U->no_es_titular_de(*this);
}

std::ostream &operator<<(std::ostream &os, const Tarjeta &T)
{
    os << T.tipo() << std::endl
       << T.numero() << std::endl
       << T.titular_facial() << std::endl
       << "Caduca: " << std::setfill('0') << std::setw(2)
       << T.caducidad().mes() << '/' << std::setw(2)
       << (T.caducidad().anno() % 100);

    return os;
}

std::ostream &operator<<(std::ostream &os, const Tarjeta::Tipo &t)
{
    switch (t)
    {
    case Tarjeta::Tipo::VISA:
        os << "VISA";
        break;

    case Tarjeta::Tipo::Mastercard:
        os << "Mastercard";
        break;

    case Tarjeta::Tipo::Maestro:
        os << "Maestro";
        break;

    case Tarjeta::Tipo::JCB:
        os << "JCB";
        break;

    case Tarjeta::Tipo::AmericanExpress:
        os << "AmericanExpress";
        break;

    default:
        os << "Tipo indeterminado";
        break;
    }

    return os;
}

bool operator<(const Tarjeta &T1, const Tarjeta &T2)
{
    return T1.numero() < T2.numero();
}
#include <algorithm>
#include <cctype>
#include <cstring>
#include <iomanip>
#include "tarjeta.hpp"

bool luhn(const Cadena &cad);
 
static Cadena str_toupper(Cadena s)
{
    std::transform(s.begin(), s.end(), s.begin(), [](unsigned char c) { return std::toupper(c); });
    
    return s;
}

Numero::Numero(const Cadena &n)
{
    Cadena aux(n);

    aux = aux.substr(0, std::remove_if(aux.begin(), aux.end(), [](unsigned char x) { return std::isspace(x); }) - aux.begin());

    if (aux.length() < 13 || aux.length() > 19 || aux.length() == 0)
        throw Incorrecto(Razon::LONGITUD);

    num_ = aux;

    if (std::count_if(num_.begin(), num_.end(), static_cast<int (*)(int)>(std::isdigit)) != num_.length())
        throw Incorrecto(Razon::DIGITOS);

    std::cout << num_ << std::endl;

    if (!luhn(num_))
        throw Incorrecto(Razon::NO_VALIDO);
}

Numero::operator const char *() const
{
    return cad_.c_str();
}

bool operator<(const Numero &N1, const Numero &N2)
{
    return strcmp(N1, N2) < 0;
}

Tarjeta::Tarjeta(Numero N, Usuario &U, Fecha F) : num_(N),
                                                  user_(&U),
                                                  caducidad_(F),
                                                  estado_(true)
{
    if (Fecha() > caducidad_)
        throw Caducada(caducidad_);

    U.es_titular_de(*this);

    switch (N[0])
    {
    case '3':
        switch (N[1])
        {
        case '4':
        case '7':
            t_ = JCB;
            break;

        default:
            t_ = AmericanExpress;
            break;
        }
        break;

    case '4':
        t_ = VISA;
        break;

    case '5':
        t_ = Mastercard;
        break;

    case '6':
        t_ = Maestro;
        break;

    default:
        t_ = Otro;
        break;
    }
}

Cadena Tarjeta::titular_facial() const
{
    return str_toupper(user_->nombre()) + " " + str_toupper(user_->apellidos());
}

void Tarjeta::anula_titular()
{
    user_ = nullptr;
    estado_ = false;
}

bool Tarjeta::activa(bool est)
{
    estado_ = est;
    return estado_;
}

Tarjeta::~Tarjeta()
{
    if (Usuario *U = const_cast<Usuario *>(user_))
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
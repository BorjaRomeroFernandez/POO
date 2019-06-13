#include "usuario.hpp"

extern "C"
{
#include <unistd.h>
}

#include <cstring>
#include <iomanip>
#include <random>

#define caracteres "zyxwvutsrqponmlkjihgfedcba.ZYXWVUTSRQPONMLKJIHGFEDCBA/9876543210"

Clave::Clave(const char *c)
{
    if (strlen(c) < 5)
        throw Clave::Incorrecta(Clave::CORTA);

    const char *seed = caracteres;

    char salt[2];
    salt[0] = seed[rand() % 64];
    salt[1] = seed[rand() % 64];

    if (crypt(c, salt) == nullptr)
        throw Clave::Incorrecta(Clave::ERROR_CRYPT);

    clave_ = crypt(c, salt);
}

bool Clave::verifica(const char *c) const
{
    if (const char *const pw = crypt(c, clave_.c_str()))
        return pw == clave_;

    throw Incorrecta(Razon::ERROR_CRYPT);
}

Usuario::Usuarios Usuario::user_;

Usuario::Usuario(const Cadena &i, const Cadena &n, const Cadena &a, const Cadena &d, const Clave &c) : identificador_(i),
                                                                                                       nombre_(n),
                                                                                                       apellidos_(a),
                                                                                                       direccion_(d),
                                                                                                       clave_(c)
{
    if (!user_.insert(id).second)
        throw Id_duplicado(identificador_);
}

void Usuario::es_titular_de(Tarjeta &T)
{
    if (this == T.titular())
    {
        t_.insert(std::make_pair(T.numero(), &T));
    }
}

void Usuario::no_es_titular_de(Tarjeta &T)
{
    T.anula_titular();
    t_.erase(T.numero());
}

void Usuario::compra(Articulo &A, unsigned c)
{
    if (c == 0)
        art_.erase(&A);
    else
        art_[&A] = c;
}

Usuario::~Usuario()
{
    for (auto &[numero, tarjeta] : t_)
        tarjeta->anula_titular();

    user_.erase(identificador_);
}

std::ostream &operator<<(std::ostream &os, const Usuario &U)
{
    os << U.identificador_ << "[" << U.clave_.clave().c_str() << "]"
       << U.nombre_ << U.apellidos_ << std::endl
       << U.direccion_ << std::endl
       << "Tarjetas:" << std::endl;

    for (const auto &[numero, tarjeta] : user.tarjetas())
        os << *tarjeta << std::endl;

    return os;
}

std::ostream &mostrar_carro(std::ostream &os, const Usuario &U)
{
    os << "Carrito de compra de " << U.id() << " [Artículos: "
       << U.n_articulos() << "]\n Cant. Artículo\n"
       << Cadena(95, '=') + "\n";

    for (const auto &[articulo, cantidad] : U.compra())
    {
        os << std::setw(4) << cantidad << "   "
           << "[" << articulo->referencia() << "] \"" << articulo->titulo()
           << "\", " << articulo->f_publi().anno() << ". " << std::fixed
           << std::setprecision(2) << articulo->precio() << " €\n";
    }

    return os;
}
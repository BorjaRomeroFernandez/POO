#include "usuario.hpp"
#include <cstring>
#include <unistd.h>
#include <cstdlib>
#include <utility>

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

    password_ = crypt(c, salt);
}

bool Clave::verifica(const char *c) const
{
    return (password_ == crypt(c, password_.c_str()));
}

Usuario::Usuarios Usuario::usuarios_;

Usuario::Usuario(const Cadena &i, const Cadena &n, const Cadena &a, const Cadena &d, const Clave &c) : identificador_(i),
                                                                                                       nombre_(n),
                                                                                                       apellidos_(a),
                                                                                                       direccion_(d),
                                                                                                       contrasena_(c)
{
    if (!usuarios_.insert(i).second)
        throw Id_duplicado(identificador_);
}

void Usuario::es_titular_de(Tarjeta &T)
{
    if (this == T.titular())
        tarjetas_.insert(std::pair<Numero, Tarjeta *>(T.numero(), &T));
}

void Usuario::no_es_titular_de(Tarjeta &T)
{
    T.anula_titular();
    tarjetas_.erase(T.numero());
}

void Usuario::compra(Articulo &A, unsigned c)
{
    if (c == 0)
    {
        articulos_.erase(&A);
    }
    else
    {
        if (articulos_.find(&A) == articulos_.end())
        {
            articulos_.insert(std::pair<Articulo *, unsigned>(&A, c));
        }
        else
        {
            articulos_.find(&A)->second = c;
        }
    }
}

unsigned Usuario::n_articulos() const
{
    unsigned cont = 0;
    std::unordered_map<Articulo *, unsigned int>::iterator it;

    for (it = this->compra().begin(); it != articulos_.end(); ++it)
    {
        cont++;
    }

    return cont;
}

Usuario::~Usuario()
{
    for (auto &[numero, tarjeta] : tarjetas_)
        tarjeta->anula_titular();

    usuarios_.erase(identificador_);
}

std::ostream &operator<<(std::ostream &os, const Usuario &U)
{
    os
        << U.id() << " [" << U.contrasena_.clave().c_str() << "] " << U.nombre() << " " << U.apellidos() << std::endl
        << U.direccion() << std::endl
        << "Tarjetas:" << std::endl;

    std::map<Numero, Tarjeta *>::iterator it;

    for (it = U.tarjetas().begin(); it != U.tarjetas().end(); ++it)
    {
        os << it->second;
    }

    return os;
}

void mostrar_carro(std::ostream &os, const Usuario &U)
{
    os
        << "Carrito de compra de " << U.id() << " [Artículos: " << U.n_articulos() << "]" << std::endl
        << " Cant. Artículo" << std::endl
        << Cadena(59, '=') << std::endl;

    std::unordered_map<Articulo *, unsigned int>::iterator it;

    for (it = U.compra().begin(); it != U.compra().end(); ++it)
    {
        os << "   " << it->second << "   " << it->first << std::endl;
    }
}
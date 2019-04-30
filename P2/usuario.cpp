#include <cstring>
#include <unistd.h>
#include <cstdlib>
#include "usuario.hpp"

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

bool Clave::verifica(const char *c)
{
    return (password_ == (c, password_.c_str()));
}

/////////////////////////////////////////////////////////////////////////////////////////


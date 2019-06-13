#include <cstring>
#include <stdexcept>
#include "cadena.hpp"
 
Cadena::Cadena(unsigned tamano, char caracter) : s_(new char[tamano + 1]),
                                                 tam_(tamano)
{
    std::memset(s_, caracter, tam_);

    s_[tam_] = '\0';
}

Cadena::Cadena(const Cadena &C) : s_(new char[C.tam_ + 1]),
                                  tam_(C.tam_)
{
    strcpy(s_, C.s_);
}

Cadena::Cadena(const char *cadena) : s_(new char[std::strlen(cadena) + 1]),
                                     tam_(std::strlen(cadena))
{
    std::strcpy(s_, cadena);
}

Cadena::Cadena(Cadena &&C) : s_(C.s_), tam_(C.tam_)
{
    C.tam_ = 0;
    C.s_ = nullptr;
}

Cadena &Cadena::operator=(const Cadena &C) noexcept
{
    if (this != &C)
    {
        delete[] s_;

        tam_ = C.tam_;
        s_ = new char[tam_ + 1];

        std::strcpy(s_, C.s_);
    }

    return *this;
}

Cadena &Cadena::operator=(const char *cadena) noexcept
{
    delete[] s_;

    tam_ = std::strlen(cadena);

    s_ = new char[tam_ + 1];
    std::strcpy(s_, cadena);

    return *this;
}

Cadena &Cadena::operator=(Cadena &&C) noexcept
{
    if (this != &C)
    {
        delete[] s_;

        tam_ = C.tam_;
        s_ = C.s_;

        C.s_ = nullptr;
        C.tam_ = 0;
    }

    return *this;
}

Cadena &Cadena::operator+=(const Cadena &C) noexcept
{
    Cadena t = *this;
    tam_ = t.tam_ + C.tam_;

    delete[] s_;

    s_ = new char[tam_ + 1];

    std::strcpy(s_, t.s_);
    std::strcat(s_, C.s_);

    return *this;
}

char &Cadena::operator[](int n) noexcept
{
    return this->s_[n];
}

char Cadena::operator[](int n) const noexcept
{
    return this->s_[n];
}

const char *Cadena::c_str() const noexcept
{
    return s_;
}

char &Cadena::at(unsigned n)
{
    if (n >= tam_)
        throw std::out_of_range("Fuera de rango");

    return s_[n];
}

char Cadena::at(unsigned n) const
{
    if (n >= tam_)
        throw std::out_of_range("Fuera de rango");

    return s_[n];
}

Cadena Cadena::substr(unsigned indice, unsigned tamano) const
{
    if (indice >= tam_ || indice + tamano > tam_ || indice + tamano < indice)
        throw std::out_of_range("Error de rango");

    Cadena x(tamano);

    std::strncpy(x.s_, s_ + indice, tamano);
    x.s_[tamano] = '\0';

    return x;
}

Cadena::~Cadena()
{
    delete[] s_;
}

Cadena operator+(const Cadena &C1, const Cadena &C2)
{
    return Cadena(C1) += C2;
}

bool operator==(const Cadena &C1, const Cadena &C2) noexcept
{
    return (strcmp(C1.c_str(), C2.c_str()) == 0);
}

bool operator!=(const Cadena &C1, const Cadena &C2) noexcept
{
    return !(C1 == C2);
}

bool operator>(const Cadena &C1, const Cadena &C2) noexcept
{
    return (C2 < C1);
}

bool operator<(const Cadena &C1, const Cadena &C2) noexcept
{
    return (strcmp(C1.c_str(), C2.c_str()) < 0);
}

bool operator>=(const Cadena &C1, const Cadena &C2) noexcept
{
    return !(C1 < C2);
}

bool operator<=(const Cadena &C1, const Cadena &C2) noexcept
{
    return !(C2 < C1);
}

std::ostream &operator<<(std::ostream &os, const Cadena &C)
{
    os << C.c_str();

    return os;
}

std::istream &operator>>(std::istream &is, Cadena &C)
{

    char *cadena = new char[33];
    int i = 0;
    char aux;

    while (isspace(is.get()) && is.good())
    {
    }

    is.unget();

    while (i < 32 && !isspace(is.peek()) && is.good() && is.peek() != '\n' && is.peek() != '\0')
    {
        aux = is.get();

        if (is.good())
            cadena[i++] = aux;
    }

    cadena[i] = '\0';
    C = cadena;

    delete[] cadena;

    return is;
}

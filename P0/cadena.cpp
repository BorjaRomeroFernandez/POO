#include "cadena.hpp"
#include <cstdio>
#include <cstring>
#include <iostream>

Cadena::Cadena(unsigned tamano, char caracter) : s_(new char[tamano + 1]),
                                                 tam_(tamano)
{
    for (unsigned i = 0; i < tamano; ++i)
        this->s_[i] = caracter;

    this->s_[tamano] = '\0';
}

Cadena::Cadena(const Cadena &C) : s_(new char[C.tam_ + 1]),
                                  tam_(C.length())
{
    strcpy(this->s_, C.s_);
}

Cadena::Cadena(const char *cadena) : s_(new char[strlen(cadena) + 1]),
                                     tam_(strlen(cadena))
{
    strcpy(this->s_, cadena);

    this->s_[this->tam_] = '\0';
}

Cadena &Cadena::operator=(const Cadena &C) noexcept
{
    if (this->length() == C.length())
    {
        strcpy(this->s_, C.s_);
    }
    else
    {
        delete[] this->s_;
        this->tam_ = C.length();
        this->s_ = new char[this->tam_ + 1];
        strcpy(this->s_, C.s_);
    }

    return *this;
}

Cadena &Cadena::operator=(const char *cadena) noexcept
{
    if (this->tam_ == strlen(cadena))
    {
        strcpy(this->s_, cadena);
    }
    else
    {
        delete[] this->s_;
        this->tam_ = strlen(cadena);
        this->s_ = new char[this->tam_ + 1];
        strcpy(this->s_, cadena);
    }

    this->s_[this->tam_] = '\0';

    return *this;
}

Cadena::operator const char *() const noexcept
{
    return this->s_;
}

Cadena &Cadena::operator+=(const Cadena &C) noexcept
{
    char *aux = new char[this->tam_];
    unsigned i = 0;

    while (i < this->tam_)
    {
        aux[i] = this->s_[i];
        ++i;
    }

    strcat(aux, C.s_);

    delete[] this->s_;
    this->tam_ += C.length();
    this->s_ = new char[this->length() + 1];
    strcpy(this->s_, aux);

    delete[] aux;

    return *this;
}

Cadena Cadena::operator+(const Cadena &C) const noexcept
{
    Cadena t = *this;

    return t += C;
}

char &Cadena::operator[](int n) noexcept
{
    return this->s_[n];
}

const char &Cadena::operator[](int n) const noexcept
{
    return this->s_[n];
}

char &Cadena::at(unsigned n)
{
    if (n < 0 || n > this->tam_ - 1)
        throw std::out_of_range("El índice es inválido");
    else
        return this->s_[n];
}

const char Cadena::at(unsigned n) const
{
    if (n < 0 || n >= this->tam_)
        throw std::out_of_range("El índice es inválido");

    return this->s_[n];
}

Cadena Cadena::substr(unsigned indice, unsigned tamano) const
{
    if (indice > this->tam_ - 1 || (indice + tamano) > this->tam_ - 1 || tamano > this->tam_ - 1)
        throw std::out_of_range("El índice es invá lido");

    char *aux = new char[tamano];

    unsigned i = 0;

    while (i < tamano)
    {
        aux[i] = this->s_[indice + i];

        ++i;
    }

    return Cadena(aux);
}

Cadena::~Cadena()
{
    this->tam_ = 0;
    delete[] this->s_;
}

bool operator==(const Cadena &C1, const Cadena &C2) noexcept
{
    return (strcmp(C1, C2) == 0);
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
    return (strcmp(C1, C2) < 0);
}

bool operator>=(const Cadena &C1, const Cadena &C2) noexcept
{
    return !(C1 < C2);
}

bool operator<=(const Cadena &C1, const Cadena &C2) noexcept
{
    return !(C2 < C1);
}
#include <cstring>
#include <iostream>
#include "cadena.hpp"

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

Cadena Cadena::operator=(const Cadena &C)
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
}

Cadena Cadena::operator=(const char *cadena)
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
}

Cadena::operator const char *()
{
    std::cout << this->s_ << std::endl;
}

Cadena Cadena::operator+=(const Cadena &C)
{
    char *aux = new char[this->tam_];
    int i = 0;

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
}

Cadena Cadena::operator+(const Cadena &C)
{
    Cadena t = *this;

    return t += C;
}

char Cadena::operator[](int n)
{
    return this->s_[n];
}

const char Cadena::operator[](int n) const
{
    return this->s_[n];
}

char Cadena::at(int n)
{
    if (n < 0 || n > this->tam_ - 1)
        throw std::out_of_range("El índice es inválido");
    else
        return this->s_[n];
}

const char Cadena::at(int n) const
{
    if (n < 0 || n > this->tam_ - 1)
        throw std::out_of_range("El índice es inválido");
    else
        return this->s_[n];
}

Cadena Cadena::substr(unsigned indice, unsigned tamano)
{
    if(indice > this->tam_ - 1 || (indice + tamano) > this->tam_ - 1)
        throw std::out_of_range("El índice es inválido");

    char* aux = new char[tamano + 1];
    unsigned i = indice;

    while(i < indice + tamano)
    {
        aux[i] = this->s_[i];
    }

    aux[indice + tamano] = '\0';

    return *this;
}

Cadena::~Cadena()
{
    
}
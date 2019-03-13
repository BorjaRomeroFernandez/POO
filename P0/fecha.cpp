#include "fecha.hpp"
#include <ctime>
#include <cstdio>

Fecha::Fecha(int d, int m, int a) : dia_(d), mes_(m), anno_(a)
{
    std::time_t tiempo_actual = std::time(nullptr);
    std::tm *fecha_actual = std::localtime(&tiempo_actual);

    if (dia_ == 0)
        dia_ = fecha_actual->tm_mday;

    if (mes_ == 0)
        mes_ = fecha_actual->tm_mon + 1;

    if (anno_ == 0)
        anno_ = fecha_actual->tm_year + 1900;

    valida();
}

Fecha::Fecha(const char *fecha)
{
    std::time_t tiempo_actual = std::time(nullptr);
    std::tm *fecha_actual = std::localtime(&tiempo_actual);

    sscanf(fecha, "%02d/%02d/%4d", &dia_, &mes_, &anno_);

    if (dia_ == 0)
        dia_ = fecha_actual->tm_mday;

    if (mes_ == 0)
        mes_ = fecha_actual->tm_mon + 1;

    if (anno_ == 0)
        anno_ = fecha_actual->tm_year + 1900;

    valida();
}

void Fecha::valida()
{
    if (anno_ < Fecha::AnnoMinimo || anno_ > Fecha::AnnoMaximo)
        throw Fecha::Invalida("El año es inválido");

    if (mes_ < 1 || mes_ > 12)
        throw Fecha::Invalida("El mes es inválido");

    if (mes_ == 1 || mes_ == 3 || mes_ == 5 || mes_ == 7 || mes_ == 8 || mes_ == 10 || mes_ == 12)
    {
        if (dia_ < 1 || dia_ > 31)
            throw Fecha::Invalida("El día es inválido: el mes tiene 31 días");
    }
    else
    {
        if (mes_ != 2)
        {
            if (dia_ < 1 || dia_ > 30)
                throw Fecha::Invalida("El día es inválido: el mes tiene 30 días");
        }
        else
        {
            if (anno_ % 4 == 0 && (anno_ % 400 == 0 || anno_ % 100 != 0))
                if (dia_ < 1 || dia_ > 29)
                    throw Fecha::Invalida("El día es inválido: el mes tiene 29 días");
                else
                {
                    if (dia_ < 1 || dia_ > 28)
                        throw Fecha::Invalida("El día es inválido: el mes tiene 28 días");
                }
        }
    }
}

Fecha &Fecha::operator++()
{
    return (*this += 1);
}

Fecha &Fecha::operator++(int)
{
    Fecha t = *this;
    *this += 1;

    return t;
}

Fecha &Fecha::operator--()
{
    return (*this += -1);
}

Fecha &Fecha::operator--(int)
{
    Fecha t = *this;
    *this += -1;

    return t;
}
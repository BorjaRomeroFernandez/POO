#include <ctime>
#include <cstdio>
#include <iostream>
#include "fecha.hpp"

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

Fecha &Fecha::operator+(int n)
{
    Fecha t = *this;

    return t += n;
}

Fecha &Fecha::operator-(int n)
{
    Fecha t = *this;

    return t += -n;
}

Fecha &Fecha::operator-=(int n)
{
    return *this += -n;
}

Fecha &Fecha::operator+=(int n)
{
    this->dia_ += n;

    tm *fecha;

    fecha->tm_mday = this->dia_;
    fecha->tm_mon = this->mes_;
    fecha->tm_year = this->anno_;

    mktime(fecha);

    this->dia_ = fecha->tm_mday;
    this->mes_ = fecha->tm_mon;
    this->anno_ = fecha->tm_year;

    return *this;
}

Fecha &Fecha::operator=(const Fecha &F)
{
    this->dia_ = F.dia();
    this->mes_ = F.mes();
    this->anno_ = F.anno();

    return *this;
}

Fecha::operator const char *()
{
    tm *fecha;

    fecha->tm_mday = this->dia_;
    fecha->tm_mon = this->mes_;
    fecha->tm_year = this->anno_;

    mktime(fecha);

    const char *DIASEM;
    const char *MES;

    switch (fecha->tm_wday)
    {
    case 0:
        DIASEM = "lunes";
        break;
    case 1:
        DIASEM = "martes";
        break;
    case 2:
        DIASEM = "miércoles";
        break;
    case 3:
        DIASEM = "jueves";
        break;
    case 4:
        DIASEM = "viernes";
        break;
    case 5:
        DIASEM = "sábado";
        break;
    case 6:
        DIASEM = "domingo";
        break;
    }

    switch (fecha->tm_mon)
    {
    case 0:
        MES = "enero";
        break;
    case 1:
        MES = "debrero";
        break;
    case 2:
        MES = "marzo";
        break;
    case 3:
        MES = "abril";
        break;
    case 4:
        MES = "mayo";
        break;
    case 5:
        MES = "junio";
        break;
    case 6:
        MES = "julio";
        break;
    case 7:
        MES = "agosto";
        break;
    case 8:
        MES = "septiembre";
        break;
    case 9:
        MES = "octubre";
        break;
    case 10:
        MES = "noviembre";
        break;
    case 11:
        MES = "diciembre";
        break;
    }

    std::cout << DIASEM << " " << fecha->tm_mday << " de " << MES << " de " << fecha->tm_year;
}

bool operator==(const Fecha &F1, const Fecha &F2)
{
    return (F1.dia() == F2.dia() && F1.mes() == F2.mes() && F1.anno() == F2.anno()) ? true : false;
}

bool operator!=(const Fecha &F1, const Fecha &F2)
{
    return !(F1 == F2);
}

bool operator>(const Fecha &F1, const Fecha &F2)
{
    return F2 < F1;
}

bool operator<(const Fecha &F1, const Fecha &F2)
{
    if (F1.anno() < F2.anno())
    {
        return true;
    }
    else
    {
        if (F1.anno() == F2.anno())
        {
            if (F1.mes() < F2.mes())
            {
                return true;
            }
            else
            {
                if (F1.mes() == F2.mes())
                {
                    if (F1.dia() < F2.dia())
                    {
                        return true;
                    }
                    else
                    {
                        return false;
                    }
                }
            }
        }
    }
}

bool operator>=(const Fecha &F1, const Fecha &F2)
{
    return !(F1 < F2);
}

bool operator<=(const Fecha &F1, const Fecha &F2)
{
    return !(F2 < F1);
}

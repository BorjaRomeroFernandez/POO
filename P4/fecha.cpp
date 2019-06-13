#include <ctime>
#include <cstdio>
#include <cstring>
#include "fecha.hpp"
 
Fecha::Fecha(int d, int m, int a) : dia_(d),
                                    mes_(m),
                                    anno_(a)
{
    std::time_t tiempo_actual = std::time(nullptr);
    std::tm fecha_actual = *std::localtime(&tiempo_actual);

    if (dia_ == 0)
        dia_ = fecha_actual.tm_mday;

    if (mes_ == 0)
        mes_ = fecha_actual.tm_mon + 1;

    if (anno_ == 0)
        anno_ = fecha_actual.tm_year + 1900;

    valida();
}

Fecha::Fecha(const char *fecha)
{
    std::time_t tiempo_actual = std::time(nullptr);
    std::tm fecha_actual = *std::localtime(&tiempo_actual);

    if (sscanf(fecha, "%d/%d/%d", &dia_, &mes_, &anno_) != 3)
        throw Fecha::Invalida("Formato incorrecto");

    if (dia_ == 0)
        dia_ = fecha_actual.tm_mday;

    if (mes_ == 0)
        mes_ = fecha_actual.tm_mon + 1;

    if (anno_ == 0)
        anno_ = fecha_actual.tm_year + 1900;

    valida();
}

void Fecha::valida() const
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
            {
                if (dia_ < 1 || dia_ > 29)
                {
                    throw Fecha::Invalida("El día es inválido: el mes tiene 29 días");
                }
            }
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
    return *this += 1;
}

Fecha Fecha::operator++(int)
{
    Fecha t = *this;
    *this += 1;

    return t;
}

Fecha &Fecha::operator--()
{
    return *this += -1;
}

Fecha Fecha::operator--(int)
{
    Fecha t = *this;
    *this += -1;

    return t;
}

Fecha Fecha::operator+(int n) const
{
    Fecha t = *this;

    return t += n;
}

Fecha Fecha::operator-(int n) const
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
    if (n != 0)
    {
        std::tm time_tm = std::tm{0, 0, 0, (dia_ + n), (mes_ - 1), (anno_ - 1900), 0, 0, 0, 0, 0};

        std::mktime(&time_tm);

        dia_ = time_tm.tm_mday;
        mes_ = time_tm.tm_mon + 1;
        anno_ = time_tm.tm_year + 1900;

        valida();
    }

    return *this;
}

const char *Fecha::cadena() const
{
    static char cadena[40];

    std::tm fecha = std::tm{0, 0, 0, dia_, (mes_ - 1), (anno_ - 1900), 0, 0, 0, 0, 0};

    std::mktime(&fecha);

    const char *DIASEM[] = {"domingo", "lunes", "martes", "miércoles", "jueves", "viernes", "sábado"};
    const char *MES[] = {"enero", "febrero", "marzo", "abril", "mayo", "junio", "julio", "agosto", "septiembre", "octubre", "noviembre", "diciembre"};

    sprintf(cadena, "%s %d de %s de %d", DIASEM[fecha.tm_wday], fecha.tm_mday, MES[fecha.tm_mon], fecha.tm_year + 1900);

    return cadena;
}

bool operator==(const Fecha &fecha1, const Fecha &fecha2) noexcept
{
    return (fecha1.dia() == fecha2.dia()) && (fecha1.mes() == fecha2.mes()) &&
           (fecha1.anno() == fecha2.anno());
}
bool operator!=(const Fecha &fecha1, const Fecha &fecha2) noexcept
{
    return !(fecha1 == fecha2);
}

bool operator<(const Fecha &fecha1, const Fecha &fecha2) noexcept
{
    if (fecha1.anno() < fecha2.anno())
        return true;
    else if (fecha1.anno() > fecha2.anno())
        return false;
    else if (fecha1.mes() < fecha2.mes())
        return true;
    else if (fecha1.mes() > fecha2.mes())
        return false;
    else
        return fecha1.dia() < fecha2.dia();
}
bool operator>(const Fecha &fecha1, const Fecha &fecha2) noexcept
{
    return fecha2 < fecha1;
}

bool operator<=(const Fecha &fecha1, const Fecha &fecha2) noexcept
{
    return ((fecha1 < fecha2) || (fecha1 == fecha2));
}

bool operator>=(const Fecha &fecha1, const Fecha &fecha2) noexcept
{
    return !(fecha1 < fecha2);
}

std::ostream &operator<<(std::ostream &os, const Fecha &F)
{
    os << F.cadena();

    return os;
}

std::istream &operator>>(std::istream &is, Fecha &F)
{
    char x[11];

    is.getline(x, 11);

    try
    {
        F = Fecha(x);
    }
    catch (const Fecha::Invalida &e)
    {
        is.setstate(std::ios_base::failbit);
        throw;
    }

    return is;
}
#ifndef ARTICULO_HPP_
#define ARTICULO_HPP_
 
#include "cadena.hpp"
#include "fecha.hpp"
#include <iostream>
#include <set>

class Autor
{
public:
    Autor(const Cadena &n, const Cadena &a, const Cadena &d);

    Cadena nombre() const noexcept { return nombre_; }
    Cadena apellidos() const noexcept { return apellidos_; }
    Cadena direccion() const noexcept { return direccion_; }

private:
    Cadena nombre_;
    Cadena apellidos_;
    Cadena direccion_;
};

class Articulo
{
public:
    typedef std::set<Autor *> Autores;

    Articulo(Autores &a, const Cadena &r, const Cadena &t, const Fecha &f, double p);

    const Autores &autores() const noexcept { return autores_; }
    const Cadena &referencia() const noexcept { return referencia_; };
    const Cadena &titulo() const noexcept { return titulo_; };
    const Fecha &f_publi() const noexcept { return f_publi_; };
    double precio() const noexcept { return precio_; };
    double &precio() noexcept { return precio_; };

    virtual void impresion_especifica(std::ostream &os) const noexcept = 0;

    class Autores_vacios
    {
    };

    virtual ~Articulo() {}

private:
    const Autores autores_;
    Cadena referencia_;
    Cadena titulo_;
    Fecha f_publi_;
    double precio_;
};

std::ostream &operator<<(std::ostream &os, const Articulo &A) noexcept;

class ArticuloAlmacenable : public Articulo
{
public:
    ArticuloAlmacenable(Autores &a, const Cadena &r, const Cadena &t, const Fecha &f, double p, unsigned s = 0);

    unsigned stock() const noexcept { return stock_; };
    unsigned &stock() noexcept { return stock_; };

    virtual void impresion_especifica(std::ostream &) const noexcept = 0;

    virtual ~ArticuloAlmacenable() {}

protected:
    unsigned stock_;
};

class Libro : public ArticuloAlmacenable
{
public:
    Libro(Autores &a, const Cadena &r, const Cadena &t, const Fecha &f, double p, unsigned pa, unsigned s = 0);

    unsigned n_pag() const noexcept { return paginas_; }

    virtual void impresion_especifica(std::ostream &) const noexcept;

private:
    const unsigned paginas_;
};

class Cederron : public ArticuloAlmacenable
{
public:
    Cederron(Autores &a, const Cadena &r, const Cadena &t, const Fecha &f, double p, unsigned ta, unsigned s = 0);

    unsigned tam() const noexcept { return tamano_; }

    virtual void impresion_especifica(std::ostream &) const noexcept;

private:
    const unsigned tamano_;
};

class LibroDigital : public Articulo
{
public:
    LibroDigital(Autores &a, const Cadena &r, const Cadena &t, const Fecha &f, double p, const Fecha &e);

    const Fecha f_expir() const noexcept { return expiracion_; }

    virtual void impresion_especifica(std::ostream &) const noexcept;

private:
    const Fecha expiracion_;
};

#endif
#ifndef USUARIO_HPP_
#define USUARIO_HPP_

#include <map>
#include <unordered_map>
#include <unordered_set>
#include "cadena.hpp"
#include "tarjeta.hpp"
#include "articulo.hpp"

class Tarjeta;
class Numero;

class Clave
{
public:
    enum Razon
    {
        CORTA,
        ERROR_CRYPT
    };

    Clave(const char *c);

    class Incorrecta
    {
    public:
        Incorrecta(Razon r) : razon_(r) {}
        Razon razon() const noexcept { return razon_; }

    private:
        Razon razon_;
    };

    const Cadena &clave() const noexcept { return clave_; };

    bool verifica(const char *c) const;

private:
    Cadena clave_;
};

/////////////////////////////////////////////////////////////////////////////////////////////

class Usuario
{
public:
    typedef std::map<Numero, Tarjeta *> Tarjetas;
    typedef std::unordered_map<Articulo *, unsigned> Articulos;
    typedef std::unordered_set<Cadena> Usuarios;

    Usuario(const Cadena &i, const Cadena &n, const Cadena &a, const Cadena &d, const Clave &c);
    Usuario(const Usuario &) = delete;
    
    Usuario &operator=(const Usuario &) = delete;

    class Id_duplicado
    {
    public:
        Id_duplicado(const Cadena &c) : id_(c) {}
        const Cadena idd() const noexcept { return id_; };

    private:
        Cadena id_;
    };

    void es_titular_de(Tarjeta &T);
    void no_es_titular_de(Tarjeta &T);

    Cadena id() const noexcept { return identificador_; }
    Cadena nombre() const noexcept { return nombre_; }
    Cadena apellidos() const noexcept { return apellidos_; }
    Cadena direccion() const noexcept { return direccion_; }
    const Tarjetas &tarjetas() const noexcept { return t_; }
    const Articulos &compra() const noexcept { return art_; }
    size_t n_articulos() const noexcept { return art_.size(); }

    void compra(Articulo &A, unsigned c = 1);

    friend std::ostream &operator<<(std::ostream &os, const Usuario &U);

    ~Usuario();

private:
    Cadena identificador_;
    Cadena nombre_;
    Cadena apellidos_;
    Cadena direccion_;
    Clave clave_;
    static Usuarios user_;
    Tarjetas t_;
    Articulos art_;
};

std::ostream &mostrar_carro(std::ostream &os, const Usuario &U);

#endif
#ifndef PEDIDO_HPP_
#define PEDIDO_HPP_

#include "fecha.hpp"
#include "tarjeta.hpp"
#include <ostream>

class Pedido_Articulo;
class Usuario_Pedido;

class Pedido
{
public:
    Pedido(Usuario_Pedido &UP, Pedido_Articulo &PA, Usuario &U, const Tarjeta &T, const Fecha &F = Fecha());

    class Vacio
    {
    public:
        Vacio(Usuario *U) : usuario_(U){};
        Usuario &usuario() const { return *usuario_; }

    private:
        Usuario *usuario_;
    };

    class Impostor
    {
    public:
        Impostor(Usuario *U) : usuario_(U){};
        Usuario &usuario() const { return *usuario_; }

    private:
        Usuario *usuario_;
    };

    class SinStock
    {
    public:
        SinStock(Articulo *A) : articulo_(A){};
        Articulo &articulo() const { return *articulo_; }

    private:
        Articulo *articulo_;
    };

    int numero() const noexcept { return numero_; };
    Tarjeta const *tarjeta() const noexcept { return tarjeta_; };
    Fecha fecha() const noexcept { return fecha_; };
    double total() const noexcept { return total_; };
    static int n_total_pedidos() noexcept { return cantidad_; };

private:
    inline static int cantidad_ = 0;
    int numero_;
    const Tarjeta *tarjeta_;
    Fecha fecha_;
    double total_;
};

std::ostream &operator<<(std::ostream &os, const Pedido &P);

#endif
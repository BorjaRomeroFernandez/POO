#ifndef PEDIDO_ARTICULO_HPP_
#define PEDIDO_ARTICULO_HPP_
 
#include <ostream>
#include "articulo.hpp"
#include "pedido.hpp"

class LineaPedido
{
public:
    explicit LineaPedido(double p, unsigned c = 1);

    double precio_venta() const noexcept { return precio_; }
    unsigned cantidad() const noexcept { return cantidad_; }

private:
    double precio_;
    unsigned cantidad_;
};

/////////////////////////////////////////////////////////////////////////////////////////

struct OrdenaPedidos : std::binary_function<const Pedido *, const Pedido *, bool>
{
    bool operator()(const Pedido *P1, const Pedido *P2) const;
};

struct OrdenaArticulos : std::binary_function<const Articulo *, const Articulo *, bool>
{
    bool operator()(const Articulo *A1, const Articulo *A2) const;
};

/////////////////////////////////////////////////////////////////////////////////////////

class Pedido_Articulo
{
public:
    typedef std::map<Articulo *, LineaPedido, OrdenaArticulos> ItemsPedido;
    typedef std::map<Pedido *, LineaPedido, OrdenaPedidos> Pedidos;

    void pedir(Pedido &P, Articulo &A, double p, unsigned c = 1);
    void pedir(Articulo &A, Pedido &P, double p, unsigned c = 1);

    ItemsPedido &detalle(Pedido &P);
    Pedidos ventas(Articulo &A);

    std::ostream &mostrarDetallePedidos(std::ostream &os);
    std::ostream &mostrarVentasArticulos(std::ostream &os);

private:
    std::map<Pedido *, ItemsPedido, OrdenaPedidos> PA;
    std::map<Articulo *, Pedidos, OrdenaArticulos> AP;
};

std::ostream &operator<<(std::ostream &os, const LineaPedido &LP);
std::ostream &operator<<(std::ostream &os, const Pedido_Articulo::Pedidos &P);
std::ostream &operator<<(std::ostream &os, const Pedido_Articulo::ItemsPedido &I);

#endif
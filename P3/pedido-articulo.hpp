#ifndef PEDIDO_ARTICULO_HPP_
#define PEDIDO_ARTICULO_HPP_

#include <ostream>
#include <map>
#include "articulo.hpp"
#include "pedido.hpp"

class LineaPedido
{
public:
    explicit LineaPedido(double p, unsigned c = 1) : precvent_(p), cant_(c) {}
    
    double precio_venta() const noexcept { return precvent_; }
    unsigned cantidad() const noexcept { return cant_; }

private:
    double precvent_;
    unsigned cant_;
};

struct OrdenaPedidos
{
    bool operator()(const Pedido *P1, const Pedido *P2) const
    {
        return (P1->numero() < P2->numero());
    }
};

struct OrdenaArticulos
{
    bool operator()(const Articulo *A1, const Articulo *A2) const
    {
        return (A1->referencia() < A2->referencia());
    }
};

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
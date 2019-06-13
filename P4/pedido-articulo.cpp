#include <iomanip>
#include "pedido-articulo.hpp"
 
LineaPedido::LineaPedido(double p, unsigned c) : precio_(p),
                                                 cantidad_(c)
{
}

bool OrdenaPedidos::operator()(const Pedido *P1, const Pedido *P2) const
{
    return P1->numero() < P2->numero();
}

bool OrdenaArticulos::operator()(const Articulo *A1, const Articulo *A2) const
{
    return (A1->referencia() < A2->referencia());
}

std::ostream &operator<<(std::ostream &os, const LineaPedido &LP)
{
    os << std::fixed << std::setprecision(2) << LP.precio_venta() << " €\t" << LP.cantidad();

    return os;
}

void Pedido_Articulo::pedir(Pedido &P, Articulo &A, double p, unsigned c)
{
    PA[&P].insert(std::make_pair(&A, LineaPedido(p, c)));
    AP[&A].insert(std::make_pair(&P, LineaPedido(p, c)));
}

void Pedido_Articulo::pedir(Articulo &A, Pedido &P, double p, unsigned c)
{
    Pedido_Articulo::pedir(P, A, p, c);
}

Pedido_Articulo::ItemsPedido &Pedido_Articulo::detalle(Pedido &P)
{
    return PA[&P];
}

Pedido_Articulo::Pedidos Pedido_Articulo::ventas(Articulo &A)
{
    return AP[&A];
}

std::ostream &operator<<(std::ostream &os, const Pedido_Articulo::Pedidos &P)
{
    unsigned tmp_cantidad = 0;
    double tmp_total = 0.0;

    os << "[Pedidos: " << P.size() << "]\n"
       << Cadena(66, '=') << std::endl
       << "  PVP\tCantidad\tFecha de venta\n"
       << Cadena(66, '=') << std::endl;

    for (const auto &i : P)
    {
        os << i.second << "\t\t" << i.first->fecha() << std::endl;

        tmp_total += i.second.precio_venta() * i.second.cantidad();
        tmp_cantidad += i.second.cantidad();
    }

    os << Cadena(66, '=') << std::endl
       << std::fixed << std::setprecision(2) << tmp_total << " €\t"
       << tmp_cantidad << std::endl;

    return os;
}

std::ostream &operator<<(std::ostream &os, const Pedido_Articulo::ItemsPedido &I)
{
    double total = 0.0;

    os << '\n'
       << Cadena(66, '=') << std::endl
       << "  PVP\tCantidad\tArtículo\n"
       << Cadena(66, '=') << std::endl;

    for (const auto &i : I)
    {
        os << i.second << "\t\t[" << i.first->referencia() << "] \""
           << i.first->titulo() << "\"" << std::endl;

        total += i.second.precio_venta() * i.second.cantidad();
    }

    os << Cadena(66, '=') << std::endl
       << "Total\t" << std::fixed << std::setprecision(2) << total << " €\n"
       << std::endl;

    return os;
}

std::ostream &Pedido_Articulo::mostrarDetallePedidos(std::ostream &os)
{
    double total = 0.0;

    for (const auto &i : PA)
    {
        os << "Pedido núm. " << i.first->numero()
           << "\nCliente: " << i.first->tarjeta()->titular()->nombre()
           << "\tFecha: " << i.first->fecha() << i.second;

        total += i.first->total();
    }

    os << std::fixed << "\nTOTAL VENTAS:\t" << std::setprecision(2)
       << total << " €" << std::endl;

    return os;
}

std::ostream &Pedido_Articulo::mostrarVentasArticulos(std::ostream &os)
{
    for (const auto &i : AP)
    {
        os << "Ventas de [" << i.first->referencia() << "] \""
           << i.first->titulo() << "\"\n"
           << i.second << std::endl;
    }

    return os;
}
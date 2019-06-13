#include <iomanip>
#include "pedido.hpp"

Pedido::Pedido(Usuario_Pedido &UP, Pedido_Articulo &PA, Usuario &U, const Tarjeta &T, const Fecha &F) : num_(cant_ + 1),
                                                                                                        tarjeta_(&T),
                                                                                                        fecha_(F),
                                                                                                        total_(0)
{
    if (U.n_articulos() == 0)
        throw Vacio(U);

    if (T.titular() != &U)
        throw Impostor(U);

    if (!T.activa())
        throw Tarjeta::Desactivada();

    if (F > T.caducidad())
        throw Tarjeta::Caducada(T.caducidad());

    bool pedido_vacio = true;

    Usuario::Articulos carro = user.compra();

    for (auto &[articulo, cantidad] : carro)
    {
        if (articulo->stock() < cantidad)
        {
            const_cast<Usuario::Articulos &>(U.compra()).clear();
            throw Pedido::SinStock(articulo);
        }
        articulo->stock() -= cantidad;
        PA.pedir(*this, *articulo, articulo->precio(), cantidad);
        total_ += articulo->precio() * cantidad;
        U.compra(*articulo, 0);
        pedido_vacio = false;
    }

    if (pedido_vacio)
        throw Vacio(U);

    UP.asocia(U, *this);
    cant_++;
}

std::ostream &operator<<(std::ostream &os, const Pedido &P)
{
    os << std::left << std::setw(13) << "Núm. pedido: " << P.numero() << std::endl
       << std::left << std::setw(13) << "Fecha:" << P.fecha() << std::endl
       << std::left << std::setw(13) << "Pagado con:" << P.tarjeta()->tipo() << " n.º: " << P.tarjeta()->numero() << std::endl
       << std::left << std::setw(13) << "Importe:" << std::fixed << std::setprecision(2) << P.total() << " €" << std::endl;

    return os;
}
#include "pedido.hpp"
#include "pedido-articulo.hpp"
#include "usuario-pedido.hpp"
#include <iomanip>

Pedido::Pedido(Usuario_Pedido &UP, Pedido_Articulo &PA, Usuario &U, const Tarjeta &T, const Fecha &F) : numero_(cantidad_ + 1),
                                                                                                        tarjeta_(&T),
                                                                                                        fecha_(F),
                                                                                                        total_(0)
{
  if (U.n_articulos() == 0)
    throw Pedido::Vacio(&U);

  if (!T.activa())
    throw Tarjeta::Desactivada();

  if (T.titular() != &U)
    throw Pedido::Impostor(&U);

  if (T.caducidad() < F)
    throw Tarjeta::Caducada(T.caducidad());

  Usuario::Articulos carro = U.compra();

  bool pedido_vacio = true;

  for (auto &[articulo, cantidad] : carro)
  {
    if (auto *libroDig = dynamic_cast<LibroDigital *>(articulo))
    {
      if (libroDig->f_expir() < Fecha())
        U.compra(*articulo, 0);
      else
      {
        PA.pedir(*this, *libroDig, articulo->precio(), cantidad);
        total_ += articulo->precio() * cantidad;
        U.compra(*articulo, 0);
        pedido_vacio = false;
      }
    }
    else if (auto *artAlmc = dynamic_cast<ArticuloAlmacenable *>(articulo))
    {
      if (artAlmc->stock() < cantidad)
      {
        const_cast<Usuario::Articulos &>(U.compra()).clear();
        throw Pedido::SinStock(articulo);
      }
      artAlmc->stock() -= cantidad;
      PA.pedir(*this, *artAlmc, articulo->precio(), cantidad);
      total_ += articulo->precio() * cantidad;
      U.compra(*articulo, 0);
      pedido_vacio = false;
    }
    else
      throw std::logic_error("Error, Articulo Desconocido");
  }

  if (pedido_vacio)
    throw Vacio(&U);

  UP.asocia(U, *this);
  ++cantidad_;
}

std::ostream &operator<<(std::ostream &os, const Pedido &P)
{
  os << std::left << std::setw(13) << "Núm. pedido: " << P.numero() << std::endl
     << std::left << std::setw(13) << "Fecha:" << P.fecha() << std::endl
     << std::left << std::setw(13) << "Pagado con:" << P.tarjeta()->tipo() << " n.º: " << P.tarjeta()->numero() << std::endl
     << std::left << std::setw(13) << "Importe:" << std::fixed << std::setprecision(2) << P.total() << " €" << std::endl;

  return os;
}

#include <iomanip>
#include "pedido.hpp"
#include "pedido-articulo.hpp"
#include "usuario-pedido.hpp"
 
Pedido::Pedido(Usuario_Pedido &u_p, Pedido_Articulo &p_a, Usuario &u,
               const Tarjeta &t, const Fecha &fecha)
    : numero_(cantidad_ + 1), tarjeta_(&t), fecha_(fecha), total_(0)
{
  if (u.n_articulos() == 0)
    throw Pedido::Vacio(&u);

  if (!t.activa())
    throw Tarjeta::Desactivada();

  if (t.titular() != &u)
    throw Pedido::Impostor(&u);

  if (t.caducidad() < fecha)
    throw Tarjeta::Caducada(t.caducidad());

  Usuario::Articulos carro = u.compra();

  bool pedido_vacio = true;

  for (auto &[articulo, cantidad] : carro)
  {
    if (auto *libroDig = dynamic_cast<LibroDigital *>(articulo))
    {
      if (libroDig->f_expir() < Fecha())
        u.compra(*articulo, 0);
      else
      {
        p_a.pedir(*this, *libroDig, articulo->precio(), cantidad);
        total_ += articulo->precio() * cantidad;
        u.compra(*articulo, 0);
        pedido_vacio = false;
      }
    }
    else if (auto *artAlmc = dynamic_cast<ArticuloAlmacenable *>(articulo))
    {
      if (artAlmc->stock() < cantidad)
      {
        const_cast<Usuario::Articulos &>(u.compra()).clear();
        throw Pedido::SinStock(articulo);
      }
      artAlmc->stock() -= cantidad;
      p_a.pedir(*this, *artAlmc, articulo->precio(), cantidad);
      total_ += articulo->precio() * cantidad;
      u.compra(*articulo, 0);
      pedido_vacio = false;
    }
    else
      throw std::logic_error("Error, Articulo Desconocido");
  }
  if (pedido_vacio)
    throw Vacio(&u);
  u_p.asocia(u, *this);
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

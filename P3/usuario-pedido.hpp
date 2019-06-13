#ifndef USUARIO_PEDIDO_HPP_
#define USUARIO_PEDIDO_HPP_

#include <set>
#include <map>
#include "pedido.hpp"

class Usuario_Pedido
{
public:
    typedef std::set<Pedido *> Pedidos;

    void asocia(Usuario &U, Pedido &P)
    {
        UP[&U].insert(&P);
        PU[&P] = &U;
    }

    void asocia(Pedido &P, Usuario &U)
    {
        asocia(U, P);
    }

    Pedidos pedidos(Usuario &U) { return UP[&U]; }
    Usuario *cliente(Pedido &P) { return PU[&P]; }

private:
    std::map<Pedido *, Usuario *> PU;
    std::map<Usuario *, Pedidos> UP;
};

#endif
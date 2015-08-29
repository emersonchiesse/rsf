#ifndef SISTEMA_TRANSPORTE_PUBLICO_H
#define SISTEMA_TRANSPORTE_PUBLICO_H

#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <assert.h>

#include "Lista.h"
#include "Linha.h"
#include "Empresa.h"
#include "CartaoUsuario.h"
#include "CalculoDeRota.h"
#include "SistemaRastreamentoPassageiro.h"

class SistemaTransportePublico
{
private:
	Lista<Linha> linhas;

	Lista<Empresa> empresas;

	Lista<CartaoUsuario> passageiros;

	CalculoDeRota calculoRota;

	SistemaRastreamentoPassageiro usuarios;

};
#endif

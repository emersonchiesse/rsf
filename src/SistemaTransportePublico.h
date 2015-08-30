#ifndef SISTEMA_TRANSPORTE_PUBLICO_H
#define SISTEMA_TRANSPORTE_PUBLICO_H

#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <assert.h>

#include "Lista.h"
#include "ListaLinhas.h"
#include "Empresa.h"
#include "CartaoUsuario.h"
#include "CalculoDeRota.h"
#include "SistemaRastreamentoPassageiro.h"


class SistemaTransportePublico
{
private:
	ListaLinhas linhas;
	Lista<Empresa> empresas;
	Lista<CartaoUsuario> passageiros;
	CalculoDeRota calculoRota;
	SistemaRastreamentoPassageiro usuarios;
public:
	SistemaTransportePublico () {};
	void Init ();

	void insereLinha(Linha *l);
	std::string listaLinhas();

};
#endif

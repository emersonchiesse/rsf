#ifndef PONTO_LINHA_H
#define PONTO_LINHA_H

#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <assert.h>

#include "Coordenada.h"
#include "TipoPonto.h"

class PontoLinha
{
private:
	std::string nome;

	long num;

	Coordenada coordenada;

	int sequencia;

	TipoPonto tipo;

	int grupo;

	std::string sentido;

};
#endif

#ifndef LINHA_H
#define LINHA_H

#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <assert.h>

#include "Entidade.h"
#include "CategoriaLinha.h"
#include "Lista.h"
#include "PontoLinha.h"

class Linha : public Entidade
{
private:
	std::string descricao;

	CategoriaLinha categoria;

	bool somente_cartao;

	Lista<PontoLinha> pontos;


public:
	std::string getDescricao();

	std::string getCategoria();

	std::string getCartao();

};
#endif

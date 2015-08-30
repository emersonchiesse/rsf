#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <assert.h>

#include "SistemaTransportePublico.h"

void SistemaTransportePublico::Init() {
//	linhas.
}

void SistemaTransportePublico::insereLinha(Linha *l) {

	linhas.insere(l);
}

std::string SistemaTransportePublico::listaLinhas() {

	return linhas.mostraLista();

}

void SistemaTransportePublico::inserePontoLinha(
		string linha, PontoLinha* p) {

	Linha *l = linhas.procura(linha);

	if (l != NULL)
		l->inserePonto(p);

}

string SistemaTransportePublico::listaPontosLinha(string linha) {

	Linha *l = linhas.procura(linha);

	return l->listaPontos();

}

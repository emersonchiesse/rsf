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

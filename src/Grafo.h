/*
 * Grafo.h
 *
 *  Created on: Jul 22, 2015
 *      Author: x
 */

#ifndef GRAFO_H_
#define GRAFO_H_

#include <string>
#include "Nodo.h"

using namespace std;

class Grafo {
private:
	std::vector<Nodo> nodos;
	int raio;

public:
	Grafo();
	virtual ~Grafo();

	void init();
	void load();
	void load(string arq);
	void loadcoords(string arq);
	void list();
	int procura(string id);
	int procura(int x, int y);
	void addNodo(Nodo n);

	void criaRandom (int);

	void caminhomaiscurto (string n1, string n2);

	const std::vector<Nodo>& getNodos() const {
		return nodos;
	}
};

#endif /* GRAFO_H_ */

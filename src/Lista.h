#ifndef LISTA_H
#define LISTA_H

#include "Elemento.h"

template<class TIPO>
class Lista {
private:

	Elemento<TIPO>* pPrimeiro;
	Elemento<TIPO>* pAtual;
public:
	Lista ( );
	~Lista ( );
	void inicializa ( );
	void limpar();
	bool incluaElemento ( Elemento<TIPO>* pElemento );
	bool incluaInfo (TIPO* pInfo );
	Elemento<TIPO>* getpPrimeiro();
	Elemento<TIPO>* getpAtual();
};

template<class TIPO>
Lista<TIPO>::Lista ( )
{
	inicializa ( );
}

template<class TIPO>
Lista<TIPO>::~Lista ( )
{
	limpar();
}

template<class TIPO>
void Lista<TIPO>::inicializa ( )
{
	pPrimeiro = 0;
	pAtual = 0;
}


template<class TIPO>
Elemento<TIPO>* Lista<TIPO>::getpPrimeiro()
{
	return pPrimeiro;
}
template<class TIPO>
Elemento<TIPO>* Lista<TIPO>::getpAtual()
{
	return pAtual;
}

template<class TIPO>
void Lista<TIPO>::limpar ( )
{
	Elemento<TIPO>* paux1;
	Elemento<TIPO>* paux2;
	paux1 = pPrimeiro;
	paux2 = paux1;
	while (paux1 != 0)
	{
		paux2 = paux1->getProximo();
		delete (paux1);
		paux1 = paux2;
	}
	pPrimeiro = 0;
	pAtual = 0;
}
#endif /* LISTA_H_ */


/*
 * Elemento.h
 *
 *  Created on: 23 de ago de 2015
 *      Author: x
 */

#ifndef ELEMENTO_H_
#define ELEMENTO_H_

template<class TIPO>
class Elemento {
private:
	Elemento<TIPO>* pProximo;
	Elemento<TIPO>* pAnterior;
	TIPO* pInfo;

public:
	Elemento();
	virtual ~Elemento();

	void setProximo(Elemento<TIPO> *p);
	Elemento<TIPO>* getProximo();

	void setAnterior(Elemento<TIPO> *p);
	Elemento<TIPO>* getAnterior();

	void setInfo (TIPO *p);
	TIPO* getInfo();


};

template<class TIPO>
Elemento<TIPO>::Elemento ( )
{
	pProximo = 0;
	pAnterior = 0;
	pInfo = 0;
}

template<class TIPO>
Elemento<TIPO>::~Elemento ( )
{
	pProximo = 0;
	pAnterior = 0;
	pInfo = 0;
}

template<class TIPO>
void Elemento<TIPO>::setProximo (
		Elemento<TIPO>* pP )
		{
	pProximo = pP;
		}

template<class TIPO>
Elemento<TIPO>* Elemento<TIPO>::getProximo ( )
{
	return pProximo;
}

template<class TIPO>
void Elemento<TIPO>::setAnterior (
		Elemento<TIPO>* pA )
		{
	pAnterior = pA;
		}

template<class TIPO>
Elemento<TIPO>* Elemento<TIPO>::getAnterior ( )
{
	return pProximo;
}

template<class TIPO>
void Elemento<TIPO>::setInfo (TIPO* pI )
{
	pInfo = pI;
}

template<class TIPO>
TIPO* Elemento<TIPO>::getInfo()
{
	return pInfo;
}

#endif /* ELEMENTO_H_ */

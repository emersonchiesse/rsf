#ifndef ENTIDADE_H
#define ENTIDADE_H

#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <assert.h>

class Entidade
{
private:
	int id;

	std::string nome;


public:
	void setId(int id);

	int getId();

	void setNome(std::string nome);

	std::string getNome();

};
#endif

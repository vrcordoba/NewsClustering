/*
 * Analizador.h
 *
 *  Created on: 26-dic-2012
 *      Author: Alvaro
 */

#ifndef ANALIZADOR_H_
#define ANALIZADOR_H_
#include "string"
#include <list>
#include "Noticia.h"

class Analizador {

	std::list<Noticia> noticias;
	std::string ruta;


public:
	Analizador();
	Analizador(std::string ruta);

	std::list<Noticia> getNoticias() const;
	void setNoticas(std::string ruta);

	std::string agruparNoticias();
	std::string agruparNoticiasGeneral();

	std::string toString()const;

private:

	std::string rellenarCeros(int n, int size)const;
	void ordenarNoticias();
	bool existe(std::list<EntidadNombrada> es, EntidadNombrada e)const;
};

#endif /* ANALIZADOR_H_ */

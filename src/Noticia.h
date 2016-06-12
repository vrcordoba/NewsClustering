/*
 * Noticia.h
 *
 *  Created on: 26-dic-2012
 *      Author: Alvaro
 */

#ifndef NOTICIA_H_
#define NOTICIA_H_
#include "string"
#include <list>
#include "EntidadNombrada.h"

class Noticia {

	std::string titulo;
	std::string cuerpo;
	std::list<EntidadNombrada> entidades;
	std::list<std::string> entidadesR;
	EntidadNombrada masFrecuente;

public:
	Noticia();
	Noticia(std::string titulo, std::string cuerpo, std::string ruta);

	void setTitulo(std::string titulo);
	void setCuerpo(std::string cuerpo);
	void setPalabrasReservadas(std::string ruta);
	void actualizar();

	std::string getTitulo()const;
	std::string getCuerpo()const;
	EntidadNombrada getMasFrecuente()const;
	std::list<EntidadNombrada> getEntidades()const;
	std::list<std::string> getPalabrasReservadas()const;
	std::list<EntidadNombrada> getEntidadesRelevantes()const;
	bool esAgrupable(Noticia n)const;
	std::string toString()const;


private:
	void setEntidades();
	void setMasFrecuente();
	void agregarEntidad(std::string nombre);
	bool esletra(char c) const;
};

#endif /* NOTICIA_H_ */

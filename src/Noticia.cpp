/*
 * Noticia.cpp
 *
 *  Created on: 26-dic-2012
 *      Author: Alvaro
 */

#include "Noticia.h"
#include "list"
#include "EntidadNombrada.h"
#include <iostream>
#include <fstream>

Noticia::Noticia() {
	this->titulo = "";
	this->cuerpo = "";
	std::list<EntidadNombrada> l;
	this->entidades = l;
	std::list<std::string> p;
	this->entidadesR = p;
	EntidadNombrada e;
	this->masFrecuente = e;
}

Noticia::Noticia(std::string titulo, std::string cuerpo, std::string ruta) {
	this->titulo = titulo;
	this->cuerpo = cuerpo;
	this->setPalabrasReservadas(ruta);
	this->setEntidades();
	this->setMasFrecuente();
}

void Noticia::setTitulo(std::string titulo) {
	this->titulo = titulo;
}

void Noticia::setCuerpo(std::string cuerpo) {
	this->cuerpo = cuerpo;
}

void Noticia::setPalabrasReservadas(std::string ruta) {
	std::ifstream f;
	f.open(ruta.c_str(), std::ofstream::in);
	std::string aux;
	while (!f.eof()) {
		f >> aux;
		this->entidadesR.push_back(aux);
	}
}

void Noticia::actualizar() {
	this->setEntidades();
	this->setMasFrecuente();
}

std::string Noticia::getTitulo() const {
	return this->titulo;
}

std::string Noticia::getCuerpo() const {
	return this->cuerpo;
}

EntidadNombrada Noticia::getMasFrecuente() const {
	return this->masFrecuente;
}

std::list<EntidadNombrada> Noticia::getEntidades() const {
	return this->entidades;
}

std::list<std::string> Noticia::getPalabrasReservadas() const {
	return this->entidadesR;
}

std::list<EntidadNombrada> Noticia::getEntidadesRelevantes() const {

	std::string aux = this->cuerpo;
	std::list<EntidadNombrada> lista;
	std::list<EntidadNombrada> misEntidades = this->entidades;

	EntidadNombrada en;
	aux = aux.substr(0, (aux.size() / 3));
	for (std::list<EntidadNombrada>::iterator it = misEntidades.begin();
			it != misEntidades.end(); it++) {
		en = *it;
		if (aux.find(en.getEntidadNombrada()) != std::string::npos) {
			lista.push_back(en);
		}
	}

	return lista;
}

bool Noticia::esAgrupable(Noticia n) const {

	bool salida = false;

	if (this->titulo.find(n.getMasFrecuente().getEntidadNombrada())
			!= std::string::npos) {
		salida = true;
	}

	std::list<EntidadNombrada> primero = this->getEntidadesRelevantes();
	std::list<EntidadNombrada> segundo = n.getEntidadesRelevantes();
	std::list<EntidadNombrada> final;
	EntidadNombrada en1;
	EntidadNombrada en2;

	for (std::list<EntidadNombrada>::iterator it1 = primero.begin();
			it1 != primero.end(); it1++) {

		en1 = *it1;
		for (std::list<EntidadNombrada>::iterator it2 = segundo.begin();
				it2 != segundo.end(); it2++) {

			en2 = *it2;
			if (en1.esIgual(en2)) {
				final.push_back(en2);
			}
		}
	}

	if (final.size() >= (segundo.size() / 3)) {
		salida = true;
	}
	return salida;
}

std::string Noticia::toString() const {

	std::string salida;
	salida = "TITULO: " + this->titulo + "\n" + "CUERPO: " + this->cuerpo + "\n"
			+ "ENTIDADES: ";

	std::list<EntidadNombrada> lista = this->getEntidades();

	for (std::list<EntidadNombrada>::iterator i = lista.begin();
			i != lista.end(); i++) {
		salida += i->toString();
		salida += " ";
	}

	salida = salida + "\n" + "MAS FRECUENTE: "
			+ this->getMasFrecuente().toString();

	return salida;
}

void Noticia::setEntidades() {
	std::string aux = "";
	std::list<EntidadNombrada> lista;

	for (unsigned int i = 0; i <= this->cuerpo.size(); i++) {
		if (this->cuerpo[i] != ' ') {
			if (this->esletra(this->cuerpo[i])) {
				aux += this->cuerpo[i];
			}
		} else {
			this->agregarEntidad(aux);
			aux = "";
		}
	}
}

void Noticia::setMasFrecuente() {
	EntidadNombrada aux;
	EntidadNombrada aux2;
	for (std::list<EntidadNombrada>::iterator i = this->entidades.begin();
			i != this->entidades.end(); ++i) { // Iterate through 'items'
		aux2 = *i;
		if (aux.getFrecuencia() < aux2.getFrecuencia()) {
			aux.setEntidadNombrada(aux2.getEntidadNombrada());
			aux.setFrecuencia(aux2.getFrecuencia());
		}
	}
	this->masFrecuente = aux;
}

void Noticia::agregarEntidad(std::string nombre) {
	bool empezar = true;
	for (std::list<std::string>::iterator i = this->entidadesR.begin();
			i != this->entidadesR.end(); i++) {
		std::string aux = nombre;
		int ascii = static_cast<int>(aux[0]);
		if ((ascii >= 65) && (ascii <= 90)) {
			aux[0] = static_cast<char>(aux[0] + 32);
		}
		if (i->compare(aux) == 0) {
			empezar = false;
		}
	}
	if (empezar) {
		bool add = true;
		for (std::list<EntidadNombrada>::iterator it = this->entidades.begin();
				it != this->entidades.end(); it++) {
			if (it->getEntidadNombrada().compare(nombre) == 0) {
				it->setFrecuencia(it->getFrecuencia() + 1);
				add = false;
			}
		}
		if (add) {
			int aux = static_cast<int>(nombre[0]);
			if ((aux >= 65) && (aux <= 90)) {
				EntidadNombrada aux(nombre, 1);
				this->entidades.push_back(aux);
			}
		}
	}
}

bool Noticia::esletra(char c) const {
	bool salida = false;
	int ascii = static_cast<int>(c);
	if ((ascii >= 65) && (ascii <= 90)) {
		salida = true;
	}
	if ((ascii >= 97) && (ascii <= 122)) {
		salida = true;
	}
	if (ascii < 0) {
		salida = true;
	}
	if ((ascii >= 48) && (ascii <= 57)) {
		salida = true;
	}
	return salida;
}


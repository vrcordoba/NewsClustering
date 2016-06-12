/*
 * EntidadNombrada.cpp
 *
 *  Created on: 26-dic-2012
 *      Author: Alvaro
 */
#include <sstream>

#include "EntidadNombrada.h"

EntidadNombrada::EntidadNombrada() :
		frecuencia(0), entidadNombrada("") {
}

EntidadNombrada::EntidadNombrada(std::string n, int f) :
		frecuencia(f), entidadNombrada(n) {
}

int EntidadNombrada::getFrecuencia() const {
	return this->frecuencia;
}

std::string EntidadNombrada::getEntidadNombrada() const {
	return this->entidadNombrada;
}

void EntidadNombrada::setFrecuencia(int const f) {
	this->frecuencia = f;
}

void EntidadNombrada::setEntidadNombrada(std::string const en) {
	this->entidadNombrada = en;
}

bool EntidadNombrada::esIgual(const EntidadNombrada& en) const {
	bool salida = false;
	if ((this->entidadNombrada.compare(en.entidadNombrada) == 0)) {
		salida = true;
	}
	return salida;
}

std::string EntidadNombrada::toString() const {
	std::stringstream s;
	s << this->entidadNombrada << " [" << this->frecuencia << "]";
	return s.str();
}

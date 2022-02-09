#include "lexico.h"

lexico::lexico(string fuente)
{
	ind = 0;
	this->fuente = fuente;
}

lexico::lexico()
{
	ind = 0;
}
string lexico::tipoAcad(int tipo)
{
	string cad = "";
	switch (tipo)
	{
	case TipoSimbolo::IDENTIFICADOR:
		cad = "Identificador";
		break;
	case TipoSimbolo::ENTERO:
		cad = "Numero Entero";
		break;
	case TipoSimbolo::REAL:
		cad = "Numero Real";
		break;
	case TipoSimbolo::CADENA:
		cad = "Cadena";
		break;
	case TipoSimbolo::TIPO:
		cad = "Tipo de dato";
		break;
	case TipoSimbolo::OPSU:
		cad = "Operador de Suma/Resta";
		break;
	case TipoSimbolo::OPMU:
		cad = "Operador de Multiplicacion/division";
		break;
	case TipoSimbolo::OPREL:
		cad = "Operador de Relacion";
		break;
	case TipoSimbolo::OPOR:
		cad = "Operador OR";
		break;
	case TipoSimbolo::OPAND:
		cad = "Operador AND";
		break;
	case TipoSimbolo::OPNOT:
		cad = "Operador NOT";
		break;
	case TipoSimbolo::OPIGUALDAD:
		cad = "Operador de igualdad";
		break;
	case TipoSimbolo::PUNTO_COMA:
		cad = "Punto y Coma";
		break;
	case TipoSimbolo::COMA:
		cad = "Coma";
		break;
	case TipoSimbolo::PARENTESIS1:
		cad = "Parentesis";
		break;
	case TipoSimbolo::PARENTESIS2:
		cad = "Parentesis";
		break;
	case TipoSimbolo::LLAVE1:
		cad = "Llave";
		break;
	case TipoSimbolo::LLAVE2:
		cad = "Llave";
		break;
	case TipoSimbolo::IGUAL:
		cad = "Operador de Asignacion";
		break;
	case TipoSimbolo::IF:
		cad = "Palabra Reservada";
		break;
	case TipoSimbolo::WHILE:
		cad = "Palabra Reservada";
		break;
	case TipoSimbolo::RETURN:
		cad = "Palabra Reservada";
		break;
	case TipoSimbolo::ELSE:
		cad = "Palabra Reservada";
		break;
	case TipoSimbolo::PESOS:
		cad = "";
		break;
	}

	return cad;
}
void lexico::entrada(string fuente)
{
	ind = 0;
	this->fuente = fuente;
}
int lexico::sigSimbolo()
{
	estado = 0;
	continua = true;
	simbolo = "";
	cont = 0;

	while (continua)
	{
		c = sigCaracter();

		switch (estado)
		{
		case 0:
			if (esLetra(c)) {
				estado = 1;
				simbolo += c;
			}
			if (esDigito(c)) {
				estado = 2;
				simbolo += c;
			}
			if (c == '+' || c == '-') {
				aceptacion(5);
			}
			if (c == '*' || c == '/')aceptacion(6);
			if (c == '<' || c == '>') {
				estado = 5;
				simbolo += c;
			}
			if (c == '|') {
				estado = 6;
				simbolo += c;
			}
			if (c == '&') {
				estado = 7;
				simbolo += c;
			}
			if (c == '!') {
				estado = 8;
				simbolo += c;
			}
			if (c == ';')aceptacion(12);
			if (c == ',')aceptacion(13);
			if (c == '(')aceptacion(14);
			if (c == ')') aceptacion(15);
			if (c == '{') aceptacion(16);
			if (c == '}') aceptacion(17);
			if (c == '=') {
				estado = 9;
				simbolo += c;
			}
			else {
				if (c == '$')aceptacion(23);
			}
			break;
		case 1:
			if (esLetra(c) || esDigito(c)) {
				estado = 1;
				simbolo += c;

			}
			else if (!esLetra(c) || !esDigito(c)) {
				aux = simbolo;
				if (aux == "int" || aux == "float" || aux == "void") {
					aceptacion(4);
				}
				else {
					aceptacion(0);
				}
				if (aux == "if") {
					aceptacion(19);
				}
				if (aux == "while") {
					aceptacion(20);
				}
				if (aux == "return") {
					aceptacion(21);
				}
				if (aux == "else") {
					aceptacion(22);
				}


			}
			break;
		case 2:
			if (esDigito(c)) {
				estado = 2;
				simbolo += c;
			}
			else if (c == '.') {
				estado = 3;
				simbolo += c;
			}
			else if (c != '.' || !esDigito(c)) {
				aceptacion(1);
			}
			break;
		case 3:
			if (esDigito(c)) {
				estado = 4;
				simbolo += c;
			}
			break;
		case 4:
			if (esDigito(c)) {
				estado = 4;
				simbolo += c;
			}
			else {
				aceptacion(2);
			}
			break;
		case 5:
			if (c != '=') {
				aceptacion(7);
			}
			else if (c == '=') {
				aceptacion(7);
			}
			break;
		case 6:
			if (c != '|') {
				aceptacion(23);
			}
			else if (c == '|') {
				aceptacion(8);
			}
			break;
		case 7:
			if (c != '&') {
				aceptacion(23);
			}
			else if (c == '&') {
				aceptacion(9);
			}
			break;
		case 8:
			if (c != '=') {
				aceptacion(10);
			}
			else if (c == '=') {
				aceptacion(11);
			}
			break;
		case 9:
			if (c != '=') {
				aceptacion(18);
			}
			else if (c == '=') {
				aceptacion(11);
			}
			break;
		}
	}
	switch (estado)
	{
	case -1:
		tipo = TipoSimbolo::ERROR;
		break;
	case 0:
		tipo = TipoSimbolo::IDENTIFICADOR;
		break;
	case 1:
		tipo = TipoSimbolo::ENTERO;
		break;
	case 2:
		tipo = TipoSimbolo::REAL;
		break;
	case 3:
		tipo = TipoSimbolo::CADENA;
		break;
	case 4:
		tipo = TipoSimbolo::TIPO;
		break;
	case 5:
		tipo = TipoSimbolo::OPSU;
		break;
	case 6:
		tipo = TipoSimbolo::OPMU;
		break;
	case 7:
		tipo = TipoSimbolo::OPREL;
		break;
	case 8:
		tipo = TipoSimbolo::OPOR;
		break;
	case 9:
		tipo = TipoSimbolo::OPAND;
		break;
	case 10:
		tipo = TipoSimbolo::OPNOT;
		break;
	case 11:
		tipo = TipoSimbolo::OPIGUALDAD;
		break;
	case 12:
		tipo = TipoSimbolo::PUNTO_COMA;
		break;
	case 13:
		tipo = TipoSimbolo::COMA;
		break;
	case 14:
		tipo = TipoSimbolo::PARENTESIS1;
		break;
	case 15:
		tipo = TipoSimbolo::PARENTESIS2;
		break;
	case 16:
		tipo = TipoSimbolo::LLAVE1;
		break;
	case 17:
		tipo = TipoSimbolo::LLAVE2;
		break;
	case 18:
		tipo = TipoSimbolo::IGUAL;
		break;
	case 19:
		tipo = TipoSimbolo::IF;
		break;
	case 20:
		tipo = TipoSimbolo::WHILE;
		break;
	case 21:
		tipo = TipoSimbolo::RETURN;
		break;
	case 22:
		tipo = TipoSimbolo::ELSE;
		break;
	case 23:
		tipo = TipoSimbolo::PESOS;
		break;
	default:
		tipo = TipoSimbolo::ERROR;
		break;
	}
	return tipo;
}
char lexico::sigCaracter()
{
	if (terminado()) return '$';

	return fuente[ind++];
}
void lexico::sigEstado(int estado)
{
	this->estado = estado;
	if (estado != 0) {
		simbolo += c;
	}
}
void lexico::aceptacion(int estado)
{
	sigEstado(estado);
	continua = false;
}
bool lexico::terminado()
{
	return ind >= fuente.length();

}
bool lexico::esLetra(char c)
{
	return c >= 'a' && c <= 'z' || c == '_' || c >= 'A' && c <= 'Z';
}
bool lexico::esDigito(char c)
{
	return isdigit(c);

}
bool lexico::esEspacio(char c)
{
	return c == ' ' || c == '\t';
}
void lexico::retroceso()
{
	if (c != '$') ind--;
	continua = false;
}
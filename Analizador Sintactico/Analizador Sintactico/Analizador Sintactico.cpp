#include <cstdlib>
#include <iostream>
#include <string>

#include "lexico.h"
#include "pila.h"

using namespace std;

int tablaR1[5][4] = {
    2,0,0,1,
    0,0,-1,0,
    0,3,0,0,
    4,0,0,0,
    0,0,-2,0
};
int tablaR2[5][4] = {
    2,0,0,1,
    0,0,-1,0,
    0,3,-3,0,
    2,0,0,4,
    0,0,-2,0
};
Pila pila;
lexico lexico;
int fila, columna, accion;
bool aceptacion = false;
void r1();
void pushR1();
void r2();

int main(int argc, char* argv[]) {

   // r1();
    r2();

 

    return 0;
}
void r1() {
    lexico.entrada("a + b");

    pila.push(TipoSimbolo::PESOS);
    pila.push(0);
    lexico.sigSimbolo();

    fila = pila.top();
    columna = lexico.tipo;
    accion = tablaR1[fila][columna];

    pila.muestra();
    cout << "Entrada: " << lexico.simbolo << endl;
    cout << "accion: " << accion << endl;

    pushR1();

    fila = pila.top();
    columna = 3;
    accion = tablaR1[fila][columna];

    pila.push(3);
    pila.push(accion);
    pila.muestra();
    cout << "Entrada: " << lexico.simbolo << endl;
    cout << "accion: " << accion << endl;

    fila = pila.top();
    columna = lexico.tipo;
    accion = tablaR1[fila][columna];
    pila.muestra();
    cout << "Entrada: " << lexico.simbolo << endl;
    cout << "accion: " << accion << endl;

    aceptacion = accion == -1;
    if (aceptacion)
        cout << "Aceptacion" << endl;

}
void pushR1() {
    pila.push(lexico.tipo);
    pila.push(accion);
    lexico.sigSimbolo();

    fila = pila.top();
    columna = lexico.tipo;
    accion = tablaR2[fila][columna];

    pila.muestra();
    cout << "Entrada: " << lexico.simbolo << endl;
    cout << "accion: " << accion << endl;
    if (accion > 0) {
        pushR1();
    }
    else if (accion < 0) {
        for (int i = 0; i < 22; i++) {
            pila.pop();
        }
        return;
    }

}
void r2() {
    lexico.entrada("a + b + c + d + e + f");
    pila.push(TipoSimbolo::PESOS);
    pila.push(0);
    lexico.sigSimbolo();

    fila = pila.top();
    columna = lexico.tipo;
    accion = tablaR2[fila][columna];

    pila.muestra();
    cout << "Entrada: " << lexico.simbolo << endl;
    cout << "accion: " << accion << endl;

    pushR1();

    fila = pila.top();
    columna = 3;
    accion = tablaR2[fila][columna];

    pila.push(3);
    pila.push(accion);
    pila.muestra();
    cout << "Entrada: " << lexico.simbolo << endl;
    cout << "accion: " << accion << endl;

    fila = pila.top();
    columna = lexico.tipo;
    accion = tablaR2[fila][columna];
    pila.muestra();
    cout << "Entrada: " << lexico.simbolo << endl;
    cout << "accion: " << accion << endl;

    aceptacion = accion == -1;
    if (aceptacion)
        cout << "Aceptacion" << endl;

}

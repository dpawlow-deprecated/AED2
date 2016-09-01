typedef unsigned long Nat;

#include <string>
#include <ostream>
#include <iostream>
#include "Pila.h"

Pila::Pila(){
    this->tam = 0;
    this->prim = 0;
}

Pila::~Pila(){
    Nodo* aux = this->prim;

    for (unsigned int i = 0; i < this->tam; i++){
        Nodo* eliminado = aux;
        aux = aux->sig;
        delete eliminado;
    }
    delete aux;
    this->tam = 0;
    this->prim = 0;
}


void Pila::apilar(ElemPila& elem){
    Nodo* nuevo = new Nodo;
    nuevo->elem = elem;
    nuevo->sig = this->prim;
    this->tam++;

    this->prim = nuevo;
}

bool Pila::esVacia(){
    return prim == 0;
}

ElemPila& Pila::tope(){
    return this->prim->elem;
}

ElemPila Pila::desapilar(){
    ElemPila elemEliminado = this->prim->elem;

    Nodo* aux = new Nodo;
    aux = this->prim;
    this->prim = this->prim->sig;
    delete aux;
    this->tam--;
    return elemEliminado;
}

Nat Pila::tamanio() const{
    return this->tam;
}


//Asignacion
Pila& Pila::operator=(const Pila & aCopiar){
    Pila* p = new Pila;

    p->tam = aCopiar.tam;
    p->prim = aCopiar.prim;

    return *p;
}

void Pila::mostrar(std::ostream& os) const{
    Nodo* aux = new Nodo;
    aux = this->prim;
    for (int i = 0; i < this->tam; i++) {
        std::cout << aux->elem;
        aux = aux->sig;
    }
    delete aux;
}

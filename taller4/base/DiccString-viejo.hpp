#ifndef DICC_STRING_H_
#define DICC_STRING_H_

#include "Conj.hpp"
#include <string>
#include <iostream>
#include <cassert>
using namespace std;


template<typename T>
class DiccString {
        public:
                /**
                CONSTRUCTOR
                * Construye un diccionario vacio.
                **/
                DiccString();

                /**
                CONSTRUCTOR POR COPIA
                * Construye un diccionario por copia.
                **/
                DiccString(const DiccString<T>&);


                /**
                DESTRUCTOR
                **/
                ~DiccString();

                /**
                DEFINIR
                * Recibe una clave con su significado de tipo T y la define.
                * Si ya estaba definida, la reescribe.
                **/
                void Definir(const string& clave, const T& significado);

                /**
                DEFINIDO?
                * Devuelve un bool, que es true si la clave pasada está definida en
                * el diccionario.
                **/
                bool Definido(const string& clave) const;

                /**
                OBTENER
                * Dada una clave, devuelve su significado.
                * PRE: La clave está definida.
                --PRODUCE ALIASING--
				-- Versión modificable y no modificable
                **/
				const T& Obtener(const string& clave) const;
                T& Obtener(const string& clave);

                /**
                OBTENER
                * Dada una clave, la borra del diccionario junto a su significado.
                * PRE: La clave está definida.
                --PRODUCE ALIASING--
                **/
                void Borrar(const string& clave);

                /**
                CLAVES
                * Devuelve las claves del diccionario.
                --NO PRODUCE ALIASING--
                **/
                const Conj<string>& Claves() const;

        private:

                struct Nodo{
                    Nodo** siguientes;
                    T* definicion;
                    Nodo(){
						siguientes = new Nodo*[256];
                        for (int i = 0; i < 256; i++){
                            siguientes[i] = NULL;
                        }
                        definicion = NULL;
                    }
                    ~Nodo(){
                        delete definicion;
						delete [] siguientes;
                    }
                };

                //Funciones auxiliares

                const int cantidadHijos(Nodo* n){

                    int res = 0;

                    for (int i = 0; i < 256; i++) {
                        if(n->siguientes[i] != NULL){
                            res++;
                        }
                    }

                    return res;
                }

                string pop_back(string s){
                    string res;

                    for (int i = 0; i < s.length()-1; i++) {
                        res.push_back(s[i]);
                    }
                    return res;
                }

                Nodo* raiz;
                Conj<string> claves;

};


template <typename T>
DiccString<T>::DiccString()
    : raiz(NULL), claves(){
        Nodo* raizNueva = new Nodo();
        raizNueva = NULL;
        this->raiz = raizNueva;

        Conj<string> clavesNuevas;

        this->claves = clavesNuevas;

}


template <typename T>
DiccString<T>::DiccString(const DiccString& d) {

    Conj<string> claves_aux = d.Claves();

    for (int i = 1; i < claves_aux.cardinal(); i++) {
        this->Definir(claves_aux.minimo(), d.Obtener(claves_aux.minimo()));
        claves_aux.remover(claves_aux.minimo());
    }

}

template <typename T>
DiccString<T>::~DiccString(){
    delete raiz;
    while(this->claves.cardinal()>0){
        this->claves.remover(this->claves.minimo());
    }
}


template <typename T>
void DiccString<T>::Definir(const string& clave, const T& significado){

    if (this->raiz == NULL){
        Nodo* nuevaRaiz = new Nodo();
        this->raiz = nuevaRaiz;
    }

    Nodo* aux = this->raiz;
    Nodo* padre = this->raiz;


    for (int i = 0; i < clave.length(); i++) {

        if (aux->siguientes[int(clave[i])] != NULL){
            //Recorre el TRIE mientras exista la primera parte de la palabra
            padre = aux;
            aux = aux->siguientes[int(clave[i])];

        }else{
            //Cuando no puede seguir genera nuevos nodos

            /*clave_aux = clave;
            for (int j = 0; j < clave_aux.length() - i; j++) {
                clave_aux = pop_back(clave_aux);
            }*/


            Nodo* nuevo = new Nodo();
            aux->siguientes[int(clave[i])] = nuevo;

            padre->siguientes[int(clave[i-1])] = aux;
            padre = aux;
            aux = aux->siguientes[int(clave[i])];
        }
    }

    T* def = new T(significado);
    aux->definicion = def;

    this->claves.insertar(clave); //Si ya existe no se modifica
}


template <typename T>
bool DiccString<T>::Definido(const string& clave) const{
    return this->claves.pertenece(clave);
}

template <typename T>
T& DiccString<T>::Obtener(const string& clave) {

    Nodo* aux = this->raiz;

    for (int i = 0; i < clave.length(); i++) {
        aux = aux->siguientes[int(clave[i])];
    }

    return *aux->definicion;


}


template <typename T>
const T& DiccString<T>::Obtener(const string& clave) const {

    Nodo* aux = this->raiz;

    for (int i = 0; i < clave.length(); i++) {
        aux = aux->siguientes[int(clave[i])];
    }

    return *aux->definicion;
}


template <typename T>
const Conj<string>& DiccString<T>::Claves() const{
    return claves;
}


template <typename T>
void DiccString<T>::Borrar(const string& clave) {

    std::cout << "borrar 1" << std::endl;

    Nodo* aux = this->raiz;
    Nodo* padre = this->raiz;

    std::cout << "borrar pre for" << std::endl;

    for (int i = 0; i < clave.length(); i++) {
        padre = aux;
        aux = aux->siguientes[int(clave[i])];
    }

    std::cout << "borrar post for" << std::endl;

    if (cantidadHijos(aux) == 0 && padre->definicion == NULL && padre != this->raiz){
        std::cout << "borrar if 1" << std::endl;


        padre->siguientes[int(clave[clave.length()-1])] = NULL;

        string clave_aux = clave;
        clave_aux = pop_back(clave_aux);

        std::cout << "borrar if 2" << std::endl;

        //delete [] aux->siguientes;
        delete aux;

        std::cout << "borrar if 3" << std::endl;

        std::cout << clave_aux << std::endl;
        if (clave.length() > 0) {
            this->Borrar(clave_aux);
        }

    }else if (cantidadHijos(aux) == 0 && padre->definicion != NULL){

        std::cout << "borrar elseif 2" << std::endl;

        delete aux;
        //delete [] aux->siguientes;
        padre->siguientes[int(clave[clave.length()-1])] = NULL;
    }

    std::cout << "post if 1" << std::endl;
    delete aux->definicion;


    std::cout << "post if 2" << std::endl;
    this->claves.remover(clave);
    std::cout << "post if 3" << std::endl;
}


#endif

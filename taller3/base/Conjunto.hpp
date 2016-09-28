#ifndef CONJUNTO_HPP_
#define CONJUNTO_HPP_

#include <iostream>
using namespace std;

template <class T>
class Conjunto
{
	public:

		// Constructor. Genera un conjunto vacío.
		Conjunto();

		// Destructor. Debe dejar limpia la memoria.
		~Conjunto();

		// Inserta un elemento en el conjunto. Si éste ya existe,
		// el conjunto no se modifica.
		void insertar(const T&);

		// Decide si un elemento pertenece al conjunto o no.
		bool pertenece(const T&) const;

		// borra un elemento del conjunto. Si éste no existe,
		// el conjunto no se modifica.
		void remover(const T&);

		// devuelve el mínimo elemento del conjunto según <.
		const T& minimo() const;

		// devuelve el máximo elemento del conjunto según <.
		const T& maximo() const;

		// devuelve la cantidad de elementos que tiene el conjunto.
		unsigned int cardinal() const;

		// muestra el conjunto.
		void mostrar(std::ostream&) const;

		friend ostream& operator<<(ostream& os, const Conjunto<T> &c) {
			c.mostrar(os);
			return os;
		}

	private:

		// la representación de un nodo interno.
		struct Nodo
		{
			// el constructor, toma el elemento al que representa el nodo.
			Nodo(const T& v);
			// el elemento al que representa el nodo.
			T valor;
			// puntero a la raíz del subárbol izq.
			Nodo* izq;
			// puntero a la raíz del subárbol der.
			Nodo* der;
		};

		// puntero a la raíz de nuestro árbol.
		Nodo* raiz_;

	// funciones auxiliares
		Conjunto<T> elimConjAux(Conjunto<T>);


};

template <class T>
Conjunto<T>::Nodo::Nodo(const T& v)
	 : valor(v), izq(NULL), der(NULL)
{}

template <class T>
Conjunto<T>::Conjunto() : raiz_(NULL)
{
	raiz_ = NULL;
}

template <class T>
Conjunto<T>::~Conjunto()
{
}

/* Auxiliares de ~Conjunto()
template <class T>
Conjunto<T> Conjunto<T>::elimConjAux(Conjunto<T> c){

}
*/


template <class T>
bool Conjunto<T>::pertenece(const T& clave) const
{
	Nodo* aux = this->raiz_;
	while (true) {
		if (aux == NULL){
			return false;
		}
		if (clave == aux->valor){
			return true;
		}
		else {
			if (clave < aux->valor){
				aux = aux->izq;
			}
			else {
				aux = aux->der;
			}
		}
	}

}


template <class T>
void Conjunto<T>::insertar(const T& clave)
{
	Nodo* aux = this->raiz_;
	bool flag = true;
	if (!(this->pertenece(clave))){
		if (this->raiz_ == NULL){
			Nodo* nuevaRaiz = new Nodo(clave);
			nuevaRaiz->valor = clave;
			nuevaRaiz->izq = NULL;
			nuevaRaiz->der = NULL;

			this->raiz_ = nuevaRaiz;
			flag = false;
		}

		while (flag){
			if (clave < aux->valor){
				if (aux->izq == NULL){

					Nodo* nuevoNodo = new Nodo(clave);
					nuevoNodo->valor = clave;
					nuevoNodo->izq = NULL;
					nuevoNodo->der = NULL;

					aux->izq = nuevoNodo;
					break;
				}
				else {
					aux = aux->izq;
				}
			}
			else {
				if (aux->der == NULL){
					Nodo* nuevoNodo = new Nodo(clave);
					nuevoNodo->valor = clave;
					nuevoNodo->izq = NULL;
					nuevoNodo->der = NULL;

					aux->izq = nuevoNodo;
					break;
				}
				else {
					aux = aux->der;
				}
			}
		}
	}
}

template <class T>
unsigned int Conjunto<T>::cardinal() const
{
	return 0;
}

template <class T>
void Conjunto<T>::remover(const T& clave)
{
}

template <class T>
const T&  Conjunto<T>::minimo() const
{
	T t;
	return t;
}

template <class T>
const T&  Conjunto<T>::maximo() const
{
	T t;
	return t;
}

template <class T>
void Conjunto<T>::mostrar(std::ostream& os) const {

}

#endif // CONJUNTO_HPP_

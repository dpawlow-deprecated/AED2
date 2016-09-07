#include <ostream>
#include "TiposBasicos.h"

/**
 * Esta clase representa una Pila de objetos de tipo genérico T.
 *
 * ATENCION: Las únicas cosas que se pueden asumir sobre 'T' es que tiene
 * definido el constructor por copia, el operador '<< (std::ostream&)' y
 * el operador de comparación '=='.
 */
template <typename T>
class Pila
{
  public:
      // Constructor sin parámetros. Crea una pila vacía.
      Pila();

      // Constructor por copia. Crea una nueva instancia de una Pila
      // que debe ser igual a la pasada por parámetro.
      Pila(const Pila& otra);

      // Destructor. Limpia toda la memoria dinámica que aún esté en uso.
      ~Pila();

      // El constructor puede ser visto como un generador
      void apilar(const T& elem);

      // En este caso, a diferencia del TAD, desapilar cambia el estado interno de mi instancia de clase
      // PRE: la pila no es vacía
      void desapilar();

    // Observadores básicos

      // Devuelve true si la Pila es vacía, false en caso contrario.
      bool esVacia() const;

      // Devuelve una referencia al elemento en el tope de la Pila.
      // PRE: La Pila no está vacía.
      T& tope();

      // Devuelve una referencia al elemento en el tope de la Pila.
      // PRE: La Pila no está vacía.
      const T& tope() const;

    // Otras operaciones

      // Devuelve la cantidad de elementos que hay en la pila.
      aed2::Nat tamanio() const;

      // Modifica esta instancia de Pila de tal manera que termine
      // siendo una copia de la Pila pasada por parámetro.
      // Devuelve una referencia a si misma.
      Pila& operator = (const Pila& otra);

      // IMPLEMENTACION OPCIONAL (no va a ser evaluada).
      // Compara dos instancias de Pila. Devuelve true si son iguales
      // y false en caso contrario.
      bool operator == (const Pila& otra) const;

      /**
       * Muestra la lista en un ostream.
       * formato de salida:
       *   [e_0, e_1, e_2, ...]
       * donde e_i es el resultado del "mostrar" el elemento i.
       * PRE: está definido el operador '<<' para los elementos de tipo 'T'.
       *
       * Nota: imprimir sobre os, es decir: os << "[" << ...
       *
       * ATENCION:
       *
       *  - entre elemento y elemento de la pila debe haber una coma y un espacio.
       *
       *  - El primer elemento que se muestra representa al tope de la pila, es
       *    decir, los elementos se muestran en orden inverso al que fueron apilados.
       */
      template<typename S>
      friend std::ostream& operator << (std::ostream& os, const Pila<S>& pila);

  private:

    struct Nodo {
        Nodo(T e) :elem(e) {}
        T elem;
        Nodo* sig;
    };

    Nodo* tope_;
    aed2::Nat tamanio_;

    void mostrar(std::ostream& os) const;

};

template <typename T>
Pila<T>::Pila()
{
    this->tamanio_ = 0;
    this->tope_ = 0;
}

template <typename T>
Pila<T>::Pila(const Pila& otra)
{
    Pila<T> p = otra;
    Pila<T> aux;
    for (int i = 0; i < otra.tamanio(); i++) {
        aux.apilar(p.tope());
        p.desapilar();
    }
    for (int i = 0; i < otra.tamanio(); i++) {
        this->apilar(aux.tope());
        aux.desapilar();
    }
}

template <typename T>
Pila<T>::~Pila()
{
    Nodo* aux = this->tope_;

    for (unsigned int i = 0; i < this->tamanio_; i++){
        Nodo* eliminado = aux;
        aux = aux->sig;
        delete eliminado;
    }
    delete aux;
    this->tamanio_ = 0;
    this->tope_ = 0;
}

template <typename T>
void Pila<T>::apilar(const T& elem)
{
    Nodo* nuevo = new Nodo(elem);

    nuevo->sig = this->tope_;
    this->tamanio_++;

    this->tope_ = nuevo;
}

template <typename T>
void Pila<T>::desapilar()
{
    Nodo* elim = this->tope_;
    this->tope_->elem = this->tope_->sig->elem;
    this->tope_->sig = this->tope_->sig->sig;

    delete elim;
    this->tamanio_--;
}

template <typename T>
bool Pila<T>::esVacia() const
{
    return tamanio_ == 0;
}

template <typename T>
T& Pila<T>::tope()
{
    return this->tope_->elem;
}

template <typename T>
const T& Pila<T>::tope() const
{
    return this->tope_->elem;
}

template <typename T>
aed2::Nat Pila<T>::tamanio() const
{
    return this->tamanio_;
}

template <typename T>
Pila<T>& Pila<T>::operator = (const Pila& otra)
{
    Pila<T> p = otra;
    Pila<T> aux;
    for (int i = 0; i < otra.tamanio(); i++) {
        aux.apilar(p.tope());
        p.desapilar();
    }
    for (int i = 0; i < otra.tamanio(); i++) {
        p.apilar(aux.tope());
        aux.desapilar();
    }

    return p;
}

/*template <typename T>
void Pila<T>::mostrar(std::ostream& os) const{

    Pila<T> p;
    p = this;
    os << "[";
    for (int i = 0; i < this->tamanio()-1; i++) {
        os << p.tope() << ", ";
        p.desapilar();
    }
    os << p.tope();
    os << "]";
}*/


template <typename T>
std::ostream& operator << (std::ostream& os, const Pila<T>& pila)
{
    /*std::cout << "hola" << std::endl;
    pila.mostrar(os);*/
    Pila<T> p(pila);
    //p = pila;
    os << "[";
    /*for (int i = 0; i < pila.tamanio()-1; i++) {
        os << p.tope() << ", ";
        p.desapilar();
    }
    os << p.tope();*/
    while (p.tamanio() > 0) {
        os << p.tope();
        p.desapilar();
        if (p.tamanio() > 1) {
            os << ", ";
        }
    }
    os << "]";
    return os;
}

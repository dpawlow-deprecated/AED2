#ifndef DICCHASHCERRADO_H_
#define DICCHASHCERRADO_H_

#include "Lista.h"

#ifndef TAM_TABLA_INI
	#define TAM_TABLA_INI 100
#endif
#ifndef UMBRAL_FC
	#define UMBRAL_FC	  0.75
#endif


namespace aed2 {

template<class S>
class DiccHashCerrado {
public:

	typedef String K;

	DiccHashCerrado();
	~DiccHashCerrado();

	bool 	 Definido(const K& clave) const;
	void 	 Definir(const K& clave, const S& significado);
	S& 		 Significado(const K& clave);
	void 	 Borrar(const K& clave);
	Nat 	 CantClaves() const;

	// solo para test!!
	Lista<K> Claves() const;
	float    factorCarga() const;
	Nat      colisiones() const;

private:

	struct TElem{
			K 	 clave;
			S 	 signif;

			TElem(const K& c, const S& v) : clave(c), signif(v) {}
		};


	Lista<TElem>*   _tabla;
	Nat             _cant_elems;
    Nat             _tam;


	Nat fn_hash (const String& str) const {

		Nat hash = 7;

		for (int i = 0; i < str.size(); i++) {
			hash *= 31;
			hash += charToNat(str[i]);
		}

		hash = hash % _tam;

		return hash;
	}

	Nat charToNat(char c) const {
			return (Nat)(c);
	}


	void redimensionarTabla(){

		Nat tamViejo = _tam;
		_tam *= 2;

		Lista<TElem>* tablaVieja = new Lista<TElem>[_tam];
		tablaVieja = _tabla;

		typename Lista<TElem>::Iterador it;

		for(Nat i=0; i < tamViejo; i++){
			for(it = _tabla[i].CrearIt(); it.HaySiguiente(); it.Avanzar()){
				Definir(it.Siguiente().clave, it.Siguiente().signif);
			}
		}


		delete tablaVieja;
		//this->_tabla = tablaNueva;
	}


};

/********************************************************************************
 * Implementacion
 ********************************************************************************/

template<class S>
DiccHashCerrado<S>::DiccHashCerrado()
: _cant_elems(0), _tam(TAM_TABLA_INI)
{
    _tabla = new Lista<TElem>[TAM_TABLA_INI];
}

template<class S>
DiccHashCerrado<S>::~DiccHashCerrado() {

    delete [] _tabla;
}

template<class S>
bool DiccHashCerrado<S>::Definido(const K& clave) const {

	typename Lista<TElem>::Iterador it;

	for (it = _tabla[fn_hash(clave)].CrearIt(); it.HaySiguiente(); it.Avanzar()) {
		if (it.Siguiente().clave == clave){
			return true;
		}
	}

	return false;
}


template<class S>
void DiccHashCerrado<S>::Definir(const K& clave, const S& significado) {

	if(factorCarga() > UMBRAL_FC){
		redimensionarTabla();
	}

	typename Lista<TElem>::Iterador it;

	for (it = _tabla[fn_hash(clave)].CrearIt(); it.HaySiguiente(); it.Avanzar()) {
		if (it.Siguiente().clave == clave){
			it.Siguiente().signif = significado;
			return;
		}
	}

	TElem e(clave, significado);
	_tabla[fn_hash(clave)].AgregarAtras(e);
	_cant_elems++;

}


template<class S>
S& DiccHashCerrado<S>::Significado(const K& clave) {

	Lista<TElem> ls = _tabla[fn_hash(clave)];

	typename Lista<TElem>::Iterador it;

	for (it = _tabla[fn_hash(clave)].CrearIt(); it.HaySiguiente(); it.Avanzar()) {
		if (it.Siguiente().clave == clave){
			S ret = it.Siguiente().signif;
			return ret;
		}
	}

}


template<class S>
void DiccHashCerrado<S>::Borrar(const K& clave) {

	Lista<TElem> ls = _tabla[fn_hash(clave)];

	typename Lista<TElem>::Iterador it;

	for (it = _tabla[fn_hash(clave)].CrearIt(); it.HaySiguiente(); it.Avanzar()) {
		if (it.Siguiente().clave == clave){
			it.EliminarSiguiente();
			_cant_elems--;
		}
	}

}


template<class S>
Nat DiccHashCerrado<S>::CantClaves() const {

	return _cant_elems;
}

// solo para test!!
template<class S>
Lista<typename DiccHashCerrado<S>::K> DiccHashCerrado<S>::Claves() const {
	Lista<K> ret;
	typename Lista<TElem>::const_Iterador it;

	for(Nat i=0; i < _tam; i++){
        for(it = _tabla[i].CrearIt(); it.HaySiguiente(); it.Avanzar())
            ret.AgregarAtras(it.Siguiente().clave);
	}

	return ret;
}

// solo para test!!
template<class S>
float DiccHashCerrado<S>::factorCarga() const {

	return float(_cant_elems)/_tam;
}

// solo para test!!
template<class S>
Nat DiccHashCerrado<S>::colisiones() const {

	Nat ret = 0;
	for(Nat i=0; i < _tam; i++){
		if (_tabla[i].Longitud() > 1)
			ret = ret + _tabla[i].Longitud() -1;
	}

	return ret;
}


} /* namespace aed2 */

#endif /* DICCHASHCERRADO_H_ */

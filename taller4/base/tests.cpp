#include <iostream>
#include "mini_test.h"

#include "DiccString.hpp"


//Chequea que el diccionario vacio no tenga claves
void test_claves_dicc_vacio() {
	DiccString<int> d;
	ASSERT(d.Claves().cardinal() == 0);
	d.Definir("hola", 1);
	ASSERT(d.Claves().cardinal() == 1);
	d.Definir("hoaeoueoau", 2);
	ASSERT(d.Claves().cardinal() == 2);
}


//Chequea el definir y definido
void test_definir_definido() {
	DiccString<int> d;
	d.Definir("hola",42);
	ASSERT( d.Definido("hola") );
	ASSERT( !d.Definido("casona") );
 	ASSERT( !d.Definido("casa") );

	d.Definir("casona",13);
	ASSERT( d.Definido("hola") );
	ASSERT( d.Definido("casona") );
  	ASSERT( !d.Definido("casa") );

  	d.Definir("casa",6);
	ASSERT( d.Definido("hola") );
	ASSERT( d.Definido("casona") );
  	ASSERT( d.Definido("casa") );
}



//cheque el obtener
void test_obtener() {
	DiccString<int> d;
	d.Definir("hola",42);
	d.Definir("casa",22);

	ASSERT( d.Obtener("hola") == 42 );
	ASSERT( d.Obtener("casa") == 22 );
}

//cheque el borrar
void test_borrar_uno() {
	DiccString<int> d;
	d.Definir("casa", 1);
	d.Borrar("casa");
	ASSERT(d.Definido("casa") == false);
	ASSERT(d.Claves().cardinal() == 0);
}

void test_borrar() {
	DiccString<int> d;
	d.Definir("hola",42);
	d.Definir("cas", 1);
	d.Definir("casa",22);
	d.Definir("casanova", 50);
 	d.Borrar("casa");

	ASSERT( d.Definido("cas") );
	ASSERT( d.Definido("hola") );
	ASSERT( d.Definido("casanova") );
	ASSERT(!d.Definido("casa") );

	d.Borrar("casanova");
	ASSERT( d.Definido("cas") );
	ASSERT( d.Definido("hola") );
	ASSERT(!d.Definido("casanova") );
	ASSERT(!d.Definido("casa") );

	d.Borrar("cas");
	ASSERT(!d.Definido("cas") );
	ASSERT( d.Definido("hola") );
	ASSERT(!d.Definido("casanova") );
	ASSERT(!d.Definido("casa") );

	d.Borrar("hola");
	ASSERT(!d.Definido("cas") );
	ASSERT(!d.Definido("hola") );
	ASSERT(!d.Definido("casanova") );
	ASSERT(!d.Definido("casa") );

	ASSERT(d.Claves().cardinal() == 0);
}

void test_copia_referencia() {
	DiccString<int> d;
	d.Definir("hola",42);
	d.Definir("cas", 1);
	d.Definir("casa",22);
	d.Definir("casanova", 50);

	DiccString<int> d2(d);
	d.Borrar("casa");

	ASSERT(d.Claves().cardinal() == d2.Claves().cardinal()-1);
	ASSERT(d.Obtener("hola") == d2.Obtener("hola"));
	ASSERT(d.Obtener("cas") == d2.Obtener("cas"));
	ASSERT(d.Obtener("casanova") == d2.Obtener("casanova"));

	ASSERT(d.Definido("casa") == false);
	ASSERT(d2.Definido("casa") == true);
	ASSERT(d2.Obtener("casa") == 22);
}

void test_todos_prefijos() {
	DiccString<int> d;
	DiccString< DiccString<int> > d2;

	d.Definir("hola", 1);
	d2.Definir("uno", d);
	ASSERT(d2.Claves().cardinal() == 1);
	ASSERT(d2.Obtener("uno").Obtener("hola")     == 1);
	ASSERT(d2.Obtener("uno").Definido("holas")   == false);
	ASSERT(d2.Obtener("uno").Definido("holasa")  == false);
	ASSERT(d2.Definido("uno")  == true);
	ASSERT(d2.Definido("unodos")  == false);
	ASSERT(d2.Definido("unodostres") == false);


	d.Definir("holas", 2);
	d2.Definir("unodos", d);
	ASSERT(d2.Claves().cardinal() == 2);
	ASSERT(d2.Obtener("unodos").Obtener("hola")     == 1);
	ASSERT(d2.Obtener("unodos").Obtener("holas")    == 2);
	ASSERT(d2.Obtener("unodos").Definido("holasa")  == false);
	ASSERT(d2.Definido("uno")  == true);
	ASSERT(d2.Definido("unodos")  == true);
	ASSERT(d2.Definido("unodostres") == false);

	d.Definir("holasa", 3);
	d2.Definir("unodostres", d);
	ASSERT(d2.Claves().cardinal() == 3);
	ASSERT(d2.Obtener("unodostres").Obtener("hola")     == 1);
	ASSERT(d2.Obtener("unodostres").Obtener("holas")    == 2);
	ASSERT(d2.Obtener("unodostres").Obtener("holasa")   == 3);
	ASSERT(d2.Definido("uno")  == true);
	ASSERT(d2.Definido("unodos")  == true);
	ASSERT(d2.Definido("unodostres") == true);

	d2.Borrar("uno");
	ASSERT(d2.Definido("uno") == false);
	ASSERT(d2.Definido("unodos") == true);
	ASSERT(d2.Definido("unodostres") == true);

	d2.Borrar("unodos");
	ASSERT(d2.Definido("uno") == false);
	ASSERT(d2.Definido("unodos") == false);
	ASSERT(d2.Definido("unodostres") == true);

	d2.Borrar("unodostres");
	ASSERT(d2.Definido("uno") == false);
	ASSERT(d2.Definido("unodos") == false);
	ASSERT(d2.Definido("unodostres") == false);
}

void test_doble_definicion() {
	DiccString<int> d;
	d.Definir("hola", 1);
	d.Definir("hola", 2);
	d.Definir("holas", 3);
	d.Definir("holas", 4);

	ASSERT(d.Obtener("hola") == 2);
	ASSERT(d.Obtener("holas") == 4);
}

void test_definicion_vacia() {
	DiccString<int> d;
	d.Definir("", 10);
	d.Definir("da", 12);
	d.Definir("dario", 13);
	d.Definir("hola", 14);

	d.Borrar("da");
	ASSERT(d.Definido("") == true);
	ASSERT(d.Definido("da") == false);
	ASSERT(d.Definido("dario") == true);
	ASSERT(d.Definido("hola") == true);

	d.Borrar("dario");
	ASSERT(d.Definido("") == true);
	ASSERT(d.Definido("da") == false);
	ASSERT(d.Definido("dario") == false);
	ASSERT(d.Definido("hola") == true);

	d.Borrar("hola");
	ASSERT(d.Definido("") == true);
	ASSERT(d.Definido("da") == false);
	ASSERT(d.Definido("dario") == false);
	ASSERT(d.Definido("hola") == false);

	d.Borrar("");
	ASSERT(d.Definido("") == false);
	ASSERT(d.Definido("da") == false);
	ASSERT(d.Definido("dario") == false);
	ASSERT(d.Definido("hola") == false);
}

void test_cardinal_claves() {
	DiccString<int> d;
	d.Definir("hola", 10);

	DiccString<int> d2(d);
	d.Definir("chau", 10);

	ASSERT(d.Claves().cardinal() == 2);
	ASSERT(d2.Claves().cardinal() == 1);
}

void test_todos_prefijos_con_varias_hojas() {
	DiccString<string> d;
	//d.Definir("", "o");
	d.Definir("a", "o");
	d.Definir("ag", "o");
	d.Definir("aga", "o");
	d.Definir("agar", "o");
	d.Definir("agarr", "o");
	d.Definir("agarra", "o");
	d.Definir("agarram", "o");
	d.Definir("agarrame", "o");
	d.Definir("agarramel", "o");
	d.Definir("agarramela", "o");
	d.Definir("agarramelo", "o");
	d.Definir("agarramele", "o");
	d.Definir("agarramelu", "o");

	//ASSERT(d.Claves().cardinal() == 14);
	//d.Borrar("");
	ASSERT(d.Claves().cardinal() == 13);
	d.Borrar("a");
	ASSERT(d.Claves().cardinal() == 12);
	d.Borrar("ag");
	ASSERT(d.Claves().cardinal() == 11);
	d.Borrar("aga");
	ASSERT(d.Claves().cardinal() == 10);
	d.Borrar("agar");
	ASSERT(d.Claves().cardinal() == 9);
	d.Borrar("agarr");
	ASSERT(d.Claves().cardinal() == 8);
	d.Borrar("agarra");
	ASSERT(d.Claves().cardinal() == 7);
	d.Borrar("agarram");
	ASSERT(d.Claves().cardinal() == 6);
	d.Borrar("agarrame");
	ASSERT(d.Claves().cardinal() == 5);
	d.Borrar("agarramel");
	ASSERT(d.Claves().cardinal() == 4);
	d.Borrar("agarramela");
	ASSERT(d.Claves().cardinal() == 3);
	d.Borrar("agarramelo");
	ASSERT(d.Claves().cardinal() == 2);
	d.Borrar("agarramele");
	ASSERT(d.Claves().cardinal() == 1);
	d.Borrar("agarramelu");
	ASSERT(d.Claves().cardinal() == 0);
}


int main() {
	RUN_TEST(test_claves_dicc_vacio);
	RUN_TEST(test_definir_definido);
	RUN_TEST(test_obtener);
	RUN_TEST(test_borrar_uno);
	RUN_TEST(test_borrar);
	RUN_TEST(test_copia_referencia);
	RUN_TEST(test_todos_prefijos);
	RUN_TEST(test_doble_definicion);
	//RUN_TEST(test_definicion_vacia);
	RUN_TEST(test_cardinal_claves);
	RUN_TEST(test_todos_prefijos_con_varias_hojas);
	//Realizar más test para chequear el funcionamiento del diccionario sobre trie.

	return 0;

}

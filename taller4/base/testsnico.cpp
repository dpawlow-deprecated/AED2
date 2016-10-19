#include <iostream>
#include "mini_test.h"

#include "DiccString.hpp"


//Chequea que el diccionario vacio no tenga claves
void test_claves_dicc_vacio() {
	DiccString<int> d;
	ASSERT(d.Claves().cardinal() == 0);
}

//Chequea que el diccionario vacio no tenga claves
void test_claves_dicc_1_elem() {
	DiccString<int> d;
	ASSERT(d.Claves().cardinal() == 0);
	d.Definir("casa", 322);
	ASSERT(d.Claves().cardinal() == 1);
	ASSERT(d.Definido("casa"));
	ASSERT(d.Obtener("casa") == 322);
	ASSERT(!d.Definido("casandra"));
	d.Borrar("casa");
	ASSERT(d.Claves().cardinal() == 0);
	ASSERT(!d.Definido("casa"));
	ASSERT(!d.Definido("casandra"));
}

//Chequea que el diccionario vacio no tenga claves
void test_claves_dicc_words_same_prefix() {
	DiccString<int> d;
	ASSERT(d.Claves().cardinal() == 0);
	d.Definir("casa", 10);
	ASSERT(d.Claves().cardinal() == 1);
	ASSERT(d.Definido("casa"));
	ASSERT(!d.Definido("casandra"));
	ASSERT(d.Obtener("casa") == 10);
	d.Definir("casandra", 20);
	ASSERT(d.Claves().cardinal() == 2);
	ASSERT(d.Definido("casa"));
	ASSERT(d.Definido("casandra"));
	ASSERT(d.Obtener("casa") == 10);
	ASSERT(d.Obtener("casandra") == 20);
	d.Borrar("casa");
	ASSERT(d.Claves().cardinal() == 1);
	ASSERT(!d.Definido("casa"));
	ASSERT(d.Definido("casandra"));
	ASSERT(d.Obtener("casandra") == 20);
	d.Borrar("casandra");
	ASSERT(d.Claves().cardinal() == 0);
	ASSERT(!d.Definido("casa"));
	ASSERT(!d.Definido("casandra"));
}
void test_claves_dicc_words_same_prefix_2() {
	DiccString<int> d;
	ASSERT(d.Claves().cardinal() == 0);
	d.Definir("casa", 10);
	ASSERT(d.Claves().cardinal() == 1);
	ASSERT(d.Definido("casa"));
	ASSERT(!d.Definido("casandra"));
	ASSERT(d.Obtener("casa") == 10);
	d.Definir("casandra", 20);
	ASSERT(d.Claves().cardinal() == 2);
	ASSERT(d.Definido("casa"));
	ASSERT(d.Definido("casandra"));
	ASSERT(d.Obtener("casa") == 10);
	ASSERT(d.Obtener("casandra") == 20);

	std::cout << "pre borrar casandra" << std::endl;
	d.Borrar("casandra");
	std::cout << "post borrar casandra 1" << std::endl;

	ASSERT(d.Claves().cardinal() == 1);

	std::cout << "post borrar casandra 2" << std::endl;

	ASSERT(d.Definido("casa"));

	std::cout << "post borrar casandra 3" << std::endl;

	ASSERT(!d.Definido("casandra"));

	std::cout << "post borrar casandra 4" << std::endl;

	ASSERT(d.Obtener("casa") == 10);

	std::cout << "post borrar casandra 5" << std::endl;


	d.Borrar("casa");

	std::cout << "post borrar casa 1" << std::endl;

	ASSERT(d.Claves().cardinal() == 0);


	std::cout << "post borrar casa 2" << std::endl;


	ASSERT(!d.Definido("casa"));

	std::cout << "post borrar casa 3" << std::endl;


	ASSERT(!d.Definido("casandra"));

	std::cout << "post borrar casa 4" << std::endl;



}

void test_claves_dicc_words_same_prefix_3() {
	DiccString<int> d;
	ASSERT(d.Claves().cardinal() == 0);
	d.Definir("casa", 10);
	ASSERT(d.Claves().cardinal() == 1);
	ASSERT(d.Definido("casa"));
	ASSERT(!d.Definido("carlos"));
	ASSERT(d.Obtener("casa") == 10);
	d.Definir("carlos", 20);
	ASSERT(d.Claves().cardinal() == 2);
	ASSERT(d.Definido("casa"));
	ASSERT(d.Definido("carlos"));
	ASSERT(d.Obtener("casa") == 10);
	ASSERT(d.Obtener("carlos") == 20);
	d.Borrar("carlos");
	ASSERT(d.Claves().cardinal() == 1);
	ASSERT(d.Definido("casa"));
	ASSERT(!d.Definido("carlos"));
	ASSERT(d.Obtener("casa") == 10);
	d.Borrar("casa");
	ASSERT(d.Claves().cardinal() == 0);
	ASSERT(!d.Definido("casa"));
	ASSERT(!d.Definido("carlos"));
}


void test_claves_dicc_words_same_prefix_4() {
	DiccString<int> d;
	ASSERT(d.Claves().cardinal() == 0);
	d.Definir("casa", 10);
	ASSERT(d.Claves().cardinal() == 1);
	ASSERT(d.Definido("casa"));
	ASSERT(!d.Definido("carlos"));
	ASSERT(d.Obtener("casa") == 10);
	d.Definir("carlos", 20);

	std::cout << "post def carlos" << std::endl;

	ASSERT(d.Claves().cardinal() == 2);
	ASSERT(d.Definido("casa"));
	ASSERT(d.Definido("carlos"));
	ASSERT(d.Obtener("casa") == 10);
	ASSERT(d.Obtener("carlos") == 20);

	std::cout << "pre borrar casa" << std::endl;

	d.Borrar("casa");

	std::cout << "post borrar casa" << std::endl;

	ASSERT(d.Claves().cardinal() == 1);
	ASSERT(d.Definido("carlos"));
	ASSERT(!d.Definido("casa"));
	ASSERT(d.Obtener("carlos") == 20);
	d.Borrar("carlos");
	ASSERT(d.Claves().cardinal() == 0);
	ASSERT(!d.Definido("casa"));
	ASSERT(!d.Definido("carlos"));
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

//cheque el obtener
void test_copia() {
	DiccString<int> d;
	ASSERT(d.Claves().cardinal() == 0);
	d.Definir("casa", 10);
	ASSERT(d.Claves().cardinal() == 1);
	ASSERT(d.Definido("casa"));
	ASSERT(!d.Definido("casandra"));
	ASSERT(d.Obtener("casa") == 10);
	d.Definir("casandra", 20);
	ASSERT(d.Claves().cardinal() == 2);
	ASSERT(d.Definido("casa"));
	ASSERT(d.Definido("casandra"));
	ASSERT(d.Obtener("casa") == 10);
	ASSERT(d.Obtener("casandra") == 20);
	DiccString<int> e = d;
	ASSERT(e.Claves().cardinal() == 2);
	ASSERT(e.Definido("casa"));
	ASSERT(e.Definido("casandra"));
	ASSERT(e.Obtener("casa") == 10);
	ASSERT(e.Obtener("casandra") == 20);
}

//cheque el obtener
void test_copia_dir_dir() {
	DiccString<int> d;
	ASSERT(d.Claves().cardinal() == 0);
	d.Definir("casa", 10);
	ASSERT(d.Claves().cardinal() == 1);
	ASSERT(d.Definido("casa"));
	ASSERT(!d.Definido("casandra"));
	ASSERT(d.Obtener("casa") == 10);
	d.Definir("casandra", 20);
	ASSERT(d.Claves().cardinal() == 2);
	ASSERT(d.Definido("casa"));
	ASSERT(d.Definido("casandra"));
	ASSERT(d.Obtener("casa") == 10);
	ASSERT(d.Obtener("casandra") == 20);
	DiccString<int> e = d;
	ASSERT(e.Claves().cardinal() == 2);
	ASSERT(e.Definido("casa"));
	ASSERT(e.Definido("casandra"));
	ASSERT(e.Obtener("casa") == 10);
	ASSERT(e.Obtener("casandra") == 20);

	DiccString<DiccString<int> > f;
	f.Definir("hola", d);
	f.Definir("holanda", e);

}

//cheque el obtener
void test_copia_dir_dir_2() {
	DiccString<int> d;
	d.Definir("casa", 10);
	d.Definir("casandra", 20);
	d.Definir("carlos", 30);
	d.Definir("pedrito", 40);
	d.Definir("peterpan", 50);
	DiccString<int> e = d;

	DiccString<DiccString<int> > f;
	f.Definir("hola", d);
	f.Definir("holanda", e);

}

//cheque el obtener
void test_copia_dir_dir_3() {
	DiccString<int> d;
	d.Definir("casa", 10);
	d.Definir("casandra", 20);
	d.Definir("carlos", 30);
	d.Definir("pedrito", 40);
	d.Definir("peterpan", 50);
	DiccString<int> e = d;

	DiccString<DiccString<int> > f;
	f.Definir("hola", d);
	f.Definir("holanda", e);


DiccString<DiccString<DiccString<int> > > k;
 k.Definir("casa", f);
 k.Definir("casandra", f);
}

//cheque el borrar
void test_borrar() {
	//Completar este test para:
	//Verificar que al borrar una palabra, esta deja de estar definida en el diccionario
	//Chequear que si dos palabras comparten prefijos y una de ellas se borrar, la otra debe seguir estando definida
	//Analizar que el borrado funciona bien si el diccionario tiene definido una sola palabra y esta se borra.

	DiccString<int> d;
	d.Definir("hola",42);
	d.Definir("casa",22);
 	d.Borrar("casa");
	ASSERT( d.Definido("hola") );
	ASSERT(!d.Definido("casa") );

}

void test_complejo() {
	//Completar este test para:
	//Verificar que al borrar una palabra, esta deja de estar definida en el diccionario
	//Chequear que si dos palabras comparten prefijos y una de ellas se borrar, la otra debe seguir estando definida
	//Analizar que el borrado funciona bien si el diccionario tiene definido una sola palabra y esta se borra.

	DiccString<int> d;
	d.Definir("casa", 10);
	d.Definir("casandra", 20);
	d.Definir("casandro", 20);
	d.Definir("casandros", 20);
	d.Definir("carlos", 30);
	d.Definir("pedrito", 40);
	d.Definir("peterpan", 50);

}



int main() {
	RUN_TEST(test_claves_dicc_vacio);
	RUN_TEST(test_claves_dicc_1_elem);
	RUN_TEST(	test_claves_dicc_words_same_prefix);
	RUN_TEST(	test_claves_dicc_words_same_prefix_2);
	RUN_TEST(	test_claves_dicc_words_same_prefix_3);
	RUN_TEST(	test_claves_dicc_words_same_prefix_4);
	RUN_TEST(test_definir_definido);
	RUN_TEST(test_obtener);
	RUN_TEST(test_copia);
	RUN_TEST(	test_copia_dir_dir);
	RUN_TEST(	test_copia_dir_dir_2);
	RUN_TEST(	test_copia_dir_dir_3);
	RUN_TEST(test_borrar);
	RUN_TEST(test_complejo);


	//Realizar más test para chequear el funcionamiento del diccionario sobre trie.

	return 0;

}

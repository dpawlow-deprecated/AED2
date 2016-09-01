#include "Pila.h"
#include "mini_test.h"
#include <iostream>

// para compilar:$ g++ -g tests.cpp Pila.cpp -o Pila
// para ejecutar con valgrind:$ valgrind --leak-check=full -v ./Pila

void test_vacia() {
  Pila p;
  ASSERT_EQ(p.tamanio(), 0);
}

void test_apilar() {
  Pila p;

  ElemPila elem;
  elem.id = 1;
  elem.nombre = "hola";
  elem.descripcion = "chau";

  p.apilar(elem);
  p.apilar(elem);
  std::cout << p;

  ASSERT_EQ(p.tamanio(), 2);
}

void test_apilar_tamanio() {
  Pila p;

  ElemPila elem;
  elem.id = 1;
  elem.nombre = "hola";
  elem.descripcion = "chau";

  p.apilar(elem);

  ASSERT_EQ(p.tamanio(), 1);
}

void test_apilar_elem() {
  Pila p;

  ElemPila elem;
  elem.id = 1;
  elem.nombre = "hola";
  elem.descripcion = "chau";

  p.apilar(elem);

  ASSERT_EQ(p.tope().id, elem.id);
}

void test_desapilar() {

    Pila p;

    ElemPila elem;
    elem.id = 1;
    elem.nombre = "hola";
    elem.descripcion = "chau";

    p.apilar(elem);


    ASSERT(p.desapilar() == elem);
}

void test_asignacion() {

    Pila p;
    ElemPila elem;
    elem.id = 1;
    elem.nombre = "hola";
    elem.descripcion = "chau";

    p.apilar(elem);

    Pila c = p;

    ASSERT(c.desapilar() == elem);
}

int main() {
  RUN_TEST(test_vacia);
  RUN_TEST(test_apilar);
  RUN_TEST(test_apilar_tamanio);
  RUN_TEST(test_apilar_elem);
  RUN_TEST(test_desapilar);
  RUN_TEST(test_asignacion);
  // HACER MAS TEST

  return 0;
}

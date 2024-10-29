#include "pa2m.h"
#include "src/abb.h"
#include <stdint.h>

int comparador(void *a, void *b)
{
	if (a == b)
		return 0;
	if (a > b)
		return 1;
	return -1;
}
int comparadornum(void *_a, void *_b)
{
	int *a = _a;
	int *b = _b;
	return *a - *b;
}
void destructor(void *elemento)
{
	printf("puntero a %p destruido\n", elemento);
}
void destructormas(void *elemento)
{
	int *numero = elemento;
	(*numero)++;
	printf("puntero a %d destruido\n", *(int *)elemento);
}

bool mostrar(void *elemento, void *ctx)
{
	// printf(" puntero %p\n", elemento);
	// if (elemento == NULL)
	// 	return false;
	// return true;

	printf("%d\n", (int)(intptr_t)elemento);
	return false;
}
bool mostrar_hasta(void *elemento, void *ctx)
{
	int *indice = (int *)ctx;
	printf("%d\n", *indice);
	(*indice)++;
	if ((*indice) == 5)
		return false;

	return true;
}
abb_t *arbolCreado()
{
	abb_t *arbol = abb_crear(&comparador);
	abb_t *sincomp = abb_crear(NULL);
	pa2m_afirmar(arbol != NULL, "existe el arbol con comparador");
	pa2m_afirmar(sincomp == NULL, "no existe el arbol sin comparador");
	return arbol;
}
void destruirArbol(abb_t *arbol)
{
	abb_destruir(arbol);
}
void pruebaInsertar(abb_t *arbol)
{
	pa2m_afirmar(abb_insertar(arbol, (void *)(intptr_t)50),
		     "se inserto %d al arbol", 50);
	pa2m_afirmar(abb_insertar(arbol, (void *)(intptr_t)19),
		     "se inserto %d al arbol", 19);
	pa2m_afirmar(abb_insertar(arbol, (void *)(intptr_t)8),
		     "se inserto %d al arbol", 8);
	pa2m_afirmar(abb_insertar(arbol, (void *)(intptr_t)60),
		     "se inserto %d al arbol", 60);
	pa2m_afirmar(abb_insertar(arbol, (void *)(intptr_t)46),
		     "se inserto %d al arbol", 46);
	pa2m_afirmar(abb_insertar(arbol, (void *)(intptr_t)25),
		     "se inserto %d al arbol", 25);
	pa2m_afirmar(abb_insertar(arbol, (void *)(intptr_t)10),
		     "se inserto %d al arbol", 10);

	printf("\n");
}
void pruebaCant(abb_t *cant)
{
	size_t nodos = abb_cantidad(cant);
	pa2m_afirmar(nodos == 7, "cantidad correcta(%d) en el arbol(%zu)", 7,
		     nodos);
}
void pruebaCant6(abb_t *cant)
{
	size_t nodos = abb_cantidad(cant);
	pa2m_afirmar(nodos == 6, "cantidad correcta(%d) en el arbol(%zu)", 6,
		     nodos);
}
void pruebaObt(abb_t *arbol)
{
	pa2m_afirmar(abb_obtener(arbol, (void *)50) != NULL, "se encontro %d ",
		     50);
	pa2m_afirmar(abb_obtener(arbol, (void *)19) != NULL,
		     "se encontro %d al arbol", 19);
	pa2m_afirmar(abb_obtener(arbol, (void *)8) != NULL,
		     "se encontro %d al arbol", 8);
	pa2m_afirmar(abb_obtener(arbol, (void *)60) != NULL,
		     "se encontro %d al arbol", 60);
	pa2m_afirmar(abb_obtener(arbol, (void *)46) != NULL,
		     "se encontro %d al arbol", 46);
	pa2m_afirmar(abb_obtener(arbol, (void *)25) != NULL,
		     "se encontro %d al arbol", 25);
	pa2m_afirmar(abb_obtener(arbol, (void *)10) != NULL,
		     "se encontro %d al arbol", 10);
}

void pruebaQuitar(abb_t *arbol)
{
	void *encontrado = NULL;
	bool prueba = abb_quitar(arbol, (void *)(intptr_t)50, &encontrado);
	pa2m_afirmar(prueba, "se encontro %p", encontrado);
	printf("\n");
}

void pruebaIterarIN(abb_t *arbol)
{
	size_t cant = abb_iterar_inorden(arbol, &mostrar, NULL);
	pa2m_afirmar(cant == 1, "se itero 1 veces(%zu)", cant);
}
void pruebaIterarIN_hasta(abb_t *arbol)
{
	int hasta = 0;
	size_t cant = abb_iterar_inorden(arbol, mostrar_hasta, &hasta);
	pa2m_afirmar(cant == 5, "se itero 5 veces(%zu)", cant);
}
void pruebaIterarPRE(abb_t *arbol)
{
	size_t cant = abb_iterar_preorden(arbol, &mostrar, NULL);
	pa2m_afirmar(cant == 1, "se itero 1 veces(%zu) pre", cant);
}
void pruebaIterarPRE_hasta(abb_t *arbol)
{
	int hasta = 0;
	size_t cant = abb_iterar_preorden(arbol, mostrar_hasta, &hasta);
	pa2m_afirmar(cant == 5, "se itero 5 veces(%zu) pre", cant);
}
void pruebaIterarPOS(abb_t *arbol)
{
	size_t cant = abb_iterar_postorden(arbol, &mostrar, NULL);
	pa2m_afirmar(cant == 1, "se itero 1 veces(%zu) pos", cant);
}
void pruebaIterarPOS_hasta(abb_t *arbol)
{
	int hasta = 0;
	size_t cant = abb_iterar_postorden(arbol, mostrar_hasta, &hasta);
	pa2m_afirmar(cant == 5, "se itero 5 veces(%zu) pos", cant);
}

void pruebaVectorizarIN(abb_t *arbol)
{
	void *vector = calloc(7, sizeof(void *));
	size_t tamanio = abb_vectorizar_inorden(arbol, vector, 7);
	pa2m_afirmar(tamanio == 7, "se lleno correctamente el vector");
	for (int i = 0; i < 7; i++) {
		printf("vector pos %d valor %p\n", i, ((void **)vector)[i]);
	}
	free(vector);
}
void pruebaVectorizarINmenos(abb_t *arbol)
{
	void *vector = calloc(5, sizeof(void *));
	size_t tamanio = abb_vectorizar_inorden(arbol, vector, 5);
	pa2m_afirmar(tamanio == 5, "se lleno correctamente el vector(%zu)",
		     tamanio);
	for (int i = 0; i < 5; i++) {
		printf("vector pos %d valor %p\n", i, ((void **)vector)[i]);
	}
	free(vector);
}
void pruebaVectorizarPRE(abb_t *arbol)
{
	void *vector = calloc(7, sizeof(void *));
	size_t tamanio = abb_vectorizar_preorden(arbol, vector, 7);
	pa2m_afirmar(tamanio == 7, "se lleno correctamente el vector");
	for (int i = 0; i < 7; i++) {
		printf("vector pos %d valor %p\n", i, ((void **)vector)[i]);
	}
	free(vector);
}
void pruebaVectorizarPOS(abb_t *arbol)
{
	void *vector = calloc(7, sizeof(void *));
	size_t tamanio = abb_vectorizar_postorden(arbol, vector, 7);
	pa2m_afirmar(tamanio == 7, "se lleno correctamente el vector");
	for (int i = 0; i < 7; i++) {
		printf("vector pos %d valor %p\n", i, ((void **)vector)[i]);
	}
	free(vector);
}
void probarNULL(abb_t *arbol)
{
	pa2m_afirmar(abb_insertar(arbol, NULL), "insercion con NULL");
	pa2m_afirmar(abb_quitar(arbol, NULL, NULL), "quitar con NULL");
	pa2m_afirmar(abb_obtener(arbol, NULL) == NULL, "obtener con NULL");
	pa2m_afirmar(abb_cantidad(NULL) == 0, "cantidad con NULL");
	pa2m_afirmar(abb_iterar_inorden(arbol, NULL, NULL) == 0,
		     "iterar con NULL");
	pa2m_afirmar(abb_vectorizar_inorden(arbol, NULL, 0) == 0,
		     "iterar con NULL");
}
void probar_eliminar_un_solo()
{
	abb_t *abb = abb_crear(comparador);
	abb_insertar(abb, (void *)(intptr_t)10);
	void *encontrado = NULL;
	abb_quitar(abb, (void *)(intptr_t)10, &encontrado);
	void *nulo = abb_obtener(abb, encontrado);
	pa2m_afirmar(abb_cantidad(abb) == 0,
		     "hay 0 elementos, se quito %p, se encontro %p\n",
		     encontrado, nulo);
	abb_destruir_todo(abb, &destructor);
}
void mostrar_vector(void **vector, size_t tamanio)
{
	for (size_t i = 0; i < tamanio; i++) {
		printf("Posición %zu: %d\n", i, (int)(intptr_t)vector[i]);
	}
}
void probar_recorrer_con_menos()
{
	abb_t *abb = abb_crear(comparador);
	abb_insertar(abb, (void *)(intptr_t)10);
	abb_insertar(abb, (void *)(intptr_t)20);
	abb_insertar(abb, (void *)(intptr_t)5);
	abb_insertar(abb, (void *)(intptr_t)30);
	void *vector = calloc(3, sizeof(void *));
	size_t tamanio = abb_vectorizar_inorden(abb, vector, 3);

	mostrar_vector((void **)vector, tamanio);
	pa2m_afirmar(tamanio == 3, "se lleno correctamente el vector(%zu)\n",
		     tamanio);
	abb_destruir_todo(abb, &destructor);
	free(vector);
}
void insertar_mucho_quitar_destruir()
{
	abb_t *abb = abb_crear(comparador);
	int a = 100, b = 100;
	abb_insertar(abb, (void *)&a);
	abb_insertar(abb, (void *)110);
	abb_insertar(abb, (void *)90);
	abb_insertar(abb, (void *)120);
	abb_insertar(abb, (void *)130);
	abb_insertar(abb, (void *)70);
	abb_insertar(abb, (void *)&b);
	abb_insertar(abb, (void *)80);

	void *encontrado80 = NULL;
	abb_quitar(abb, (void *)80, &encontrado80);

	void *buscado80 = abb_obtener(abb, encontrado80);
	pa2m_afirmar(buscado80 != encontrado80, "buscado %p\n", buscado80);

	printf("cantidad = %zu\n", abb_cantidad(abb));
	void *encontrado100 = NULL;
	abb_quitar(abb, &a, &encontrado100);

	void *buscado100 = abb_obtener(abb, (void *)&a);

	pa2m_afirmar(buscado100 != encontrado100, "buscado %p encontrado %p\n",
		     buscado100, encontrado100);

	printf("cantidad = %zu\n", abb_cantidad(abb));
	abb_destruir_todo(abb, destructor);
}
void insertar_repetidos()
{
	abb_t *abb = abb_crear(comparadornum);
	int a = 10, b = 10, c = 5, d = 15, f = 10;
	abb_insertar(abb, &a);
	abb_insertar(abb, &b);
	abb_insertar(abb, &c);
	abb_insertar(abb, &d);
	abb_insertar(abb, &f);
	printf("cantidad = %zu\n", abb_cantidad(abb));
	void *encontrado80 = NULL;
	abb_quitar(abb, &a, &encontrado80);
	printf("encontrado a %p\n", encontrado80);
	void *buscado80 = abb_obtener(abb, encontrado80);
	pa2m_afirmar(buscado80 != encontrado80, "buscado %p\n", buscado80);
	void *buscado100 = abb_obtener(abb, &b);
	pa2m_afirmar(buscado100 != encontrado80, "buscado %p\n", buscado100);
	printf("cantidad = %zu\n", abb_cantidad(abb));
	abb_destruir_todo(abb, destructor);
}
void pruebaObtenerRaiz(abb_t *arbol)
{
	void *encontrado = NULL;
	pa2m_afirmar(abb_quitar(arbol, (void *)50, &encontrado) == false,
		     "se encontro %p ", (void *)encontrado);
}

void insertar_quitar()
{
	abb_t *abb = abb_crear(comparador);
	int b = 10, c = 5, d = 15, f = 20;
	abb_insertar(abb, &b);
	abb_insertar(abb, &c);
	abb_insertar(abb, &d);
	abb_insertar(abb, &f);
	printf("cantidad = %zu\n", abb_cantidad(abb));
	void *encontrado80 = NULL;

	pa2m_afirmar(abb_quitar(abb, &b, &encontrado80), "Quitado elemento %d",
		     (int)(intptr_t)encontrado80);
	void *buscadoB = abb_obtener(abb, &b);
	pa2m_afirmar(buscadoB == NULL, "elemento quitado no se encontro");
	abb_destruir_todo(abb, destructor);
}

void prueba_destructor_todo()
{
	abb_t *abb = abb_crear(comparador);
	int b = 10, c = 5, d = 15, f = 20;
	int a = 8, t = 30, n = 13, m = 3;
	abb_insertar(abb, &b);
	abb_insertar(abb, &c);
	abb_insertar(abb, &d);
	abb_insertar(abb, &f);
	abb_insertar(abb, &a);
	abb_insertar(abb, &t);
	abb_insertar(abb, &n);
	abb_insertar(abb, &m);
	printf("cantidad = %zu\n", abb_cantidad(abb));

	pa2m_afirmar(abb_quitar(abb, &a, NULL), "se quito correctamente");
	pa2m_afirmar(abb_quitar(abb, &t, NULL), "se quito correctamente");
	pa2m_afirmar(abb_quitar(abb, &n, NULL), "se quito correctamente");
	pa2m_afirmar(abb_quitar(abb, &m, NULL), "se quito correctamente");
	printf("cantidad despues de quitar = %zu\n", abb_cantidad(abb));
	abb_destruir_todo(abb, destructormas);
	pa2m_afirmar(b == 11,
		     "variable b con numero original 10, ahora es %d\n", b);
	pa2m_afirmar(c == 6, "variable c con numero original 5, ahora es %d\n",
		     c);
	pa2m_afirmar(d == 16,
		     "variable d con numero original 15, ahora es %d\n", d);
	pa2m_afirmar(f == 21,
		     "variable f con numero original 20, ahora es %d\n", f);
}
int main()
{
	pa2m_nuevo_grupo("============== ??? ===============");
	insertar_mucho_quitar_destruir();
	abb_t *arbol = arbolCreado();
	pruebaInsertar(arbol);

	pa2m_nuevo_grupo("============== ??? ===============");
	pruebaIterarIN(arbol);
	pruebaCant(arbol);
	pruebaIterarPOS(arbol);
	pruebaIterarPRE(arbol);
	pruebaIterarIN_hasta(arbol);
	pruebaIterarPOS_hasta(arbol);
	pruebaIterarPRE_hasta(arbol);
	pa2m_nuevo_grupo("============== ??? ===============");
	pruebaVectorizarIN(arbol);
	pruebaVectorizarINmenos(arbol);
	pruebaVectorizarPRE(arbol);
	pruebaVectorizarPOS(arbol);
	pa2m_nuevo_grupo("============== ??? ===============");
	pruebaObt(arbol);
	pruebaQuitar(arbol);
	pa2m_nuevo_grupo("============== ??? ===============");
	pruebaCant6(arbol);
	probarNULL(arbol);
	//abb_destruir(arbol);

	printf("\n");
	probar_eliminar_un_solo();
	pruebaObtenerRaiz(arbol);

	abb_destruir_todo(arbol, &destructor);

	insertar_quitar();
	probar_recorrer_con_menos();
	insertar_repetidos();

	pa2m_nuevo_grupo("============== ??? ===============");
	prueba_destructor_todo();

	return pa2m_mostrar_reporte();
}

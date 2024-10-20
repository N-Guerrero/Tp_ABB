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
	printf("puntero %p destruido\n", elemento);
}

bool mostrar(void *elemento, void *ctx)
{
	printf(" puntero %p\n", elemento);
	if (elemento == NULL)
		return false;
	return true;
	// return false;
}
bool mostrar_hasta(void *elemento, void *ctx)
{
	int *indice = (int *)ctx;

	if ((*indice) == 5)
		return false;
	//printf("%d\n",*indice);
	(*indice)++;
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
	pa2m_afirmar(cant == 7, "se itero 7 veces(%zu)", cant);
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
	pa2m_afirmar(cant == 7, "se itero 7 veces(%zu)", cant);
}
void pruebaIterarPRE_hasta(abb_t *arbol)
{
	int hasta = 0;
	size_t cant = abb_iterar_preorden(arbol, mostrar_hasta, &hasta);
	pa2m_afirmar(cant == 5, "se itero 5 veces(%zu)", cant);
}
void pruebaIterarPOS(abb_t *arbol)
{
	size_t cant = abb_iterar_postorden(arbol, &mostrar, NULL);
	pa2m_afirmar(cant == 7, "se itero 7 veces(%zu)", cant);
}
void pruebaIterarPOS_hasta(abb_t *arbol)
{
	int hasta = 0;
	size_t cant = abb_iterar_postorden(arbol, mostrar_hasta, &hasta);
	pa2m_afirmar(cant == 5, "se itero 5 veces(%zu)", cant);
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
	pa2m_afirmar(tamanio == 5, "se lleno correctamente el vector(%zu)",tamanio);
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
	pa2m_afirmar(!abb_quitar(arbol, NULL, NULL), "quitar con NULL");
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

int main()
{
	pa2m_nuevo_grupo("============== ??? ===============");
	abb_t *arbol = arbolCreado();
	pruebaInsertar(arbol);
	pruebaCant(arbol);
	// pa2m_nuevo_grupo("============== ??? ===============");
	pruebaIterarIN(arbol);
	 pruebaIterarPOS(arbol);
	 pruebaIterarPRE(arbol);
	pruebaIterarIN_hasta(arbol);
	 pruebaIterarPOS_hasta(arbol);
	 pruebaIterarPRE_hasta(arbol);
	// pa2m_nuevo_grupo("============== ??? ===============");
	 pruebaVectorizarIN(arbol);
	 pruebaVectorizarINmenos(arbol);
	 pruebaVectorizarPRE(arbol);
	 pruebaVectorizarPOS(arbol);
	// pa2m_nuevo_grupo("============== ??? ===============");
	 pruebaObt(arbol);
	pruebaQuitar(arbol);
	// pa2m_nuevo_grupo("============== ??? ===============");
	pruebaCant6(arbol);
	probarNULL(arbol);
	abb_destruir(arbol);
	pruebaCant(arbol);
	printf("\n");
	probar_eliminar_un_solo();
	abb_destruir_todo(arbol, &destructor);

	return pa2m_mostrar_reporte();
}

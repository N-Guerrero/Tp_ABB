#include "pa2m.h"
#include "src/abb.h"
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
	pa2m_afirmar(abb_insertar(arbol, (void *)50), "se inserto %d al arbol",
		     50);
	pa2m_afirmar(abb_insertar(arbol, (void *)19), "se inserto %d al arbol",
		     19);
	pa2m_afirmar(abb_insertar(arbol, (void *)8), "se inserto %d al arbol",
		     8);
	pa2m_afirmar(abb_insertar(arbol, (void *)3), "se inserto %d al arbol",
		     3);
	pa2m_afirmar(abb_insertar(arbol, (void *)46), "se inserto %d al arbol",
		     46);
	pa2m_afirmar(abb_insertar(arbol, (void *)25), "se inserto %d al arbol",
		     25);
	pa2m_afirmar(abb_insertar(arbol, (void *)10), "se inserto %d al arbol",
		     10);
}
void pruebaCant(abb_t *cant)
{
	pa2m_afirmar(abb_cantidad(cant) == 7,
		     "cantidad correcta(%d) en el arbol", 7);
}

void pruebaObt(abb_t *arbol)
{
	pa2m_afirmar(abb_obtener(arbol, (void *)50) != NULL, "se encontro %d ",
		     50);
	pa2m_afirmar(abb_obtener(arbol, (void *)19) != NULL,
		     "se encontro %d al arbol", 19);
	pa2m_afirmar(abb_obtener(arbol, (void *)8) != NULL,
		     "se encontro %d al arbol", 8);
	pa2m_afirmar(abb_obtener(arbol, (void *)3) != NULL,
		     "se encontro %d al arbol", 3);
	pa2m_afirmar(abb_obtener(arbol, (void *)46) != NULL,
		     "se encontro %d al arbol", 46);
	pa2m_afirmar(abb_obtener(arbol, (void *)25) != NULL,
		     "se encontro %d al arbol", 25);
	pa2m_afirmar(abb_obtener(arbol, (void *)10) != NULL,
		     "se encontro %d al arbol", 10);
}

void pruebaQuitar(abb_t *arbol)
{
	abb_insertar(arbol, (void *)40);
	void *encontrado = NULL;
	bool prueba = abb_quitar(arbol, (void *)40, &encontrado);
	pa2m_afirmar(prueba, "se encontro %p", encontrado);
}

void pruebaIterarIN(abb_t *arbol)
{
	size_t cant = abb_iterar_inorden(arbol, &mostrar, NULL);
	pa2m_afirmar(cant == 7, "se itero 7 veces");
}
void pruebaIterarPRE(abb_t *arbol)
{
	size_t cant = abb_iterar_preorden(arbol, &mostrar, NULL);
	pa2m_afirmar(cant == 7, "se itero 7 veces");
}
void pruebaIterarPOS(abb_t *arbol)
{
	size_t cant = abb_iterar_postorden(arbol, &mostrar, NULL);
	pa2m_afirmar(cant == 7, "se itero 7 veces");
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

int main()
{
	pa2m_nuevo_grupo("============== ??? ===============");
	abb_t *arbol = arbolCreado();
	pruebaInsertar(arbol);
	pruebaCant(arbol);
	pa2m_nuevo_grupo("============== ??? ===============");
	pruebaIterarIN(arbol);
	pruebaIterarPOS(arbol);
	pruebaIterarPRE(arbol);
	pa2m_nuevo_grupo("============== ??? ===============");
	pruebaVectorizarIN(arbol);
	pruebaVectorizarPRE(arbol);
	pruebaVectorizarPOS(arbol);
	pa2m_nuevo_grupo("============== ??? ===============");
	pruebaObt(arbol);
	pruebaQuitar(arbol);
	pa2m_nuevo_grupo("============== ??? ===============");
	probarNULL(arbol);
	//abb_destruir(arbol);
	abb_destruir_todo(arbol, &destructor);

	return pa2m_mostrar_reporte();
}

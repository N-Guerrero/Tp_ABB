#include "abb.h"
#include "abb_estructura_privada.h"
#include <stdio.h>
#include <stdint.h>
abb_t *abb_crear(int (*comparador)(void *, void *))
{
	abb_t *Arbol = malloc(sizeof(abb_t));
	if (Arbol == NULL || comparador == NULL) {
		free(Arbol);
		return NULL;
	}
	Arbol->nodos = 0;
	Arbol->raiz = NULL;
	Arbol->comparador = comparador;
	return Arbol;
}

void nodo_destruir_todo(nodo_t *nodo, void (*destructor)(void *))
{
	if (nodo == NULL) {
		return;
	}
	//if (nodo->izq != NULL)
	nodo_destruir_todo(nodo->izq, destructor);
	//if (nodo->der != NULL)
	nodo_destruir_todo(nodo->der, destructor);
	if (destructor != NULL) {
		destructor(nodo->elemento);
	}
	free(nodo);
}
void abb_destruir_todo(abb_t *abb, void (*destructor)(void *))
{
	if (abb == NULL)
		return;

	if (abb->raiz != NULL) {
		nodo_destruir_todo(abb->raiz, destructor);
	}
	destructor(abb->raiz);
	free(abb);
}

void abb_destruir(abb_t *abb)
{
	abb_destruir_todo(abb, NULL);
}

nodo_t *nodo_crear(void *elemento)
{
	nodo_t *nuevo_nodo = calloc(1, sizeof(nodo_t));
	if (nuevo_nodo == NULL)
		return NULL;
	nuevo_nodo->elemento = elemento;
	return nuevo_nodo;
}

nodo_t *nodo_insertar(nodo_t *nodo_actual, nodo_t *nuevo_nodo, abb_t *abb)
{
	if (nuevo_nodo == NULL || abb == NULL)
		return NULL;

	if (nodo_actual == NULL) {
		abb->nodos++;
		return nuevo_nodo;
	}
	int comparador =
		abb->comparador(nuevo_nodo->elemento, nodo_actual->elemento);

	if (comparador <= 0) {
		nodo_actual->izq =
			nodo_insertar(nodo_actual->izq, nuevo_nodo, abb);
	} else
		nodo_actual->der =
			nodo_insertar(nodo_actual->der, nuevo_nodo, abb);

	return nodo_actual;
}

bool abb_insertar(abb_t *abb, void *elemento)
{
	if (abb == NULL)
		return false;

	if (abb->raiz == NULL) {
		abb->raiz = nodo_crear(elemento);
		if (abb->raiz == NULL)
			return false;
		abb->nodos++;
		return true;
	}

	if (nodo_insertar(abb->raiz, nodo_crear(elemento), abb) != NULL)
		return true;
	return false;
}

nodo_t *nodo_buscar(nodo_t *nodo_actual, abb_t *abb, void *elemento)
{
	if (nodo_actual == NULL)
		return NULL;
	int comparador = abb->comparador(elemento, nodo_actual->elemento);

	if (comparador == 0) {
		return nodo_actual;
	} else if (comparador < 0) {
		return nodo_buscar(nodo_actual->izq, abb, elemento);
	} else if (comparador > 0) {
		return nodo_buscar(nodo_actual->der, abb, elemento);
	}
	return NULL;
}

nodo_t *nodo_quitar_rec(nodo_t *nodo_actual, abb_t *abb, void *elemento,
			void **encontrado)
{
	if (nodo_actual == NULL)
		return NULL;
	int comparador = abb->comparador(elemento, nodo_actual->elemento);

	if (comparador == 0) {
		if (encontrado != NULL) {
			*encontrado = nodo_actual->elemento;
		}
		if (nodo_actual->der != NULL && nodo_actual->izq != NULL) {
			nodo_t *pre = nodo_actual->izq;

			while (pre->der != NULL) {
				pre = pre->der;
			}

			nodo_actual->elemento = pre->elemento;
			nodo_actual->izq = nodo_quitar_rec(
				nodo_actual->izq, abb, pre->elemento, NULL);
			return nodo_actual;
		}

		nodo_t *hijo = nodo_actual->izq;
		if (hijo == NULL)
			hijo = nodo_actual->der;

		free(nodo_actual);
		abb->nodos--;
		return hijo;
	}
	if (comparador < 0)
		nodo_actual->izq = nodo_quitar_rec(nodo_actual->izq, abb,
						   elemento, encontrado);

	else
		nodo_actual->der = nodo_quitar_rec(nodo_actual->der, abb,
						   elemento, encontrado);
	return nodo_actual;
}

bool abb_quitar(abb_t *abb, void *buscado, void **encontrado)
{
	if (abb == NULL || abb->raiz == NULL || encontrado == NULL) {
		return false;
	}
	abb->raiz = nodo_quitar_rec(abb->raiz, abb, buscado, encontrado);

	if (*encontrado == NULL)
		return false;
	return true;
}

size_t abb_cantidad(abb_t *abb)
{
	if (abb == NULL)
		return 0;

	return abb->nodos;
}

void *abb_obtener(abb_t *abb, void *elemento)
{
	if (abb == NULL) {
		return NULL;
	}
	nodo_t *nodo_buscado = nodo_buscar(abb->raiz, abb, elemento);
	if (nodo_buscado == NULL)
		return NULL;
	return nodo_buscado->elemento;
}

// size_t nodo_iterar(nodo_t *raiz, abb_t *abb, bool (*f)(void *, void *),
// 		   void *ctx, int orden, bool *cont)
// {
// 	if (raiz == NULL)
// 		return 0;

// 	size_t iteraciones = 0;

// 	if (orden == 0) {
// 		iteraciones += nodo_iterar(raiz->izq, abb, f, ctx, orden, cont);

// 		if ((*cont)){

// 		if (!f(raiz->elemento, ctx)) {
// 			*cont = false;
//             return iteraciones;

// 		}
//         iteraciones++;
//         }
//         if ((*cont)){
// 		iteraciones += nodo_iterar(raiz->der, abb, f, ctx, orden, cont);
//         }
// 	}
// 	if (orden == -1) {
// 		if ((*cont)){

// 		if (!f(raiz->elemento, ctx)) {
// 			return iteraciones;
// 		}
//         iteraciones++;
// }
//         if ((*cont))
// 		iteraciones += nodo_iterar(raiz->izq, abb, f, ctx, orden, cont);
//         if ((*cont))
// 		iteraciones += nodo_iterar(raiz->der, abb, f, ctx, orden, cont);
// 	}
// 	if (orden == 1) {
// 		iteraciones += nodo_iterar(raiz->izq, abb, f, ctx, orden, cont);

// 		iteraciones += nodo_iterar(raiz->der, abb, f, ctx, orden, cont);
// 		if ((*cont)){

// 		if (!f(raiz->elemento, ctx)) {
// 			return iteraciones ;
// 		}
//         iteraciones++;
//         }
// 	}
// 	return iteraciones;
// }
size_t nodo_iterar_inorden(nodo_t *raiz, abb_t *abb, bool (*f)(void *, void *),
			   void *ctx)
{
	if (raiz == NULL) {
		return 0;
	}
	size_t cant = 0;
	cant += nodo_iterar_inorden(raiz->izq, abb, f, ctx);

	if (!f(raiz->elemento, ctx)) {
		return cant;
	}
	cant++;
	cant += nodo_iterar_inorden(raiz->der, abb, f, ctx);
	return cant;
}

size_t nodo_iterar_postorden(nodo_t *raiz, abb_t *abb,
			     bool (*f)(void *, void *), void *ctx)
{
	if (raiz == NULL) {
		return 0;
	}
	size_t cant = 0;
	cant += nodo_iterar_postorden(raiz->izq, abb, f, ctx);

	cant += nodo_iterar_postorden(raiz->der, abb, f, ctx);
	if (!f(raiz->elemento, ctx)) {
		return cant;
	}
	cant++;
	return cant;
}

size_t nodo_iterar_preorden(nodo_t *raiz, abb_t *abb, bool (*f)(void *, void *),
			    void *ctx)
{
	if (raiz == NULL) {
		return 0;
	}
	size_t cant = 0;
	if (!f(raiz->elemento, ctx)) {
		return cant;
	}
	cant++;
	cant += nodo_iterar_preorden(raiz->izq, abb, f, ctx);

	cant += nodo_iterar_preorden(raiz->der, abb, f, ctx);

	return cant;
}
size_t abb_iterar_inorden(abb_t *abb, bool (*f)(void *, void *), void *ctx)
{
	if (abb == NULL || abb->raiz == NULL || f == NULL)
		return 0;
	return nodo_iterar_inorden(abb->raiz, abb, f, ctx);
}
size_t abb_iterar_preorden(abb_t *abb, bool (*f)(void *, void *), void *ctx)
{
	if (abb == NULL || abb->raiz == NULL || f == NULL)
		return 0;
	return nodo_iterar_preorden(abb->raiz, abb, f, ctx);
}
size_t abb_iterar_postorden(abb_t *abb, bool (*f)(void *, void *), void *ctx)
{
	if (abb == NULL || abb->raiz == NULL || f == NULL)
		return 0;
	return nodo_iterar_postorden(abb->raiz, abb, f, ctx);
}
struct vectorizar {
	void **vector;
	size_t pos;
	size_t tamanio;
};
bool llenar_vector(void *elemento, void *ctx)
{
	struct vectorizar *datos = (struct vectorizar *)ctx;
	if (datos->pos >= datos->tamanio)
		return false;

	datos->vector[datos->pos] = elemento;
	datos->pos++;

	return true;
}
size_t abb_vectorizar_inorden(abb_t *abb, void **vector, size_t tamaño)
{
	if (vector == NULL || abb == NULL || abb->raiz == NULL)
		return 0;
	struct vectorizar datos = { .vector = vector,
				    .pos = 0,
				    .tamanio = tamaño };
	return abb_iterar_inorden(abb, llenar_vector, &datos);
}
size_t abb_vectorizar_preorden(abb_t *abb, void **vector, size_t tamaño)
{
	if (vector == NULL || abb == NULL || abb->raiz == NULL)
		return 0;
	struct vectorizar datos = { .vector = vector,
				    .pos = 0,
				    .tamanio = tamaño };
	return abb_iterar_preorden(abb, llenar_vector, &datos);
}
size_t abb_vectorizar_postorden(abb_t *abb, void **vector, size_t tamaño)
{
	if (vector == NULL || abb == NULL || abb->raiz == NULL)
		return 0;
	struct vectorizar datos = { .vector = vector,
				    .pos = 0,
				    .tamanio = tamaño };
	return abb_iterar_postorden(abb, llenar_vector, &datos);
}

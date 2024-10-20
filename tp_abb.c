#include "src/abb.h"
#include "src/csv.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct pokemon {
	char *nombre;
	char tipo;
	int fuerza;
	int destreza;
	int resistencia;
};
bool leer_int(const char *str, void *ctx)
{
	return sscanf(str, "%d", (int *)ctx) == 1;
}

bool leer_caracter(const char *str, void *ctx)
{
	*(char *)ctx = *(char *)str;
	return true;
}
bool crear_string_nuevo(const char *str, void *ctx)
{
	char *nuevo = malloc(strlen(str) + 1);
	if (nuevo == NULL)
		return false;
	strcpy(nuevo, str);
	*(char **)ctx = nuevo;
	return true;
}

int comparar_nombre_pokemon(void *_p1, void *_p2)
{
	struct pokemon *p1 = _p1;
	struct pokemon *p2 = _p2;
	return strcmp(p1->nombre, p2->nombre);
}
void liberar_pokemon(void *pokemon)
{
	struct pokemon *liberado = pokemon;
	if (liberado != NULL) {
		free(liberado->nombre);
		free(liberado);
		liberado = NULL;
	}
}
void agregar_pokemon_desde_archivo(abb_t *pokedex, struct archivo_csv *archivo)
{
	bool (*funciones[5])(const char *, void *) = { crear_string_nuevo,
						       leer_caracter, leer_int,
						       leer_int, leer_int };

	int fuerza;
	int resistencia;
	int destreza;
	char tipo;
	char *nombre = NULL;
	void *punteros[5] = { &nombre, &tipo, &fuerza, &destreza,
			      &resistencia };

	while (leer_linea_csv(archivo, 5, funciones, punteros) == 5) {
		struct pokemon *nuevo_pokemon = malloc(sizeof(struct pokemon));
		nuevo_pokemon->nombre = nombre;
		nuevo_pokemon->fuerza = fuerza;
		nuevo_pokemon->destreza = destreza;
		nuevo_pokemon->tipo = tipo;
		nuevo_pokemon->resistencia = resistencia;

		if (abb_insertar(pokedex, nuevo_pokemon))
			printf("%s capturado\n", nuevo_pokemon->nombre);
	}
	cerrar_archivo_csv(archivo);
}
void mostrar_pokemon(struct pokemon *pokemon)
{
	printf("Nombre: %s\nTipo: %c\nFuerza:%d\nDestreza:%d\nResistencia:%d\n",
	       pokemon->nombre, pokemon->tipo, pokemon->fuerza,
	       pokemon->destreza, pokemon->resistencia);
}
bool listar_pokemon(void *pokemon, void *ctx)
{
	struct pokemon *pokemon_actual = (struct pokemon *)pokemon;
	int *indice = (int *)ctx;
	if (pokemon_actual == NULL) {
		printf("pokemon NULL\n");
		return false;
	}
	printf("%d. %s\n", *indice, pokemon_actual->nombre);
	(*indice)++;
	return true;
}

int main(int argc, char *argv[])
{
	abb_t *abb = abb_crear(&comparar_nombre_pokemon);

	struct archivo_csv *archivo = abrir_archivo_csv(argv[1], ';');

	if (archivo != NULL)
		agregar_pokemon_desde_archivo(abb, archivo);

	int opcion = -1;
	do {
		printf("Pokedex iniciada.\nQue desea hacer?\n");
		printf("1.Buscar pokemon en la pokedex\n2.Listar pokemones capturados\n");
		printf("0.salir\n");
		if (scanf("%d", &opcion) != 1)
			printf("opcion invalida\n");
		if (opcion == 1) {
			printf("que pokemon desea buscar?\n");
			char pokemon_buscado[100];
			int correcto = scanf("%99s", pokemon_buscado);
			if (correcto == 0)
				continue;
			struct pokemon buscado = { .nombre = pokemon_buscado };

			struct pokemon *encontrado = abb_obtener(abb, &buscado);

			if (encontrado != NULL) {
				printf("Se encontro al pokemon buscado!!\n");
				mostrar_pokemon(encontrado);
			} else {
				printf("pokemon no encontrado\n");
			}

			opcion = 0;
		}
		if (opcion == 2) {
			size_t cant_pokemons = abb_cantidad(abb);
			int indice = 1;
			if (abb_iterar_inorden(abb, listar_pokemon, &indice) ==
			    cant_pokemons) {
				printf("Fin de Pokedex\n");
			}
			opcion = 0;
		}
	} while (opcion != 0);

	abb_destruir_todo(abb, liberar_pokemon);

	return 0;
}

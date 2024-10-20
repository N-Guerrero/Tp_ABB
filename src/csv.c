#include "csv.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_LINEA 300
struct archivo_csv {
	FILE *archivo_nombre;
	char separador;
};

struct archivo_csv *abrir_archivo_csv(const char *nombre_archivo,
				      char separador)
{
	struct archivo_csv *pokedex_file = malloc(sizeof(struct archivo_csv));

	pokedex_file->archivo_nombre = fopen(nombre_archivo, "r");

	if (pokedex_file->archivo_nombre == NULL) {
		free(pokedex_file);
		return NULL;
	}
	pokedex_file->separador = separador;
	return pokedex_file;
}

size_t leer_linea_csv(struct archivo_csv *archivo, size_t columnas,
		      bool (*funciones[])(const char *, void *), void *ctx[])
{
	for (size_t i = 0; i < columnas; i++) {
		if (funciones[i] == NULL) {
			columnas = i;
		}
		if (ctx[i] == NULL) {
			// columnas = i;
		}
	}
	if (archivo == NULL)
		return 0;

	char linea[MAX_LINEA];
	size_t col_read = 0;
	if (fgets(linea, 300, archivo->archivo_nombre) != NULL) {
		char *inicio = linea;

		while (col_read < columnas) {
			char *pos_delimiter =
				strchr(inicio, archivo->separador);
			if (pos_delimiter != NULL) {
				size_t longiud_palabra =
					(size_t)pos_delimiter - (size_t)inicio;

				char palabra[longiud_palabra + 1];
				strncpy(palabra, inicio, longiud_palabra);
				palabra[longiud_palabra] = '\0';
				if (funciones == NULL)
					return col_read;
				if (ctx[col_read] != NULL) {
					if (!funciones[col_read](palabra,
								 ctx[col_read]))
						return col_read;
				}
				inicio = pos_delimiter + 1;

				col_read++;
			} else {
				if (funciones == NULL)
					return col_read;
				if (ctx[col_read] != NULL) {
					bool check = funciones[col_read](
						inicio, ctx[col_read]);
					if (check == false)
						return col_read;
				}
				col_read++;
				// printf("read %zu\n",col_read);
			}
		}
	}
	// printf("read %zu\n",col_read);
	return col_read;
}

void cerrar_archivo_csv(struct archivo_csv *archivo)
{
	if (archivo == NULL)
		return;
	if (fclose(archivo->archivo_nombre) == (-1))
		perror("error al cerrar archivo");

	free(archivo);
	archivo = NULL;
}

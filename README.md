<div align="right">
<img width="32px" src="img/algo2.svg">
</div>

# TDA ABB


## Alumno: Nicolas Martin Guerrero - (112514) - guerreronico81@gmail.com

- Para compilar:

```bash
gcc tp_abb.c src/*.c
```

- Para ejecutar:

```bash
./a/out pokedex.csv
```

- Para ejecutar con valgrind:
```bash
valgrind ./a/out pokedex.csv
```

---

##  Funcionamiento

Mi ABB utiliza funciones auxiliares, que son recursivas, para moverse entre los nodos del ABB y poder hacer la tarea necesaria dependiendo de la funcion, ya sea iterar o buscar. En el caso de la funcion de eliminar, cuando se encuentra un nodo con 2 hijos, la busqueda de su predecesor inorden la realizo con un while ya que la posicion del predecesor ya es conocida y cumple con ciertos requisitos, como que no tenga hijos y que sea el nodo mas la derecha de la rama izquierda del nodo a eliminar.

### Por ejemplo:

El programa funciona abriendo el archivo pasado como parámetro y leyendolo línea por línea. Por cada línea crea un registro e intenta agregarlo al vector. La función de lectura intenta leer todo el archivo o hasta encontrar el primer error. Devuelve un vector con todos los registros creados.

<div align="center">
<img width="70%" src="img/diagrama1.svg">
</div>

En el archivo `sarasa.c` la función `funcion1` utiliza `realloc` para agrandar la zona de memoria utilizada para conquistar el mundo. El resultado de `realloc` lo guardo en una variable auxiliar para no perder el puntero original en caso de error:

```c
int *vector = realloc(vector_original, (n+1)*sizeof(int));

if(vector == NULL)
    return -1;
vector_original = vector;
```


<div align="center">
<img width="70%" src="img/diagrama2.svg">
</div>

---

## Respuestas a las preguntas teóricas
Incluír acá las respuestas a las preguntas del enunciado (si aplica).

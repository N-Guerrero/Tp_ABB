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

La estructura de cada nodo del ABB tiene 3 punteros: uno al elemento que guarda y los otros dos apuntan a un hijo cada uno. Esto permite tener un ABB que almacena cualquier tipo de dato, pero es necesario tener una forma de comparar los datos almacenados. Para lograr esta comparación, se requiere una función comparadora que se almacena en la estructura del ABB, que tiene un puntero a esa función comparadora, un puntero al primer nodo del ABB (la raíz) y un `int` que indica la cantidad de nodos que se encuentran en el árbol.

Mi ABB utiliza funciones auxiliares, que son recursivas, para moverse entre los nodos del ABB y realizar la tarea necesaria dependiendo de la función, ya sea iterar o buscar. En el caso de la función de eliminar, cuando se encuentra un nodo con 2 hijos, la búsqueda de su predecesor inorden se realiza con un while, ya que la posición del predecesor ya es conocida y cumple con ciertos requisitos, como que no tenga hijos y que sea el nodo más a la derecha de la rama izquierda del nodo a eliminar.

Por el diseño de los árboles, la recursividad es una herramienta muy útil, especialmente para iterar, por eso usé recursividad en casi todos los casos. La única excepción es la búsqueda del predecesor inorden cuando quiero quitar un nodo con 2 hijos. En este caso, la iteración me permite ignorar las reglas del ABB para moverme; es decir, al iterar en una dirección en concreto, no me interesa comparar el elemento que busco con el actual para elegir una dirección. Esto es algo que hace muy bien la recursividad y es el motivo por el cual la inserción de elementos funciona correctamente.

Las 2 funciones que más problemas causaron fueron las de iterar y vectorizar, no por tener diferentes órdenes, sino por contabilizar correctamente la cantidad de iteraciones realizadas en el caso de iterar. Obtener la cantidad de iteraciones cuando la función pasada como parámetro daba true no era problema alguno; la dificultad está en sumar cuando esta función devolvía false. Cuando F devuelve false, hay que sumar 1 y cortar las recursiones, y la manera de cortar las recursiones que ya se llamaron pero que no sumaron todavía es con un `bool*` que indique cuándo continuar y cuándo no continuar.

En las funciones de vectorizar parecía fácil al inicio, ya que el orden está dado por las funciones de iterar; entonces, solo tenía que hacer una función que vectorice el elemento de un nodo. El problema del que no me percaté al planificar esta función es que la función que vectoriza tenía que cumplir con bool `(*f)(void *, void *)`, por lo que debía tener esta forma:` bool llenar_vector(void *elemento, void *ctx)`. Para pasarle la información necesaria para manejar el vector, esta información debe entrar en un `void*`, y con ese propósito usé un struct. Originalmente pensé en pasar un vector de `void**` que tuviera en la primera posición el vector en donde guardar los elementos, en la segunda posición el tope del vector en donde guardar los elementos y en la tercera en qué posición del vector guardar el elemento. Sin embargo, después de investigar (YouTube y el canal de Discord), encontré que era más fácil si usaba un struct.

```c
struct vectorizar {
	void **vector;
	size_t pos;
	size_t tamanio;
};
```



```c
nodo_t *pre = nodo_actual->izq;

			while (pre->der != NULL) {
				pre = pre->der;
			}

			nodo_actual->elemento = pre->elemento;
			nodo_actual->izq = nodo_quitar_rec(
				nodo_actual->izq, abb, pre->elemento, NULL);

			return nodo_actual;
```

---

## Respuestas a las preguntas teóricas
Incluír acá las respuestas a las preguntas del enunciado (si aplica).

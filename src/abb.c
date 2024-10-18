#include "abb.h"
#include "abb_estructura_privada.h"

abb_t *abb_crear(int (*comparador)(void *, void *)){
    abb_t *Arbol = malloc(sizeof(abb_t));
    if(Arbol==NULL){
        free(Arbol);
        return NULL;
    }
    Arbol->nodos=0;
    Arbol->raiz=NULL;
    Arbol->comparador=comparador;
    return Arbol;
}

void nodo_destruir_todo(nodo_t *nodo,void (*destructor)(void *)){

    if(nodo->izq!= NULL)
        nodo_destruir_todo(nodo->izq,destructor);
    if(nodo->der != NULL)
        nodo_destruir_todo(nodo->der,destructor);
    if(destructor != NULL)
        destructor(nodo->elemento);
    free(nodo);
    
}

void abb_destruir_todo(abb_t *abb, void (*destructor)(void *)){

    if(abb==NULL)
        return;
        
    if(abb->raiz != NULL){
        nodo_destruir_todo(abb->raiz,destructor);
    }
    free(abb);
}

void abb_destruir(abb_t *abb){
    abb_destruir_todo(abb,NULL);
}

nodo_t *nodo_crear(void* elemento){
    nodo_t *nuevo_nodo = calloc(1,sizeof(nodo_t));
    if(nuevo_nodo==NULL)
        return NULL;
    nuevo_nodo->elemento=elemento;
    return nuevo_nodo;
}

nodo_t* nodo_insertar(nodo_t* nodo_actual,nodo_t* nuevo_nodo,abb_t *abb){

    if(nuevo_nodo==NULL || abb==NULL)
        return NULL;
    
    if(nodo_actual==NULL){
        abb->nodos++;
        return nuevo_nodo;
    }
    int comparador =abb->comparador(nuevo_nodo->elemento,nodo_actual->elemento);

    if(comparador <= 0){
        nodo_actual->izq=nodo_insertar(nodo_actual->izq,nuevo_nodo,abb);
    }else
        nodo_actual->der=nodo_insertar(nodo_actual->der,nuevo_nodo,abb);

    return nodo_actual;

}

bool abb_insertar(abb_t *abb, void *elemento){
    if(abb==NULL)
        return false;
    
    
    if(abb->raiz==NULL){
        abb->raiz=nodo_crear(elemento);
        if(abb->raiz ==NULL)
            return false;
        abb->nodos++;
        return true;
    }
    
    if(nodo_insertar(abb->raiz,nodo_crear(elemento),abb)!=NULL)
        return true;
    return false;
}

nodo_t *nodo_buscar(nodo_t *nodo_actual,abb_t *abb,void* elemento){
    if(nodo_actual==NULL)
        return NULL;
    int comparador=abb->comparador(elemento,nodo_actual);

    if(comparador==0){
        return nodo_actual;
    }else if(comparador < 0)
        return nodo_buscar(nodo_actual->izq,abb,elemento);
    
    return nodo_buscar(nodo_actual->der,abb,elemento);

}

nodo_t *nodo_quitar_rec(nodo_t *nodo_actual,abb_t *abb,void* elemento,void** encontrado){
    if(nodo_actual==NULL)
        return NULL;
    int comparador=abb->comparador(elemento,nodo_actual);

    if(comparador==0){

        if(nodo_actual->der !=NULL && nodo_actual->izq!=NULL){
            nodo_t *pre=nodo_actual->izq;
            while(pre->der!=NULL){
                pre=pre->der;
            }
            *encontrado=nodo_actual->elemento;
            nodo_actual->elemento=pre->elemento;
            nodo_actual->izq=nodo_quitar_rec(nodo_actual->izq,abb,pre->elemento,NULL);

        }

        nodo_t *hijo = nodo_actual->izq;
        if(hijo==NULL)
            hijo=nodo_actual->der;
        if(encontrado!=NULL)
            *encontrado=&nodo_actual->elemento;
        free(nodo_actual);
        return hijo;
    }
    if(comparador < 0)
        nodo_actual->izq=nodo_quitar_rec(nodo_actual->izq,abb,elemento,encontrado);
    
    else 
        nodo_actual->der=nodo_quitar_rec(nodo_actual->der,abb,elemento,encontrado);
    return nodo_actual;
}

bool abb_quitar(abb_t *abb, void *buscado, void **encontrado){

    if(abb==NULL || buscado==NULL){
        return NULL;
    }
    nodo_quitar_rec(abb->raiz,abb,buscado,encontrado);

    if(*encontrado ==NULL)
        return false;
    return true;
}

size_t abb_cantidad(abb_t *abb){
    if(abb==NULL)
        return 0;
    return abb->nodos;
}

void *abb_obtener(abb_t *abb, void *elemento){
    nodo_t *nodo_buscado = nodo_buscar(abb->raiz,abb,elemento);
    if(nodo_buscado==NULL)
        return NULL;
    return nodo_buscado->elemento;
}
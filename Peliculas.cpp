#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <float.h>

typedef struct Pelicula {
    char nombre[100];
    int año;
    char genero[50];
    float recaudacion;
} Pelicula;

typedef struct Nodo {
    Pelicula pelicula;
    struct Nodo* izquierda;
    struct Nodo* derecha;
} Nodo;

Nodo* crearNodo(Pelicula pelicula) {
    Nodo* nuevo = (Nodo*)malloc(sizeof(Nodo));
    nuevo->pelicula = pelicula;
    nuevo->izquierda = nuevo->derecha = NULL;
    return nuevo;
}

Nodo* insertar(Nodo* raiz, Pelicula pelicula) {
    if (raiz == NULL) {
        return crearNodo(pelicula);
    }
    
    if (pelicula.año < raiz->pelicula.año) {
        raiz->izquierda = insertar(raiz->izquierda, pelicula);
    } else if (pelicula.año > raiz->pelicula.año) {
        raiz->derecha = insertar(raiz->derecha, pelicula);
    } else {
        
        raiz->izquierda = insertar(raiz->izquierda, pelicula);
    }
    
    return raiz;
}

void inorden(Nodo* raiz) {
    if (raiz != NULL) {
        inorden(raiz->izquierda);
        printf("Nombre: %s, Año: %d, Genero: %s, Recaudacion: %.2f millones\n",
               raiz->pelicula.nombre, raiz->pelicula.año, raiz->pelicula.genero, raiz->pelicula.recaudacion);
        inorden(raiz->derecha);
    }
}

void preorden(Nodo* raiz) {
    if (raiz != NULL) {
        printf("Nombre: %s, Año: %d, Genero: %s, Recaudacion: %.2f millones\n",
               raiz->pelicula.nombre, raiz->pelicula.año, raiz->pelicula.genero, raiz->pelicula.recaudacion);
        preorden(raiz->izquierda);
        preorden(raiz->derecha);
    }
}

void posorden(Nodo* raiz) {
    if (raiz != NULL) {
        posorden(raiz->izquierda);
        posorden(raiz->derecha);
        printf("Nombre: %s, Año: %d, Genero: %s, Recaudacion: %.2f millones\n",
               raiz->pelicula.nombre, raiz->pelicula.año, raiz->pelicula.genero, raiz->pelicula.recaudacion);
    }
}

Nodo* buscarPorNombre(Nodo* raiz, const char* nombre) {
    if (raiz == NULL) return NULL;
    
    if (strcmp(raiz->pelicula.nombre, nombre) == 0) {
        return raiz;
    }
    
    Nodo* encontrado = buscarPorNombre(raiz->izquierda, nombre);
    if (encontrado == NULL) {
        encontrado = buscarPorNombre(raiz->derecha, nombre);
    }
    
    return encontrado;
}

void mostrarPorGenero(Nodo* raiz, const char* genero) {
    if (raiz != NULL) {
        mostrarPorGenero(raiz->izquierda, genero);
        if (strcmp(raiz->pelicula.genero, genero) == 0) {
            printf("Nombre: %s, Año: %d, Recaudacion: %.2f millones\n",
                   raiz->pelicula.nombre, raiz->pelicula.año, raiz->pelicula.recaudacion);
        }
        mostrarPorGenero(raiz->derecha, genero);
    }
}

void encontrarFracasos(Nodo* raiz, Pelicula fracasos[3]) {
    if (raiz == NULL) return;
    
    encontrarFracasos(raiz->izquierda, fracasos);
    
    for (int i = 0; i < 3; i++) {
        if (raiz->pelicula.recaudacion < fracasos[i].recaudacion) {
            
            for (int j = 2; j > i; j--) {
                fracasos[j] = fracasos[j-1];
            }
            fracasos[i] = raiz->pelicula;
            break;
        }
    }
    
    encontrarFracasos(raiz->derecha, fracasos);
}

void liberarArbol(Nodo* raiz) {
    if (raiz != NULL) {
        liberarArbol(raiz->izquierda);
        liberarArbol(raiz->derecha);
        free(raiz);
    }
}

int main() {
    Nodo* raiz = NULL;
    int opcion;
    
   
    do {
        printf("\n--- Menu de Arbol Binario de Peliculas ---\n");
        printf("1. Insertar pelicula\n");
        printf("2. Mostrar recorridos\n");
        printf("3. Buscar pelicula por nombre\n");
        printf("4. Mostrar peliculas por genero\n");
        printf("5. Mostrar los 3 fracasos taquilleros\n");
        printf("0. Salir\n");
        printf("Seleccione una opcion: ");
        scanf("%d", &opcion);
        getchar(); 
        
        switch (opcion) {
            case 1: {
                Pelicula nueva;
                printf("Nombre de la pelicula: ");
                fgets(nueva.nombre, 100, stdin);
                nueva.nombre[strcspn(nueva.nombre, "\n")] = '\0'; 
                
                printf("Año de realizacion: ");
                scanf("%d", &nueva.año);
                getchar();
                
                printf("Genero: ");
                fgets(nueva.genero, 50, stdin);
                nueva.genero[strcspn(nueva.genero, "\n")] = '\0';
                
                printf("Recaudacion (en millones de dolares): ");
                scanf("%f", &nueva.recaudacion);
                getchar();
                
                raiz = insertar(raiz, nueva);
                printf("Pelicula insertada correctamente.\n");
                break;
            }
            case 2: {
                printf("\nRecorrido Inorden:\n");
                inorden(raiz);
                
                printf("\nRecorrido Preorden:\n");
                preorden(raiz);
                
                printf("\nRecorrido Posorden:\n");
                posorden(raiz);
                break;
            }
            case 3: {
                char nombre[100];
                printf("Ingrese el nombre de la pelicula a buscar: ");
                fgets(nombre, 100, stdin);
                nombre[strcspn(nombre, "\n")] = '\0';
                
                Nodo* encontrado = buscarPorNombre(raiz, nombre);
                if (encontrado != NULL) {
                    printf("\nPelicula encontrada:\n");
                    printf("Nombre: %s\n", encontrado->pelicula.nombre);
                    printf("Año: %d\n", encontrado->pelicula.año);
                    printf("Genero: %s\n", encontrado->pelicula.genero);
                    printf("Recaudacion: %.2f millones\n", encontrado->pelicula.recaudacion);
                } else {
                    printf("Pelicula no encontrada.\n");
                }
                break;
            }
            case 4: {
                char genero[50];
                printf("Ingrese el genero a buscar: ");
                fgets(genero, 50, stdin);
                genero[strcspn(genero, "\n")] = '\0';
                
                printf("\nPeliculas del genero %s:\n", genero);
                mostrarPorGenero(raiz, genero);
                break;
            }
            case 5: {
                Pelicula fracasos[3] = {
                    {"", 0, "", FLT_MAX},
                    {"", 0, "", FLT_MAX},
                    {"", 0, "", FLT_MAX}
                };
                
                encontrarFracasos(raiz, fracasos);
                
                printf("\nLos 3 fracasos taquilleros:\n");
                for (int i = 0; i < 3; i++) {
                    if (fracasos[i].recaudacion != FLT_MAX) {
                        printf("%d. %s (Año: %d, Genero: %s) - Recaudacion: %.2f millones\n",
                               i+1, fracasos[i].nombre, fracasos[i].año, fracasos[i].genero, fracasos[i].recaudacion);
                    }
                }
                break;
            }
            case 0:
                printf("Saliendo del programa...\n");
                break;
            default:
                printf("Opcion no valida. Intente de nuevo.\n");
        }
    } while (opcion != 0);
    
    liberarArbol(raiz);
    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definición de la estructura Cliente
typedef struct Cliente {
    int id;
    char nombre[30];
    int edad;
    char genero;
    char motivo[50];
    struct Cliente *siguiente;
} Cliente;

// Estructura para la cola FIFO
typedef struct {
    Cliente *frente;
    Cliente *final;
    int cantidadM;
    int cantidadF;
} Cola;

// Estructura para la pila LIFO
typedef struct NodoPila {
    Cliente cliente;
    struct NodoPila *siguiente;
} NodoPila;

// Función para inicializar la cola
void inicializarCola(Cola *cola) {
    cola->frente = cola->final = NULL;
    cola->cantidadM = cola->cantidadF = 0;
}

// Función para inicializar la pila
NodoPila *inicializarPila() {
    return NULL;
}

// Función para agregar un cliente a la cola
void agregarCliente(Cola *cola, int id, char nombre[], int edad, char genero, char motivo[]) {
    if ((cola->cantidadM - cola->cantidadF > 4 && genero == 'M') ||
        (cola->cantidadF - cola->cantidadM > 4 && genero == 'F')) {
        printf("No se puede agregar, diferencia de género mayor a 4.\n");
        return;
    }

    Cliente *nuevo = (Cliente *)malloc(sizeof(Cliente));
    nuevo->id = id;
    strcpy(nuevo->nombre, nombre);
    nuevo->edad = edad;
    nuevo->genero = genero;
    strcpy(nuevo->motivo, motivo);
    nuevo->siguiente = NULL;

    if (cola->final == NULL) {
        cola->frente = cola->final = nuevo;
    } else {
        cola->final->siguiente = nuevo;
        cola->final = nuevo;
    }

    if (genero == 'M') cola->cantidadM++;
    else cola->cantidadF++;

    printf("Cliente agregado exitosamente.\n");
}

// Función para mostrar los clientes en espera
void mostrarClientes(Cola *cola) {
    Cliente *actual = cola->frente;
    while (actual != NULL) {
        printf("ID: %d, Nombre: %s, Edad: %d, Género: %c, Motivo: %s\n", actual->id, actual->nombre, actual->edad, actual->genero, actual->motivo);
        actual = actual->siguiente;
    }
}

// Función para contar los clientes en espera
int contarClientes(Cola *cola) {
    int contador = 0;
    Cliente *actual = cola->frente;
    while (actual != NULL) {
        contador++;
        actual = actual->siguiente;
    }
    return contador;
}

// Función para atender al siguiente cliente y registrarlo en la pila
void atenderCliente(Cola *cola, NodoPila **pila) {
    if (cola->frente == NULL) {
        printf("No hay clientes en espera.\n");
        return;
    }
    if (cola->frente->edad < 18) {
        printf("No se puede atender a menores de edad.\n");
        return;
    }

    Cliente *atendido = cola->frente;
    cola->frente = atendido->siguiente;
    if (cola->frente == NULL) cola->final = NULL;

    // Registrar en la pila
    NodoPila *nuevoNodo = (NodoPila *)malloc(sizeof(NodoPila));
    nuevoNodo->cliente = *atendido;
    nuevoNodo->siguiente = *pila;
    *pila = nuevoNodo;

    if (atendido->genero == 'M') cola->cantidadM--;
    else cola->cantidadF--;

    printf("Cliente atendido y registrado en el historial.\n");
    free(atendido);
}

// Función para mostrar el historial de atenciones
void mostrarHistorial(NodoPila *pila) {
    NodoPila *actual = pila;
    while (actual != NULL) {
        printf("ID: %d, Nombre: %s, Edad: %d, Género: %c, Motivo: %s\n", actual->cliente.id, actual->cliente.nombre, actual->cliente.edad, actual->cliente.genero, actual->cliente.motivo);
        actual = actual->siguiente;
    }
}

// Función para deshacer la última atención
void deshacerAtencion(Cola *cola, NodoPila **pila) {
    if (*pila == NULL) {
        printf("No hay atenciones para deshacer.\n");
        return;
    }

    NodoPila *ultimo = *pila;
    *pila = ultimo->siguiente;
    agregarCliente(cola, ultimo->cliente.id, ultimo->cliente.nombre, ultimo->cliente.edad, ultimo->cliente.genero, ultimo->cliente.motivo);
    free(ultimo);
    printf("Última atención deshecha y cliente reintegrado a la cola.\n");
}

// Menú del sistema
void menu() {
    Cola cola;
    NodoPila *pila = inicializarPila();
    inicializarCola(&cola);
    int opcion, id, edad;
    char nombre[30], genero, motivo[50];

    do {
        printf("\n1. Agregar cliente a la cola\n");
        printf("2. Mostrar clientes en espera\n");
        printf("3. Contar clientes en espera\n");
        printf("4. Atender siguiente cliente\n");
        printf("5. Mostrar historial de atenciones\n");
        printf("6. Deshacer última atención\n");
        printf("7. Salir\n");
        printf("Seleccione una opción: ");
        scanf("%d", &opcion);
        getchar();

        switch (opcion) {
            case 1:
                printf("Ingrese ID: "); scanf("%d", &id); getchar();
                printf("Ingrese Nombre: "); fgets(nombre, 30, stdin);
                nombre[strcspn(nombre, "\n")] = 0;
                printf("Ingrese Edad: "); scanf("%d", &edad); getchar();
                printf("Ingrese Género (M/F): "); scanf("%c", &genero); getchar();
                printf("Ingrese Motivo: "); fgets(motivo, 50, stdin);
                motivo[strcspn(motivo, "\n")] = 0;
                agregarCliente(&cola, id, nombre, edad, genero, motivo);
                break;
            case 2:
                mostrarClientes(&cola);
                break;
            case 3:
                printf("Clientes en espera: %d\n", contarClientes(&cola));
                break;
            case 4:
                atenderCliente(&cola, &pila);
                break;
            case 5:
                mostrarHistorial(pila);
                break;
            case 6:
                deshacerAtencion(&cola, &pila);
                break;
        }
    } while (opcion != 7);
}

int main() {
    menu();
    return 0;
}

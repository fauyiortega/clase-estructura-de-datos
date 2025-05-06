//Fauyi Andrei Ortega Estrada y Julian Andres Lizalda Aristizabal
#include <iostream>
#include <malloc.h>
#include <cstring> // Para strcmp

using namespace std;

struct nodo {
    int val = 0; // Año de publicación
    char nombre[30];
    char genero[30];
    double recaudado = 0;
    nodo *izq;
    nodo *der;
};

nodo *raiz = NULL, *aux = NULL, *aux2 = NULL;

// Función para posicionar nodo en el árbol
void posicionar() {
    if(aux->val < aux2->val){
        if(aux2->izq != NULL){
            aux2 = aux2->izq;
            posicionar();
        } else {
            aux2->izq = aux;
        }
    }
    else if(aux->val > aux2->val){
        if(aux2->der != NULL){
            aux2 = aux2->der;
            posicionar();
        } else {
            aux2->der = aux;
        }
    }
    else {
        if(aux2->izq != NULL){
            aux2 = aux2->izq;
            posicionar();
        } else {
            aux2->izq = aux;
        }
    }
}

// Registrar nueva película
void registrar() {
    aux = (struct nodo *) malloc(sizeof(struct nodo));
    cout << "Nombre de la película: ";
    cin.ignore();
    cin.getline(aux->nombre, 30);
    cout << "Fecha de publicación: ";
    cin >> aux->val;
    cout << "Género de la película: ";
    cin >> aux->genero;
    cout << "Dinero recaudado (en millones de dólares): ";
    cin >> aux->recaudado;
    aux->izq = aux->der = NULL;

    if(raiz == NULL){
        raiz = aux;
    } else {
        aux2 = raiz;
        posicionar();
    }
}

// Recorridos
void preorden(nodo *r) {
    if (r == NULL) return;
    cout << "Nombre: " << r->nombre 
         << ", Fecha: " << r->val 
         << ", Género: " << r->genero 
         << ", Recaudado: $" << r->recaudado << " millones\n";
    preorden(r->izq);
    preorden(r->der);
}

void inorden(nodo *r) {
    if (r == NULL) return;
    inorden(r->izq);
    cout << "Nombre: " << r->nombre 
         << ", Fecha: " << r->val 
         << ", Género: " << r->genero 
         << ", Recaudado: $" << r->recaudado << " millones\n";
    inorden(r->der);
}

void postorden(nodo *r) {
    if (r == NULL) return;
    postorden(r->izq);
    postorden(r->der);
    cout << "Nombre: " << r->nombre 
         << ", Fecha: " << r->val 
         << ", Género: " << r->genero 
         << ", Recaudado: $" << r->recaudado << " millones\n";
}

// Búsqueda por nombre
void buscarPorNombre(nodo *r, const char buscado[]) {
    if (r == NULL) return;

    if (strcmp(buscado, r->nombre) == 0) {
        cout << "Película encontrada:\n";
        cout << "Nombre: " << r->nombre 
             << ", Fecha: " << r->val 
             << ", Género: " << r->genero 
             << ", Recaudado: $" << r->recaudado << " millones\n";
        return;
    }

    buscarPorNombre(r->izq, buscado);
    buscarPorNombre(r->der, buscado);
}

// Mostrar por género
void mostrarPorGenero(nodo *r, const char generoBuscado[]) {
    if (r == NULL) return;

    if (strcmp(r->genero, generoBuscado) == 0) {
        cout << "Nombre: " << r->nombre 
             << ", Fecha: " << r->val 
             << ", Género: " << r->genero 
             << ", Recaudado: $" << r->recaudado << " millones\n";
    }

    mostrarPorGenero(r->izq, generoBuscado);
    mostrarPorGenero(r->der, generoBuscado);
}

// Mantener los 3 fracasos taquilleros (sin vector ni sort)
void buscarFracasos(nodo* actual, nodo* fracasos[3]) {
    if (actual == NULL) return;

    buscarFracasos(actual->izq, fracasos);
    buscarFracasos(actual->der, fracasos);

    // Insertar si hay lugar vacío
    for (int i = 0; i < 3; ++i) {
        if (fracasos[i] == NULL) {
            fracasos[i] = actual;
            return;
        }
    }

    // Reemplazar si el actual recauda menos que el mayor de los tres
    int maxIndex = 0;
    for (int i = 1; i < 3; ++i) {
        if (fracasos[i]->recaudado > fracasos[maxIndex]->recaudado) {
            maxIndex = i;
        }
    }

    if (actual->recaudado < fracasos[maxIndex]->recaudado) {
        fracasos[maxIndex] = actual;
    }
}

void mostrarFracasosTaquilleros() {
    nodo* fracasos[3] = {NULL, NULL, NULL};
    buscarFracasos(raiz, fracasos);

    cout << "\nTop 3 fracasos taquilleros:\n";
    for (int i = 0; i < 3; ++i) {
        if (fracasos[i]) {
            cout << "Nombre: " << fracasos[i]->nombre
                 << ", Fecha: " << fracasos[i]->val
                 << ", Género: " << fracasos[i]->genero
                 << ", Recaudado: $" << fracasos[i]->recaudado << " millones\n";
        }
    }
}

// Menú principal
int main() {
    int opc = 0;
    do {
        cout << "\nJordan´s Movies:\n";
        cout << "0. Registrar Película\n";
        cout << "1. Mostrar recorrido\n";
        cout << "2. Buscar película por nombre\n";
        cout << "3. Mostrar películas por género\n";
        cout << "4. Mostrar los 3 fracasos taquilleros\n";
        cout << "5. Salir\n";
        cin >> opc;

        switch(opc) {
            case 0: registrar(); break;
            case 1: {
                cout << "Tipo de recorrido:\n1. Preorden\n2. Inorden\n3. Postorden\n";
                int tipo;
                cin >> tipo;
                if (raiz == NULL) {
                    cout << "Todavía no hay peliculas en la cartelera de Jordan´s Movies\n";
                    break;
                }
                if (tipo == 1) preorden(raiz);
                else if (tipo == 2) inorden(raiz);
                else if (tipo == 3) postorden(raiz);
                else cout << "Opción no válida.\n";
                break;
            }
            case 2: {
                if (raiz == NULL) {
                    cout << "Todavía no hay peliculas en la cartelera de Jordan´s Movies\n";
                    break;
                }
                cin.ignore();
                char nombreBuscado[30];
                cout << "Nombre de la película: ";
                cin.getline(nombreBuscado, 30);
                buscarPorNombre(raiz, nombreBuscado);
                break;
            }
            case 3: {
                if (raiz == NULL) {
                    cout << "Todavía no hay peliculas en la cartelera de Jordan´s Movies\n";
                    break;
                }
                cin.ignore();
                char generoBuscado[30];
                cout << "Género a mostrar: ";
                cin.getline(generoBuscado, 30);
                cout << "Películas del género \"" << generoBuscado << "\":\n";
                mostrarPorGenero(raiz, generoBuscado);
                break;
            }
            case 4: {
                if (raiz == NULL) {
                    cout << "Todavía no hay peliculas en la cartelera de Jordan´s Movies\n";
                    break;
                }
                mostrarFracasosTaquilleros();
                break;
            }
            case 5: break;
            default: cout << "Opción no válida.\n"; break;
        }
    } while(opc != 5);
    
    return 0;
}

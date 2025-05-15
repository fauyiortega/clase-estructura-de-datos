//Fauyi Andrei Ortega Estrada y Julián Andrés Lizalda Aristizabal 
#include <iostream>
#include <cstring> // Para strcmp, strcpy

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
    cout << "Nombre de la pelicula: ";
    cin.ignore();
    cin.getline(aux->nombre, 30);
    cout << "Fecha de publicacion: ";
    cin >> aux->val;
    cout << "Genero de la película: ";
    cin >> aux->genero;
    cout << "Dinero recaudado (en millones de dolares): ";
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
         << ", Genero: " << r->genero 
         << ", Recaudado: $" << r->recaudado << " millones\n";
    preorden(r->izq);
    preorden(r->der);
}

void inorden(nodo *r) {
    if (r == NULL) return;
    inorden(r->izq);
    cout << "Nombre: " << r->nombre 
         << ", Fecha: " << r->val 
         << ", Genero: " << r->genero 
         << ", Recaudado: $" << r->recaudado << " millones\n";
    inorden(r->der);
}

void postorden(nodo *r) {
    if (r == NULL) return;
    postorden(r->izq);
    postorden(r->der);
    cout << "Nombre: " << r->nombre 
         << ", Fecha: " << r->val 
         << ", Genero: " << r->genero 
         << ", Recaudado: $" << r->recaudado << " millones\n";
}

// Búsqueda por nombre
void buscarPorNombre(nodo *r, const char buscado[]) {
    if (r == NULL) return;

    if (strcmp(buscado, r->nombre) == 0) {
        cout << "Pelicula encontrada:\n";
        cout << "Nombre: " << r->nombre 
             << ", Fecha: " << r->val 
             << ", Genero: " << r->genero 
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
             << ", Genero: " << r->genero 
             << ", Recaudado: $" << r->recaudado << " millones\n";
    }

    mostrarPorGenero(r->izq, generoBuscado);
    mostrarPorGenero(r->der, generoBuscado);
}

// Top 3 fracasos
void buscarFracasos(nodo* actual, nodo* fracasos[3]) {
    if (actual == NULL) return;

    buscarFracasos(actual->izq, fracasos);
    buscarFracasos(actual->der, fracasos);

    for (int i = 0; i < 3; ++i) {
        if (fracasos[i] == NULL) {
            fracasos[i] = actual;
            return;
        }
    }

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
                 << ", Genero: " << fracasos[i]->genero
                 << ", Recaudado: $" << fracasos[i]->recaudado << " millones\n";
        }
    }
}

// Función para eliminar un nodo por nombre
nodo* eliminarNodo(nodo* r, const char nombre[]) {
    if (r == NULL) return NULL;

    if (strcmp(nombre, r->nombre) < 0) {
        r->izq = eliminarNodo(r->izq, nombre);
    } else if (strcmp(nombre, r->nombre) > 0) {
        r->der = eliminarNodo(r->der, nombre);
    } else {
        // Nodo encontrado
        if (r->izq == NULL && r->der == NULL) {
            free(r);
            return NULL;
        }
        else if (r->izq == NULL) {
            nodo* temp = r->der;
            free(r);
            return temp;
        }
        else if (r->der == NULL) {
            nodo* temp = r->izq;
            free(r);
            return temp;
        }
        else {
            nodo* sucesor = r->der;
            while (sucesor->izq != NULL)
                sucesor = sucesor->izq;

            strcpy(r->nombre, sucesor->nombre);
            strcpy(r->genero, sucesor->genero);
            r->val = sucesor->val;
            r->recaudado = sucesor->recaudado;

            r->der = eliminarNodo(r->der, sucesor->nombre);
        }
    }
    return r;
}

void eliminarPorNombre() {
    if (raiz == NULL) {
        cout << "El arbol esta vacio.\n";
        return;
    }
    char nombreEliminar[30];
    cin.ignore();
    cout << "Nombre de la pelicula a eliminar: ";
    cin.getline(nombreEliminar, 30);
    raiz = eliminarNodo(raiz, nombreEliminar);
    cout << "Pelicula eliminada (si existia).\n";
}

// Menú principal
int main() {
    int opc = 0;
    do {
        cout << "\n\tJordans Movies:\n";
        cout << "0. Registrar Pelicula\n";
        cout << "1. Mostrar recorrido\n";
        cout << "2. Buscar pelicula por nombre\n";
        cout << "3. Mostrar peliculas por genero\n";
        cout << "4. Mostrar los 3 fracasos taquilleros\n";
        cout << "5. Eliminar pelicula por nombre\n";
        cout << "6. Salir: ";
        cin >> opc;

        switch(opc) {
            case 0: registrar(); break;
            case 1: {
                cout << "Tipo de recorrido:\n1. Preorden\n2. Inorden\n3. Postorden\n";
                int tipo;
                cin >> tipo;
                if (raiz == NULL) {
                    cout << "Todavia no hay peliculas en la cartelera de Jordans Movies\n";
                    break;
                }
                if (tipo == 1) preorden(raiz);
                else if (tipo == 2) inorden(raiz);
                else if (tipo == 3) postorden(raiz);
                else cout << "Opcion no valida.\n";
                break;
            }
            case 2: {
                if (raiz == NULL) {
                    cout << "Todavia no hay peliculas en la cartelera de Jordans Movies\n";
                    break;
                }
                cin.ignore();
                char nombreBuscado[30];
                cout << "Nombre de la pelicula: ";
                cin.getline(nombreBuscado, 30);
                buscarPorNombre(raiz, nombreBuscado);
                break;
            }
            case 3: {
                if (raiz == NULL) {
                    cout << "Todavia no hay peliculas en la cartelera de Jordans Movies\n";
                    break;
                }
                cin.ignore();
                char generoBuscado[30];
                cout << "Genero a mostrar: ";
                cin.getline(generoBuscado, 30);
                cout << "Peliculas del genero \"" << generoBuscado << "\":\n";
                mostrarPorGenero(raiz, generoBuscado);
                break;
            }
            case 4: {
                if (raiz == NULL) {
                    cout << "Todavía no hay peliculas en la cartelera de Jordans Movies\n";
                    break;
                }
                mostrarFracasosTaquilleros();
                break;
            }
            case 5:
                eliminarPorNombre();
                break;
            case 6:system("cls"); cout<<"\nchao\n";break;

            default: cout << "Opcion no valida.\n"; break;
        }
    } while(opc != 6);

    return 0;
}

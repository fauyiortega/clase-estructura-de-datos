// Edwin Leonel Baltan 
// Fauyi Andrei Ortega 
// Jeison Castillo

#include <iostream>
#include <cstring>
#include <cstdlib>
using namespace std;

struct nodo {
    int val;
    char nombre[30];
    char genero[30];
    double recaudado;
    nodo *izq;
    nodo *der;
};

nodo *raiz = NULL, *aux = NULL, *aux2 = NULL;

// Crear nuevo nodo
nodo* createNode(int val, const char* nombre, const char* genero, double recaudado) {
    nodo* node = (nodo*)malloc(sizeof(nodo));
    if (node) {
        node->val = val;
        strcpy(node->nombre, nombre);
        strcpy(node->genero, genero);
        node->recaudado = recaudado;
        node->izq = node->der = NULL;
    }
    return node;
}

// Posicionar en el árbol
void posicionar() {
    if (aux->val < aux2->val) {
        if (aux2->izq != NULL) {
            aux2 = aux2->izq;
            posicionar();
        } else {
            aux2->izq = aux;
        }
    } else {
        if (aux2->der != NULL) {
            aux2 = aux2->der;
            posicionar();
        } else {
            aux2->der = aux;
        }
    }
}

// Registrar película
void registrar() {
    aux = (nodo*)malloc(sizeof(nodo));
    cout << "Nombre de la pelicula: ";
    cin.ignore();
    cin.getline(aux->nombre, 30);
    cout << "Fecha de publicacion: ";
    cin >> aux->val;
    cout << "Genero de la pelicula: ";
    cin.ignore();
    cin.getline(aux->genero, 30);
    cout << "Dinero recaudado (en millones): ";
    cin >> aux->recaudado;
    aux->izq = aux->der = NULL;

    if (raiz == NULL) {
        raiz = aux;
    } else {
        aux2 = raiz;
        posicionar();
    }
}

// Recorridos
void preorden(nodo *r) {
    if (r == NULL) return;
    cout << "Nombre: " << r->nombre << ", Fecha: " << r->val << ", Genero: " << r->genero << ", Recaudado: $" << r->recaudado << "M\n";
    preorden(r->izq);
    preorden(r->der);
}

void inorden(nodo *r) {
    if (r == NULL) return;
    inorden(r->izq);
    cout << "Nombre: " << r->nombre << ", Fecha: " << r->val << ", Genero: " << r->genero << ", Recaudado: $" << r->recaudado << "M\n";
    inorden(r->der);
}

void postorden(nodo *r) {
    if (r == NULL) return;
    postorden(r->izq);
    postorden(r->der);
    cout << "Nombre: " << r->nombre << ", Fecha: " << r->val << ", Genero: " << r->genero << ", Recaudado: $" << r->recaudado << "M\n";
}

// Buscar por nombre
void buscarPorNombre(nodo *r, const char buscado[]) {
    if (r == NULL) return;
    if (strcmp(buscado, r->nombre) == 0) {
        cout << "Pelicula encontrada:\n";
        cout << "Nombre: " << r->nombre << ", Fecha: " << r->val << ", Genero: " << r->genero << ", Recaudado: $" << r->recaudado << "M\n";
        return;
    }
    buscarPorNombre(r->izq, buscado);
    buscarPorNombre(r->der, buscado);
}

// Mostrar por género
void mostrarPorGenero(nodo *r, const char generoBuscado[]) {
    if (r == NULL) return;
    if (strcmp(r->genero, generoBuscado) == 0) {
        cout << "Nombre: " << r->nombre << ", Fecha: " << r->val << ", Genero: " << r->genero << ", Recaudado: $" << r->recaudado << "M\n";
    }
    mostrarPorGenero(r->izq, generoBuscado);
    mostrarPorGenero(r->der, generoBuscado);
}

// Top 3 fracasos taquilleros
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
    for (int i = 1; i < 3; ++i)
        if (fracasos[i]->recaudado > fracasos[maxIndex]->recaudado)
            maxIndex = i;

    if (actual->recaudado < fracasos[maxIndex]->recaudado)
        fracasos[maxIndex] = actual;
}

void mostrarFracasosTaquilleros() {
    nodo* fracasos[3] = {NULL, NULL, NULL};
    buscarFracasos(raiz, fracasos);
    cout << "\nTop 3 fracasos taquilleros:\n";
    for (int i = 0; i < 3; ++i)
        if (fracasos[i])
            cout << "Nombre: " << fracasos[i]->nombre << ", Fecha: " << fracasos[i]->val << ", Genero: " << fracasos[i]->genero << ", Recaudado: $" << fracasos[i]->recaudado << "M\n";
}

// Eliminar nodo por nombre
nodo* eliminarNodo(nodo* r, const char nombre[]) {
    if (r == NULL) return NULL;
    if (strcmp(nombre, r->nombre) < 0) {
        r->izq = eliminarNodo(r->izq, nombre);
    } else if (strcmp(nombre, r->nombre) > 0) {
        r->der = eliminarNodo(r->der, nombre);
    } else {
        if (r->izq == NULL && r->der == NULL) {
            free(r);
            return NULL;
        } else if (r->izq == NULL) {
            nodo* temp = r->der;
            free(r);
            return temp;
        } else if (r->der == NULL) {
            nodo* temp = r->izq;
            free(r);
            return temp;
        } else {
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
    cout << "Pelicula eliminada si existia.\n";
}

// Recolección en arreglo (estilo C)
void almacenarEnArreglo(nodo* r, nodo** arreglo, int& index) {
    if (r == NULL) return;
    almacenarEnArreglo(r->izq, arreglo, index);
    arreglo[index++] = r;
    almacenarEnArreglo(r->der, arreglo, index);
}

// Árbol balanceado
nodo* construirBalanceado(nodo** arreglo, int inicio, int fin) {
    if (inicio > fin) return NULL;
    int mid = (inicio + fin) / 2;
    nodo* root = createNode(arreglo[mid]->val, arreglo[mid]->nombre, arreglo[mid]->genero, arreglo[mid]->recaudado);
    root->izq = construirBalanceado(arreglo, inicio, mid - 1);
    root->der = construirBalanceado(arreglo, mid + 1, fin);
    return root;
}

// Liberar memoria
void liberar(nodo* r) {
    if (r == NULL) return;
    liberar(r->izq);
    liberar(r->der);
    free(r);
}

// Rebalancear el árbol sin vector
void rebalancear() {
    if (raiz == NULL) return;

    int total = 100; // Tamaño máximo estimado (puedes ajustarlo)
    nodo** arreglo = (nodo**)malloc(sizeof(nodo*) * total);
    int index = 0;
    almacenarEnArreglo(raiz, arreglo, index);

    liberar(raiz); // Libera la raíz vieja (se reconstruirá)
    raiz = construirBalanceado(arreglo, 0, index - 1);

    free(arreglo);
    cout << "Arbol reestructurado correctamente.\n";
}

// Menú
int main() {
    int opcion;
    do {
        cout << "\n1. Registrar pelicula\n2. Preorden\n3. Inorden\n4. Postorden\n5. Buscar por nombre\n6. Mostrar por genero\n7. Top 3 fracasos\n8. Eliminar pelicula\n9. Rebalancear arbol\n0. Salir\nOpcion: ";
        cin >> opcion;
        switch (opcion) {
            case 1: registrar(); break;
            case 2: preorden(raiz); break;
            case 3: inorden(raiz); break;
            case 4: postorden(raiz); break;
            case 5: {
                char nombre[30];
                cin.ignore();
                cout << "Nombre a buscar: ";
                cin.getline(nombre, 30);
                buscarPorNombre(raiz, nombre);
                break;
            }
            case 6: {
                char genero[30];
                cin.ignore();
                cout << "Genero a buscar: ";
                cin.getline(genero, 30);
                mostrarPorGenero(raiz, genero);
                break;
            }
            case 7: mostrarFracasosTaquilleros(); break;
            case 8: eliminarPorNombre(); break;
            case 9: rebalancear(); break;
            case 0: liberar(raiz); cout << "Adios.\n"; break;
            default: cout << "Opcion invalida.\n";
        }
    } while (opcion != 0);
    return 0;
}

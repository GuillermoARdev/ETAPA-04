#include <iostream>
using namespace std;

// Estructura que representa a un miembro del árbol genealógico
struct Miembro {
    string nombre;
    Miembro* izquierdo;
    Miembro* derecho;

    // Constructor
    Miembro(string nom) {
        nombre = nom;
        izquierdo = NULL;
        derecho = NULL;
    }
};

// Clase que representa el árbol genealógico
class ArbolGenealogico {
private:
    Miembro* raiz;

    // Inserta un nuevo miembro en el árbol (forma recursiva)
    Miembro* insertar(Miembro* nodo, string nombre) {
        if (nodo == NULL) return new Miembro(nombre);

        if (nombre < nodo->nombre)
            nodo->izquierdo = insertar(nodo->izquierdo, nombre);
        else if (nombre > nodo->nombre)
            nodo->derecho = insertar(nodo->derecho, nombre);

        return nodo;
    }

    // Busca un miembro por nombre
    Miembro* buscar(Miembro* nodo, string nombre) {
        if (nodo == NULL || nodo->nombre == nombre)
            return nodo;

        if (nombre < nodo->nombre)
            return buscar(nodo->izquierdo, nombre);
        else
            return buscar(nodo->derecho, nombre);
    }

    // Encuentra el nodo con el valor mínimo (más a la izquierda)
    Miembro* encontrarMin(Miembro* nodo) {
        while (nodo != NULL && nodo->izquierdo != NULL)
            nodo = nodo->izquierdo;
        return nodo;
    }

    // Elimina un miembro del árbol
    Miembro* eliminar(Miembro* nodo, string nombre) {
        if (nodo == NULL) return nodo;

        if (nombre < nodo->nombre)
            nodo->izquierdo = eliminar(nodo->izquierdo, nombre);
        else if (nombre > nodo->nombre)
            nodo->derecho = eliminar(nodo->derecho, nombre);
        else {
            // Caso: sin hijo izquierdo
            if (nodo->izquierdo == NULL) {
                Miembro* temp = nodo->derecho;
                delete nodo;
                return temp;
            }
            // Caso: sin hijo derecho
            else if (nodo->derecho == NULL) {
                Miembro* temp = nodo->izquierdo;
                delete nodo;
                return temp;
            }

            // Caso: dos hijos
            Miembro* temp = encontrarMin(nodo->derecho);
            nodo->nombre = temp->nombre;
            nodo->derecho = eliminar(nodo->derecho, temp->nombre);
        }
        return nodo;
    }

    // Recorrido inorden (izquierda, raíz, derecha)
    void inorden(Miembro* nodo) {
        if (nodo == NULL) return;
        inorden(nodo->izquierdo);
        cout << nodo->nombre << " ";
        inorden(nodo->derecho);
    }

    // Recorrido preorden (raíz, izquierda, derecha)
    void preorden(Miembro* nodo) {
        if (nodo == NULL) return;
        cout << nodo->nombre << " ";
        preorden(nodo->izquierdo);
        preorden(nodo->derecho);
    }

    // Recorrido postorden (izquierda, derecha, raíz)
    void postorden(Miembro* nodo) {
        if (nodo == NULL) return;
        postorden(nodo->izquierdo);
        postorden(nodo->derecho);
        cout << nodo->nombre << " ";
    }

public:
    // Constructor
    ArbolGenealogico() {
        raiz = NULL;
    }

    // Inserta un nombre en el árbol
    void insertar(string nombre) {
        raiz = insertar(raiz, nombre);
    }

    // Devuelve true si el nombre existe
    bool buscar(string nombre) {
        return buscar(raiz, nombre) != NULL;
    }

    // Elimina un miembro por nombre
    void eliminar(string nombre) {
        raiz = eliminar(raiz, nombre);
    }

    // Muestra el árbol en inorden
    void mostrarInorden() {
        cout << "Inorden: ";
        inorden(raiz);
        cout << endl;
    }

    // Muestra el árbol en preorden
    void mostrarPreorden() {
        cout << "Preorden: ";
        preorden(raiz);
        cout << endl;
    }

    // Muestra el árbol en postorden
    void mostrarPostorden() {
        cout << "Postorden: ";
        postorden(raiz);
        cout << endl;
    }
};

// Función principal con menú interactivo
int main() {
    ArbolGenealogico arbol;
    int opcion;
    string nombre;

    do {
        cout << "\n=== MENU DEL ARBOL GENEALOGICO ===\n";
        cout << "1. Insertar miembro\n";
        cout << "2. Buscar miembro\n";
        cout << "3. Eliminar miembro\n";
        cout << "4. Mostrar Inorden\n";
        cout << "5. Mostrar Preorden\n";
        cout << "6. Mostrar Postorden\n";
        cout << "0. Salir\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                cout << "Ingrese el nombre del miembro a insertar: ";
                cin >> nombre;
                arbol.insertar(nombre);
                cout << "Miembro insertado con exito.\n";
                break;
            case 2:
                cout << "Ingrese el nombre a buscar: ";
                cin >> nombre;
                if (arbol.buscar(nombre))
                    cout << nombre << " sí existe en el árbol.\n";
                else
                    cout << nombre << " no se encuentra.\n";
                break;
            case 3:
                cout << "Ingrese el nombre a eliminar: ";
                cin >> nombre;
                arbol.eliminar(nombre);
                cout << "Miembro eliminado (si existía).\n";
                break;
            case 4:
                arbol.mostrarInorden();
                break;
            case 5:
                arbol.mostrarPreorden();
                break;
            case 6:
                arbol.mostrarPostorden();
                break;
            case 0:
                cout << "Saliendo del programa.\n";
                break;
            default:
                cout << "Opción inválida. Intente de nuevo.\n";
        }
    } while (opcion != 0);

    return 0;
}

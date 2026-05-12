#include "../incs/piloto.h"

// ====================== ALGORITMOS DE BUSQUEDA ======================

// busqueda secuencial estandar, no requiere orden previo
int busqueda_secuencial(piloto p[], int tamano, int id_buscado){
    int i;
    for(i=0; i<tamano; i++){
        if(p[i].Id == id_buscado){
            return i;
        }
    }
    return -1;
}

// busqueda binaria por id en version iterativa (requiere arreglo ordenado por Id)
int busqueda_binaria_id(piloto p[], int tamano, int id_buscado){
    int abajo = 0;
    int alto = tamano - 1;
    int mid;
    while(abajo <= alto){
        mid = abajo + (alto - abajo) / 2;
        if(p[mid].Id == id_buscado){
            return mid;
        }
        if(p[mid].Id < id_buscado){
            abajo = mid + 1;
        }
        else{
            alto = mid - 1;
        }
    }
    return -1;
}

int busqueda_binaria_recursiva(piloto p[], int id_buscado, int bajo, int alto) {
    if (bajo > alto) {
        return -1; // Si no se encontro
    }
    
    int mid = bajo + (alto - bajo) / 2;
    
    if (p[mid].Id == id_buscado) return mid;
    
    if (p[mid].Id > id_buscado) {
        return busqueda_binaria_recursiva(p, id_buscado, bajo, mid - 1);
    } else {
        return busqueda_binaria_recursiva(p, id_buscado, mid + 1, alto);
    }
}

int busqueda_interpolacion(piloto p[], int tamano, int id_buscado) {
    int bajo = 0, alto = tamano - 1;

    while (bajo <= alto && id_buscado >= p[bajo].Id && id_buscado <= p[alto].Id) {
        if (bajo == alto) {
            if (p[bajo].Id == id_buscado) return bajo;
            return -1;
        }

        // aplicacion de la formula
        int pos = bajo + (((double)(alto - bajo) / (p[alto].Id - p[bajo].Id)) * (id_buscado - p[bajo].Id));

        if (p[pos].Id == id_buscado) return pos;
        if (p[pos].Id < id_buscado) bajo = pos + 1;
        else alto = pos - 1;
    }
    return -1;
}

int busqueda_exponencial(piloto p[], int tamano, int id_buscado) {
    if (p[0].Id == id_buscado) return 0;

    int i = 1;
    while (i < tamano && p[i].Id <= id_buscado) {
        i = i * 2;
    }

    // Llama a la funcion recursiva para el rango encontrado
    // Usamos fmin para no pasarnos del tamaño del arreglo
    return busqueda_binaria_recursiva(p, id_buscado, i / 2, fmin(i, tamano - 1));
}

void busqueda_rango_puntaje(piloto p[], int tamano, float puntaje_buscado) {
    int bajo = 0, alto = tamano - 1;
    int encontrado = -1;

    // busqueda binaria normal
    while (bajo <= alto) {
        int mid = bajo + (alto - bajo) / 2;
        if (p[mid].Puntaje == puntaje_buscado) {
            encontrado = mid;
            break;
        } else if (p[mid].Puntaje < puntaje_buscado) {
            bajo = mid + 1;
        } else {
            alto = mid - 1;
        }
    }

    if (encontrado == -1) {
        printf("No se encontro a nadie con %.2f puntos.\n", puntaje_buscado);
        return;
    }

    // luego se expande hacia la izquierda para buscar el inicio del rango
    int primera_pos = encontrado;
    while (primera_pos > 0 && p[primera_pos - 1].Puntaje == puntaje_buscado) {
        primera_pos--;
    }

    // se expande hacia la derecha para buscar el final del rango
    int ultima_pos = encontrado;
    while (ultima_pos < tamano - 1 && p[ultima_pos + 1].Puntaje == puntaje_buscado) {
        ultima_pos++;
    }

    printf("El puntaje %.2f aparece desde la posicion %d hasta la %d.\n", puntaje_buscado, primera_pos, ultima_pos);
    
    // imprimir los deportistas en ese rango
    for(int i = primera_pos; i <= ultima_pos; i++){
        printf("- %s (Equipo: %s)\n", p[i].Nombre, p[i].Equipo);
    }
}
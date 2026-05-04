#include <stdio.h>
#include "../incs/p.h"

// generador independiente: crea el CSV con los datos aleatorios
// se compila por separado con make run-db

int main(){
    srand(time(NULL));

    int tamano;
    printf("Cuantos deportistas generar: ");
    scanf("%d", &tamano);

    piloto* mi_lista = crear_lista(tamano);
    fisher_yates(mi_lista, tamano);
    guardar_en_csv(mi_lista, tamano, "db/a.csv");

    free(mi_lista);
    return 0;
}
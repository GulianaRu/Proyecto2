#include <stdio.h>
#include "../incs/p.h"

int main(){
    srand(time(NULL));
    int opcion;
    int tamano = 0;
    piloto* p = NULL;

    do {
        printf("\n===== MENU =====\n");
        printf("1. Generar datos\n");
        printf("2. Ordenar\n");
        printf("3. Buscar por ID\n");
        printf("4. Ranking top N\n");
        printf("5. Benchmark algoritmos\n");
        printf("6. Salir\n");
        printf("Opcion: ");
        scanf("%d", &opcion);

        switch(opcion){
            case 1: {
                printf("Cuantos deportistas generar: ");
                scanf("%d", &tamano);
                if(p != NULL) free(p);
                p = crear_lista(tamano);
                fisher_yates(p, tamano);
                guardar_en_csv(p, tamano, "db/a.csv");
                break;
            }
            case 2: {
                if(p == NULL){
                    printf("Primero genera los datos (opcion 1)\n");
                    break;
                }
                int campo, algoritmo;
                printf("Ordenar por:\n");
                printf("1. ID\n2. Nombre\n3. Equipo\n4. Puntaje\n5. Competencias\n");
                printf("Campo: ");
                scanf("%d", &campo);
                printf("Algoritmo:\n");
                printf("1. Bubble sort\n2. Insertion sort\n3. Selection sort\n4. Cocktail shaker\n");
                printf("Algoritmo: ");
                scanf("%d", &algoritmo);
                switch(algoritmo){
                    case 1: buble_sort(p, tamano, campo); break;
                    case 2: insertion_sort(p, tamano, campo); break;
                    case 3: selection_sort(p, tamano, campo); break;
                    case 4: cocktail_shaker_sort(p, tamano, campo); break;
                    default: printf("Algoritmo invalido\n");
                }
                printf("Ordenado correctamente\n");
                break;
            }
            case 3: {
                if(p == NULL){
                    printf("Primero genera los datos (opcion 1)\n");
                    break;
                }
                int id;
                printf("ID a buscar: ");
                scanf("%d", &id);

                // ordenamos por id antes de buscar binariamente
                buble_sort(p, tamano, 1);
                int resultado = busqueda_binaria_id(p, tamano, id);

                if(resultado == -1){
                    printf("No encontrado\n");
                } else {
                    printf("ID: %d | Nombre: %s | Equipo: %s | Puntaje: %.2f | Competencias: %d\n",
                        p[resultado].Id,
                        p[resultado].Nombre,
                        p[resultado].Equipo,
                        p[resultado].Puntaje,
                        p[resultado].Competencias);
                }
                break;
            }
            case 4: {
                if(p == NULL){
                    printf("Primero genera los datos (opcion 1)\n");
                    break;
                }
                int n;
                printf("Cuantos deportistas mostrar: ");
                scanf("%d", &n);
                if(n > tamano) n = tamano;
                buble_sort(p, tamano, 4);
                printf("\n=== TOP %d ===\n", n);
                for(int i = tamano - 1; i >= tamano - n; i--){
                    printf("%d. %s | Puntaje: %.2f\n",
                        tamano - i, p[i].Nombre, p[i].Puntaje);
                }
                break;
            }
            case 5: {
                // tamanios de prueba para el benchmark
                int tamanios[] = {1000, 5000, 10000, 50000, 100000};
                int n_tamanios = 5;
                benchmark_sorts(tamanios, n_tamanios);
                benchmark_busquedas(tamanios, n_tamanios);
                break;
            }
            case 6:
                printf("Saliendo...\n");
                break;
            default:
                printf("Opcion invalida\n");
        }
    } while(opcion != 6);

    if(p != NULL) free(p);
    return 0;
}
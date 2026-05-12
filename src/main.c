#include <stdio.h>
#include "../incs/piloto.h"

int main(){
    srand(time(NULL));
    int opcion;
    int tamano = 0;
    piloto* p = NULL;

    do {
        printf("\n===== MENU =====\n");
        printf("1. Generar datos\n");
        printf("2. Ordenar\n");
        printf("3. Busquedas\n");
        printf("4. Ranking top N\n");
        printf("5. Benchmark algoritmos\n");
        printf("6. quick select\n");
        printf("7. Salir\n");
        printf("Opcion: ");
        // Verificamos si scanf no pudo leer 1 numero
        if (scanf("%d", &opcion) != 1) {
            while (getchar() != '\n'); // Limpia la letra trabada
            opcion = -1; // Forzamos una opcion invalida para que el switch no haga nada raro
        }
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
                int algoritmo;
                printf("Algoritmo:\n");
                printf("5. Merge sort\n6. Quick sort\n");
                printf("Algoritmo: ");
                scanf("%d", &algoritmo);
                switch(algoritmo){
                    case 5: merge(p, tamano, 4); break;
                    case 6: quick_sort(p, tamano, 4); break;
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
                
                int tipo_busqueda;
                printf("\n--- MENU DE BUSQUEDAS ---\n");
                printf("1. Busqueda Secuencial (Iterativa Tarea 1)\n");
                printf("2. Busqueda Binaria Recursiva\n");
                printf("3. Busqueda por Interpolacion\n");
                printf("4. Busqueda Exponencial\n");
                printf("5. Busqueda de Rangos (Por Puntaje)\n");
                printf("Opcion: ");
                scanf("%d", &tipo_busqueda);

                // si no es secuencial ni rangos, asumimos que busca por ID y necesita estar ordenado
                if (tipo_busqueda >= 1 && tipo_busqueda <= 4) {
                    int id;
                    printf("Ingrese el ID a buscar: ");
                    if (scanf("%d", &id) != 1) {
                        while (getchar() != '\n');
                        id = -1; // o algun manejo de error
                        printf("Entrada invalida. Debe ser un numero.\n");
                        continue; // Salta al inicio del menu
                    }
                    
                    int resultado = -1;

                    // la busqueda secuencial no necesita orden, pero las otras si.
                    // para evitar errores, ordenamos por ID siempre que no sea secuencial.
                    if (tipo_busqueda != 1) {
                         // ordenamos por id antes de buscar binariamente
                         buble_sort(p, tamano, 1);
                    }

                    switch(tipo_busqueda) {
                        case 1:
                            // La secuencial
                            resultado = busqueda_secuencial(p, tamano, id);
                            break;
                        case 2:
                            // La nueva recursiva
                            resultado = busqueda_binaria_recursiva(p, id, 0, tamano - 1);
                            break;
                        case 3:
                            // Interpolacion
                            resultado = busqueda_interpolacion(p, tamano, id);
                            break;
                        case 4:
                            // Exponencial
                            resultado = busqueda_exponencial(p, tamano, id);
                            break;
                    }

                    if(resultado == -1){
                        printf("\nNo se encontro a ningun deportista con el ID %d.\n", id);
                    } else {
                        printf("\n[DEPORTISTA ENCONTRADO]\n");
                        printf("ID: %d | Nombre: %s | Equipo: %s | Puntaje: %.2f | Competencias: %d\n",
                            p[resultado].Id, p[resultado].Nombre, p[resultado].Equipo, p[resultado].Puntaje, p[resultado].Competencias);
                    }
                } 
                else if (tipo_busqueda == 5) {
                    float puntaje;
                    printf("Ingrese el Puntaje a buscar (ej. 85.50): ");
                    scanf("%f", &puntaje);
                    
                    // ordenamos por puntaje
                    buble_sort(p, tamano, 4); 
                    busqueda_rango_puntaje(p, tamano, puntaje);
                }
                else {
                    printf("Opcion de busqueda invalida.\n");
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
                merge_optimizado_recursivo(p, 0, tamano - 1, 4, 10);
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
            case 6: {
                if(p == NULL){
                    printf("Primero genera los datos (opcion 1)\n");
                    break;
                }
                int espacio, aux;
                printf("buscar por id\n");
                printf("espacio: ");
                scanf("%d", &espacio);
                printf("Algoritmo:quick select\n");
                aux = quick_select(p, 0, tamano - 1 , espacio, 1);
                
                printf("ID: %d | Nombre: %s | Equipo: %s | Puntaje: %.2f | Competencias: %d | en el espacio %d \n",
                        p[aux].Id,
                        p[aux].Nombre,
                        p[aux].Equipo,
                        p[aux].Puntaje,
                        p[aux].Competencias,
                        aux
                    );
                break;
            }
            case 7:
                printf("Saliendo...\n");
                break;
            default:
                printf("Algoritmo invalido\n");
                break;
        }
    } while(opcion != 7);

    if(p != NULL) free(p);
    return 0;
}
// el ifnef define y endif https://www.reddit.com/r/C_Programming/comments/sbp0k4/if_i_define_my_structs_in_the_h_file_what_do_i/

#ifndef piloto_H
#define piloto_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

typedef struct 
{
    int Id;
    char Nombre[10];
    char Equipo[15];
    float Puntaje;
    int Competencias;
} piloto;

int comparar(piloto a, piloto b, int campo);
piloto inicializar_piloto(int registro, piloto a);
piloto* crear_lista(int tamano);
void buble_sort(piloto p[], int tamano, int campo);
void insertion_sort(piloto p[], int tamano, int campo);
void selection_sort(piloto p[], int tamano, int campo);
void cocktail_shaker_sort(piloto p[], int tamano, int campo);
void fisher_yates(piloto p[], int tamano);
int busqueda_secuencial(piloto p[], int tamano, int id_buscado);
int busqueda_binaria_id(piloto p[], int tamano, int id_buscado);
void guardar_en_csv(piloto lista[], int tamano, const char* nombre_archivo);
piloto* leer_csv(const char* nombre_archivo, int tamano_esperado);
void benchmark_sorts(int tamanios[], int n_tamanios);
void benchmark_busquedas(int tamanios[], int n_tamanios);

// ====================== COMPARADOR POR CAMPO ======================
// compara dos pilotos segun el campo indicado:
// 1=Id, 2=Nombre, 3=Equipo, 4=Puntaje, 5=Competencias
// retorna negativo si a < b, 0 si iguales, positivo si a > b
int comparar(piloto a, piloto b, int campo){
    switch(campo){
        case 1: return a.Id - b.Id;
        case 2: return strcmp(a.Nombre, b.Nombre);
        case 3: return strcmp(a.Equipo, b.Equipo);
        case 4: return (a.Puntaje > b.Puntaje) - (a.Puntaje < b.Puntaje);
        case 5: return a.Competencias - b.Competencias;
        default: return 0;
    }
}

// ====================== INICIALIZAR PILOTO ======================
// informacion de escoger nombre al azar sacada de https://www.forosdelweb.com/f96/seleccionar-elemento-aleatorio-array-con-c-912843/

piloto inicializar_piloto(int registro, piloto a){
    a.Id = registro;
    int i;

    // generamos nombre solo con letras A-Z (antes incluia caracteres especiales como [, \, ])
    for(i = 0; i < 9; i++){
        // rand() % 26 da un numero entre 0 y 25, + 65 da A-Z
        a.Nombre[i] = (rand() % 26) + 65;
    }
    a.Nombre[9] = '\0';

    const char *equipos[] = {"Red Bull", "Monster", "Castrol", "Shell", "Mobil 1", "Pirelli", "Michelin", "Goodyear", "Bridgestone", "Ferrari", "Lamborghini", "Porsche", 
        "McLaren", "Aston Martin", "Bugatti", "Pagani", "Koenigsegg", "BMW", "Audi", "Mercedes-Benz", "Honda", "Toyota", "Nissan", "Subaru", "Mazda", "Ford", "Chevrolet", 
        "Dodge", "Jeep", "Hyundai", "Kia", "Peugeot", "Renault", "Citroën", "Volkswagen", "Volvo", "Jaguar", "Land Rover", "Alfa Romeo", "Maserati", "Lotus", "Sauber", 
        "Haas", "Williams", "Oracle", "Petronas", "Aramco", "Texaco", "Bosch", "Brembo"};

    int indice = rand() % 50;
    strcpy(a.Equipo, equipos[indice]);

    // puntaje entre 0.0 y 10000.0
    a.Puntaje = (float)(rand() % 1000000) / 100.0f;
    // competencias entre 1 y 200
    a.Competencias = (rand() % 200) + 1;
    return a;
}

piloto* crear_lista(int tamano){
    int i;
    piloto* carrera = (piloto*)malloc(tamano * sizeof(piloto));
    for(i=0; i<tamano; i++){
        carrera[i] = inicializar_piloto(i, carrera[i]);
    }
    return carrera;
}

// ====================== ALGORITMOS DE ORDENAMIENTO ======================
// los algoritmos de busqueda y ordenamientos fueron inspirados de https://www.geeksforgeeks.org/
// todos reciben el campo a ordenar: 1=Id, 2=Nombre, 3=Equipo, 4=Puntaje, 5=Competencias

// bubble sort con optimizacion para detectar arreglos ya ordenados
void buble_sort(piloto p[], int tamano, int campo){
    piloto paux;
    int i;
    int j;
    int swap;
    for(i=0; i<tamano-1; i++){
        swap = 0;
        for(j=0; j<tamano-1-i; j++){
            if(comparar(p[j], p[j+1], campo) > 0){
                paux = p[j];
                p[j] = p[j+1];
                p[j+1] = paux;
                swap = 1;
            }
        }
        if(swap == 0){
            break;
        }
    }
}

// insertion sort estandar
void insertion_sort(piloto p[], int tamano, int campo){
    piloto key;
    int i;
    int j;
    for(i=1; i<tamano; i++){
        key = p[i];
        j = i - 1;
        while(j >= 0 && comparar(p[j], key, campo) > 0){
            p[j+1] = p[j];
            j--;
        }
        p[j+1] = key;
    }
}

// selection sort con optimizacion para evitar intercambios innecesarios
void selection_sort(piloto p[], int tamano, int campo){
    piloto paux;
    int min_index;
    int i;
    int j;
    for(i=0; i<tamano-1; i++){
        min_index = i;
        for(j = i + 1; j < tamano; j++){
            if(comparar(p[j], p[min_index], campo) < 0){
                min_index = j;
            }
        }
        // optimizacion: solo intercambia si el minimo no esta en su lugar
        if(min_index != i){       
            paux = p[i];          
            p[i] = p[min_index];
            p[min_index] = paux;
        }
    }
}

// cocktail_shaker_sort fue basado en un ejemplo dado por grok ia
void cocktail_shaker_sort(piloto p[], int tamano, int campo){
    piloto paux;
    int i;
    int izq = 0;
    int der = tamano - 1;
    int swap;
    do {
        swap = 0;
        for(i=izq; i<der; i++){
            if(comparar(p[i], p[i+1], campo) > 0){
                paux = p[i];
                p[i] = p[i+1];
                p[i+1] = paux;
                swap = 1;
            }
        }
        der--;
        for(i=der; i>izq; i--){
            if(comparar(p[i], p[i-1], campo) < 0){
                paux = p[i];
                p[i] = p[i-1];
                p[i-1] = paux;
                swap = 1;
            }
        }
        izq++;
    } while(swap && izq < der);
}

// ====================== MEZCLAR ======================
void fisher_yates(piloto p[], int tamano){
    int i, j;
    piloto paux;
    for(i = tamano - 1; i > 0; i--){
        j = rand() % (i + 1);
        paux = p[i];
        p[i] = p[j];
        p[j] = paux;
    }
}

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

// ====================== CSV ======================
// el guardar csv y el leer csv fueron hechos por grok

void guardar_en_csv(piloto lista[], int tamano, const char* nombre_archivo){
    FILE *archivo = fopen(nombre_archivo, "w");
    if(archivo == NULL){
        printf("Error: No se pudo abrir %s para escritura\n", nombre_archivo);
        return;
    }

    // encabezado del CSV
    fprintf(archivo, "Id,Nombre,Equipo,Puntaje,Competencias\n");

    // escribir cada piloto en una linea
    for(int i = 0; i < tamano; i++){
        fprintf(archivo, "%d,%s,%s,%.2f,%d\n",
                lista[i].Id,
                lista[i].Nombre,
                lista[i].Equipo,
                lista[i].Puntaje,
                lista[i].Competencias);
    }

    fclose(archivo);
    printf("Datos guardados correctamente en %s (%d pilotos)\n", nombre_archivo, tamano);
}

piloto* leer_csv(const char* nombre_archivo, int tamano_esperado){
    FILE* archivo = fopen(nombre_archivo, "r");
    if(archivo == NULL){
        printf("Error: No se pudo abrir %s\n", nombre_archivo);
        return NULL;
    }

    char linea[256];

    // saltar encabezado de forma segura (evita la advertencia de gcc)
    if(fgets(linea, sizeof(linea), archivo) == NULL){
        printf("El archivo esta vacio o no tiene encabezado\n");
        fclose(archivo);
        return NULL;
    }

    // reservamos exactamente la memoria que necesitamos
    piloto* lista = (piloto*)malloc(tamano_esperado * sizeof(piloto));
    if(lista == NULL){
        printf("Error: No se pudo reservar memoria\n");
        fclose(archivo);
        return NULL;
    }

    int tamano = 0;
    while(fgets(linea, sizeof(linea), archivo) && tamano < tamano_esperado){
        int id, competencias;
        char nombre[20], equipo[15];
        float puntaje;

        if(sscanf(linea, "%d,%19[^,],%14[^,],%f,%d",
                   &id, nombre, equipo, &puntaje, &competencias) == 5){
            lista[tamano].Id           = id;
            strcpy(lista[tamano].Nombre, nombre);
            strcpy(lista[tamano].Equipo, equipo);
            lista[tamano].Puntaje      = puntaje;
            lista[tamano].Competencias = competencias;
            tamano++;
        }
    }

    fclose(archivo);
    printf("Cargados %d pilotos desde %s (esperados: %d)\n", tamano, nombre_archivo, tamano_esperado);
    return lista;
}

// ====================== MEDICION DE TIEMPOS ======================
// usamos clock() para medir tiempo de CPU en segundos
// se crea una copia del arreglo para no alterar el original en cada medicion

// tipo de funcion de ordenamiento que acepta campo
typedef void (*func_sort)(piloto[], int, int);

double medir_tiempo_sort(func_sort fn, piloto p[], int tamano, int campo){
    // creamos copia para no modificar el arreglo original
    piloto* copia = (piloto*)malloc(tamano * sizeof(piloto));
    memcpy(copia, p, tamano * sizeof(piloto));

    clock_t inicio = clock();
    fn(copia, tamano, campo);
    clock_t fin = clock();

    free(copia);
    return (double)(fin - inicio) / CLOCKS_PER_SEC;
}

// tipo de funcion de busqueda
typedef int (*func_busqueda)(piloto[], int, int);

double medir_tiempo_busqueda(func_busqueda fn, piloto p[], int tamano, int id){
    clock_t inicio = clock();
    fn(p, tamano, id);
    clock_t fin = clock();
    return (double)(fin - inicio) / CLOCKS_PER_SEC;
}

// corre el benchmark completo y guarda resultados en CSV
// tamanios[] es el arreglo de tamanios a probar, n_tamanios es cuantos hay
void benchmark_sorts(int tamanios[], int n_tamanios){
    int t;
    printf("\n=== BENCHMARK ORDENAMIENTO ===\n");
    printf("%-12s %-15s %-15s %-15s %-15s\n", "Tamano", "Bubble", "Insertion", "Selection", "Cocktail");

    // guardar en CSV para graficos
    FILE* f = fopen("docs/benchmark_sorts.csv", "w");
    if(f != NULL){
        fprintf(f, "Tamano,Bubble,Insertion,Selection,Cocktail\n");
    }

    for(t=0; t<n_tamanios; t++){
        int tam = tamanios[t];
        piloto* lista = crear_lista(tam);
        fisher_yates(lista, tam);

        // ordenar por puntaje (campo 4) en todos
        double tb = medir_tiempo_sort(buble_sort,            lista, tam, 4);
        double ti = medir_tiempo_sort(insertion_sort,        lista, tam, 4);
        double ts = medir_tiempo_sort(selection_sort,        lista, tam, 4);
        double tc = medir_tiempo_sort(cocktail_shaker_sort,  lista, tam, 4);

        printf("%-12d %-15.6f %-15.6f %-15.6f %-15.6f\n", tam, tb, ti, ts, tc);

        if(f != NULL){
            fprintf(f, "%d,%.6f,%.6f,%.6f,%.6f\n", tam, tb, ti, ts, tc);
        }

        free(lista);
    }

    if(f != NULL){
        fclose(f);
        printf("Resultados guardados en docs/benchmark_sorts.csv\n");
    }
}

void benchmark_busquedas(int tamanios[], int n_tamanios){
    int t;
    printf("\n=== BENCHMARK BUSQUEDA ===\n");
    printf("%-12s %-20s %-20s\n", "Tamano", "Secuencial(peor)", "Binaria(peor)");

    FILE* f = fopen("docs/benchmark_busquedas.csv", "w");
    if(f != NULL){
        fprintf(f, "Tamano,Secuencial,Binaria\n");
    }

    for(t=0; t<n_tamanios; t++){
        int tam = tamanios[t];
        piloto* lista = crear_lista(tam);

        // peor caso secuencial: buscar un id que no existe (-1)
        double ts = medir_tiempo_busqueda(busqueda_secuencial, lista, tam, -1);

        // para binaria primero ordenamos por id (requisito)
        buble_sort(lista, tam, 1);
        // peor caso binaria: buscar un id que no existe (-1)
        double tb = medir_tiempo_busqueda(busqueda_binaria_id, lista, tam, -1);

        printf("%-12d %-20.6f %-20.6f\n", tam, ts, tb);

        if(f != NULL){
            fprintf(f, "%d,%.6f,%.6f\n", tam, ts, tb);
        }

        free(lista);
    }

    if(f != NULL){
        fclose(f);
        printf("Resultados guardados en docs/benchmark_busquedas.csv\n");
    }
}

#endif
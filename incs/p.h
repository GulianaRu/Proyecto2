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
int partition(piloto p[], int izq, int der, int campo);
int quick_select(piloto p[], int izq, int der, int k, int campo);
void insertion_sort(piloto p[], int tamano, int campo);
void selection_sort(piloto p[], int tamano, int campo);
void cocktail_shaker_sort(piloto p[], int tamano, int campo);
void fisher_yates(piloto p[], int tamano);
int busqueda_secuencial(piloto p[], int tamano, int id_buscado);
int busqueda_binaria_id(piloto p[], int tamano, int id_buscado);
int busqueda_binaria_recursiva(piloto p[], int id_buscado, int bajo, int alto);
int busqueda_interpolacion(piloto p[], int tamano, int id_buscado);
int busqueda_exponencial(piloto p[], int tamano, int id_buscado);
void busqueda_rango_puntaje(piloto p[], int tamano, float puntaje_buscado);
void guardar_en_csv(piloto lista[], int tamano, const char* nombre_archivo);
piloto* leer_csv(const char* nombre_archivo, int tamano_esperado);
void benchmark_sorts(int tamanios[], int n_tamanios);
void benchmark_busquedas(int tamanios[], int n_tamanios);
double medir_tiempo_qs(piloto p[], int izq, int der, int id, int campo);
void merge(piloto p[], int tamano, int campo);
void quick_sort(piloto p[], int tamano, int campo);
void merge_benchmark(piloto p[], int tamano, int campo);
void merge_optimizado_benchmark(piloto p[], int tamano, int campo);
void quick_ultimo_benchmark(piloto p[], int tamano, int campo);
void quick_mediana_benchmark(piloto p[], int tamano, int campo);
void mezclar(piloto p[], int izq, int medio, int der, int campo);
void merge_recursivo(piloto p[], int izq, int der, int campo);
void merge_optimizado_recursivo(piloto p[], int izq, int der, int campo, int umbral);
void insertion_sort_rango(piloto p[], int izq, int der, int campo);
void swap_piloto(piloto *a, piloto *b);
int seleccionar_pivote(piloto p[], int izq, int der, int campo, int tipo_pivote);
int partition_quick_sort(piloto p[], int izq, int der, int campo, int tipo_pivote);
void quick_sort_recursivo(piloto p[], int izq, int der, int campo, int tipo_pivote);

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
// los algoritmos de busqueda , ordenamientos y quick select fueron inspirados de https://www.geeksforgeeks.org/
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

// quick select con optimizacion para detectar arreglos ya ordenados
int partition(piloto p[], int izq, int der, int campo){
    piloto paux;
    piloto par = p[der];
    int i = (izq - 1);
    int j;
    for (j = izq; j <= der; j++){
        if(comparar(p[j], par, campo) < 0){
            i++;
            paux = p[j];
            p[j] = p[i];
            p[i] = paux;
        }
    }
    paux = p[i+1];
    p[i+1] = p[der];
    p[der] = paux;
    return (i + 1);
}

int quick_select(piloto p[], int izq, int der, int k, int campo){
    int pivote = partition(p,izq,der,campo);
    if(pivote == k - 1){
        return pivote;
    }
    else if(pivote > k - 1){
        return quick_select(p,izq,pivote-1,k,campo);
    }
    else{
        return quick_select(p,pivote+1,der,k,campo);
    }
    return -1;
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

// MERGE SORT - Mezcla 2 mitades ya ordenadas
void mezclar(piloto p[], int izq, int medio, int der, int campo){
    int n1 = medio - izq + 1;
    int n2 = der - medio;

    piloto *izquierda = (piloto*)malloc(n1 * sizeof(piloto));
    piloto *derecha = (piloto*)malloc(n2 * sizeof(piloto));

    if(izquierda == NULL || derecha == NULL){
        printf("Error al reservar memoria en merge sort\n");
        free(izquierda);
        free(derecha);
        return;
    }

    for(int i = 0; i < n1; i++){
        izquierda[i] = p[izq + i];
    }

    for(int j = 0; j < n2; j++){
        derecha[j] = p[medio + 1 + j];
    }

    int i = 0;
    int j = 0;
    int k = izq;

    while(i < n1 && j < n2){
        if(comparar(izquierda[i], derecha[j], campo) <= 0){
            p[k] = izquierda[i];
            i++;
        }
        else{
            p[k] = derecha[j];
            j++;
        }
        k++;
    }

    while(i < n1){
        p[k] = izquierda[i];
        i++;
        k++;
    }

    while(j < n2){
        p[k] = derecha[j];
        j++;
        k++;
    }

    free(izquierda);
    free(derecha);
}

// merge sort clasico recursivo
void merge_recursivo(piloto p[], int izq, int der, int campo){
    if(izq < der){
        int medio = izq + (der - izq) / 2;

        merge_recursivo(p, izq, medio, campo);
        merge_recursivo(p, medio + 1, der, campo);

        mezclar(p, izq, medio, der, campo);
    }
}

// insertion sort aplicado solo a un rango del arreglo
// se usa para el merge sort optimizado
void insertion_sort_rango(piloto p[], int izq, int der, int campo){
    piloto key;
    int i;
    int j;

    for(i = izq + 1; i <= der; i++){
        key = p[i];
        j = i - 1;

        while(j >= izq && comparar(p[j], key, campo) > 0){
            p[j + 1] = p[j];
            j--;
        }

        p[j + 1] = key;
    }
}

// merge sort optimizado con insertion sort para arreglos pequenos
void merge_optimizado_recursivo(piloto p[], int izq, int der, int campo, int umbral){
    if(izq >= der){
        return;
    }

    if((der - izq + 1) <= umbral){
        insertion_sort_rango(p, izq, der, campo);
        return;
    }

    int medio = izq + (der - izq) / 2;

    merge_optimizado_recursivo(p, izq, medio, campo, umbral);
    merge_optimizado_recursivo(p, medio + 1, der, campo, umbral);

    mezclar(p, izq, medio, der, campo);
}

// funcion principal que llama el main
void merge(piloto p[], int tamano, int campo){
    int opcion;
    int umbral;

    printf("\nTipo de Merge Sort:\n");
    printf("1. Clasico\n");
    printf("2. Optimizado con Insertion Sort\n");
    printf("Opcion: ");
    scanf("%d", &opcion);

    if(opcion == 1){
        merge_recursivo(p, 0, tamano - 1, campo);
    }
    else if(opcion == 2){
        printf("Ingrese umbral para usar Insertion Sort, por ejemplo 10, 20 o 30: ");
        scanf("%d", &umbral);

        if(umbral <= 0){
            umbral = 20;
        }

        merge_optimizado_recursivo(p, 0, tamano - 1, campo, umbral);
    }
    else{
        printf("Opcion invalida\n");
    }
}

// QUICK SORT
// intercambia dos pilotos
void swap_piloto(piloto *a, piloto *b){
    piloto aux = *a;
    *a = *b;
    *b = aux;
}

// seleccion del pivote:
// 1 = ultimo elemento
// 2 = primer elemento
// 3 = aleatorio
// 4 = mediana de tres
int seleccionar_pivote(piloto p[], int izq, int der, int campo, int tipo_pivote){
    if(tipo_pivote == 1){
        return der;
    }
    else if(tipo_pivote == 2){
        return izq;
    }
    else if(tipo_pivote == 3){
        return izq + rand() % (der - izq + 1);
    }
    else if(tipo_pivote == 4){
        int medio = izq + (der - izq) / 2;

        piloto a = p[izq];
        piloto b = p[medio];
        piloto c = p[der];

        if((comparar(a, b, campo) <= 0 && comparar(b, c, campo) <= 0) ||
           (comparar(c, b, campo) <= 0 && comparar(b, a, campo) <= 0)){
            return medio;
        }

        if((comparar(b, a, campo) <= 0 && comparar(a, c, campo) <= 0) ||
           (comparar(c, a, campo) <= 0 && comparar(a, b, campo) <= 0)){
            return izq;
        }

        return der;
    }

    return der;
}

// particion de Lomuto para quick sort
int partition_quick_sort(piloto p[], int izq, int der, int campo, int tipo_pivote){
    int indice_pivote = seleccionar_pivote(p, izq, der, campo, tipo_pivote);

    // Lomuto trabaja con el pivote al final, por eso se mueve el pivote elegido a der
    swap_piloto(&p[indice_pivote], &p[der]);

    piloto pivote = p[der];
    int i = izq - 1;

    for(int j = izq; j <= der - 1; j++){
        if(comparar(p[j], pivote, campo) <= 0){
            i++;
            swap_piloto(&p[i], &p[j]);
        }
    }

    swap_piloto(&p[i + 1], &p[der]);
    return i + 1;
}

// quick sort recursivo
void quick_sort_recursivo(piloto p[], int izq, int der, int campo, int tipo_pivote){
    if(izq < der){
        int pivote = partition_quick_sort(p, izq, der, campo, tipo_pivote);

        quick_sort_recursivo(p, izq, pivote - 1, campo, tipo_pivote);
        quick_sort_recursivo(p, pivote + 1, der, campo, tipo_pivote);
    }
}

// funcion principal que llama el main
void quick_sort(piloto p[], int tamano, int campo){
    int tipo_pivote;

    printf("\nTipo de pivote para Quick Sort:\n");
    printf("1. Ultimo elemento\n");
    printf("2. Primer elemento\n");
    printf("3. Elemento aleatorio\n");
    printf("4. Mediana de tres\n");
    printf("Opcion: ");
    scanf("%d", &tipo_pivote);

    if(tipo_pivote >= 1 && tipo_pivote <= 4){
        quick_sort_recursivo(p, 0, tamano - 1, campo, tipo_pivote);
    }
    else{
        printf("Tipo de pivote invalido\n");
    }
}

void merge_benchmark(piloto p[], int tamano, int campo){
    merge_recursivo(p, 0, tamano - 1, campo);
}

void merge_optimizado_benchmark(piloto p[], int tamano, int campo){
    int umbral = 20;
    merge_optimizado_recursivo(p, 0, tamano - 1, campo, umbral);
}

void quick_ultimo_benchmark(piloto p[], int tamano, int campo){
    quick_sort_recursivo(p, 0, tamano - 1, campo, 1);
}

void quick_mediana_benchmark(piloto p[], int tamano, int campo){
    quick_sort_recursivo(p, 0, tamano - 1, campo, 4);
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
    // en esta busqueda se implementara la busqueda de rango por puntaje
    // ya que si se hace por id, como estos son unicos no habran repetidos

    // busqueda binaria normal, como la busqueda binaria era por id
    // se implemento nuevamente en un while
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

double medir_tiempo_qs(piloto p[], int izq, int der, int id, int campo){
    clock_t inicio = clock();
    quick_select(p, izq, der, id, campo);
    clock_t fin = clock();
    return (double)(fin - inicio) / CLOCKS_PER_SEC;
}

// corre el benchmark completo y guarda resultados en CSV
// tamanios[] es el arreglo de tamanios a probar, n_tamanios es cuantos hay
void benchmark_sorts(int tamanios[], int n_tamanios){
    int t;
    printf("\n=== BENCHMARK ORDENAMIENTO ===\n");
    printf("%-12s %-12s %-12s %-12s %-12s %-12s %-12s %-12s %-12s\n",
       "Tamano", "Bubble", "Insertion", "Selection", "Cocktail",
       "Merge", "MergeOpt", "QuickUlt", "QuickMed");

    // guardar en CSV para graficos
    FILE* f = fopen("docs/benchmark_sorts.csv", "w");
    if(f != NULL){
        fprintf(f, "Tamano,Bubble,Insertion,Selection,Cocktail,Merge,MergeOpt,QuickUlt,QuickMed\n");
    }

    for(t=0; t<n_tamanios; t++){
        int tam = tamanios[t];
        piloto* lista = crear_lista(tam);
        fisher_yates(lista, tam);

        // ordenar por puntaje (campo 4) en todos
        double tb = medir_tiempo_sort(buble_sort,                   lista, tam, 4);
        double ti = medir_tiempo_sort(insertion_sort,               lista, tam, 4);
        double ts = medir_tiempo_sort(selection_sort,               lista, tam, 4);
        double tc = medir_tiempo_sort(cocktail_shaker_sort,         lista, tam, 4);

        double tm = medir_tiempo_sort(merge_benchmark,              lista, tam, 4);
        double tmo = medir_tiempo_sort(merge_optimizado_benchmark,  lista, tam, 4);
        double tq1 = medir_tiempo_sort(quick_ultimo_benchmark,      lista, tam, 4);
        double tq4 = medir_tiempo_sort(quick_mediana_benchmark,     lista, tam, 4);

        printf("%-12d %-12.6f %-12.6f %-12.6f %-12.6f %-12.6f %-12.6f %-12.6f %-12.6f\n",
            tam, tb, ti, ts, tc, tm, tmo, tq1, tq4);

        if(f != NULL){
            fprintf(f, "%d,%.6f,%.6f,%.6f,%.6f,%.6f,%.6f,%.6f,%.6f\n",
                tam, tb, ti, ts, tc, tm, tmo, tq1, tq4);
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
    printf("%-12s %-20s %-20s %-20s\n", "Tamano", "Secuencial(peor)", "Binaria(peor)", "QuickSelect(k)");

    FILE* f = fopen("docs/benchmark_busquedas.csv", "w");
    if(f != NULL){
        fprintf(f, "Tamano,Secuencial(peor),Binaria(peor),QuickSelect(k)\n");
    }

    for(t=0; t<n_tamanios; t++){
        int tam = tamanios[t];
        piloto* lista = crear_lista(tam);

        // peor caso secuencial: buscar un id que no existe (-1)
        double ts = medir_tiempo_busqueda(busqueda_secuencial, lista, tam, -1);

        buble_sort(lista, tam, 1);

        // qiqck sort peor caso
        double qs = medir_tiempo_qs(lista, 0, tam -1, (tam/2), 1);

        // peor caso binaria: buscar un id que no existe (-1)
        double tb = medir_tiempo_busqueda(busqueda_binaria_id, lista, tam, -1);

        printf("%-12d %-20.6f %-20.6f %-20.6f\n", tam, ts, tb, qs);

        if(f != NULL){
            fprintf(f, "%d,%.6f,%.6f,%.6f\n", tam, ts, tb,qs);
        }

        free(lista);
    }

    if(f != NULL){
        fclose(f);
        printf("Resultados guardados en docs/benchmark_busquedas.csv\n");
    }
}

#endif
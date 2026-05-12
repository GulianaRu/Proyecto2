#include "../incs/piloto.h"

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

// Funciones wrapper (envoltorios) para que los nuevos algoritmos encajen en el puntero a funcion
void merge_benchmark(piloto p[], int tamano, int campo){
    // luego Enlazar con las funciones reales de merge luego
    buble_sort(p, tamano, campo); // temporal para que no explote
}

void merge_optimizado_benchmark(piloto p[], int tamano, int campo){
    buble_sort(p, tamano, campo); // temporal para que no explote
}

void quick_ultimo_benchmark(piloto p[], int tamano, int campo){
    buble_sort(p, tamano, campo); // temporal para que no explote
}

void quick_mediana_benchmark(piloto p[], int tamano, int campo){
    buble_sort(p, tamano, campo); // temporal para que no explote
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

        // ATENCION ROL 3: Conecta aca las firmas verdaderas cuando esten listas
        double tm = 0.0; // medir_tiempo_sort(merge_benchmark,              lista, tam, 4);
        double tmo = 0.0; // medir_tiempo_sort(merge_optimizado_benchmark,  lista, tam, 4);
        double tq1 = 0.0; // medir_tiempo_sort(quick_ultimo_benchmark,      lista, tam, 4);
        double tq4 = 0.0; // medir_tiempo_sort(quick_mediana_benchmark,     lista, tam, 4);

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
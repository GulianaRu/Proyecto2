#include "../incs/piloto.h"

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
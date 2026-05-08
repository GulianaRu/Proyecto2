# grafico comparativo de algoritmos de ordenamiento
# lee desde docs/benchmark_sorts.csv y guarda en plots/comparatives/

set datafile separator ","
set terminal pngcairo size 900,600 enhanced font "Arial,12"
set output "plots/comparatives/sorts_comparativo.png"

set title "Comparacion de algoritmos de ordenamiento"
set xlabel "Tamano del arreglo (n)"
set ylabel "Tiempo (segundos)"
set grid
set key top left
set style data linespoints

# saltar la primera fila (encabezado)
set key autotitle columnheader

plot "docs/benchmark_sorts.csv" using 1:2 title "Bubble Sort" lw 2, \
     "docs/benchmark_sorts.csv" using 1:3 title "Insertion Sort" lw 2, \
     "docs/benchmark_sorts.csv" using 1:4 title "Selection Sort" lw 2, \
     "docs/benchmark_sorts.csv" using 1:5 title "Cocktail Shaker" lw 2, \
     "docs/benchmark_sorts.csv" using 1:6 title "Merge Sort" lw 2, \
     "docs/benchmark_sorts.csv" using 1:7 title "Merge Sort Optimizado" lw 2, \
     "docs/benchmark_sorts.csv" using 1:8 title "Quick Sort Ultimo Pivote" lw 2, \
     "docs/benchmark_sorts.csv" using 1:9 title "Quick Sort Mediana de Tres" lw 2

# grafico comparativo de Merge Sort y Quick Sort
set output "plots/comparatives/comp_merge_quick.png"
set title "Comparacion de Merge Sort y Quick Sort"
set xlabel "Tamano del arreglo (n)"
set ylabel "Tiempo (segundos)"
set grid
set key top left
set style data linespoints

plot "docs/benchmark_sorts.csv" using 1:6 title "Merge Sort" lw 2, \
     "docs/benchmark_sorts.csv" using 1:7 title "Merge Sort Optimizado" lw 2, \
     "docs/benchmark_sorts.csv" using 1:8 title "Quick Sort Ultimo Pivote" lw 2, \
     "docs/benchmark_sorts.csv" using 1:9 title "Quick Sort Mediana de Tres" lw 2

# grafico individual bubble sort
set output "plots/bubblesort/bubble_sort.png"
set title "Bubble Sort - tiempo de ejecucion"
plot "docs/benchmark_sorts.csv" using 1:2 title "Bubble Sort" lw 2 lc rgb "red"

# grafico individual insertion sort
set output "plots/insertionsort/insertion_sort.png"
set title "Insertion Sort - tiempo de ejecucion"
plot "docs/benchmark_sorts.csv" using 1:3 title "Insertion Sort" lw 2 lc rgb "blue"

# grafico individual selection sort
set output "plots/selectionsort/selection_sort.png"
set title "Selection Sort - tiempo de ejecucion"
plot "docs/benchmark_sorts.csv" using 1:4 title "Selection Sort" lw 2 lc rgb "green"

# grafico individual Cocktail shaker sort
set output "plots/cocktail_shaker_sort/Cocktail_shaker_sort.png"
set title "Cocktail Shaker Sort - tiempo de ejecucion"
plot "docs/benchmark_sorts.csv" using 1:5 title "Cocktail Shaker Sort" lw 2 lc rgb "orange"

# grafico individual Merge Sort
set output "plots/comparatives/merge_sort.png"
set title "Merge Sort - tiempo de ejecucion"
plot "docs/benchmark_sorts.csv" using 1:6 title "Merge Sort" lw 2

# grafico individual Merge Sort Optimizado
set output "plots/comparatives/merge_sort_optimizado.png"
set title "Merge Sort Optimizado - tiempo de ejecucion"
plot "docs/benchmark_sorts.csv" using 1:7 title "Merge Sort Optimizado" lw 2

# grafico individual Quick Sort Ultimo Pivote
set output "plots/comparatives/quick_sort_ultimo.png"
set title "Quick Sort Ultimo Pivote - tiempo de ejecucion"
plot "docs/benchmark_sorts.csv" using 1:8 title "Quick Sort Ultimo Pivote" lw 2

# grafico individual Quick Sort Mediana de Tres
set output "plots/comparatives/quick_sort_mediana_tres.png"
set title "Quick Sort Mediana de Tres - tiempo de ejecucion"
plot "docs/benchmark_sorts.csv" using 1:9 title "Quick Sort Mediana de Tres" lw 2
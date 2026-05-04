# grafico comparativo de algoritmos de ordenamiento
# lee desde docs/benchmark_sorts.csv y guarda en plots/comparatives/

set datafile separator ","
set terminal pngcairo size 900,600 enhanced font "Arial,12"
set output "plots/comparatives/sorts_comparativo.png"

set title "Comparacion algoritmos de ordenamiento"
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
     "docs/benchmark_sorts.csv" using 1:5 title "Cocktail Shaker" lw 2

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
set title "Cocktail shaker Sort - tiempo de ejecucion"
plot "docs/benchmark_sorts.csv" using 1:5 title "Cocktail shaker Sort" lw 2 lc rgb "orange"

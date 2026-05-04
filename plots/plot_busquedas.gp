# grafico comparativo de algoritmos de busqueda
# lee desde docs/benchmark_busquedas.csv y guarda en plots/

set datafile separator ","
set terminal pngcairo size 900,600 enhanced font "Arial,12"
set output "plots/comparatives/busquedas_comparativo.png"

set title "Comparacion algoritmos de busqueda (peor caso)"
set xlabel "Tamano del arreglo (n)"
set ylabel "Tiempo (segundos)"
set grid
set key top left
set style data linespoints

set key autotitle columnheader

plot "docs/benchmark_busquedas.csv" using 1:2 title "Busqueda Secuencial" lw 2 lc rgb "red", \
     "docs/benchmark_busquedas.csv" using 1:3 title "Busqueda Binaria" lw 2 lc rgb "blue"

# grafico individual busqueda secuencial
set output "plots/sequentialsearch/busqueda_secuencial.png"
set title "Busqueda Secuencial - tiempo de ejecucion"
plot "docs/benchmark_busquedas.csv" using 1:2 title "Secuencial" lw 2 lc rgb "red"

# grafico individual busqueda binaria
set output "plots/binarysearch/busqueda_binaria.png"
set title "Busqueda Binaria - tiempo de ejecucion"
plot "docs/benchmark_busquedas.csv" using 1:3 title "Binaria" lw 2 lc rgb "blue"

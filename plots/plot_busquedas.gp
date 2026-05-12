# grafico comparativo de algoritmos de busqueda
# lee desde docs/benchmark_busquedas.csv y guarda en plots/

set datafile separator ","
set terminal pngcairo size 900,600 enhanced font "Arial,12"
set output "plots/comparatives/busquedas_comparativo.png"

set title "Comparacion de algoritmos de busqueda (peor caso)"
set xlabel "Tamano del arreglo (n)"
set ylabel "Tiempo (segundos)"
set grid
set key top left
set style data linespoints

set key autotitle columnheader

plot "docs/benchmark_busquedas.csv" using 1:2 title "Busqueda Secuencial" lw 2 lc rgb "red", \
     "docs/benchmark_busquedas.csv" using 1:3 title "Busqueda Binaria" lw 2 lc rgb "blue", \
     "docs/benchmark_busquedas.csv" using 1:4 title "Busqueda Binaria Optimisada" lw 2 lc rgb "green", \
     "docs/benchmark_busquedas.csv" using 1:5 title "QuickSelect(k)" lw 2 lc rgb "purple", \
     "docs/benchmark_busquedas.csv" using 1:6 title "Busqueda Exponencial" lw 2 lc rgb "brown", \
     "docs/benchmark_busquedas.csv" using 1:7 title "Busqueda interpolacion" lw 2 lc rgb "yellow", \

# grafico individual busqueda secuencial
set output "plots/sequentialsearch/busqueda_secuencial.png"
set title "Busqueda Secuencial - tiempo de ejecucion"
plot "docs/benchmark_busquedas.csv" using 1:2 title "Secuencial" lw 2 lc rgb "red"

# grafico individual busqueda binaria
set output "plots/binarysearch/busqueda_binaria.png"
set title "Busqueda Binaria - tiempo de ejecucion"
plot "docs/benchmark_busquedas.csv" using 1:3 title "Binaria" lw 2 lc rgb "blue"

# grafico individual Busqueda Binaria Optimisada
set output "plots/binarysearch/binaria_optimisada.png"
set title "Busqueda Binaria Optimisada - tiempo de ejecucion"
plot "docs/benchmark_busquedas.csv" using 1:4 title "Busqueda Binaria Optimisada" lw 2 lc rgb "green"

# grafico individual QuickSelect(k)
set output "plots/quickselect/quickselect.png"
set title "QuickSelect(k) - tiempo de ejecucion"
plot "docs/benchmark_busquedas.csv" using 1:5 title "QuickSelect" lw 2 lc rgb "purple"

# grafico individual Busqueda Exponencial
set output "plots/exponencial/busqueda_exponencial.png"
set title "Busqueda Exponencial - tiempo de ejecucion"
plot "docs/benchmark_busquedas.csv" using 1:6 title "Exponencial" lw 2 lc rgb "brown"

# grafico individual Busqueda interpolacion
set output "plots/interpolacion/busqueda_interpolacion.png"
set title "Busqueda interpolacion - tiempo de ejecucion"
plot "docs/benchmark_busquedas.csv" using 1:7 title "interpolacion" lw 2 lc rgb "yellow"

set terminal post enhanced colour solid font 25  
set encoding iso_8859_2

# ZALOZENIE: w pliku lambda.dat znajduja sie dane w formie dwoch kolumn oddzielonych spacja lub tabulatorem:
#       numer_iteracji aktualna_lambda
# Po zmianie k (numeru wartosci wlasnej) w pliku powinny znajdowac sie dwie puste linie.

l_width = 1
p_size = 1.5
set style line 1 lt rgb "red" lw l_width pt 7 ps p_size
set style line 2 lt rgb "black" lw l_width pt 7 ps p_size
set style line 3 lt rgb "dark-spring-green" lw l_width pt 7 ps p_size
set style line 4 lt rgb "goldenrod" lw l_width*2 pt 7 ps p_size*1.2
set style line 5 lt rgb "turquoise" lw l_width pt 7 ps p_size
set style line 6 lt rgb "royalblue" lw l_width pt 7 ps p_size
set style line 7 lt rgb "brown" lw l_width pt 7 ps p_size

set output "lambda.eps"
set key out center top horizontal
set xlabel "Numer iteracji"
set ylabel "{/Symbol l}_k"
set xrange [1:]
set yrange [:0.6]
set multiplot
plot for [i=0:6] "lambda.dat" i i u 1:2 w lp ls (i+1) t "{/Symbol l}_".i.""

set origin 0.09, 0.45
set size 0.6, 0.4
unset key
unset xlabel 
unset ylabel
unset yrange 
set xtics font ", 20" offset 0, 0.5
set ytics 0.002 font ", 20" offset 0.5, 0
plot "lambda.dat" i 0 u 1:2 w lp ls 1 t "{/Symbol l}_0"

unset multiplot



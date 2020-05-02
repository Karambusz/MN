set terminal post enhanced colour solid font 21 
set encoding iso_8859_2

set key spacing 2 samplen 3 center bottom
set xlabel "x" 
set ylabel "g(x)"
set grid
x0 = 2.
sigma = 4.
x_min = -3.*sigma + x0
x_max = 3.*sigma + x0
g(x) = exp(-(x-x0)**2/(2.*sigma**2))
l_width = 5
p_size = 1.3
set xtics -10,4

set style line 1 lt rgb "gray30" lw 6 pt 7 ps p_size*1.15
set style line 2 lt rgb "red" lw l_width pt 7 ps p_size
set style line 3 lt rgb "royalblue" lw l_width*2.4 pt 7 ps p_size*1.2

# Skrypt zaklada, ze w plikach znajduja sie trzy serie danych,
# oddzielone dwiema pustymi liniami:
# - pkt.dat: dwie kolumny z polozeniami wezlow i wartosciami funkcji: x_j, g_j
# - G.dat: dwie kolumny z wynikiem aproksymacji: x, G(x)

# 1. APROKSYMACJA: N = 11, alpha = 0
set output "app1.eps"
plot [x_min:x_max] g(x) ls 3 t "g(x)",\
 "G.dat" i 0 w l ls 2 t "G(x); N=11, {/Symbol a} = 0.0",\
 "pkt.dat" i 0 ls 1 t "g(x_i)"

# 2. APROKSYMACJA: N = 11, alpha = 0.5
set output "app2.eps"
plot [x_min:x_max] "pkt.dat" i 1 ls 1 t "g(x_i)",\
 "G.dat" i 1 w l ls 2 t "G(x); N=11, {/Symbol a} = 0.5"

# 3. APROKSYMACJA: N = 101, alpha = 0.5
set output "app3.eps"
plot [x_min:x_max] "pkt.dat" i 2 ls 1 t "g(x_i)",\
 "G.dat" i 2 w l ls 2 t "G(x); N=101, {/Symbol a} = 0.5"

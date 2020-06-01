set terminal post enhanced colour solid font 25  

set style line 1 lt rgb "red" lw 5 pt 7 ps 1.3
set grid
set xlabel "x_{20}"
set ylabel "|^{(V_{dok}-V_n)}/_{V_{dok}}|"

# W PLIKU out.dat ZAPISANO 7 SERII DANYCH:
# 		- 1. seria danych: wyniki dla n = 5 w dwoch kolumnach:  x20  epsilon
# 			(poniewaz rysujemy epsilon == blad wzgledny w funkcji parametru x20).
# 		- Po dwoch pustych liniach: 2. seria danych, tj. wyniki dla n = 10 w tej samej formie.
# 		- Po dwoch pustych liniach: 3. seria danych dla n = 15.
# 		- itd. dla pozostalych n = 20, 25, 30, 35.

set output "epsilon.eps"
set key right top spacing 1
plot for [j=1:7] "out.dat" i j-1 u 1:2 w lp ls 1 lc j t "n = ".(j*5).""

# UWAGA: jesli ktos woli osobne rysunki dla kazdego n, to trzeba odkomentowac ponizsza petle:

# set key right top spacing 3
# do for [j=1:7]{
# 	n = j*5
# 	set output "n".n.".eps"
# 	plot "out.dat" i j-1 u 1:2 ls 1 t "|^{(V_{dok}-V_n)}/_{V_{dok}}|, n = ".n.""
# }


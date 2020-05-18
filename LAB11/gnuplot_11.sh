set terminal post enhanced colour solid font 25 

l_width = 5
p_size = 1.3
set style line 1 lt rgb "black" lw 1 pt 1 ps 1
set style line 2 lt rgb "black" lw l_width*1.2 pt 7 ps 0.7
set style line 3 lt rgb "red" lw 1 pt 2 ps 1
set style line 4 lt rgb "red" lw l_width*0.6 pt 7 ps 0.5 
set style line 5 lt rgb "gray50" lw 1 pt 1 ps 1

omega(n) = 2.*2.*pi/n
f_0(t,n) = sin(omega(n)*t)+sin(2.*omega(n)*t)+sin(3.*omega(n)*t) # funkcja (1): sygnal niezaburzony

# 1. WYKRES: Czesc rzeczywista i urojona transformaty dla k = 8.
#           W pliku fft8.dat powinny byc trzy kolumny: i, y[2*i], y[2*i+1] 
#           (tablica y po wykonaniu gsl_fft_complex_radix2_forward)

k = 8
n(k) = 2**k
set grid
set key top center spacing 2
set output "ReIm_k8.eps"
set xlabel "i"
set ylabel "FFT[y(i)]"
set samples 500
plot [0:n(k)-1][] "fft8.dat" i 0 u 1:2 w lp ls 1 t "Re(FFT[y(i)])",\
 "" i 0 u 1:3 w lp ls 3 t "Im(FFT[y(i)])"

# 2. WYKRES: moduly wspolczynnikow transformaty dla k = 8.
#           Gnuplot obliczy moduly na podstawie pliku fft8.dat 
#            (nie trzeba do niego nic dopisywac).
#           Dodatkowo: Gnuplot znajdzie i wypisze wartosc y_max, 
#            ktorej polowa jest progiem dyskryminacji
#            (mozna porownac: program powinien obliczyc te sama wartosc).

stats "fft8.dat" u (sqrt($2**2 + $3**2)) name "y" nooutput
print sprintf("Dla k = 8: y_max = %g", y_max)

set output "mod_k8.eps"
set ylabel "|FFT[y(i)]|"
plot [0:n(k)-1][] "fft8.dat" i 0 u 1:(sqrt($2**2 + $3**2)) w lp ls 1 t "|FFT[y(i)]|",\
 y_max/2. ls 4 t "Prog dyskryminacji: y_{max}/2"



# PETLA DLA WYKRESOW WYNIKOW ODSZUMIANIA wedlug plikow y8.dat, y10.dat, y12.dat.
# W kazdym z nich (dla odpowiedniego k podanego w nazwie pliku) sa dwie serie danych:
#        - 1. seria: oryginalny, zaszumiony sygnal y wedlug wzoru (4) w dwoch kolumnach: i, y[2*i].
#        - 2. seria (po dwoch pustych liniach): odszumiony sygnal, 
#              czyli tablica y po zakonczeniu wszyskich krokow programu w dwoch kolumnach: i, y[2*i].
# Nie trzeba wypisywac elementow o nieparzystych indeksach (czesci urojone powinny znikac).

set ylabel "y(i)"
set key outside top Right horizontal samplen 2 font ",20" spacing 1

do for [k = 8:12:2]{
    set output "approx_k".k.".eps"
    plot [0:n(k)-1][] "y".k.".dat" i 0 u 1:2 w lp ls 5 t "y(i) = y_0(i)+{/Symbol D}",\
     f_0(x,n(k)) ls 2 t "y_0(i)",\
     "y".k.".dat" i 1 u 1:2 w lp ls 4 t "y(i) po odszumieniu"
}


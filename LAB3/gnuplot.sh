set terminal post enhanced colour solid font 25  # wybor formatu, w jakim chcemy utworzyc wynikowy rysunek
set encoding iso_8859_2  # kodowanie

# Ustawienie styli linii (style 1, 2, 3 i 4):
set style line 1 pt 7 ps 1.1 lc rgb "red"               
set style line 2 pt 7 ps 1.1 lc rgb "blue" 
set style line 3 pt 7 ps 0.5 lw 2 lc rgb "dark-green"
set style line 4 pt 7 ps 0.5 lw 2 lc rgb "gray"


set output "rys.eps"      # Nazwa obrazka
set size 1.618, 1         # Proporcje wymiarow obrazka
set key right center      # Polozenie legendy
set xlabel "k (numer iteracji)"                      # Podpis osi OX
set ylabel "||r_k||_2" tc rgb "red" offset 2, 0      # Podpis LEWEJ osi OY
set y2label "||x_k||_2" tc rgb "blue" rotate by -90  # Podpis PRAWEJ osi OY
set ytics nomirror        # Uniezaleznienie znacznikow skali osi OY od drugiej osi OY
set y2tics nomirror       # Analogicznie.
set logscale y            # Skala logarytmiczna na LEWEJ osi OY
set ytics tc rgb "red"    # Kolor podpisow znacznikow LEWEJ osi OY
set y2tics tc rgb "blue"  # Kolor podpisow znacznikow PRAWEJ osi OY
set grid                  # Wlaczenie widocznosci siatki

# Komenda rysowania czterech serii danych z dwoch plikow:
plot "zad_a.dat" u 1:2 ls 1 t "||r_k||_2, x_0=0", \
"" u 1:4 ls 2 t "||x_k||_2, x_0=0" axes x1y2, \
"zad_b.dat" u 1:2 w lp ls 3 t "||r_k||_2, x_0=1", \
"" u 1:4 w lp ls 4 t "||x_k||_2, x_0=1" axes x1y2

# INFORMACJE NA TEMAT PLIKOW Z DANYMI:
#
# 1. plik: zad_a.dat
#          Zawiera wyniki dla x_0 = 0:
#          - W pierwszej kolumnie: k        -- numer iteracji
#          - W drugiej kolumnie:   ||r_k||  -- norma z r_k
#          - W trzeciej kolumnie:  alfa_k
#          - W czwartej kolumnie:  ||x_k||  -- norma z x_k
#
# 2. plik: zad_b.dat
#          Zawiera wyniki dla x_0 = 1, kolumny ulozone analogicznie do 1. pliku.

# WYJASNIENIE OPCJI KOMENDY plot:
#          u 1:2 == using 1:2 -- 1. kolumna danych zostanie uznana za wartosci osi OX, 2. kolumna: OY (u 1:4 -- analogicznie przy uzyciu 1. i 4. kolumny danych)
#          ls 1  == linestyle 1 -- wybor stylu linii
#          t "tekst" == title "tekst" -- "tekst" bedzie podpisem na legendzie
#          axes x1y2 -- uzycie PRAWEJ osi OY (bez tej opcji Gnuplot domyslnie wybierze LEWA os OY).

set terminal post enhanced colour solid font 30

set output "wielomian.eps" 
set key right top
set xlabel "x" 
set ylabel "f(x)" 
set samples 1000
fprim(x) = 4*x**3 - 30.3*x**2 + 73.5*x - 56.331
f(x) = (x-1.2)*(x-2.3)*(x-3.3)**2
pkt(x) = (abs(x-1.2)<1.e-3 ? 0 : \
        ( abs(x-2.3)<2.e-3 ? 0 : \
        ( abs(x-3.3)<1.e-3 ? 0 : 1./0 )))
set xzeroaxis lw 5
set grid 
plot [0.9:3.7][-1:2.5] f(x) lw 4 t "f(x)", fprim(x) t "f'(x)",\
 pkt(x) w p pt 7 ps 1.5 lc rgb "red" notitle

set terminal post enhanced colour solid font 25 

g(x, y) = x**2 - 4.*x + y**2 -4.*y + x*y

xmin = 4/3;
ymin = 4/3;
set xrange [-10:10]
set yrange [-10:10]
set isosample 250, 250
set table "mapa.dat"
splot g(x,y)
unset table
reset

set xrange [-10:10]
set yrange [-10:10]
set table "kontur.dat"
set contour
unset surface
set view map
set isosamples 100
set cntrparam levels 50
splot g(x,y) 
unset table
reset

set output "g.eps"
unset key
set xlabel "x"
set ylabel "y"
set cblabel "g(x,y)" rotate by -90
set cbtics offset -0.6, 0
set xrange [-10:10]
set yrange [-10:10]
set xtics out
set ytics out
set size ratio -1
set palette rgbformulae 33,13,10
plot "mapa.dat" with image,  "kontur.dat" u 1:2 w l lt -1, "<echo e" us (xmin):(ymin) pt 2 lc 5


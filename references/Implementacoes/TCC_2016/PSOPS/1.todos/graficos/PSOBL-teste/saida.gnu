set style data lines
set ylabel '{/Symbol r}({/Symbol t})'
set xlabel '{/Symbol t}'
set term postscript eps enhanced color
set output 'saida2.eps'
set key right bottom
#set xrange [1:12457.33573521096]
set xrange [1:1.2]
set yrange [0.6:0.9]
plot 'out_N1_saida.gnu.dat' u ($1):($2)  title 'N1' lw 10 lt 0 , 'out_N2_saida.gnu.dat' u ($1):($2)  title 'N2' lw 10 lt 1 , 'out_N3_saida.gnu.dat' u ($1):($2)  title 'N3' lw 10 lt 2
set output 'saida.gnu_bar.eps'
unset key
set ylabel 'Area'
set xlabel 'Algorithm'
set autoscale
unset logscale x
set boxwidth 0.8
set style fill solid border -1
set xrange [1:7]
set yrange [0.5:1.005]
set xtics ('N1' 2, 'N2' 4, 'N3' 6)
plot 'out_saida.gnu.dat' usi (2):1 title 'N1' w boxes lt 0, 'out_saida.gnu.dat' usi (4):2 title 'N2' w boxes lt 1, 'out_saida.gnu.dat' usi (6):3 title 'N3' w boxes lt 2

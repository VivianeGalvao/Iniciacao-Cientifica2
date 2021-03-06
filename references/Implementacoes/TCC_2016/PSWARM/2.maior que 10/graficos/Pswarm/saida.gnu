#set style data lines
#set ylabel '{/Symbol r}({/Symbol t})'
#set xlabel '{/Symbol t}'
#set term postscript eps enhanced color
#set output 'saida.gnu.eps'
#set key right bottom
#set xrange [1:11.944487316775882]
#set yrange [0:1.01]

#set size 1,1
set size 0.3,1
set style data lines
unset key
#set key right bottom
#set key font ",20"
#set logscale x
set ylabel '{/Symbol r}({/Symbol t})'
#set xlabel 'log({/Symbol t})' font ",15"
set xlabel '{/Symbol t}'
set term postscript eps enhanced color font ",15"
#set output 'saida.gnu.eps'
set output 'saida1.eps'
#set xrange [1:104119.00499999999]
#set xrange [1.03:100]
set xrange [1:1.03]
set xtics 1.03
#set yrange [0:1.01]
set yrange [0:1.01]
#unset ytics

plot 'out_N1_saida.gnu.dat' u ($1):($2)  title 'PSWARM' lw 10 lt 0 , 'out_N2_saida.gnu.dat' u ($1):($2)  title 'PSWARM+PS*' lw 10 lt 1

#set output 'saida.gnu_bar.eps'
#unset key
#set ylabel 'Area'
#set xlabel 'Algorithm'
#set autoscale
##unset logscale x
#set boxwidth 0.8
#set style fill solid border -1
#set xrange [1:5]
#set yrange [0.5:1.005]
#set xtics ('N1' 2, 'N2' 4)
#plot 'out_saida.gnu.dat' usi (2):1 title 'N1' w boxes lt 0, 'out_saida.gnu.dat' usi (4):2 title 'N2' w boxes lt 1

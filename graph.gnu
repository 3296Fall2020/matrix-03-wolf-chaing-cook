set terminal png size 1000, 1000
set output 'graph.png'

set xlabel 'Matrix Size'
set ylabel 'Time (sec)'
set title 'Matrix size vs Time'
plot "datatable.txt" using 1:2 title 'mmult' with linespoint, "datatable.txt" using 1:3 title 'SIMD' with linespoint

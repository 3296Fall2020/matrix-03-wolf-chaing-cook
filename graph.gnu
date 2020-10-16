set terminal png size 800,600
set output 'out.png'

set xlabel 'Matrix size'
set ylabel 'Time(sec)'
set title 'Matrix Multiplication Speed on Wolfgang Cluster'

plot "clusterNoSIMD.txt" using 1:3 title 'Vectorized-SIMD: 4 Hosts' with linespoint, "clusterOMP.txt" using 1:3 title 'OpenMP: 4 Hosts' with linespoint, "clusterMPI.txt" using 1:3 title 'MPI: 4 Hosts' with linespoint, "clusterVecSIMP.txt" using 1:3 title 'Unoptimized: 4 Hosts' with linespoint

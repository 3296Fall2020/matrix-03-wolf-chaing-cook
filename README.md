# matrix-03-wolf-chaing-cook
matrix-03-wolf-chaing-cook created by GitHub Classroom

The differences between Single Instruction Multiple Data (SIMD), Open Multi-Processing (OMP) and Message Passing Interface (MPI) is 
that SIMD is that each instruction does the same operation on multiple streams of data at the same. The code contains nested for 
loops and can run with the -03 optimization. OpenMP is shared memory and contains a parallel region and it needs to be sepecified 
whether the variables are private or shared, where the data from the shared will be accessible for the threads and the threads will 
have the same address space. The number of iterations has to be known for it to handle the for loops and we would need -fopenmp to 
run the OpenMP program. MPI is distributed memory and is library for message passing where the processes would send or receive 
messages to each other. There are two types of process, which is the controller process and the worker process and the controller 
process would be the ones to send the messages and give the workers work essentially, while the worker receives that data and give 
the result back to the controller.
For Task 4 was about matrix multiplication with OPENMP. It's basically running the mmult_omp_timing and changing the graph.gnu so were are able to run it with our script. The graph for OMP looks like a straight line going across, which makes sense considering that our matrix size is quite small so we are not able to see a significant difference. If we compare our OMP to the one on the slides for Quad core, the more threads the more that the time is reaching towards zero.
Task 5 was about matrix multiplication with MPI. For task 5 in our case we wrote the c code for it to only realize we could have just run the mxv_omp_mpi.c file, which is basically a hybrid of the mpi and the omp as it states in it's name. We just needed to make changes to the graph.gnu and then run our run auto script so we are able to see the results. From our auto-generated graph it's more like a straight line, which I believe is similar to the graph represented in the slides, but the graph shown is for numbers in the thousands to see significant change. Our program was only able to handle a few hundred for now.


Trello: https://trello.com/b/kfWbrZQM/parallel-computing

The output graph:
![alt text](https://github.com/3296Fall2020/matrix-03-wolf-chaing-cook/blob/master/out.png?raw=true)

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

Trello: https://trello.com/b/kfWbrZQM/parallel-computing

The output graph:
![alt text](https://github.com/3296Fall2020/matrix-03-wolf-chaing-cook/blob/master/out.png?raw=true)

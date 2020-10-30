# matrix-03-wolf-chaing-cook
matrix-03-wolf-chaing-cook created by GitHub Classroom

Tyler Wolf, Wayne Cook, Aley Chaing

Comparing the Different Types of Parallel Computing
---
The differences between Single Instruction Multiple Data (SIMD), Open Multi-Processing (OMP) and Message Passing Interface (MPI) is 
that SIMD is that each instruction does the same operation on multiple streams of data at the same. The code contains nested for 
loops and can run with the -03 optimization. OpenMP is shared memory and contains a parallel region and it needs to be sepecified 
whether the variables are private or shared, where the data from the shared will be accessible for the threads and the threads will 
have the same address space. The number of iterations has to be known for it to handle the for loops and we would need -fopenmp to 
run the OpenMP program. MPI is distributed memory and is library for message passing where the processes would send or receive 
messages to each other. There are two types of process, which is the controller process and the worker process and the controller 
process would be the ones to send the messages and give the workers work essentially, while the worker receives that data and give 
the result back to the controller.

Writing for Mandatory Tasks
---
For Task 1 for the automated running we created a script to be able to compile all of the program and then run the programs that we need to and then just add on the data text files to the corresponding method.
For Task 2 we were basically running the mmult_omp_timing through our script and changing some things around so we can have it on the gnu graph
For Task 3  we were running test_mmult from which we edited mmult.c file to be with SIMD and with vectorization and did the same by changing things around so we can plot it on the graph.
For Task 4 was about matrix multiplication with OPENMP. It's basically running the mmult_omp_timing and changing the graph.gnu so were are able to run it with our script. The graph for OMP looks like a straight line going across, which makes sense considering that our matrix size is quite small so we are not able to see a significant difference. If we compare our OMP to the one on the slides for Quad core, the more threads the more that the time is reaching towards zero.
Task 5 was about matrix multiplication with MPI. For task 5 in our case we wrote the c code for it to only realize we could have just run the mxv_omp_mpi.c file, which is basically a hybrid of the mpi and the omp as it states in it's name. We just needed to make changes to the graph.gnu and then run our run auto script so we are able to see the results. From our auto-generated graph it's more like a straight line, which I believe is similar to the graph represented in the slides, but the graph shown is for numbers in the thousands to see significant change. Our program was only able to handle a few hundred for now.
For the additional task we did the we did the matrix multiplication parallelization in C on our own machine from which we just ran the script again because I believe that OpenMP and MPI were already parallelized so we just ran the entire thing again. We ran the program through kali linux in virtualbox and we just received the exact same result from what we received from when we ran the program on the wolfgang cluster.

Distributed Parallel Computing
---
The architecture of our solution is just the Parallel Computer architecture from which we implemented the Single Instruction Multiple Data (SIMD), the Single Instruction Multiple Threads (SIMT), Symmetric Multiprocessing, and the Distributed memory. Although I believed we implemented a sub-architecture for the distributed memory where we used the master-slave pattern.
The variations of the algorithm implemented was mostly explained in the writing for the mandatory tasks.

Teamwork
---
For the master branch we actually did not lock the master branch, but we did just look over the commits that were made during the branches before we merged it onto the master branch and from the master branch we all did a test to make sure that everything was working properly.

Tyler:
Wrote a seperate automation C program apart from our script in order to provide a broader matrix size to the limited matrix size that the script was able to handle. Also helped partners looked over the code and was there when needed.

Wayne:
Did Task 1, 2, 4 and edited the script and the graph.gnu everytime we needed to add on to the graph. Helped look over partner's work, in which also helped edit for Task 3 and Task 5.

Aley: 
I did the writing for Task 3, Task 5 and just ran the additional task. I also did the readme and reviewed over partner's work and help test run once everything was merged to the master.

Full Project Life Cycle
---
For the project board we just used trello. All we did was add tasks, put the ones we were doing in progress and add it to the complete section, when we were finished. 
In a sense it was the same where we would write the code, compile the code, run the code and test the code. The only thing that felt different working with the wolfgang cluster, was the issue of it running slowly, but apart from that some of us  normally did not write code on the command line using vim, so that was something that we adapted for the purpose of this project, although we knew we could have edited with our IDE.
The testing that we used for this project was mostly checking if everything was compiling and then running the script and taking a look at the graph to see if that's how the graph was supposed to look like according to how the graphs were represented in the slides for the different types of parallel computing. I'm not sure if we considered that the professors had flaws in the program, but we did look into the files in order to make any modifications if needed.
In our case, we can just modifiy our script to be able to take a specific matrix size which was automated, although for the script we were a bit limited in the hundreds, but in the case of Tyler's version we were able to get the graph to be able to take the graph with the matrix sizes in the thousands.
I felt like the earlier tasks took the majority of our time writing variations of the matrix multiplication algorithm and the rest was about testing and reporting activities, although it might be all of it was testing and reporting activities since we made the script to output the graph for the different types of parallel computing as we went along all the way to the end.


Trello: https://trello.com/b/kfWbrZQM/parallel-computing

The output graph:
![alt text](https://github.com/3296Fall2020/matrix-03-wolf-chaing-cook/blob/master/out.png?raw=true)


Output Graph on computer:
![alt text](https://github.com/3296Fall2020/matrix-03-wolf-chaing-cook/blob/master/outForComp.png?raw=true)


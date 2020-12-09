# Levenshtein distance sequential and parallel

## Build
Using VSCode: press ctrl + shift + b and choose the build option. Either with or without openmp.

With openmp:
~~~ g++ src/*.cpp -fopenmp -o out/multithread.o -O2 ~~~

Without openmp:
~~~ g++ src/*.cpp -o out/singlethread.o -O2 ~~~

The files for testing are located in the res/ directory. 
l.txt and r.txt are 64K big ones. The others are either smaller or have a corresponding file title.


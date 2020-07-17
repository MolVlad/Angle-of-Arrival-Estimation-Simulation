#!/bin/bash
gcc -c *.c; gcc -o main *.o -lm libmwnhood.so libmwimregionalmax.so; patchelf --set-rpath /home/condorsync/sync/molodtsov/ main; cp main ../../../run_cluster/

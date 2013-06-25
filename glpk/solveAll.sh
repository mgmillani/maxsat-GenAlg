#!/bin/sh


time glpsol -m maxsat -d logistics.a.data -o logistics.a.out
time glpsol -m maxsat -d qg4-08.data -o qg4-08.out
time glpsol -m maxsat -d uf175-053.data -o uf175-053.out
time glpsol -m maxsat -d uf75-031.data -o  uf75-031.out

time glpsol -m maxsat -d logistics.b.data -o logistics.b.out
time glpsol -m maxsat -d uf250-097.data -o  uf250-097.out
time glpsol -m maxsat -d uf250-093.data -o uf250-093.out

time glpsol -m maxsat -d qg7-09.data -o qg7-09.out
time glpsol -m maxsat -d uf75-041.data -o uf75-041.out
time glpsol -m maxsat -d uf175-058.data -o uf175-058.out



#!/bin/sh

time glpsol -m maxsat -d qg7-09.data -o qg7-09.out
time glpsol -m maxsat -d uf75-041.data -o uf75-041.out
time glpsol -m maxsat -d uf175-058.data -o uf175-058.out
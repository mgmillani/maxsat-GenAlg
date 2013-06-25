#!/bin/sh

time glpsol -m maxsat -d logistics.b.data -o logistics.b.out
time glpsol -m maxsat -d uf250-097.data -o  uf250-097.out
time glpsol -m maxsat -d uf250-093.data -o uf250-093.out
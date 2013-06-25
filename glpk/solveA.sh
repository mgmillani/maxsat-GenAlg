#!/bin/sh

time glpsol -m maxsat -d uf75-031.data -o  uf75-031.out
echo "######## uf75-031 ###########3\n\n\n"
time glpsol -m maxsat -d uf175-053.data -o uf175-053.out
echo "######## uf175-053 ##########3\n\n\n"
time glpsol -m maxsat -d qg4-08.data -o qg4-08.out
echo "######## qg4-08  ##########3\n\n\n"
time glpsol -m maxsat -d logistics.a.data -o logistics.a.out
echo "######### logistics.a ########3\n\n\n"
#!/bin/sh

./maxsat
./maxsat logistics.a.cnf > logistics.a.data
./maxsat logistics.b.cnf > logistics.b.data
./maxsat qg4-08.cnf > qg4-08.data
./maxsat qg7-09.cnf > qg7-09.data
./maxsat uf175-053.cnf > uf175-053.data
./maxsat uf175-058.cnf > uf175-058.data
./maxsat uf250-093.cnf > uf250-093.data
./maxsat uf250-097.cnf > uf250-097.data
./maxsat uf75-031.cnf > uf75-031.data
./maxsat uf75-041.cnf > uf75-041.data
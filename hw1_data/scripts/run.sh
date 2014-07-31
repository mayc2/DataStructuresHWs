#!/bin/bash
I_DIR="../input"
O_DIR="../output"
echo 'compiling'
echo '....'
g++ main.cpp -o justify.exe
echo '.'
echo '.'
echo '.'
echo 'executing flush left'
echo '.'
./justify.exe ../input/example.txt ../output/fl_out.txt 16 flush_left;echo '.'
echo '.'
echo '.'
echo 'executing flush right'
echo '.'
./justify.exe ../input/example.txt ../output/fr_out.txt 16 flush_right;echo '.'
echo '.'
echo '.'
echo 'executing full justify'
echo '.'
./justify.exe ../input/example.txt ../output/full_out.txt 16 full_justify;echo '.'
echo '.'
echo '.'
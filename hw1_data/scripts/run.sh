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
echo 'executing getty flush left'
echo '.'
./justify.exe ../input/gettysburg_address.txt ../output/gtsbrg_FL.txt 70 flush_left;echo '.'
echo '.'
echo '.'
echo 'executing getty flush right'
echo '.'
./justify.exe ../input/gettysburg_address.txt ../output/gtsbrg_FR.txt 70 flush_right;echo '.'
echo '.'
echo '.'
echo 'executing getty full justify'
echo '.'
./justify.exe ../input/gettysburg_address.txt ../output/gtsbrg_FJ.txt 70 full_justify;echo '.'
echo '.'
echo '.'
echo 'executing long full justify'
echo '.'
./justify.exe ../input/long_word.txt ../output/Lword_FJ.txt 15 full_justify;echo '.'
echo '.'
echo '.'
echo 'testing normal left justify'
diff ../output/example_16_flush_left.txt ../output/fl_out.txt;echo " "
echo " "
echo 'testing normal right justify'
diff ../output/example_16_flush_right.txt ../output/fr_out.txt;echo " "
echo " "
echo 'testing normal full justify'
diff ../output/example_16_full_justify.txt ../output/full_out.txt;echo " "
echo " "
echo 'testing getty left'
diff ../output/gettysburg_address_70_flush_left.txt ../output/gtsbrg_FL.txt;echo " "
echo " "
echo 'testing getty right'
diff ../output/gettysburg_address_70_flush_right.txt ../output/gtsbrg_FR.txt;echo " "
echo " "
echo 'testing getty full'
diff ../output/gettysburg_address_70_full_justify.txt ../output/gtsbrg_FJ.txt;echo " "
echo " "
echo 'testing long full'
diff ../output/long_word_15_full_justify.txt ../output/Lword_FJ.txt;echo " "
echo " "
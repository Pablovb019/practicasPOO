cd Vilar_Bustillo_Pablo/P0
make
clear
make clean
clear
make
./test-P0-auto 
make valgrind
make check
make clean
clear
cd ../P1
make
./test-P1-auto 
make valgrind
make check
exit
cd Vilar_Bustillo_Pablo/P0
clear
make
make clean
ckear
clear
make
./test-P0-auto 
./test-fechacadena-consola 
make valgrind
clear
make check+
make check
make clean
clear
cd ../P1
clear
make
make clean
clear
make
make check
make valgrind
./test-P1-auto 
make clean
clear
ls
cd ../P0/
ls
exit
ls -1 Vilar_Bustillo_Pablo/P1/{cadena,fecha}.[ch]pp | tar -cvzf Vilar_Bustillo_Pablo.tar.gz -T -
clear
ls
tar -tvzf Vilar_Bustillo_Pablo.tar.gz 
end
exit

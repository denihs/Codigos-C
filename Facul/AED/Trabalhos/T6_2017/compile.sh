cd librarys/carro/ &&
gcc -c carro.c &&
cd ../../ && ar r library.a librarys/carro/carro.o  &&
gcc -o main main.c library.a -lm &&
./main

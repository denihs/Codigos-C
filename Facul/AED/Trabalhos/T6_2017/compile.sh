cd carro/ &&
gcc -c carro.c &&
cd ../ && ar r library.a carro/carro.o &&
gcc -o main main.c library.a -lm &&
./main

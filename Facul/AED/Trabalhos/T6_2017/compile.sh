cd librarys/cliente/ &&
  gcc -c cliente.c &&
cd ../ &&
cd carro/ &&
  gcc -c carro.c &&

cd ../../ && ar r library.a librarys/cliente/cliente.o librarys/carro/carro.o  &&
gcc -o main main.c library.a -lm &&
./main

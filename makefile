argumentos.o: /home/mateus/Unicamp/MC404/trab01/fonte/argumentos.c
	gcc -c /home/mateus/Unicamp/MC404/trab01/fonte/argumentos.c -o /home/mateus/Unicamp/MC404/trab01/argumentos.o

dados.o: /home/mateus/Unicamp/MC404/trab01/fonte/dados.c
	gcc -c dados.c -o /home/mateus/Unicamp/MC404/trab01/dados.o

leitura.o: /home/mateus/Unicamp/MC404/trab01/fonte/leitura.c
	gcc -c /home/mateus/Unicamp/MC404/trab01/fonte/leitura.c -o /home/mateus/Unicamp/MC404/trab01/leitura.o

listaRot.o: /home/mateus/Unicamp/MC404/trab01/fonte/listaRot.c
	gcc -c /home/mateus/Unicamp/MC404/trab01/fonte/listaRot.c -o /home/mateus/Unicamp/MC404/trab01/listaRot.o

listaCon.o: /home/mateus/Unicamp/MC404/trab01/fonte/listaCon.c
	gcc -c /home/mateus/Unicamp/MC404/trab01/fonte/listaCon.c -o /home/mateus/Unicamp/MC404/trab01/listaCon.o

metodos.o: /home/mateus/Unicamp/MC404/trab01/fonte/metodos.c
	gcc -c /home/mateus/Unicamp/MC404/trab01/fonte/metodos.c -o /home/mateus/Unicamp/MC404/trab01/metodos.o

main.o: main.c
	gcc -c main.c -o main.o
	
prog: argumentos.o dados.o leitura.o listaRot.o listaCon.o metodos.o main.o
	gcc dados.o listaRot.o listaCon.o main.o metodos.o argumentos.o leitura.o -o prog

clean:
	rm -f dados.o listaRot.o listaCon.o main.o metodos.o argumentos.o leitura.o prog

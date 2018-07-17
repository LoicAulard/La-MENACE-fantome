all : menace.exe test.exe

menace.exe: menace.o mytab.o main.o mytab.h menace.h
	gcc -g -Wall -Wextra menace.o mytab.o main.o -o menace.exe

menace.o: menace.c menace.h
	gcc -g -Wall -Wextra -c menace.c

mytab.o: mytab.c mytab.h
	gcc -g -Wall -Wextra -c mytab.c

main.o: main.c
	gcc -g -Wall -Wextra -c main.c

tree.o: tree.c tree.h
	gcc -g -Wall -Wextra -c tree.c

hashtable.o : hashtable.c hashtable.h
	gcc -g -Wall -Wextra -c hashtable.c

list.o: list.c list.h
	gcc -g -Wall -Wextra -c list.c

test.exe : list.o hashtable.o menace.o mytab.o mytab.h menace.h hashtable.h test.c
	gcc -g -Wall -Wextra list.o hashtable.o tree.o menace.o mytab.o test.c -o test.exe

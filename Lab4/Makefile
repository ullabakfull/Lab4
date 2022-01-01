
output: lab4.o myhead.o
	gcc -o output lab4.o myhead.o

lab4.o: lab4.c
	gcc -c lab4.c

myhead.o: myhead.c myhead.h
	gcc -c myhead.c

clean:
	-rm output lab4.o stack.o
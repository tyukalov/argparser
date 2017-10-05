all:
	gcc -c argparser.c
	ar rc libargparser.a argparser.o
	rm *.o
test:
	gcc test.c libargparser.a -o test0
	gcc test1.c libargparser.a -o test1
clean:
	rm test0 test1

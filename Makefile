
output: user1.o
	gcc user1.o -o output

user1.o: user1.c
	gcc -c user1.c

clean:
	rm *.o output
CC=gcc
.PHONY : clean run

test : test.o lightControll.o lightControllSM.o

clean:
	rm -f *.o *~
	rm -f test

run: test
	./test

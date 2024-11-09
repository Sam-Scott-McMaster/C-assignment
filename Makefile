convert:
	gcc -o convert --coverage conversion.c cmdLineInterpreter.c main.c

clean:
	rm -f *.o *.gcno *.gcda convert 

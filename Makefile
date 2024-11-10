convert:
	gcc -o convert conversion.c cmdLineInterpreter.c main.c

# Testing version with coverage
ctest:
	gcc -o ctest --coverage conversion.c cmdLineInterpreter.c main.c

# Clean build files
clean:
	rm -f *.o *.gcno *.gcda convert ctest 

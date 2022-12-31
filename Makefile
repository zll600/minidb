objects = main.o repl.o

minidb : $(objects) 
	clang -o minidb ${objects}

main.o : main.c repl.h 
	clang -c main.c

repl.o : repl.c repl.h 
	clang -c repl.c

.PHONY : clean
clean :
	-rm minidb ${objects}

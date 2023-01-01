objects = main.o repl.o tokenizer.o parser.o code_generator.o

minidb : $(objects) 
	clang -o minidb ${objects}

main.o : main.c repl.h 
	clang -c main.c

repl.o : repl.c repl.h 
	clang -c repl.c

tokenizer.o : tokenizer.c tokenizer.h
	clang -c tokenizer.c

parser.o : parser.c parser.h
	clang -c parser.c

code_generator.o : code_generator.c code_generator.h
	clang -c code_generator.c

.PHONY : clean
clean :
	-rm minidb ${objects}

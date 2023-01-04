objects = main.o repl.o tokenizer.o parser.o code_generator.o table.o row.o pager.o cursor.o
CFLAGS = -Wall -fcommon

minidb : $(objects) 
	clang ${CFLAGS} -o minidb ${objects}

main.o : main.c repl.h parser.h table.h tokenizer.h code_generator.h
	clang ${CFLAGS} -c main.c

repl.o : repl.c repl.h 
	clang -c repl.c

tokenizer.o : tokenizer.c tokenizer.h
	clang -c tokenizer.c

parser.o : parser.c parser.h row.h
	clang ${CFLAGS} -c parser.c

code_generator.o : code_generator.c code_generator.h table.h
	clang ${FLAGS} -c code_generator.c

table.o : table.c table.h row.h
	clang -c table.c

row.o : row.c row.h
	clang -c row.c

pager.o : pager.c pager.h
	clang -c pager.c

cursor.o : cursor.c cursor.h
	clang -c cursor.c

.PHONY : clean
clean :
	-rm -f minidb ${objects} mydb.db

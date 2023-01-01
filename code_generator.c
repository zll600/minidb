#include "code_generator.h"

#include <stdio.h>

void execute_statement(Statement *statement) {
    switch (statement->type) {
    case (STATEMENT_INSERT):
        printf("This is where we would do an insert.\n");
        break;
    case (STATEMENT_SELECT):
        printf("This is where we do select.\n");
        break;
    }
}

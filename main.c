#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "code_generator.h"
#include "parser.h"
#include "repl.h"
#include "table.h"
#include "tokenizer.h"

int main(int argc, char *argv[]) {
    Table *table = new_table();
    InputBuffer *input_buffer = new_input_buffer();
    while (true) {
        print_prompt();
        read_input(input_buffer);

        // Non-SQL statements like .exit are called “meta-commands”
        // They all start with a dot, check for them and handle them in a
        // separate function.
        if (input_buffer->buffer[0] == '.') {
            switch (do_meta_command(input_buffer)) {
            case (META_COMMAND_SUCCESS):
                continue;
            case (META_COMMAND_UNRECOGNIZED_COMMAND):
                printf("Unrecongized command %s \n", input_buffer->buffer);
                continue;
            }
        }

        Statement statement;
        switch (prepare_statement(input_buffer, &statement)) {
        case (PREPARE_SUCCESS):
            printf("Insert Successfully.");
            break;
        case (PREPARE_NEGATIVE_ID):
            printf("Can't insert record with negative id.");
            break;
        case (PREPARE_STRING_TOO_LONG):
            printf("This record has a too big field.");
            break;
        case (PREPARE_SYNTAX_ERROR):
            printf("Syntax error. Couldn't parse this statement.\n");
            continue;
        case (PREPARE_UNRECOGNIZED_STATEMENT):
            printf("Unrecongized keyword at start of %s \n",
                   input_buffer->buffer);
        }

        // execute_statement(&statement, table);
        switch (execute_statement(&statement, table)) {
        case (EXECUTE_SUCCESS):
            printf("Executed.\n");
            break;
        case (EXECUTE_TABLE_FULL):
            printf("Error: table is full.\n");
            break;
        }
    }
    return 0;
}

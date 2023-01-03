#include "parser.h"

#include <stdio.h>
#include <string.h>

PrepareResult prepare_statement(InputBuffer *input_buffer,
                                Statement *statement) {
    if (!strncmp(input_buffer->buffer, "insert", 6)) {
        statement->type = STATEMENT_INSERT;
        int args_assigned = sscanf(input_buffer->buffer, "insert %d %s %s",
                                   &(statement->row_to_insert.id),
                                   statement->row_to_insert.username,
                                   statement->row_to_insert.email);
        if (args_assigned < 3) {
            return PREPARE_SYNTAX_ERROR;
        }
        return PREPARE_SUCCESS;
    } else if (!strncmp(input_buffer->buffer, "select", 6)) {
        statement->type = STATEMENT_SELECT;
        return PREPARE_SUCCESS;
    }
    return PREPARE_UNRECOGNIZED_STATEMENT;
}

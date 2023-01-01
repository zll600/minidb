#include "parser.h"

#include <string.h>

PrepareResult prepare_statement(InputBuffer *input_buffer,
                                Statement *statement) {
    if (!strncmp(input_buffer->buffer, "insert", 6)) {
        statement->type = STATEMENT_INSERT;
        return PREPARE_SUCCESS;
    } else if (!strncmp(input_buffer->buffer, "select", 6)) {
        statement->type = STATEMENT_SELECT;
        return PREPARE_SUCCESS;
    }
    return PREPARE_UNRECOGNIZED_STATEMENT;
}

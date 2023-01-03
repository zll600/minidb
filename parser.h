#ifndef MINIDB_PARSER_H_
#define MINIDB_PARSER_H_

#include "repl.h"

#include "row.h"

typedef enum {
    PREPARE_SUCCESS,
    PREPARE_NEGATIVE_ID,
    PREPARE_STRING_TOO_LONG,
    PREPARE_UNRECOGNIZED_STATEMENT,
    PREPARE_SYNTAX_ERROR,
} PrepareResult;

typedef enum {
    STATEMENT_INSERT,
    STATEMENT_SELECT,
} StatementType;

typedef struct {
    StatementType type;
    // only used by insert statement
    Row row_to_insert;
} Statement;

PrepareResult prepare_statement(InputBuffer *input_buffer,
                                Statement *statement);
PrepareResult prepare_insert(InputBuffer *input_buffer, Statement *statement);

#endif // MINIDB_PARSER_H_

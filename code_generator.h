#ifndef MINIDB_CODEGENERATOR_H_
#define MINIDB_CODEGENERATOR_H_

#include "cursor.h"
#include "parser.h"
#include "table.h"

typedef enum {
    EXECUTE_SUCCESS,
    EXECUTE_TABLE_FULL,
    EXECUTE_DUPLICATE_KEY
} ExecuteResult;

void leaf_node_insert(Cursor *cursor, uint32_t key, Row *value);
void leaf_node_split_and_insert(Cursor *cursor, uint32_t key, Row *value);

ExecuteResult execute_statement(Statement *statement, Table *table);

ExecuteResult execute_insert(Statement *statement, Table *table);
ExecuteResult execute_select(Statement *statement, Table *table);

void print_constants(void);

// void print_row(Row *row);

#endif // MINIDB_CODEGENERATOR_H_

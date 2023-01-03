#ifndef MINIDB_CODEGENERATOR_H_
#define MINIDB_CODEGENERATOR_H_

#include "parser.h"
#include "table.h"

typedef enum { EXECUTE_SUCCESS, EXECUTE_TABLE_FULL } ExecuteResult;

ExecuteResult execute_statement(Statement *statement, Table *table);

ExecuteResult execute_insert(Statement *statement, Table *table);
ExecuteResult execute_select(Statement *statement, Table *table);

// void print_row(Row *row);

#endif // MINIDB_CODEGENERATOR_H_

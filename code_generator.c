#include "code_generator.h"

#include <stdio.h>

#include "row.h"
#include "table.h"
#include "cursor.h"

static void print_row(Row *row) {
    printf("(%d %s %s)\n", row->id, row->username, row->email);
}

ExecuteResult execute_statement(Statement *statement, Table *table) {
    switch (statement->type) {
    case (STATEMENT_INSERT):
        printf("This is where we would do an insert.\n");
        return execute_insert(statement, table);
    case (STATEMENT_SELECT):
        printf("This is where we do select.\n");
        return execute_select(statement, table);
    }
}

ExecuteResult execute_insert(Statement *statement, Table *table) {
    if (table->num_rows >= TABLE_MAX_ROWS) {
        return EXECUTE_TABLE_FULL;
    }
    Row *row_to_insert = &(statement->row_to_insert);
	Cursor *cursor = table_end(table);
    serialize_row(row_to_insert, cursor_value(cursor));
    table->num_rows += 1;

	free(cursor);
    return EXECUTE_SUCCESS;
}

ExecuteResult execute_select(Statement *statement, Table *table) {
    Row row;
	Cursor *cursor = table_start(table);
	while (!cursor->end_of_file) {
        deserialize_row(cursor_value(cursor), &row);
        print_row(&row);
		cursor_advance(cursor);
    }

	free(cursor);
    return EXECUTE_SUCCESS;
}

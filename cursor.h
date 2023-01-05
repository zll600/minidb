#ifndef MINIDB_CURSOR_H_
#define MINIDB_CURSOR_H_

#include <stdbool.h>

#include "table.h"

// represent a position in the table.
typedef struct {
    Table *table;
    // locate one record by page_num + cell_num
    uint32_t page_num;
    uint32_t cell_num;
    // indicates a position one past the last element.
    bool end_of_file;
} Cursor;

Cursor *table_start(Table *table);

Cursor *table_end(Table *table);

// return the position of the given key.
// if the key is not present, return position.
// where it should be inserted.
Cursor *table_find(Table *table, uint32_t key);

// return.
// - the position of the key.
// - the position of another key that we'll need to move if we want to insert
// the key.
// - the position of last key.
Cursor *leaf_node_find(Table *table, uint32_t page_num, uint32_t key);

// figure out where to read/write in memory for a particular row
void *cursor_value(Cursor *cursor);

// advance the cursor
void cursor_advance(Cursor *cursor);

#endif // MINIDB_CURSOR_H_

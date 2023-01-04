#ifndef MINIDB_TABLE_H_
#define MINIDB_TABLE_H_

#include <stdint.h>

#include "pager.h"

typedef struct {
    uint32_t num_rows;
    Pager *pager;
} Table;

// opening database file.
// initializing a pager data structure.
// initializing a table data structure.
Table *db_open(const char *filename);

// flush the page cache to disk.
// closes the database file.
// frees the memory for the Pager and Table data structure.
void db_close(Table *table);

#endif // MINIDB_TABLE_H_

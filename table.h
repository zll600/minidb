#ifndef MINIDB_TABLE_H_
#define MINIDB_TABLE_H_

#include <stdint.h>

#define TABLE_MAX_PAGE 100
// 4kb per page
#define PAGE_SIZE 4096
#define ROWS_PER_PAGE (PAGE_SIZE / ROW_SIZE)
#define TABLE_MAX_ROWS (ROWS_PER_PAGE * TABLE_MAX_PAGE)

typedef struct {
    uint32_t num_rows;
    void *pages[TABLE_MAX_PAGE];
} Table;

// figure out where to read/write in memory for a particular row
void *row_slot(Table *talbe, uint32_t row_num);

Table *new_table(void);
void free_table(Table *table);

#endif // MINIDB_TABLE_H_

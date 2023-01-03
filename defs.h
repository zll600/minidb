#ifndef MINIDB_DEFS_H_
#define MINIDB_DEFS_H_

// === properties of row
#define COLUMN_USERNAME_SIZE 32
#define COLUMN_EMAIL_SIZE 255

#define size_of_attribute(Struct, Attribute) sizeof(((Struct *)0)->Attribute)

// === properties of table
#define TABLE_MAX_PAGES 100
// 4kb per page
#define PAGE_SIZE 4096
#define ROWS_PER_PAGE (PAGE_SIZE / ROW_SIZE)
#define TABLE_MAX_ROWS (ROWS_PER_PAGE * TABLE_MAX_PAGES)

#endif // MINIDB_DEFS_H_

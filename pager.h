#ifndef MINIDB_PAGER_H_
#define MINIDB_PAGER_H_

#include <stdint.h>

#include "defs.h"

typedef struct {
    int file_descriptor;
    uint32_t file_length;
	// number of pages in use by minidb
	uint32_t num_pages;
    void *pages[TABLE_MAX_PAGES];
} Pager;

// open database file.
// keep track of file size.
// initialize the page cache to all NULLs.
Pager *pager_open(const char *filename);

// We assume pages are saved one after another in the database file.
// page 0 at offset 0.
// page 1 at offset 4096
// page ...
// this method handles cache miss.
void *get_page(Pager *pager, uint32_t page_num);

// one page can has free space
void pager_flush(Pager *pager, int page_num);

#endif // MINIDB_PAGER_H_

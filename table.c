#include "table.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "row.h"
#include "btree.h"


Table *db_open(const char *filename) {
    Pager *pager = pager_open(filename);
    uint32_t num_rows = pager->file_length / ROW_SIZE;

    Table *table = (Table *)malloc(sizeof(Table));
    // table->num_rows = num_rows;
    table->pager = pager;
	// initialize page 0 to be the empty leaf node(the root page)
	table->root_page_num = 0;

	if (pager->num_pages == 0) {
		// New database file, Initialize page 0 as leaf node.
		void *root_page = get_page(table->pager, 0);
		initilalize_leaf_node(root_page);
	}

    return table;
}

void db_close(Table *table) {
    Pager *pager = table->pager;

    for (uint32_t i = 0; i < pager->num_pages; i++) {
        if (pager->pages[i] == NULL) {
            continue;
        }
        pager_flush(pager, i);
        free(pager->pages[i]);
        pager->pages[i] = NULL;
    }

    int result = close(pager->file_descriptor);
    if (result == -1) {
        printf("Error closing db file.\n");
        exit(EXIT_FAILURE);
    }
    for (uint32_t i = 0; i < TABLE_MAX_PAGES; i++) {
        void *page = pager->pages[i];
        if (page) {
            free(page);
            pager->pages[i] = NULL;
        }
    }
    free(pager);
    free(table);
}

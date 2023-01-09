#include "table.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "btree.h"
#include "row.h"

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
        initialize_leaf_node(root_page);
        set_node_root(root_page, true);
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

void create_new_root(Table *table, uint32_t right_child_page_num) {
    /*
    handle splitting the root.
    old root copied to new page, becomes left child.
    address of right child passed in.
    re-initialize root page to contain the new root node.
    new root node points to two children.
    */
    void *root = get_page(table->pager, table->root_page_num);
    void *right_child = get_page(table->pager, right_child_page_num);
    uint32_t left_child_page_num = get_unused_page_num(table->pager);
    void *left_child = get_page(table->pager, left_child_page_num);

    // left child has data copied from old root.
    memcpy(left_child, root, PAGE_SIZE);
    set_node_root(left_child, false);

    // root node is a new internal node with one key and two children.
    set_node_root(root, true);
    *internal_node_num_keys(root) = 1;
    *internal_node_child(root, 0) = left_child_page_num;
    uint32_t left_child_max_key = get_node_max_key(left_child);
    *internal_node_key(root, 0) = left_child_max_key;
    *internal_node_right_child(root) = right_child_page_num;
}

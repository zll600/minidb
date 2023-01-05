#include "cursor.h"

#include <stdio.h>
#include <stdlib.h>

#include "btree.h"
#include "row.h"

Cursor *table_start(Table *table) {
    Cursor *cursor = (Cursor *)malloc(sizeof(Cursor));
    cursor->table = table;
    cursor->page_num = table->root_page_num;
    cursor->cell_num = 0;

    void *node = get_page(table->pager, table->root_page_num);
    uint32_t num_cells = *leaf_node_num_cells(node);
    cursor->end_of_file = (num_cells == 0);
    return cursor;
}

Cursor *table_end(Table *table) {
    Cursor *cursor = (Cursor *)malloc(sizeof(Cursor));
    cursor->table = table;
    cursor->page_num = table->root_page_num;

    void *root_node = get_page(table->pager, table->root_page_num);
    uint32_t num_cells = *leaf_node_num_cells(root_node);
    cursor->cell_num = num_cells;
    cursor->end_of_file = true;

    return cursor;
}

Cursor *table_find(Table *table, uint32_t key) {
    uint32_t root_page_num = table->root_page_num;
    void *root_node = get_page(table->pager, root_page_num);

    if (get_node_type(root_node) == NODE_LEAF) {
        return leaf_node_find(table, root_page_num, key);
    } else {
        printf("Need to implement searching an internal node.\n");
        exit(EXIT_FAILURE);
    }
}

Cursor *leaf_node_find(Table *table, uint32_t page_num, uint32_t key) {
    void *node = get_page(table->pager, page_num);
    uint32_t num_cells = *leaf_node_num_cells(node);

    Cursor *cursor = (Cursor *)malloc(sizeof(Cursor));
    cursor->table = table;
    cursor->page_num = page_num;

    // do binary search.
    uint32_t min_indx = 0;
    uint32_t one_past_max_index = num_cells;
    while (one_past_max_index != min_indx) {
        uint32_t index = (min_indx + one_past_max_index) / 2;
        uint32_t key_at_index = *leaf_node_key(node, index);
        if (key == key_at_index) {
            // this key already exists.
            cursor->cell_num = index;
            return cursor;
        }
        if (key < key_at_index) {
            one_past_max_index = index;
        } else {
            min_indx = index + 1;
        }
    }
    cursor->cell_num = min_indx;
    return cursor;
}

void *cursor_value(Cursor *cursor) {
    uint32_t page_num = cursor->page_num;
    void *page = get_page(cursor->table->pager, page_num);

    return leaf_node_value(page, cursor->cell_num);
}

void cursor_advance(Cursor *cursor) {
    uint32_t page_num = cursor->page_num;
    void *node = get_page(cursor->table->pager, page_num);
    cursor->cell_num += 1;
    if (cursor->cell_num >= *leaf_node_num_cells(node)) {
        cursor->end_of_file = true;
    }
}

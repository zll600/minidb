#include "code_generator.h"

#include <stdio.h>
#include <string.h>

#include "btree.h"
#include "defs.h"
#include "row.h"

static void print_row(Row *row) {
    printf("(%d %s %s)\n", row->id, row->username, row->email);
}

void leaf_node_insert(Cursor *cursor, uint32_t key, Row *value) {
    void *node = get_page(cursor->table->pager, cursor->page_num);

    uint32_t num_cells = *leaf_node_num_cells(node);
    if (num_cells >= LEAF_NODE_MAX_CELLS) {
        // node full
        leaf_node_split_and_insert(cursor, key, value);
    }

    if (cursor->cell_num < num_cells) {
        // make room for new cell.
        for (uint32_t i = num_cells; i > cursor->cell_num; i--) {
            memcpy(leaf_node_cell(node, i), leaf_node_cell(node, i - 1),
                   LEAF_NODE_CELL_SIZE);
        }
    }

    *(leaf_node_num_cells(node)) += 1;
    *(leaf_node_key(node, cursor->cell_num)) = key;
    serialize_row(value, (leaf_node_value(node, cursor->cell_num)));
}

void leaf_node_split_and_insert(Cursor *cursor, uint32_t key, Row *value) {
    /*
    create a new node and move half the cells over.
    insert the new value in one of the two nodes.
    update parent or create a new parent.
    */
    void *old_node = get_page(cursor->table->pager, cursor->page_num);
    uint32_t new_page_num = get_unused_page_num(cursor->table->pager);
    void *new_node = get_page(cursor->table->pager, new_page_num);
    initialize_leaf_node(new_node);
    *leaf_node_next_leaf(new_node) = *leaf_node_next_leaf(old_node);
    *leaf_node_next_leaf(old_node) = new_page_num;

    /*
    all existsing keys plus new key should be divided evenly between old(left)
    and new(right) nodes. starting from the right, move each key to correct
    position.
    */
    for (int32_t cell_num = LEAF_NODE_MAX_CELLS; cell_num >= 0; cell_num--) {
        void *destination_node;
        if (cell_num >= LEAF_NODE_LEFT_SPLIT_COUNT) {
            destination_node = new_node;
        } else {
            destination_node = old_node;
        }

        uint32_t index_within_node = cell_num % LEAF_NODE_LEFT_SPLIT_COUNT;
        void *destination = leaf_node_cell(destination_node, cell_num);

        if (cell_num == cursor->cell_num) {
            serialize_row(value, destination);
            serialize_row(value,
                          leaf_node_value(destination_node, index_within_node));
            *leaf_node_key(destination_node, index_within_node) = key;
        } else if (cell_num > cursor->cell_num) {
            memcpy(destination, leaf_node_cell(old_node, cell_num - 1),
                   LEAF_NODE_CELL_SIZE);
        } else {
            memcpy(destination, leaf_node_cell(old_node, cell_num),
                   LEAF_NODE_CELL_SIZE);
        }
    }

    /*
    update cell count on both leaf nodes.
    */
    *(leaf_node_num_cells(old_node)) = LEAF_NODE_LEFT_SPLIT_COUNT;
    *(leaf_node_num_cells(new_node)) = LEAF_NODE_RIGHT_SPLIT_COUNT;

    if (is_node_root(old_node)) {
        return create_new_root(cursor->table, new_page_num);
    } else {
        printf("Need to implement updating parent after split\n");
        exit(EXIT_FAILURE);
    }
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
    void *node = get_page(table->pager, table->root_page_num);
    uint32_t num_cells = *(leaf_node_num_cells(node));

    Row *row_to_insert = &(statement->row_to_insert);
    // print_row(row_to_insert);
    uint32_t key_to_insert = row_to_insert->id;
    // search the table for the correct place to insert the key.
    Cursor *cursor = table_find(table, key_to_insert);
    if (cursor->cell_num < num_cells) {
        uint32_t key_at_index = *leaf_node_key(node, cursor->cell_num);
        if (key_at_index == key_to_insert) {
            // if key already exists, return an error.
            return EXECUTE_DUPLICATE_KEY;
        }
    }
    leaf_node_insert(cursor, row_to_insert->id, row_to_insert);

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

void print_constants(void) {
    printf("ROW_SIZE: %zd\n", ROW_SIZE);
    printf("COMMON_NODE_HEADER_SIZE: %zd\n", COMMON_NODE_HEADER_SIZE);
    printf("LEAF_NODE_HEADER_SIZE: %zd\n", LEAF_NODE_HEADER_SIZE);
    printf("LEAF_NODE_CELL_SIZE: %zd\n", LEAF_NODE_CELL_SIZE);
    printf("LEAF_NODE_SPACE_FOR_CELLS: %zd\n", LEAF_NODE_SPACE_FOR_CELLS);
    printf("LEAF_NODE_MAX_CELLS: %zd\n", LEAF_NODE_MAX_CELLS);
}

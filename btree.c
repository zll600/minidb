#include "btree.h"

#include <stdio.h>

#include "defs.h"
#include "row.h"

// access metadata
uint32_t *leaf_node_num_cells(void *node) {
    return node + LEAF_NODE_NUM_CELL_OFFSET;
}
void *leaf_node_cell(void *node, uint32_t cell_num) {
    return node + LEAF_NODE_HEADER_SIZE + LEAF_NODE_CELL_SIZE * cell_num;
}
// access key
uint32_t *leaf_node_key(void *node, uint32_t cell_num) {
    return leaf_node_cell(node, cell_num);
}
// access value
void *leaf_node_value(void *node, uint32_t cell_num) {
    return leaf_node_cell(node, cell_num) + LEAF_NODE_KEY_OFFSET;
}

void initilalize_leaf_node(void *node) {
    set_node_type(node, NODE_LEAF);
    *leaf_node_num_cells(node) = 0;
}

void print_leaf_node(void *node) {
    uint32_t num_cells = *leaf_node_num_cells(node);
    printf("leaf (size %d)\n", num_cells);
    for (uint32_t cell_num = 0; cell_num < num_cells; cell_num++) {
        uint32_t key = *leaf_node_key(node, cell_num);
        printf("   - %d: %d\n", cell_num, key);
    }
}

NodeType get_node_type(void *node) {
    uint8_t value = *((uint8_t *)(node + NODE_TYPE_OFFSET));
    return (NodeType)(value);
}

void set_node_type(void *node, NodeType node_type) {
    uint8_t value = node_type;
    *((uint8_t *)(node + NODE_TYPE_OFFSET)) = value;
}

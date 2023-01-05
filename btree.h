#ifndef MINIDB_BTREE_H_
#define MINIDB_BTREE_H_

#include <stdint.h>

typedef enum {
    NODE_INTERNAL,
    NODE_LEAF,
} NodeType;

// each node will correspond to one page.
// internal node will store the children's page number.
// ask the pager for a particular page number.

// access metadata
uint32_t *leaf_node_num_cells(void *node);
void *leaf_node_cell(void *node, uint32_t cell_num);
// access key
uint32_t *leaf_node_key(void *node, uint32_t cell_num);
// access value
void *leaf_node_value(void *node, uint32_t cell_num);

void initilalize_leaf_node(void *node);

void print_leaf_node(void *node);

NodeType get_node_type(void *node);
void set_node_type(void *node, NodeType type);

#endif // MINIDB_BTREE_H_

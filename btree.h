#ifndef MINIDB_BTREE_H_
#define MINIDB_BTREE_H_

#include <stdbool.h>
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

uint32_t *leaf_node_next_leaf(void *node);

void initialize_leaf_node(void *node);

void print_leaf_node(void *node);

NodeType get_node_type(void *node);
void set_node_type(void *node, NodeType type);

uint32_t *internal_node_num_keys(void *node);
uint32_t *internal_node_right_child(void *node);
uint32_t *internal_node_cell(void *node, uint32_t cell_num);
uint32_t *internal_node_child(void *node, uint32_t child_num);
uint32_t *internal_node_key(void *node, uint32_t key_num);
void initialize_internal_node(void *node);

uint32_t get_node_max_key(void *node);

bool is_node_root(void *node);
void set_node_root(void *node, bool is_root);

#endif // MINIDB_BTREE_H_

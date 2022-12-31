#ifndef MINIDB_REPL_H
#define MINIDB_REPL_H

#include <stdlib.h>

typedef struct {
    char *buffer;
    size_t buffer_length;
    ssize_t input_length;
} InputBuffer;

InputBuffer *new_input_buffer(void);

void print_prompt(void);
void read_input(InputBuffer *input_buffer);
void close_input_buffer(InputBuffer *input_buffer);

#endif // MINIDB_REPL_H

#ifndef MINIDB_TOKENIZER_H
#define MINIDB_TOKENIZER_H

#include "repl.h"
#include "table.h"

typedef enum {
    META_COMMAND_SUCCESS,
    META_COMMAND_UNRECOGNIZED_COMMAND,
} MetaCommandResult;

MetaCommandResult do_meta_command(InputBuffer *input_buffer, Table *table);

#endif // MINIDB_TOKENIZER_H

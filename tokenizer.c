#include "tokenizer.h"

#include <string.h>
#include <stdio.h>

#include "code_generator.h"
#include "btree.h"

MetaCommandResult do_meta_command(InputBuffer *input_buffer, Table *table) {
    if (!strcmp(input_buffer->buffer, ".exit")) {
        db_close(table);
        exit(EXIT_SUCCESS);
    } else if (!strcmp(input_buffer->buffer, ".constants")) {
		printf("Constant.\n");
		print_constants();
		return META_COMMAND_SUCCESS;
	} else if (!strcmp(input_buffer->buffer, ".btree")) {
		printf("Tree\n");
		print_leaf_node(get_page(table->pager, 0));
		return META_COMMAND_SUCCESS;
	}

    return META_COMMAND_UNRECOGNIZED_COMMAND;
}

#ifndef MINIDB_ROW_H_
#define MINIDB_ROW_H_

#include <stdint.h>

#include "defs.h"

typedef struct {
    uint32_t id;
    char username[COLUMN_USERNAME_SIZE + 1];
    char email[COLUMN_EMAIL_SIZE + 1];
} Row;

void serialize_row(Row *source, void *destination);
void deserialize_row(void *source, Row *destination);

#endif // MINIDB_ROW_H_

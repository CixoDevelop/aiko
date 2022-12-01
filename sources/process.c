#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <stdlib.h>
#include "process.h"
#include "message_box.h"

/** \fn process_create
 * This create new process in space passed in parameter.
 * @*process Process to work on
 */
void process_create(process_t *process) {
    process->type = EMPTY;
    message_box_create(process->message);
}

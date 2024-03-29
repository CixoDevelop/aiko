/*
 * This project is Aiko, an operating system for weak devices like 
 * microcontrollers. It has support for devices based on eight-bit 
 * architectures. It is suitable even for devices with only 128 bytes 
 * of operational memory. You can make it easier to code your projects 
 * based on such platforms by using Aiko as a scheduler.
 *
 * Author: Cixo
 */

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <stdlib.h>
#include "process.h"
#include "message_box.h"

/** \fn process_create
 * This create new process in space passed in parameter.
 * @param *process Process to work on
 */
void process_create(process_t *process) {
    process->type = EMPTY;
    message_box_create(process->message);
}

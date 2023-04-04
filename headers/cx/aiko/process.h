/*
 * This project is Aiko, an operating system for weak devices like 
 * microcontrollers. It has support for devices based on eight-bit 
 * architectures. It is suitable even for devices with only 128 bytes 
 * of operational memory. You can make it easier to code your projects 
 * based on such platforms by using Aiko as a scheduler.
 *
 * Author: Cixo
 */

#ifndef HEADERS_AIKO_PROCESS_H_INCLUDED
#define HEADERS_AIKO_PROCESS_H_INCLUDED

#include "message_box.h"
#include "numbers.h"

/** \enum process_type_t
 * This store type of process.
 */
typedef enum {
    
    /* Process does not exists */
    EMPTY = 0x00,

    /* Process will be executed when anybody send something to messagebox */
    REACTIVE = 0x01,

    /* Process will be execute whenever processor does not doing anything */
    CONTINUOUS = 0x02,

    /* Process will be execute whenever their signal will be triggered */
    SIGNAL = 0x03

} process_type_t;

/** \struct process_t
 * This struct store process.
 */
typedef struct {
    
    /* This store type of process */
    process_type_t type;

    /* This store process message box */
    message_box_t message[1];

    /* This store process worker, process main function */
    void (*worker)(void *, void *);

    /* This store parameter for process worker */
    void *parameter;

} process_t;

/** \fn process_create
 * This create new process in space passed in parameter.
 * @param *process Process to work on
 */
void process_create(process_t *process);

#endif

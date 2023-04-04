/*
 * This project is Aiko, an operating system for weak devices like 
 * microcontrollers. It has support for devices based on eight-bit 
 * architectures. It is suitable even for devices with only 128 bytes 
 * of operational memory. You can make it easier to code your projects 
 * based on such platforms by using Aiko as a scheduler.
 *
 * Author: Cixo
 */

#ifndef CX_AIKO_MESSAGE_BOX_H_INCLUDED
#define CX_AIKO_MESSAGE_BOX_H_INCLUDED

#include <stdbool.h>

/** \struct message_box_t
 * This struct is usable to sending commands between processes. System use it
 * to manage whitch of processes is ready to run. You can check if message box
 * is full, or you can write into it.
 */
typedef struct {
    
    /* If message box is blank, it is false */
    bool readable;

    /* Pointer to message from other process */
    void *message;

} message_box_t;

/** \fn message_box_create
 * This prepare new message box to work.
 * @param *box Message box to work on
 */
void message_box_create(message_box_t *box);

/** \fn message_box_is_readable
 * This check and return true if message box is readable or false if not.
 * @param *box Message box to work on
 * @return True if message box is readable, or false if not
 */
bool message_box_is_readable(message_box_t *box);

/** \fn message_box_is_sendable
 * This check and return true if message box is sendable or false if not.
 * @param *box Message box to work on
 * @return True if message box is sendable, false if not
 */
bool message_box_is_sendable(message_box_t *box);

/** \fn message_box_send
 * This function send data to message box.
 * @param *box Message box to work on
 * @param *data Data to send
 */
void message_box_send(message_box_t *box, void *data);

/** \fn message_box_show
 * This function return content which is save in message box. That not change
 * message box flag.
 * @param *box Message box to work on
 * @return Message box content 
 */
void* message_box_show(message_box_t *box);
 
/** \fn message_box_receive 
 * This function receive data from message box.
 * @param *box Message box to work on
 * @return Message box content
 */
void* message_box_receive(message_box_t *box);

#endif

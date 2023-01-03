#ifndef HEADERS_AIKO_MESSAGE_BOX_H_INCLUDED
#define HEADERS_AIKO_MESSAGE_BOX_H_INCLUDED

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
 * @*box Message box to work on
 */
void message_box_create(message_box_t *box);

/** \fn message_box_is_readable
 * This check and return true if message box is readable or false if not.
 * @*box Message box to work on
 */
bool message_box_is_readable(message_box_t *box);

/** \fn message_box_is_sendable
 * This check and return true if message box is sendable or false if not.
 * @*box Message box to work on
 */
bool message_box_is_sendable(message_box_t *box);

/** \fn message_box_send
 * This function send data to message box.
 * @*box Message box to work on
 * @*data Data to send
 */
void message_box_send(message_box_t *box, void *data);

/** \fn message_box_show
 * This function return info which is save in message box.
 * @*box Message box to work on
 */
void* message_box_show(message_box_t *box);
 
/** \fn message_box_receive 
 * This function receive data from message box.
 * @*box Message box to work on
 */
void* message_box_receive(message_box_t *box);

#endif

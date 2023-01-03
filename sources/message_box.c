#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>
#include "message_box.h"

/** \fn message_box_create
 * This prepare new message box to work.
 * @*box Message box to work on
 */
void message_box_create(message_box_t *box) {
    box->readable = false;
    box->message = NULL;
}

/** \fn message_box_is_readable
 * This check and return true if message box is readable or false if not.
 * @*box Message box to work on
 */
bool message_box_is_readable(message_box_t *box) {
    return box->readable;
}

/** \fn message_box_is_sendable
 * This check and return true if message box is sendable or false if not.
 * @*box Message box to work on
 */
bool message_box_is_sendable(message_box_t *box) {
    return !box->readable;
}

/** \fn message_box_send
 * This function send data to message box.
 * @*box Message box to work on
 * @*data Data to send
 */
void message_box_send(message_box_t *box, void *data) {
    box->readable = true;
    box->message = data;
}

/** \fn message_box_show
 * This function return info which is save in message box.
 * @*box Message box to work on
 */
void* message_box_show(message_box_t *box) {
    return box->message;
}

/** \fn message_box_receive 
 * This function receive data from message box.
 * @*box Message box to work on
 */
void* message_box_receive(message_box_t *box) {
    box->readable = false;
    return box->message;
}

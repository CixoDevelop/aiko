/*
 * This project is Aiko, an operating system for weak devices like 
 * microcontrollers. It has support for devices based on eight-bit 
 * architectures. It is suitable even for devices with only 128 bytes 
 * of operational memory. You can make it easier to code your projects 
 * based on such platforms by using Aiko as a scheduler.
 *
 * Author: Cixo
 */

#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include "process.h"
#include "message_box.h"
#include "numbers.h"
#include "kernel.h"

/** \fn kernel_create 
 * This create instance of kernel.
 * @param *kernel Kernel instance to work on
 * @paran size Size of processes array
 */
void kernel_create(kernel_instance_t *kernel, uint_t size) {
    if (size > MAX_PID_VALUE) size = MAX_PID_VALUE;

    kernel->processes = malloc(sizeof(process_t) * size);
    kernel->size = size;
    kernel->last_changed = ERROR_PID;

    for (kernel_pid_t count = 0x00; count < size; ++count) {
        process_create(kernel->processes + count);
    }
}

/** \fn kernel_create_static 
 * This create kernel, but use static memory instead allocated by maloc.
 * @param *kernel Kernel instance to work on
 * @param *processes Static process table address
 * @param size Size ot process table address
 */
void kernel_create_static(
    kernel_instance_t *kernel, 
    process_t *processes, 
    uint_t size
) {
    if (size > MAX_PID_VALUE) size = MAX_PID_VALUE;

    kernel->processes = processes;
    kernel->size = size;
    kernel->last_changed = ERROR_PID;

    for (kernel_pid_t count = 0x00; count < size; ++count) {
        process_create(kernel->processes + count);
    } 
}

/** \fn kernel_remove
 * This function remove kernel instance and dealocate memory.
 * @param *kernel Kernel instance to work on
 */
void kernel_remove(kernel_instance_t *kernel) {
    kernel->size = 0x00;
    free(kernel->processes);
}

/** \fn kernel_remove_static
 * This function remove kernel instance created by kernel_create_static.
 * @param *kernel Kernel instance to work on
 */
void kernel_remove_static(kernel_instance_t *kernel) {
    kernel->size = 0x00;
}

/** \fn kernel_standard_scheduler
 * This function run standard scheduler if any process is not marked to 
 * executed.
 * @param *kernel Kernel instance to work on
 */
static inline void kernel_standard_scheduler(kernel_instance_t *kernel) {
    for (kernel_pid_t count = 0; count < kernel->size; ++count) {
        process_t *current = kernel->processes + count;

        if (current->type == EMPTY) continue;
        if (
            current->type != CONTINUOUS &&
            !message_box_is_readable(current->message)
        ) continue;
            
        current->worker(kernel, current);
    }
}

/** \fn kernel_marked_scheduler
 * This run scheduler when any process had been market do execute on first
 * kernel loop.
 * @param *kernel Kernel to work on
 */
static inline void kernel_marked_scheduler(kernel_instance_t *kernel) {
    kernel_pid_t last_changed = kernel->last_changed;

    kernel->last_changed = ERROR_PID;
    process_t *current = kernel->processes + last_changed;

    if (current->type == EMPTY) return;

    current->worker(kernel, current);
}

/** \fn kernel_scheduler
 * This is main system loop. When You call them, it would not return. Also
 * if it return, that means any error was corrupted.
 * @param *kernel Kernel instance to work on
 */
void kernel_scheduler(kernel_instance_t *kernel) {
    while (true) {
        if (kernel->size == 0x00) return;

        if (kernel->last_changed != ERROR_PID) {
            kernel_marked_scheduler(kernel);      
            continue;
        }
        
        kernel_standard_scheduler(kernel);        
    }
}

/** \fn kernel_get_empty_pid
 * This function search and return first empty pid in array.
 * @param *kernel Kernel instance to work on
 * @return Empty pid for new process
 */
kernel_pid_t kernel_get_empty_pid(kernel_instance_t *kernel) {
    for (kernel_pid_t count = 0x00; count < kernel->size; ++count) {
        if ((kernel->processes + count)->type == EMPTY) return count;
    }

    return ERROR_PID;
}

/** \fn kernel_create_process
 * This will create new process in system from given params.
 * @param *kernel Kernel instance to work on
 * @param process_pid Pid of new process
 * @param type Type of new process
 * @param (*worker)(...) Process worker, process main function
 * @param *parameter Parameter to worker
 */
void kernel_create_process(
    kernel_instance_t *kernel,
    kernel_pid_t process_pid,
    process_type_t type,
    void (*worker)(kernel_instance_t *, process_t *),
    void *parameter
) {
    if (process_pid >= kernel->size) return;
    
    process_t *process = kernel->processes + process_pid;

    process_create(process);

    process->type = type;
    process->parameter = parameter;
    
    process->worker = (void (*)(void *, void *)) (worker);

    if (type == CONTINUOUS) kernel->last_changed = process_pid;
}

/** \fn kernel_kill_process
 * This function kill process which given pid.
 * @param *kernel Kernel instance to work on
 * @param process_pid Pid of process to kill
 */
void kernel_kill_process(
    kernel_instance_t *kernel,
    kernel_pid_t process_pid
) {
    if (process_pid >= kernel->size) return;

    (kernel->processes + process_pid)->type = EMPTY;
}

#define FILLED (!kernel_is_process_message_box_sendable(kernel, count))
#define PROCESS_SIGNAL (kernel_process_message_box_show(kernel, count))
#define CURRENT_PRIORITY_HIGHER (PROCESS_SIGNAL >= signal_as_pointer)

/** \fn kernel_trigger_signal
 * This function trigger signal in operating system.
 * @param *kernel Kernel instance to work on
 * @param signal Signal to trigger
 */
void kernel_trigger_signal(kernel_instance_t *kernel, uintptr_t signal) {
    void* signal_as_pointer = (void *)signal;

    for (kernel_pid_t count = 0x00; count < kernel->size; ++count) {
        if ((kernel->processes + count)->type != SIGNAL) continue;
        if (FILLED && CURRENT_PRIORITY_HIGHER) continue;

        kernel_process_message_box_send(kernel, count, signal_as_pointer);
    }
}

#undef FILLED 
#undef PROCESS_SIGNAL 
#undef CURRENT_PRIORITY_HIGHER 

/** \fn kernel_sum_signal
 * This function logical sum current send signal, and new signal, then project
 * can use all of bits as diferent signals, and then all of it can be 
 * tiggered in same time without overwrite.
 * @param *kernel Kernel instance to work on
 * @param signal Signal to add
 */
void kernel_sum_signal(kernel_instance_t *kernel, uintptr_t new_signal) {
    void* signal_to_add = (void *)new_signal;

    for (kernel_pid_t count = 0x00; count < kernel->size; ++count) {
        if ((kernel->processes + count)->type != SIGNAL) continue;
        
        if (kernel_is_process_message_box_sendable(kernel, count)) {
            kernel_process_message_box_send(kernel, count, signal_to_add);
            continue;
        }

        uintptr_t compared_signal = (uintptr_t)signal_to_add;
        compared_signal |= (uintptr_t)(
            kernel_process_message_box_show(kernel, count)
        );

        kernel_process_message_box_send(
            kernel, 
            count, 
            (void*)compared_signal
        );
    }
}

/** \fn kernel_is_process_message_box_sendable
 * This function check if process message box is ready to receive new data.
 * @param *kernel Kernel instance to work on
 * @param process_pid Pid of process to check
 * @return This return process message box state
 */
bool kernel_is_process_message_box_sendable(
    kernel_instance_t *kernel,
    kernel_pid_t process_pid
) {
    if (process_pid >= kernel->size) return false;

    return message_box_is_sendable(
        (kernel->processes + process_pid)->message
    );
}

/** \fn kernel_process_message_box_show
 * This function show value in message box for process which have specified 
 * process id
 * @param *kernel Kernel instance to work on
 * @param process_pid Pid of process to show
 * @return Current content of process message box
 */
void* kernel_process_message_box_show(
    kernel_instance_t *kernel, 
    kernel_pid_t process_pid
) {
    if (process_pid >= kernel->size) return 0x00;

    return message_box_show((kernel->processes + process_pid)->message);
}

/** \fn kernel_process_message_box_send
 * This function send data to message box of process with given pid.
 * @param *kernel Kernel instance to work on
 * @param process_pid Pid of process to send
 * @param *data Data to send
 */
void kernel_process_message_box_send(
    kernel_instance_t *kernel,
    kernel_pid_t process_pid,
    void *message
) {
    if (process_pid >= kernel->size) return;

    message_box_send(
        (kernel->processes + process_pid)->message,
        message
    );
}

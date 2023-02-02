#ifndef AIKO_KERNEL_H_INCLUDED
#define AIKO_KERNEL_H_INCLUDED

#include "process.h"
#include "message_box.h"
#include "numbers.h"

/** \typedef pid_t 
 * This type store process id in system.
 */
typedef uint_t kernel_pid_t;

/** \def MAX_PID_VALUE
 * This define max value of pid that can be used.
 */
#define MAX_PID_VALUE ((MAX_UINT_VALUE) - 1)

/** \def ERROR_PID
 * This define pid that means error.
 */
#define ERROR_PID MAX_UINT_VALUE

/** \struct kernel_instance_t
 * This struct store instance of kernel in system.
 */
typedef struct {
    
    /* This store address to first element of processes array */
    process_t *processes;
    
    /* This store size of processes array */
    kernel_pid_t size;

    /* This store process that will be executed next */
    kernel_pid_t last_changed;

} kernel_instance_t;

/** \fn kernel_create 
 * This create instance of kernel.
 * @*kernel Kernel instance to work on
 * @size Size of processes array
 */
void kernel_create(kernel_instance_t *kernel, uint_t size);

/** \fn kernel_create_static 
 * This create kernel, but use static memory instead allocated by maloc.
 * @*kernel Kernel instance to work on
 * @*processes Static process table address
 * @size Size ot process table address
 */
void kernel_create_static(
    kernel_instance_t *kernel, 
    process_t *processes, 
    uint_t size
);

/** \fn kernel_remove
 * This function remove kernel instance and dealocate memory.
 * @*kernel Kernel instance to work on
 */
void kernel_remove(kernel_instance_t *kernel);

/** \fn kernel_remove_static
 * This function remove kernel instance created by kernel_create_static.
 * @*kernel Kernel instance to work on
 */
void kernel_remove_static(kernel_instance_t *kernel);

/** \fn kernel_scheduler
 * This is main system loop. When You call them, it would not return. Also
 * if it return, that means any error was corrupted.
 * @*kernel Kernel instance to work on
 */
void kernel_scheduler(kernel_instance_t *kernel);

/** \fn kernel_get_empty_pid
 * This function search and return first empty pid in array.
 * @*kernel Kernel instance to work on
 */
kernel_pid_t kernel_get_empty_pid(kernel_instance_t *kernel);

/** \fn kernel_trigger_signal
 * This function trigger signal in operating system.
 * @*kernel Kernel instance to work on
 * @signal Signal to trigger
 */
void kernel_trigger_signal(kernel_instance_t *kernel, uint_t signal);

/** \fn kernel_generate_signal_parameter
 * This generate param for process from signal.
 * @signal Signal to generate from
 */
void* kernel_generate_signal_parameter(uint_t signal);

/** \fn kernel_create_process
 * This will create new process in system from given params.
 * @*kernel Kernel instance to work on
 * @process_pid Pid of new process
 * @type Type of new process
 * @(*worker)(...) Process worker, process main function
 * @*parameter Parameter to worker
 */
void kernel_create_process(
    kernel_instance_t *kernel,
    kernel_pid_t process_pid,
    process_type_t type,
    void (*worker)(kernel_instance_t *, process_t *),
    void *parameter
);

/** \fn kernel_kill_process
 * This function kill process which given pid.
 * @*kernel Kernel instance to work on
 * @process_pid Pid of process to kill
 */
void kernel_kill_process(
    kernel_instance_t *kernel,
    kernel_pid_t process_pid
);

/** \fn kernel_is_process_message_box_sendable
 * This function check if process message box is ready to receive new data.
 * @*kernel Kernel instance to work on
 * @process_pid Pid of process to check
 */
bool kernel_is_process_message_box_sendable(
    kernel_instance_t *kernel,
    kernel_pid_t process_pid
);

/** \fn kernel_process_message_box_send
 * This function send data to message box of process with given pid.
 * @*kernel Kernel instance to work on
 * @process_pid Pid of process to check
 */
void kernel_process_message_box_send(
    kernel_instance_t *kernel,
    kernel_pid_t process_pid,
    void *message
);

/** \fn kernel_process_message_box_show
 * This function show value in message box for process which have specified 
 * process id
 * @*kernel Kernel instance to work on
 * @process_pid Pid of process to show
 */
void* kernel_process_message_box_show(
    kernel_instance_t *kernel, 
    kernel_pid_t process_pid
);

#endif

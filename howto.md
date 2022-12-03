# Let's start!

Aiko is not a complicated library, its learning is very simple and fast. The 
first thing you need to remember is that your processes must be fast. They 
must return quickly because they are not being dispossessed. It is better to 
have more processes than processes that take longer. Processes should use 
inboxes to exchange data. They are used by Aiko to decide what process to 
perform next. So remember: Small short functions, data exchange using inboxes.


## Process types in Aiko

Of course, apart from the processes that will be called when their box 
receives new data (REACTIVE), there are also processes that will be executed 
every time the processor has a free moment (CONTINUOUS), as well as those that 
will be executed during some event (SIGNAL).


## Beginning of programming in Aiko

First, include the header files:
 * aiko.h - Imports all Aiko header files
 * aiko/process.h - Imports process structure only.
 * aiko/kernel.h - Imports kernel functions and kernel structure only.
 * aiko/message_box.h - Imports the structure and functions needed for 
   the box to work.


Then it's downhill, you will need the kernel structure:

// To reference items with "&" and items with "."
kernel_instance_t kernel;
// To refer by name and items by "->"
kernel_instance_t kernel[1];


The kernel exists from initialization until deletion. You can initialize the 
kernel dynamically using the malloc instruction and the destructor calls free. 
This is different with static init, where it is your job to provide memory for
the process table. The advantage of this method is that you don't need to 
implement malloc in your environment.


Dynamic initialization:

// The kernel does not exist yet
kernel_create(kernel, 10 /* process table size */); // Or &
// The kernel exists, you can add processes and run it
kernel_remove(kernel);
// The kernel has been removed and is no longer usable unless reinitialized


Static initialization:

// The kernel does not exist yet
process_t processes[10 /* Array size */];
kernel_create_static(kernel, processes, 10 /* process table size */); // Or &
// The kernel exists, you can add processes and run it
kernel_remove_static(kernel);
// The kernel has been removed and is no longer usable unless reinitialized


## Creating a process

A process is nothing more than a void function that takes as arguments:
 * kernel_instance_t * - The kernel that the process calls
 * kernel_pid_t - ID of the currently running process
 * message_box_t * - Box of the currently running process
 * void * - The parameter that was passed when creating the process

So, create a function, for example:

void process(
    kernel_instance_t *kernel, 
    kernel_pid_d pid, 
    message_box_t *message, 
    void *parameter
) {
}


Once the process body has been created, the next step is to add it to the 
kernel array with the kernel_create_process instruction. It takes the 
following parameters:
 * kernel_instance_t * - Kernel instance to which the process will be added
 * kernel_pid_t - ID the new process should get
 * process_type_t - The type of the new process
 * void (*) (...) - Address of the body (process function)
 * void * - Parameter for the process


For example:

kernel_create_process(kernel, 0x00, REACTIVE, process, NULL);


Now you have a single process waiting for data in the inbox.


You can also remove a process from the list of processes with the 
kernel_kill_process command, which takes the following parameters:
 * kernel_instance_t * - The instance from which the process will be removed
 * kernel_pid_t - ID of the process to be removed
For example:
kernel_kill_process(kernel, 0x00);


## How process IDs work

Of course, it's nothing complicated, it's just an individual numeric process 
label. Only one process with a given ID can exist in the process table, the 
lower the ID, the higher the priority of the process. If you want to 
automatically get a free process ID, call kernel_get_empty_pid, which returns 
the available process ID and takes as parameters:
 * kernel_instance_t * - The kernel instance in which it is looking for a 
   free ID.


## Using signals in the system

Signals is a special process synchronization option. The process will be 
suspended until the same signal it is waiting for is triggered in the system 
then each process waiting for such a signal will be executed in turn. Note
the signal cannot be zero. In order for the process to wait for a signal, give
it a SIGNAL type, and set as a parameter what the 
kernel_generate_signal_parameter function returned, which takes as a 
parameter:
 * uint_t - Signal number


For example:

kernel_create_process(
    kernel, 
    0x00, 
    SIGNAL, 
    process, 
    kernel_generate_signal_parameter(0x20)
);


Now to trigger this signal call: kernel_trigger_signal which takes as 
parameters:
 * kernel_instance_t * - The kernel instance in which the trigger 
   will be triggered
 * uint_t - Signal to trigger


## Sending information using mailboxes to recipients

Inboxes are a simple mechanism, it consists in the fact that after sending 
some information, the inbox sets the busy flag to true, it can be read from 
it, but it cannot be written to. Then the kernel will find the process that 
received the information and execute it. This should receive the information
the box will set the flag, the process will set to false, you can write to 
it but you can't read from it. The process to which it belongs will receive 
the information and process it.


You can use the following functions to directly interact with the mailbox:
  * message_box_is_readable - Checks whether the box is readable
  * message_box_is_sendable - Checks whether it is possible to write to the 
    mailbox
  * message_box_send - Send data to the box
  * message_box_receive - Will receive data from the box


Attention, the received data is of type void *, but it is possible to transfer
the pointer to any object in this way, or a number of type uintptr_t.


To send data to process inboxes you can use kernel function:
  * kernel_is_process_message_box_sendable - Checks if it can be sent to the 
    process inbox
  * kernel_process_message_box_send - Sends data to the process inbox


The specification of the next functions is as follows

message_box_is_sendable:
  * message_box_t * - The box he is working on


message_box_is_readable:
  * message_box_t * - The box he is working on


message_box_is_send:
  * message_box_t * - The box he is working on
  * void * - Data to be sent


message_box_receive:
  * message_box_t * - The box he is working on


kernel_is_process_message_box_sendable
  * kernel_instance_t * - The box it is working on
  * kernel_pid_t - ID of the process to work on


kernel_process_message_box_send
  * kernel_instance_t * - The box it is working on
  * kernel_pid_t - ID of the process to work on
  * void * - Data to be sent


## Other important data

Generally, Aiko uses unsigned int by default, but you can use uint8_t on 
platforms that have problems when processing larger data. To do this, use 
the -DAIKO_SHORT_NUMBERS switch during compilation, remember that you must 
also add it to the compilation of your project and not only to the compilation
of the library.


## Good luck!

After reading this guide, you should be able to create interesting projects 
with Aiko without any problems!

# Change Log

## 2023-04-04
 * Fix comments to improve support with doxygen.
 * Remove kernel_generate_signal_parameter, and change kernel signal format
   to uintptr_t. Now project can use simple numbers, without generating 
   signal parameter with function.

## 2023-03-27
 * Add kernel_sum_signal, that can logical sum signal, to not lose all of
   signals, when more than one had been corrupted in same time.

## 2023-02-02
 * Change process call, to two parameters, kernel and process. Process object
   given to worker, is current process. Worker can change whatever want.

## 2023-01-03
 * Add signal priority: when signal handles have not been done, then signal 
   would be override by new triggered signal, if that has higher priotity.
   Higher signal number has higher priority.
 * Add option for get data from message box without change sendable flag.

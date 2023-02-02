# Change Log

## 2023-02-02
 * Change process call, to two parameters, kernel and process. Process object
   given to worker, is current process. Worker can change whatever want.

## 2023-01-03
 * Add signal priority: when signal handles have not been done, then signal 
   would be override by new triggered signal, if that has higher priotity.
   Higher signal number has higher priority.
 * Add option for get data from message box without change sendable flag.

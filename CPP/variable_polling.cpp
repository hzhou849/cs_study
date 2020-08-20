In embedded systems, there are several methods to be notified when a variable changes:

Poll -- have some background code that monitors the variable and executes an associated function (via pointer) when the variable changes.
RTOS Mechanism -- Associate the variable with a semaphore, mutex or message queue.
Interrupt -- Maybe your variable is an interrupt register of some hardware device or you will get interrupted when a hardware registers is modified.
For polling, your best solution is to assign a pointer to the memory address and set the pointer to point to a volatile item. You may want to use a sleep function call so as not to hog all the processor time.

# Aiko lightweight powerful operating system

## What is Aiko?

Aiko is a small open source operating system for managing asynchronous 
functions. It does not preserve the context of the process, nor does it 
expropriate. However, it allows you to create asynchronous processes that 
are called when they receive a message, similar to what happens in Elixir. 
Your process is a function that works on what it gets in the inbox, it can 
call other functions, send information to other people's inboxes or work 
with hardware. After completing the routine, he returns with a return 
statement, and Aiko decides what next function he should call.


## Aiko is out of context. What if I need to keep the context?

Don't worry about it, you can just use Aiko inside Linux or FreeRTOS as a 
process of those systems and they will take care of properly managing the 
context of those processes that require it.


## Why else should I consider Aiko?
  * It is stable, the processes are extremely easy to test.
  * It is easy to implement in existing projects.
  * It is extremely lightweight, fits on almost all microcontrollers.


## You convinced me. How can I use Aiko?
  * Clone this repository to your project's library directory.
  * Build Aiko, which one you should build depends on your compiler and 
    environment, but you'll find the appropriate build-[platform] directory. 
    Enter it and execute build.sh. A libaiko.a file will be created, this is 
    the library you need to add to your project.
  * Now also add the headers that are in the headers directory.
  * Congratulations, you are ready to start programming!

## How to program using Aiko?
  * If you like to learn by example, see project with tests [there](https://github.com/CixoDevelop/aiko-tests).
  * If you prefer tutorials, read howto.md.
  * When you read howto.md, you can also read source code and docs.

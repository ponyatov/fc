# bytecode
### байт-код

- https://habr.com/ru/companies/badoo/articles/425325/
- https://habr.com/ru/companies/badoo/articles/428878/
- https://habr.com/ru/articles/757998/
- [[vm/Virtual Machine Showdown Stack Versus Registers]]

## advantages of bytecode over native machine code

https://stackoverflow.com/questions/48144/what-are-advantages-of-bytecode-over-native-code

- **slower than native code**
  - as it requires @ref vm for bytecode execution (interpretation)
+ **unlimited control of execution** and **security**
  - due to software interpretation
+ **portability**
  + same binary can be used on any hardware in case of
    + platform-independent command set and 
    + **[[#hardware isolation]]**: every `.bc` program runs in its own address space (virtual @ref M emory)
    + **I/O virtualization**: no hardware i/o or real memory available directly
+ **size in memory**
  - much more compact if stack machine architecture was used: only opcodes and short addresses
  - commands encoding does not spend memory on arguments and registers selection
+ **unlimited variations of VM architecture**
  - you can select any mechanics and features of your own @ref vm
  - you don't limited to use mainstream (and heavy) arch/infrastructure such as [[JVM]]
  - any command set and program format, register/stack/mem2mem arch, messaging, custom commands for signal and [graphics](md_doc_graphics.html) processing, software multitasking,..

## stack architecture

- **stack-based architecture** keeps instructions compact (no register operands).
- single-byte opcode and unaligned variable size commands allows **the most compact code**

## hardware isolation

- 16-bit @ref addr esses is enough for MCU-specific domains but makes control transfer commands 2x shorter
- every bytecode process runs in its own virtual @ref M emory

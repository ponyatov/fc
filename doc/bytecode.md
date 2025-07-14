# bytecode
### байт-код
also: [[Rust/VM|VM]]

- https://habr.com/ru/companies/badoo/articles/425325/
- https://habr.com/ru/companies/badoo/articles/428878/
- https://habr.com/ru/articles/757998/
- [[vm/Virtual Machine Showdown Stack Versus Registers]]

## advantages of bytecode over native machine code
https://stackoverflow.com/questions/48144/what-are-advantages-of-bytecode-over-native-code
- **slower then native code** <br> as it requires [[VM]] for its execution (interpretation)
+ **unlimited control of execution** and **security** <br> due to software interpretation
+ **portability**
+ **size in memory** <br> much more compact if stack machine architecture was used -- only opcodes and short addresses, commands encoding does not spend memory on arguments and registers selection
+ **unlimited variations of VM architecture** <br> you can select any mechanics and features of your own [[VM]] (if you don't limited to use mainstream infrastructure such as [[JVM]]) -- any command set and program format, register/stack/mem2mem arch, messaging, custom commands for signal and graphics processing, software multitasking,..

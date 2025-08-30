# A turn-based combat simulator in C++
This project is intended to implement a traditional action-value algorithm used in many turn-based RPGS and gradually expand upon it. Currently, this project is powered by [fmt](https://github.com/fmtlib/fmt) for log formatting and [catch2](https://github.com/catchorg/Catch2) as a testing framework.

## dev roadmap

### the absolute bare minimum
- [X] basic engine functionality
- [X] style consistency
- [X] comments
- [X] use header files properly

### have actually useful functionality and good practices
- [ ] more complex combat system
	- [X] effects
	- [X] damage calculator
	- [ ] armor system
	- [ ] stat balance system
- [X] console logs
- [X] unit tests
- [X] refactor to actually make use of c++ (iterators, lambdas, references, etc.)
- [X] implement entity-component-system
- [ ] bounded character stats & default values
- [ ] use constants
- [ ] normalize naming scheme

#### running todo list
- move effect log messages to their own function implementations
- fix redundancy in defining curr_health and max_health
- make master effects header
- update unit tests to use new damage systems
- implement armor and on-hit effects

# A turn-based combat simulator in C++
This project is intended to implement a traditional action-value algorithm used in many turn-based RPGS and gradually expand upon it. Currently, this project is powered by [fmt](https://github.com/fmtlib/fmt) for log formatting and [catch2](https://github.com/catchorg/Catch2) as a testing framework.

## dev roadmap

### the absolute bare minimum
- [X] basic engine functionality
- [X] style consistency
- [X] comments
- [X] use .h files properly

### have actually useful functionality and good practices
- [ ] more complex combat system
	- [X] effects
	- [ ] damage calculator
	- [ ] armor system
	- [ ] stat balance system
- [X] console logs
- [X] unit tests
- [X] refactor to actually make use of c++ (iterators, lambdas, references, etc.)
- [ ] bounded character stats & default values

### more advanced features (lock in)
- [ ] start using pull requests for individual features
- [ ] castorice global passive
- [ ] rpg class system
- [ ] playable interface
- [ ] save logs to file
- [ ] pseudo-api for character functionality w/ documentation
- [ ] write a devblog about this

#### running todo list 
- implement constants file
- decide on putting names or not in constants file
- move effect log messages to their own function implementations
- fix redundancy in defining curr_health and max_health
- make master effects header
- standardize naming scheme
- use numerical limits
- update unit tests to use new damage systems
- implement armor and on-hit effects

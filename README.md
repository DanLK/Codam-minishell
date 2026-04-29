*This project has been created as part of the 42 curriculum by rojornod and dloustal*

# Minishell

This project is a [shell](https://en.wikipedia.org/wiki/Shell_(computing)) written in C.

## Description

Our shell works in interactive mode and simulates a Bash Shell. It has a working history, and handles basic functionalities, like:

- Single and double quotes
- Redirections <, >, <<, >>
- Pipes (|)
- Environment variables
- $? for a command status
- Signals ```ctrl-C```, ```ctrl-D``` and ```ctrl-\```
- The following built-in commands:
	- ```echo``` with the option ```-n```
	- ```cd``` with only a relative or absolute path
	- ```pwd``` with no options
	- ```export``` with no options
	- ```unset``` with no options
	- ```env``` with no options or arguments
	- ```exit``` with no options

## Instructions

To run, from the ```minishell``` sub-directory make the project with ```make```. Then run as ```./minishell```. 


## Resources

Our shell is a Bash Shell, so the functionalities are based on the [Bash manual](https://www.gnu.org/savannah-checkouts/gnu/bash/manual/).
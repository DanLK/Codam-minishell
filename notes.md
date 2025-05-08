## GIT

- [A guide to collaborating with Github](https://medium.com/@jonathanmines/the-ultimate-github-collaboration-guide-df816e98fb67)

## BASH

- [Bash manual](https://www.gnu.org/savannah-checkouts/gnu/bash/manual/)
- [Minishell 42 article](https://m4nnb3ll.medium.com/minishell-building-a-mini-bash-a-42-project-b55a10598218)

## Linux file system 

- [Linux filesystem video](https://www.youtube.com/watch?v=P0QZnAnsQ4c&list=PLvrGkX6pcHIC8-UKfChyYGcQtvJtniH3c&index=4)
- [Linux filesystem video -- faster](https://www.youtube.com/watch?v=A3G-3hp88mo)

## Readline 

- [Programming with GNU Readline](https://web.mit.edu/gnu/doc/html/rlman_2.html)

## Redirections

- [Redirections info](https://megamorf.gitlab.io/cheat-sheets/cheat-sheet-bash-redirections/)

## Prompt examples

- `echo "Hello"`
- `echo "Hello" > output.txt`
- `cat < input.txt`
- `echo "Hello" >> output.txt`
- `cat << EOF` (with input until EOF is entered)
- `echo "Hello" | cat`
- `cd /usr && pwd`
- `cd .. && pwd`
- `export MYVAR="Hello" && echo $MYVAR`
- `unset MYVAR && echo $MYVAR`
- `echo $?`
- `echo "Hello $USER"`
- `export PATH="/usr/bin:$PATH" && env | grep PATH`
- `echo "Hello" | echo "Ignored"`
- `echo "Hello" > file.txt && cat < file.txt`
- `echo "Hello" > file.txt && cat file.txt | echo "Output ignored"`

1. Redirections with Pipes

    ```
	echo "Hello" > file.txt && cat < file.txt | echo "Ignored"
    echo "Line 1" > file.txt && echo "Line 2" >> file.txt && cat < file.txt
    echo "Hello" > file.txt && cat < file.txt | echo $? > status.txt
    export MYVAR="Test" && echo $MYVAR > file.txt && cat < file.txt | echo $?
    echo "Hello" > file.txt && echo "World" >> file.txt && cat < file.txt | echo $? >> status.txt
	```

2. Here-Document (<<) with Pipes

	```
    cat << EOF | echo "Processing" (followed by input, ends with EOF)
    cat << STOP | echo "Received input" (followed by input, ends with STOP)
    cat << END | env | grep PATH (followed by input, ends with END)
    cat << DONE | echo $? (followed by input, ends with DONE)
    cat << DATA | export VAR="Hello" && echo $VAR (followed by input, ends with DATA)
	```

	Just heredoc
	```
	cat <<EOF > myfile.txt
	[database]
	user=admin
	password=secret
	host=localhost
	EOF
	```
	
3. Pipes and Environment Variables

	```
    export MYVAR="Hello" && echo $MYVAR | cat
    export MYVAR="Test" && echo $MYVAR | echo $?
    export PATH="/usr/bin:$PATH" && env | grep PATH | echo "Path Updated"
    echo "Hello" | env | grep PATH
    export USERNAME="User" && echo "Welcome, $USERNAME" | echo $? > status.txt
	```

4. Combining Built-ins with Redirections and Pipes

	```
    pwd | echo "Current directory ignored"
    pwd > path.txt && cat < path.txt
    cd /usr && pwd | echo "Changed directory"
    cd .. && pwd | echo $? > status.txt
    export TEMP="Data" && echo $TEMP > temp.txt && cat < temp.txt | echo $?
	```


# BUILTINS SYNTAX

- echo

- cd

	Accepts exactly one parameter

- pwd

	Accepts more parameters and just ignores them

- export (with no options)

	With no arguments it displays all the exported variables

	```export name[=value]``` Meaning it can have one TKN_WORD as an argument or [TKN_WORD, EQUAL, TKN_WORD] 

- unset

	```unset var_name_here``` if there is no ```var_name``` then it does nothing. It can take multiple varnames to unset



## Special cases

- ```echo -n -n -n```



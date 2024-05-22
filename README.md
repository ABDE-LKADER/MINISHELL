# Minishell

Minishell is a 42 school project that involves reimplementing a "mini" bash terminal. In this project, I've re-implemented the following built-in functions:


## Installation 

To create the executable, navigate to the root folder of the project and use the following command:

```bash
  make
```

Then, you can run the program with:

```bash
  ./minishell
```


## Your shell should:

* Display a prompt when waiting for a new command.
* Have a working history.
* Search and launch the right executable (based on the PATH variable or using arelative or an absolute path).


> **Note:** Avoid using more than one global variable to indicate a received signal. Con the implications: this approach ensures that your signal handler will not access yourin data structures.
Be careful. This global variable cannot provide anyoth information or data access than the number of a received signal.
Therefore, using "norm" type structures in the global scope is forbidden.


# Mandatory Part
### Minishell As Beautiful As a Shell

* Not interpret unclosed quotes or special characters which are not required by the subject such as \ (backslash) or ; (semicolon).
* Handle ’ (single quote) which should prevent the shell from interpreting the metacharacters in the quoted sequence.
* Handle " (double quote) which should prevent the shell from interpreting the metacharacters in the quoted sequence except for $ (dollar sign).
* Implement redirections:
* < should redirect input.
* > should redirect output.
* << should be given a delimiter, then read the input until a line containing the
delimiter is seen. However, it doesn’t have to update the history!
* >> should redirect output in append mode.
* Implement pipes (| character). The output of each command in the pipeline is
connected to the input of the next command via a pipe.
* Handle environment variables ($ followed by a sequence of characters) which
should expand to their values.
* Handle $? which should expand to the exit status of the most recently executed
foreground pipeline.
* Handle ctrl-C, ctrl-D and ctrl-\ which should behave like in bash.
* In interactive mode:
* ctrl-C displays a new prompt on a new line.
* ctrl-D exits the shell.
* ctrl-\ does nothing.
* Your shell must implement the following builtins:
* echo with option -n
* cd with only a relative or absolute path
* pwd with no options
* export with no options
*  unset with no options
*  env with no options or arguments
*  xit with no options

The readline() function can cause memory leaks. You don’t have to fix them. But
that doesn’t mean your own code, yes the code you wrote, can have memory
leaks.
You should limit yourself to the subject description. Anything that
is not asked is not required.
If you have any doubt about a requirement, take bash as a reference.

# Bonus part

Your program has to implement:
• && and || with parenthesis for priorities.
• Wildcards * should work for the current working directory.
The bonus part will only be assessed if the mandatory part is
PERFECT. Perfect means the mandatory part has been integrally done
and works without malfunctioning. If you have not passed ALL the
mandatory requirements, your bonus part will not be evaluated at all.

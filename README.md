# pipex
A program reproducing the pipe feature from bash in C

### Installation
- Clone the repository
- Use the terminal command ``make`` to compile everything

### Usage
Pipex does the exact same thing as this command:  
``< input_file command1 | command2 output_file >``

But formatted as below:  
``./pipex input_file "command1" "command2" output_file``

### Examples
Once compiled, you can try the program by using this command:  
```./pipex Makefile "cat -e" "head -10" 10_first_lines.txt```  
It should output the 10 first lines of Makefile with a $ at the end of each line into a new file called **10_first_lines.txt**.

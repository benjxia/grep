## Grep
A simplified version of the UNIX command utility, adapted for Windows because I was bored.
<br>
### Usage: <br>
`grep <-c> <-r> <query> <query> <query> ... <search_directory_or_file>`
<br>
`-c` flag: Search case-sensitive (optional)
<br>
`-r` flag: Search specified directory recursively (optional). If `grep` is passed a directory and `-r` is not given, 
the program will search the directory's files but not any nested directories.
<br>
`<query>` Patterns to search in specified directory or file, any number of queries is valid.
<br>
`<search_directory_or_file>` Relative path to file or directory to search for pattern(s).
<br>
**Note: the final argument to the program must be the search directory/file**

# File module

Functions to help with reading words, lines, and files.

See `files.h` for a complete and up-to-date documentation about these functions.

## lines_in_file
To return the number of lines in a file.

```c
int lines_in_file(FILE *fp);
```

## readfilep
Read the rest of the input file and return a pointer to a malloc'd buffer holding all the characters.

```c
char *readfilep(FILE *fp);
```

## readlinep
Read a line of input and return a pointer to a malloc'd buffer holding the characters of that line.

```c
char *readlinep(FILE *fp);
```

## readwordp
Read a word of input and return a pointer to a malloc'd buffer holding the characters of that word.

```c
char *readwordp(FILE *fp);
```

## readuntil
A general-purpose function to read characters into a buffer, and return a pointer to that buffer, until a matching "stop" character is found.  Unlikely to be used by external users of the module.

```c
char *readuntil(FILE *fp, int (*stopfunc)(int c) );
```

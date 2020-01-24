README for subtemplate.c example
My Name, January 2020

Compiling:
	mygcc -o subtemplate subtemplate.c

Usage:
/* 
 * subtemplate.c - substitute text into a template file
 * 
 * usage: subtemplate target replacement
 * where:
 *   target is a string to be replaced wherever it appears in the input;
 *   replacement is a filename for file containing replacement text
 * output:
 *   read the stdin, copying it to stdout, but wherever the 
 *   target text is found, replace it with the contents of the 
 *   replacement file.
 * stdin: the input template
 * stdout: the modified template
 * stderr: error messages
 *
 * My Name, January 2020
 */

Example command lines:

  cat header.template | ./subtemplate TITLE title.txt 
  cat header.template | ./subtemplate TITLE title.txt  | ./subtemplate HEADCAPTION header.txt 

Exit status:
  0 - success
  1 - incorrect number of arguments
  2 - bad target string
  3 - cannot open replacement file
  4 - error during input

Assumptions:

- replacement files should not contain subsequent target strings,
  except where desired; in the second example above, if title.txt
  contains @HEADCAPTION@ it will be replaced by the second
  subtemplate; but if header.txt contains @TITLE@ it will not be
  replaced; this assumption imposes order on the pipeline, and may or
  may not lead to desired behavior.

"Non"-Assumptions:

- stdin and replacement file need not end with a newline
- stdin and replacement file may contain any characters
- target string may contain any characters (other than null, of course)
- target string may occur multiple times on a line, or in the file

Limitations:

- certain types of target strings will fail; for example, target
  "ababc" will not be found in input "abababc".


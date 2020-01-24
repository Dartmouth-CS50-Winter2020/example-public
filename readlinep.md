---
layout: page
title: readlinep - reading lines of arbirary length
---

This *Lecture extra* is not something we have time to cover in lecture, but is important to read.

## Improving readline

Earlier we developed a simple `readline()` function (and its companion `freadline()` to read from a file), which in [readline.h]({{site.examples}}/readline.h) has prototype

```c
bool readline(char *buf, const int len);
```

This would read from stdin into `buf` until it encountered a newline, or the buffer (of length `len`) was full.
In the latter case it would return false and discard the whole line of input.

To be more accommodating, we developed `readlinep` (and its companion `freadlinep`).
In [readlinep.h]({{site.examples}}/readlinep.h) we see the prototypes:

```c
extern char *freadlinep(FILE *fp);
static inline char *readlinep(void) { return freadlinep(stdin); }
```

Notice that `readlinep` is an "inline" function, which means that it is compiled directly into the code wherever it is called, rather than being a true function.
(That's why it has to be declared `static`: because every file that includes `readlinep.h` needs its only private 'copy' of `readlinep`.)  It's a simple wrapper that just calls `freadline(stdin)`.

## freadlinep

Notice that `freadlinep` returns a string - and yet it takes no pointer to a buffer.
Instead, it allocates heap memory and returns a pointer to the new string; it returns NULL on error.
The caller is later responsible to `free` that pointer.

> One other difference between `readline` and `readlinep`: the former includes the newline and the latter removes it.
The difference is a historical accident and, ideally, these two functions would be reconciled and behave the same way.

The core of the `freadlinep` code is below.
Notice:

* we start off by allocating a character array from the heap, using `calloc`, hoping it is big enough to hold most input lines.
* we then loop, getting characters from the input file, until we reach EOF or a newline character.
* we insert each new character into `buf[pos]`, bumping the index `pos` each time through the loop.
* but we carefully monitor `pos` and its relation to the current length of the buffer; if the new character would cause us to overflow the buffer, we ask `realloc()` to grow the buffer by one more byte.
* we return NULL if there is any memory allocation error, or if we reach EOF.
* otherwise we return a pointer to the buffer.

```c
  // allocate buffer big enough for "typical" words/lines
  int len = 81;
  char *buf = calloc(len, sizeof(char));
  if (buf == NULL) {
    return NULL;              // out of memory
  }

  // Read characters from file until newline or EOF,
  // expanding the buffer when needed to hold more.
  int pos;
  char c;
  for (pos = 0; (c = fgetc(fp)) != EOF && (c != '\n'); pos++) {
    // We need to save buf[pos+1] for the terminating null
    // and buf[len-1] is the last usable slot,
    // so if pos+1 is past that slot, we need to grow the buffer.
    if (pos+1 > len-1) {
      char *newbuf = realloc(buf, ++len);
      if (newbuf == NULL) {
        free(buf);
        return NULL;          // out of memory
      } else {
        buf = newbuf;
      }
    }
    buf[pos] = c;
  }

  if (pos == 0 && c == EOF) {
    // no characters were read and we reached EOF
    free(buf);
    return NULL;
  } else {
    // pos characters were read into buf[0]..buf[pos-1].
    buf[pos] = '\0'; // terminate string
    return buf;
  }
```

> It may seem inefficient to grow the buffer by only one byte each time.
We trust `realloc` to be smart, moving the buffer to a new location (by copying it) that leaves room for growth, rather than incurring a copy of the whole string every time we call `realloc`.
It's far easier for us to leave those complexities to `realloc` than to implement them at this layer.

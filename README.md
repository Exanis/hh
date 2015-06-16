hh
==

HH is a toolkit adding object paradigm to the C language. Using a huge set of define and pre-processor, it give a whole set of encapsulation and new keywords, without ressorting to anything else that pure gcc extensions.

Note that HH will not work with clang, since they didn't implement gcc's constructing call extension (and this is one of the basics for this to work).

# How to use

## Headers inclusion

Most of the job in HH is done using headers. Unlike most of usual C headers, HH headers are _meant_ to be included multiple times, and need to be used in a very specific order. Namely, you must include in *every file of your program* :

* Any system header that you may need
* _If your file is a class file:__ the specific header for this class
* _If your file is *not* a class file:__ the header hh/noclass.h
* Any other class header you may need
* The header hh.h

And, in every class header, you must include the header hh.h (meaning it will be included both in .h and .c file).

Here come an exemple:

*myclass.h*
```c
#pragma once

#include "hh.h"

class (myclass)
{
  /* Whatever you need */
} end;
```

*myclass.c*
```c
#include <stdio.h>
#include "myclass.h"
#include "anotherclass.h"
#include "hh.h"

class (myclass)
{
  /* Whatever you need here */
} end;
```

*main.c*
```c
#include "hh/noclass.h"
#include "myclass.h"
#include "hh."

int	main()
{
  /* Whatever you need here */
  return 0;
}
```
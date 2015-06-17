hh
==

HH is a toolkit adding object paradigm to the C language. Using a huge set of define and pre-processor, it give a whole set of encapsulation and new keywords, without ressorting to anything else that pure gcc extensions.

Note that HH will not work with clang, since they didn't implement gcc's constructing call extension (and this is one of the basics for this to work).

# How to use

## Compilation flags

In order to provide all it's amazing (trust me on this one) functionnalities, HH need you to add a few flags when compiling your files. The two you need to use are *-std=c99* and *-fplan9-extensions*.

You also need to remove any flags that would interfere with those two (such as, but not limited to, *-ansi*, *-pedantic* or *-std=c89*).

## Headers inclusion

Most of the job in HH is done using headers. Unlike most of usual C headers, HH headers are _meant_ to be included multiple times, and need to be used in a very specific order. Namely, you must include in *every file of your program* :

* Any system header that you may need
* _If your file is a class file:_ the specific header for this class
* _If your file is *not* a class file:_ the header hh/noclass.h
* Any other class header you may need
* The header hh.h

And, in every class header, you must include the header hh.h (meaning it will be included both in .h and .c file). Please note that class header need to respect a precise order, described below.

Here come an example:

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
};
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

In your header files, the order is the opposite as the one in your C file : first, you have ton include "hh.h", then other files. Not only that, but you should only include in your .h file the classes that you will **inherit from** (see inheritance below). If you only want to use a class as a parameter or return type, use the keyword *using*, like this :

```c
#pragma once

#include "hh.h"
#include "anotherclass.h"

using(theclass);

class (myclass)
{
  extends(anotherclass);
  theclass	public(method hello)(int a);
  void		public(method something)(theclass param);
} end;
```

## Core functionnality

Most of the basics of HH will seems pretty natural to anyone already used to object-oriented languages. The basic unit of any HH program is the class, that may be declared using the _class_ keyword, both in .c and .h file, as shown above. Note a little specific here: a class should always end with the "end" keyword, after the closing bracket, but only in the .h file. We decided to avoid the need for end in .c file to avoid some pretty obscure error when naming a variable end.

Just as many other object-oriented languages, HH expect you to put one and only one class in a given file. Nonetheless, HH does not support imbricated classes. However, you don't have to name your file the same as the class inside it - but it's quite strongly recommanded for a sake of clarity.

Class may contain multiple methods and properties. HH give three levels of visibility : public, protected and private. Those levels are the reason why it's fundamental that you include your headers in the correct order, and that you don't include your class header in another header.

In addition to public, private and protected keywords, hh define four important keywords: using, class, method and end.

Keyword *using* as already been explained : it is meant to allow the use of a class as a parameter, member or return value of another class, without including it's own header.

Keywords *class* and *end* are used to define a class. A class always start with class (name) and end with end. More example below.

Finally, keyword *method* is used to define a method. It is meant to be used before the method name, in the visibility part.

Here is an example of your typical .h file :

```c
#pragma once

#include "hh.h"
#include "aclass.h"

using(theclass);

class(myclass)
{
  extends(aclass);
  int	public(method getInt)();
  void	public(method setInt)(int value);
  int	protected(value);
  void	private(method setFromTheClass)(theclass from);
} end;
```

Please note that when you use a class made in hh, you will always manipulate it as an object, IE as a pointer, and never as a direct structure.

In your .c file, things are easier, since you won't need to copy visibility. You don't even need to include your parent class' header file - but you probably want to include the header files for the class you used with *using*. You will still have a bit of work to do when your class have parents and want to construct around it, be we'll cover that later.

Note that you will still have to declare your methods, and all must bee in the scope of your class, but the use of the *method* keywords change slightly :

```c
#include "myclass.h"
#include "theclass.h"
#include "hh.h"

class(myclass)
{
  int	method(getInt)()
  {
    return $(this)->value;
  }

  void	method(setInt)(int value)
  {
    $(this)->value = value;
  }

  void	method(setFromTheClass)(theclass from)
  {
    $(this)->value = $(from)->aMethodThatReturnTheValue();
  }
};
```

One thing that you may have noticed in the previous example is that any use of a class variable (weither it is *this* or a parameter) is wrapped by $(). This is mandatory in your code. Basically, any call to something inside a class must be done by wrapping the object with $().

## Memory allocation, free, constructors and destructors

As many object-oriented tools, HH allow the use of keywords new, delete, and use constructors and destructors. Note that HH does _not_ managed the memory for you (but can help you to do it by yourself, see below), so you still need to take care of allocating and removing resources.

To managed memory, HH introduce five new keywords:

*new* is used to allocate a class. It must be used both with local and non-local allocation (you should never do *myclass a;*, only *myclass a = new(a)* - see below). It can take parameters, that will be transfered to the class' constructor.

*delete* is the opposite of new. It must be called every time you want to remove a variable. You can avoid using it with local allocation (see below). The *delete* keyword will automatically call any sub-class delete (more on this later).

*construct* and *destruct* respectivly define class' constructor and destructor. Like any other object-oriented language, construct() and destruct() are not typed and return nothing. Note that there is a little thing to do when you extend a class in your constructor (kind of a chain initialization in C++).

*local* keyword is a simple keyword used to define a local-only variable. This variable can be used as any other, but will be destroyed as soon as leaving the scope, just as if you had used destruct() on it. This is a tool to help you to manage your memory without the need for a specific call to destruct.

Here is an exemple of all those keywords :

*myclass.h*
```c
#pragma once

#include "hh.h"

class (myclass)
{
  int	public(method sayHi)();
  int	public(method sayHello)();
} end;
```

*myclass.c*
```c
#include <stdio.h>
#include "myclass.h"
#include "helloclass.h"
#include "hh.h"

class (myclass)
{
  construct(int value)
  {
    printf("Constructing class with value %d\n", value);
  }
  
  destruct()
  {
    printf("Destructing class.\n");
  }

  int	method(sayHi)()
  {
    local helloclass hello = new(helloclass, "Hi");

    $(hello)->say();
    return 42;
  }

  int	method(sayHello)()
  {
    helloclass hello = new(helloclass, "Hello");

    $(hello)->say();
    delete(hello);
    return 21;
  }
};
```

## Object inheritancy

One of the best parts of any object-oriented language is the ability to extend the possibilities of an object in another. This is named inheritance and, yes, it's possible in C using HH !

There have been many ways to use inheritance in different languages, so here goes the caracteristics of HH's one :
- You can extends multiple class in a unique one (IE, A can be a child of both B and C)
- You can of course extends a class already extended (IE, A can be a child of B and C, and C can be a child of D)
- You can use any method of a parent class in a child class (IE, if A is a child of B, A can use B's method - public and protected ones only, of course)
- You _cannot_ use any method of a child class in a parent class (IE, if A is a child of B, B cannot use A's method)
- You can overload any function of a parent class in a child class by simply redefining it (but you cannot change it's function signature).
- You _may_ create abstract class and/or interfaces by not defining their method in your .c file. However, this is not encouraged because if you use your abstract class and/or not define your method, it will lead to a segmentation fault.
- You can pass a child class as a parent class to any function or method.
- You _cannot_ create any kind of diamond inheritancy or anything that may lead to two distinct member of the same class having the same name (this will not compile. Of course, this include extending two time the same class, but what could lead you to this idea anyway ?)

To be able to use inheritancy, there is a few things that you must do:
- First, respect #include order in your .h. As specified before, you must first include hh.h, then any class' .h that you want to extends
- Add your extensions **at the beginning** of your class. Anywhere else will fail and/or lead to a segfault / infinite loop (or kill kittens)
- Create a constructor for your child class, even if neither your parent nor your child class need it.
- Call parent(parentclass) in your child class.

Here come a little exemple, featuring overload, abstract methods, and all this stuff. Please note how the extends() keyword is used in class2.h and how the parent() keyword is used in class2's constructor :

*class1.h*
```c
#pragma once

#include "hh.h"

class(class1)
{
  int	protected(value);
  int	public(method getValue)();
} end;
```

*class1.c*
```c
#include <stdio.h>
#include "class1.h"
#include "hh.h"

class(class1)
{
  construct()
    {
      $(this)->value = 3;
    }
  
  int	method(getValue)()
  {
    printf("In class 1\n");
    return ($(this)->value);
  }
};
```

*class2.h*
```c
#pragma once

#include "hh.h"
#include "class1.h"

class(class2)
{
  extends(class1);
  void	public(method setValue)();
} end;
```

*class2.c*
```c
#include <stdio.h>
#include "class2.h"
#include "hh.h"

class(class2)
{
  construct()
    {
      parent(class1);
    }
  
  int	method(getValue)()
  {
    printf("In class 2\n");
    return ($(this)->value);
  }

  void	method(setValue)(int value)
  {
    $(this)->value = value;
  }
};
```

*main.c*
```c
#include <stdio.h>
#include "hh/noclass.h"
#include "class2.h"
#include "hh.h"

void	test(class1 clazz)
{
  printf("Value is %d\n", $(clazz)->getValue());
}

int	main()
{
  local class2 clazz = new(class2);

  $(clazz)->setValue(2);
  test(clazz);
}
```


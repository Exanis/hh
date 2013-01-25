#include	<stdio.h>

#define	extend(name)	name
#define	class(name)	typedef struct s_##name name; struct s_##name

class(parent)
{
  int	a;
};

class(otherparent)
{
  int	c;
};

class(child)
{
  extend(parent);
  extend(otherparent);
  int	b;
};

int	test(parent *a)
{
  return (a->a);
}

int	othertest(otherparent *a)
{
  return (a->c);
}

int	main()
{
  child	c;

  c.a = 42;
  c.b = c.a + 2;
  c.c = 21;
  printf("%d\n", test(&c));
  printf("%d\n", othertest(&c));
}

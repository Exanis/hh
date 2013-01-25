#include	<stdio.h>

#if __STDC_VERSION__ < 201112L
# error "HH need to be compiled with C11 support - try -std=c11"
#endif

#define	extend(name)	name
#define	class(name)	typedef struct s_##name name; struct s_##name

class(parent)
{
  int	a;
};

class(child)
{
  extend(parent);
  int	b;
};

int	test(parent *a)
{
  return (a->a);
}

int	main()
{
  child	c;

  c.a = 42;
  c.b = c.a + 2;
  printf("%d\n", test(&c));
}

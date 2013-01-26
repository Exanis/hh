#include	<stdio.h>
#include	<unistd.h>
#include	<sys/mman.h>

#define	_class(name)	typedef struct s_##name name;	\
  struct s_##name

#define	class(name)	typedef name current_class;	\
  void	__init__##name(name *ret)

#define	_public(name)	(*name) _ADD_THIS
#define	_ADD_THIS(...)	(void *this, ##__VA_ARGS__)

#define	public(name)	*type_of_##name;		\
  auto typeof(*type_of_##name) func_##name ();		\
							\
  ret->name = &func_##name;				\
  typeof(*type_of_##name)	func_##name ADD_THIS

#define	ADD_THIS(...)	(current_class *this, ##__VA_ARGS__)

#define	$(elem)	({ typeof(elem) self = elem; elem->SUB_FUNC
#define	SUB_FUNC(name)	name PARAM_THIS
#define	PARAM_THIS(...)	(self, ##__VA_ARGS__);})
#define	new_a(from, type)	__init__##type(from)

_class(clazz) {
  int	i;
  int   _public(get)();
  void	_public(set)(int i);
};

class(clazz) {
  int	public(get)() {
    return (this->i);
  }

  void	public(set)(int i) {
    this->i = i;
  }
}

int	main()
{
  clazz	elem;
  clazz	*test = &elem;

  new_a(test, clazz);
  $(test)(set)(42);
  printf("%d\n", $(test)(get)());
}

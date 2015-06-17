#pragma once

#define	test(name, description)	results[0]++;		\
  if (name())						\
    {							\
      results[1]++;					\
      printf("[%d/%d][\033[32mPASS\033[0m][%s] %s\n",	\
	     results[0],				\
	     results[1],				\
	     #name,					\
	     description);				\
    } else {						\
    printf("[%d/%d][\033[31mFAIL\033[0m][%s] %s\n",	\
	   results[0],					\
	   results[1],					\
	   #name,					\
	   description);				\
  }

#define main_test(name)	results[0]++; results[1] += launch_test(&name, #name)

void	test_class(int results[2]);
void	test_parent(int results[2]);

#include "hh.h"

void	*hh_exception_result_ptr = NULL;
void	*hh_good_exception_caught = NULL;
typedef struct	hh_jmp_buffer	hh_jmp_buffer_t;

struct hh_jmp_buffer
{
  jmp_buf		buffer;
  hh_jmp_buffer_t	*next;
};

static hh_jmp_buffer_t	*buffers = NULL;

jmp_buf	*hh_add_try_context()
{
  hh_jmp_buffer_t	*buffer = malloc(sizeof(hh_jmp_buffer_t));

  buffer->next = buffers;
  buffers = buffer;
  return (&(buffer->buffer));
}

void	hh_remove_try_context(__attribute__((unused)) void *_)
{
  hh_jmp_buffer_t	*tmp = buffers;

  buffers = tmp->next;
  free(tmp);
}

jmp_buf	*hh_get_last_try_context()
{
  return (buffers->buffer);
}

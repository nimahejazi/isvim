#include <unistd.h>

typedef struct {
  pid_t pid;
  pid_t ppid;
  char name[32];
} proc_t;

#include <stdio.h>
#include <unistd.h>
#include "isvim.h"
#include <stdlib.h>
#include <string.h>
#ifdef __APPLE__
  #include <libproc.h>
#elif __linux__
  #include <sys/types.h>
  #include <dirent.h>
  #include <ctype.h>
#endif

#ifdef __APPLE__
int pid_info(pid_t pid, proc_t *rproc)
{
  struct proc_bsdinfo proc;
  int ret = proc_pidinfo(pid, PROC_PIDTBSDINFO, 0, &proc, PROC_PIDTBSDINFO_SIZE);

  // error when size is wrong
  if (ret != PROC_PIDTBSDINFO_SIZE)
    return ret;

  rproc->pid = proc.pbi_pid;
  rproc->ppid = proc.pbi_ppid;
  strncpy(rproc->name, proc.pbi_name, sizeof(rproc->name));
  return ret;
}
#elif __linux__
DIR *dir;

// if 0 returned, there is an error
int pid_info(pid_t pid, proc_t *rproc)
{
  if (pid == 0)
    return 0;
  FILE *fd;
  char filepath[32];
  char buffer[512];
  snprintf(filepath, sizeof(filepath), "/proc/%d/status", pid);
  if ((fd = fopen(filepath, "r")) == NULL)
  {
    fprintf(stderr, "Error opening %s file\n", filepath);
    return 0;
  }

  while(fgets(buffer, sizeof(buffer), fd))
  {
    char *title = strtok(buffer, ":\t");
    char *value = strtok(NULL, ":\t\n");
    if (!strcmp(title, "Name"))
      strncpy(rproc->name, value, sizeof(rproc->name));
    else if (!strcmp(title, "Pid"))
      rproc->pid = atol(value);
    else if (!strcmp(title, "PPid"))
      rproc->ppid = atol(value);


    // if name if not filled, 0 will be returned return sizeof(rproc->name);
  }

  fclose(fd);
  return sizeof(rproc->name);
  
}
#endif

int main()
{
  pid_t ppid = getppid();
  // current process and parent process
  proc_t cur_proc, par_proc;

  pid_info(ppid, &cur_proc);

  // when return 0, it means shell has no parent
  
  if (!pid_info(cur_proc.ppid, &par_proc))
    return 1;

  if (!strcmp(par_proc.name, "vim"))
  {
    printf("VIM is running (%d)\n", par_proc.pid);
    return 0;
  }

  return 1;
}

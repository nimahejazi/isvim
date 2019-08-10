#include <stdio.h>
#include <unistd.h>
#include <libproc.h>
#include "isvim.h"
#include <stdlib.h>
#include <string.h>

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

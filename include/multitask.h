#ifndef __MULTITASK_H__
#define __MULTITASK_H__

#include "common/print.h"
#include "common/types.h"
#include "gdt.h"
class Task;
struct CPUState
{
    uint32_t eax, ebx, ecx, edx, esi, edi, ebp;
    uint32_t error, eip, cs, eflags, esp, ss;
} __attribute__((packed));

class TaskManger
{
  public:
    TaskManger();
    ~TaskManger();
    bool AddTask(Task *task);
    CPUState *Schedule(CPUState *cpuState);

  protected:
    Task *tasks[256];
    uint8_t numTasks;
    int currentTask;
};
class Task
{
  public:
    Task(GlobalDescriptionTable *gdt, void(entrypoint)());
    ~Task();
    CPUState friend *TaskManger::Schedule(CPUState *cpuState);

  protected:
    uint8_t stack[4096];
    CPUState *cpuState;
};

#endif // !__MULTITASK_H__
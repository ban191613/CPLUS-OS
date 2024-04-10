#include "multitask.h"
Task::Task(GlobalDescriptionTable *gdt, void(entrypoint)())
{
    cpuState = (CPUState *)(stack + 4096 - sizeof(CPUState));
    cpuState->eax = 0;
    cpuState->ebx = 0;
    cpuState->ecx = 0;
    cpuState->edx = 0;

    cpuState->esi = 0;
    cpuState->edi = 0;
    cpuState->ebp = 0;

    cpuState->eip = (uint32_t)entrypoint;
    cpuState->cs = gdt->CodeSegmentSelector();
    cpuState->eflags = 0x202; // 0010 0000 0010
}
Task::~Task()
{
}
TaskManger::TaskManger() : numTasks(0), currentTask(-1)
{
}
TaskManger::~TaskManger()
{
}
bool TaskManger::AddTask(Task *task)
{
    if (numTasks >= 256)
    {
        return false;
    }
    tasks[numTasks++] = task;
    return true;
}
CPUState *TaskManger::Schedule(CPUState *cpuState)
{
    if (numTasks <= 0)
        return cpuState;
    if (currentTask >= 0)
    {
        tasks[currentTask]->cpuState = cpuState;
    }

    if (++currentTask >= numTasks)
    {
        currentTask %= numTasks;
    }
    return tasks[currentTask]->cpuState;
}

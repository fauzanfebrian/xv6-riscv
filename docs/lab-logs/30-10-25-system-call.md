# System Call

An Operating system has two modes: `Kernel` mode and `User` mode. When a program running in user mode wants to access the kernel, it must request to the kernel. This process is called a system call. This week's task is to understand how a system call works. Given an example of how to create one, take a look at the [Source Code](../../user/hello.c).

In C, there's so called C Standard Library. The C Standard Library's main purpose is to wrap functions for system call, in other words, it acts as a layer between the kernel and the programmer.

## Implementation

This week's task is to create a simple user-space program, create a calculation program. Because this week's key point is to understand `System Call`, then I implemented a `pipe` in this calc program. I was inspired by Go's Channel, were a worker does the jobs and the parent sits and waiting for the result. For the IPC, I implemented the `pipe` syscall, XV6 already implemented in its C Standard Library for this syscall, so i just use it to transfer a data from a worker to its parent, here's the [Source Code](../../user/calc.c).

# This directory is System call settings

In this project you must use system call.
So, you modify your optee-os like This

## System call files
Below is our modifying files in optee_os


core/arch/arm/tee/arch_svc.c                : contains tee_svc_syscall_table  
lib/libutee/include/tee_syscall_numbers.h   : contains SYSCALL number  
core/include/tee/tee_svc.h                  : define SYSCALL function  
core/tee/tee_svc.c                          : implement SYSCALL function  
lib/libutee/include/utee_syscalls.h         : syscall defined for userland  
lib/libutee/arch/arm/utee_syscalls_asm.S    : add UTEE_SYSCALL  
lib/libutee/include/tee_api.h               : wrapper function for using in user TA  
lib/libutee/tee_api.c                       : implement user TA wrapper function  






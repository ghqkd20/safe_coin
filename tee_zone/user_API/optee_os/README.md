# OP-TEE Trusted OS
This git contains source code for the secure side implementation of OP-TEE
project.

All official OP-TEE documentation has moved to http://optee.readthedocs.io.

// OP-TEE core maintainers



The built directory is 'out' 

in mk directory, we can see all flags to build



//SYSCALL
core/arch/arm/tee/arch_svc.c	: contains tee_svc_syscall_table
lib/libutee/include/tee_syscall_numbers.h	: contains SYSCALL number
core/include/tee/tee_svc.h		: define SYSCALL function
core/tee/tee_svc.c				: implement SYSCALL function                    (syscall_syscallname)
lib/libutee/include/utee_syscalls.h	: syscall defined for userland
lib/libutee/arch/arm/utee_syscalls_asm.S : add UTEE_SYSCALL                     (_utee_syscallname)
lib/libutee/include/tee_api.h	: wrapper function for using in user TA
lib/libutee/tee_api.c			: implement user TA wrapper function

[reference] : https://m.blog.naver.com/PostView.nhn?isHttpsRedirect=true&blogId=hw5773&logNo=221381598701
To find my syscall, 'grep -r '/* User define system call*/' *'
current my syscall is void TEE_GetMySyscall(int result)

syscall reverse analysis(elf file analysis)

TEE_OpenTASession, TEE_InvokeTACommand -> copy_param
copy_param -> tee_map_zi    or    TEE_OpenTASession, TEE_InvokeTACommand-> tee_unmap or ?->tee_invoke_supp_plugin
tee_map_zi or tee_unmap  or tee_invoke_supp_plugin
invoke_system_pta
TEE_OpenTASession





// OP-TEE secure Storage SYSCALL
core/arch/arm/tee/arch_svc.c
lib/libutee/include/tee_syscall_numbers.h
core/include/tee/tee_svc_storage.h
core/tee/tee_svc_storage.c                          -->modify
lib/libutee/include/utee_syscalls.h
lib/libutee/arch/arm/utee_syscalls_asm.S
lib/libutee/include/tee_api.h
lib/libutee/tee_api_objects.c

//ERROR CODE
lib/libutee/include/tee_api_defines.h


// back up
cp lib/libutee/tee_api.c lib/libutee/include/tee_api.h lib/libutee/arch/arm/utee_syscalls_asm.S lib/libutee/include/utee_syscalls.h core/tee/tee_svc_storage.c core/include/tee/tee_svc_storage.h lib/libutee/include/tee_syscall_numbers.h core/arch/arm/tee/arch_svc.c ~/syscall_direct/0804/

//github upload
cp  core/arch/arm/tee/arch_svc.c ~/Desktop/work/graduation/safe_coin/tee_zone/Systemcall



//EMSG
lib/libutils/ext/include/trace.h
        define EMSG ->  trace_printf_helper -> trace_printf
lib/libutils/ext/trace.c
        trace_printf
100     va_start(ap, fmt);
101     trace_vprintf(function, line, level, level_ok, fmt, ap);
102     va_end(ap);


// caller function name
https://stackoverflow.com/questions/16100090/how-can-we-know-the-caller-functions-name
https://stackoverflow.com/questions/59049614/print-name-of-caller-function


void a()
{
    /* Your code */
}

void a_special( char const * caller_name )
{
    printf( "a was called from %s", caller_name );
    a();
}

#define a() a_special(__func__)

void b()
{
    a();
}



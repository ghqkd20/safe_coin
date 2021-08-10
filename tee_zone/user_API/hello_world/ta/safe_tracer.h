#ifndef TEST_H
#define TEST_H

#include <tee_internal_api.h>
#include <tee_internal_api_extensions.h>

#include <compiler.h>
#include <sys/cdefs.h>
#include <stdint.h>
#include <util.h>
#include <stdarg.h>
#include <stdio.h>


static __always_inline __noprof uint64_t get_pc()
{
    uint64_t val;
    asm volatile ("adr %0, ." : "=r" (val));
    EMSG("####GET PC#####%"PRIu64,val);
    return val;
}

/*Show current function and line number
 *In this Function, call system call
 *First is variadic function
 *Second is pointer 
 *
 */
TEE_Result D_test(const char* f_name, int line_num,const int count, ...);
TEE_Result D_test2(const char* f_name, int line_num,const int count, void *args);


void siba();

/*
 * LOG with Hashing
 * first get program counter(location)
 * and then test overflow and send to kernel
 * User Only use This macro
 *
 * count : # of operands
 * args  : operands
 */
#define LOGH(count , ...) ({                         \
    get_pc();                                            \
    D_test(__func__, __LINE__, count , __VA_ARGS__);    \
})

//version 2, using pointer
#define LOGH2(count , args) ({                         \
    get_pc();                                            \
    D_test2(__func__, __LINE__, count , args);    \
})



#endif

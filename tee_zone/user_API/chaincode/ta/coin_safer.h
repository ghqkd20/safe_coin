#ifndef SAFE_HASH_H
#define SAFE_HASH_H

#include <tee_internal_api.h>
#include <tee_internal_api_extensions.h>

#include <compiler.h>
#include <sys/cdefs.h>
#include <stdint.h>
#include <util.h>
#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>

static bool overflowflag = false;
typedef enum TYPE_LIMITS{
    NON_B     = 0x00,
    ONE_B     = 0xFF,
    TWO_B     = 0xFFFF,
    FOUR_B    = 0xFFFFFFFF,
    EIGHT_B   = 0xFFFFFFFFFFFFFFFF,
} TYPE_LIMITS;

TYPE_LIMITS set_limit(size_t val);

//sign same, res = 0
#define CHECK_SIGN(a, b, type)    ({                            \
                TYPE_LIMITS limits = set_limit(sizeof(type));   \
                limits = (limits>>1) ^ limits;                  \
                uint64_t c = (a & limits) ^ (b & limits);     \
                c = ((c == 0)? 1 : 0);                         \
                DMSG("%x %x??????? %x",a,b,c); \
                c;                                              \
})




/*Operations
 *We support operations agianst overflow
 *assume 'a' and 'b' must same type
 *and result type is 'type'
 *if overflow occured, flag be set
 *This valid at GCC compiler
 */

#define O_UADD(a,b, type)    ({                                \
                TYPE_LIMITS limits = set_limit(sizeof(type));   \
                uint64_t c = (a+b)&limits;                               \
                if(c<a) overflowflag=true;                      \
                (type) c;                                       \
})

#define O_ADD(a, b, type)   ({                                              \
                TYPE_LIMITS limits = set_limit(sizeof(type));   \
                uint64_t equal_sign = CHECK_SIGN(a,b,type);                 \
                int64_t res =a+b;                                         \
                DMSG("res :: %d",res);      \
                if(equal_sign && !CHECK_SIGN(res,a,type)) overflowflag = true;   \
                (type) res;                                                 \
})


/*
#define ADD_OVERFLOW



#define U_SUB_OVERFLOW
#define SUB_OVERFLOW
#define U_MUL_OVERFLOW
#define MUL_OVERFLOW
#define U_DIV_OVERFLOW
#define DIV_OVERFLOW
*/

/*
 *get overflow flag
 *
 */
bool check_overflow();

/*Show current program counter value
 *We use inline assmbly
 */
static __always_inline __noprof uint64_t get_pc()
{
    uint64_t val;
    asm volatile ("adr %0, ." : "=r" (val));
    return val;
}

/*Show current function and line number
 *In this Function, call system call
 *First is variadic function
 *Second is pointer 
 *
 */
TEE_Result D_test(const char* f_name, int line_num, uint64_t pc, const int count, ...);
TEE_Result D_test2(const char* f_name, int line_num, uint64_t pc, const int count, void *args);
char* get_hash();

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
    uint64_t pc = get_pc();                                            \
    D_test(__func__, __LINE__, pc ,count , __VA_ARGS__);    \
})

//version 2, using pointer
#define LOGH2(count , args) ({                         \
    uint64_t pc = get_pc();                                            \
    D_test2(__func__, __LINE__, pc ,count , args);    \
})



#endif

#include <safe_tracer.h>

/*
typedef enum TYPE_LIMITS{                                                                                              
    ZERO    = 0x00,
    ONE     = 0xFF,
    TWO     = 0xFFFF,
    FOUR    = 0xFFFFFFFF,
    EIGHT   = 0xFFFFFFFFFFFFFFFF,
} TYPE_LIMITS;

TYPE_LIMITS set_limit(size_t val){
    TYPE_LIMITS res = ZERO;
    switch(val){
        case 1:
            res = ONE;
            break;
        case 2:
            res = TWO;
            break;
        case 4:
            res = FOUR;
            break;
        case 8:
            res = EIGHT;
            break;
        default:
            break;
    }
    return res;
}
*/

TEE_Result D_test(const char* f_name, int line_num,const int count, ...)
{

    EMSG("FUNCTION NAME : %s, LINE NUMBER : %d",f_name, line_num);
    uint64_t program_counter = 10;

    /*
     *TODO :: Check operation overflow with Variadic parameters
     *  This function could be passed all type variable
     *  In this case, you set each variable type
     *
     */
    bool isFault = false;
    if(count > 0){
        va_list ap;
        va_start(ap, count);
        for(int i=0; i<count; i++){
            EMSG("%d",va_arg(ap,int));
        }
        va_end(ap);
    }
    return TEE_GetMySyscall(program_counter/*, isFault*/);
}

TEE_Result D_test2(const char* f_name, int line_num,const int count, void *args)
{

    EMSG("FUNCTION NAME : %s, LINE NUMBER : %d",f_name, line_num);
    uint64_t program_counter = 10;

    /*
     *TODO :: Check operation overflow with pointer
     *  You cast arguments type
     *  This arguments are be structure or array
     *
     */
    bool isFault = false;
    if(count > 0){
        int* my_args = (int*) args;
        for(int i=0; i<count; i++){
            EMSG("%d",*(my_args+i));
        }
    }
    return TEE_GetMySyscall(program_counter/*, isFault*/);
}





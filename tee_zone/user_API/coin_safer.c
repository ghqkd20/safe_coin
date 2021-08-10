#include <test.h>

/*
typedef enum TYPE_LIMITS{                                                                                              
    NON_B     = 0x00,
    ONE_B     = 0xFF,
    TWO_B     = 0xFFFF,
    FOUR_B    = 0xFFFFFFFF,
    EIGHT_B   = 0xFFFFFFFFFFFFFFFF,
} TYPE_LIMITS;
*/
TYPE_LIMITS set_limit(size_t val){
    TYPE_LIMITS res = NON_B;
    switch(val){
        case 1:
            res = ONE_B;
            break;
        case 2:
            res = TWO_B;
            break;
        case 4:
            res = FOUR_B;
            break;
        case 8:
            res = EIGHT_B;
            break;
        default:
            break;
    }
    return res;
}


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





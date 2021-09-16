#include <coin_safer.h>

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
        case 16:
            res = SIXTEEN_B;
            break;
        default:
            break;
    }
    return res;
}


TEE_Result D_test(const char* f_name, int line_num,uint64_t pc ,const int count, ...)
{

    EMSG("FUNCTION NAME : %s, LINE NUMBER : %d",f_name, line_num);

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
    return TEE_GetMySyscall(pc);
}

TEE_Result D_test2(const char* f_name, int line_num,uint64_t pc, const int count, void *args)
{

    EMSG("FUNCTION NAME : %s, LINE NUMBER : %d",f_name, line_num);

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
    return TEE_GetMySyscall(pc);
}


char* get_hash()
{
    static char hash_test[64];
    TEE_Result res = TEE_SUCCESS;
    res = TEE_GetMyHash(hash_test,false);

    if(res != TEE_SUCCESS){
        EMSG("GetMyHash Error !!");
        return NULL;
    }
    /*for debugging
    DMSG("EXECUTED???????????????");
    for(int i=0; i<16; i++){
        DMSG("%02x",hash_test[i]);
    }
    */
    return hash_test;
}   


char* pop_hash()
{
    static char hash_test[64];
    TEE_Result res = TEE_SUCCESS;
    res = TEE_GetMyHash(hash_test,true);

    if(res != TEE_SUCCESS){
        EMSG("GetMyHash Error !!");
        return NULL;
    }

    bool check_overflow = false;
    
    res = TEE_GetMyFlag(&check_overflow);
    
    if(res != TEE_SUCCESS){
        EMSG("GetMyFlag Error !!");
        return NULL;
    }
    
    if(check_overflow){
        TEE_MemMove(hash_storage+16, "true", 4);
    }else{
        TEE_MemMove(hash_storage+16, "false", 5);
    }


    /*for debugging
    DMSG("EXECUTED???????????????");
    for(int i=0; i<16; i++){
        DMSG("%02x",hash_test[i]);
    }
    */
    return hash_test;
}

/* 
 *  Get overflow flag
 *  WARNING :: if the flag already set, reset to init(false)
 *  only for debugging
 */
bool get_flag()
{
    bool check_overflow = false;
    TEE_GetMyFlag(&check_overflow);
    return check_overflow;
}



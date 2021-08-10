# Trusted Zone code

## Trace Flow API
This directory offer API for tracing control flow and calculate overflow
We use System call to protect each informations with hashing
This hash value send to peer and confirm validity

## user_API

### USAGE
1. Put API in your work space(This API use several tool supported by optee-os)
2. modify add API in sub.mk(i.e. 'srcs-y += test.c')
3. include in your code
4. USE LOGH() or LOGH2()

### hello_world
This directory is example directory.

### problems
1. current D_test function is non-static


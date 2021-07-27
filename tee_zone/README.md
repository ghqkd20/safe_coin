# Trusted Zone code

## About Syscall
  Our code is use syscall to record control flow with hashing.
  To guarantee integrity, we record it on secure OS(OPTEE-OS)

## About Chaincode
  This chaincode use 'coffee_tracking' chaincode.
  The 'Chaincode' directory contains execution in TEE.

## About static binary analysis and modifier
  Our implements is needed trampoline that intercept flow and call system call.
  So, This analyzer search branch code and modify it.

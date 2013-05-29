
  For TNKernel v.2.6 and later you should set (in an IDE or makefile)
the preprocessor defenition according to you port:

   - for ARM       - TNKERNEL_PORT_ARM,
   - for Cortex M3 - TNKERNEL_PORT_CORTEXM3,
   - for MSP430x   - TNKERNEL_PORT_MSP430X

   (see file 'tn_port.h' for more details)

otherwise you'll get the preprocessor error "TNKernel port undefined".


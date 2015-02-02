################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../example/keil/TNKernel/tn.c \
../example/keil/TNKernel/tn_dqueue.c \
../example/keil/TNKernel/tn_event.c \
../example/keil/TNKernel/tn_mem.c \
../example/keil/TNKernel/tn_mutex.c \
../example/keil/TNKernel/tn_sem.c \
../example/keil/TNKernel/tn_tasks.c \
../example/keil/TNKernel/tn_utils.c 

OBJS += \
./example/keil/TNKernel/tn.o \
./example/keil/TNKernel/tn_dqueue.o \
./example/keil/TNKernel/tn_event.o \
./example/keil/TNKernel/tn_mem.o \
./example/keil/TNKernel/tn_mutex.o \
./example/keil/TNKernel/tn_sem.o \
./example/keil/TNKernel/tn_tasks.o \
./example/keil/TNKernel/tn_utils.o 

C_DEPS += \
./example/keil/TNKernel/tn.d \
./example/keil/TNKernel/tn_dqueue.d \
./example/keil/TNKernel/tn_event.d \
./example/keil/TNKernel/tn_mem.d \
./example/keil/TNKernel/tn_mutex.d \
./example/keil/TNKernel/tn_sem.d \
./example/keil/TNKernel/tn_tasks.d \
./example/keil/TNKernel/tn_utils.d 


# Each subdirectory must supply rules for building sources it contributes
example/keil/TNKernel/%.o: ../example/keil/TNKernel/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../example/keil/user/hw_init.c \
../example/keil/user/main.c \
../example/keil/user/tn_user.c \
../example/keil/user/utils_uart.c 

OBJS += \
./example/keil/user/hw_init.o \
./example/keil/user/main.o \
./example/keil/user/tn_user.o \
./example/keil/user/utils_uart.o 

C_DEPS += \
./example/keil/user/hw_init.d \
./example/keil/user/main.d \
./example/keil/user/tn_user.d \
./example/keil/user/utils_uart.d 


# Each subdirectory must supply rules for building sources it contributes
example/keil/user/%.o: ../example/keil/user/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



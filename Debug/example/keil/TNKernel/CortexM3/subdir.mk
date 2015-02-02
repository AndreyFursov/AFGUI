################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../example/keil/TNKernel/CortexM3/tn_port_cm3.c 

OBJS += \
./example/keil/TNKernel/CortexM3/tn_port_cm3.o 

C_DEPS += \
./example/keil/TNKernel/CortexM3/tn_port_cm3.d 


# Each subdirectory must supply rules for building sources it contributes
example/keil/TNKernel/CortexM3/%.o: ../example/keil/TNKernel/CortexM3/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



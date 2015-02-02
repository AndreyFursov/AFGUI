################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../example/keil/StdLib/CMSIS/CoreSupport/core_cm3.c 

OBJS += \
./example/keil/StdLib/CMSIS/CoreSupport/core_cm3.o 

C_DEPS += \
./example/keil/StdLib/CMSIS/CoreSupport/core_cm3.d 


# Each subdirectory must supply rules for building sources it contributes
example/keil/StdLib/CMSIS/CoreSupport/%.o: ../example/keil/StdLib/CMSIS/CoreSupport/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



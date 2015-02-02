################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
ASM_SRCS += \
../example/keil/StdLib/CMSIS/Device/ST/STM32F2xx/Source/Templates/TASKING/cstart_thumb2.asm 

OBJS += \
./example/keil/StdLib/CMSIS/Device/ST/STM32F2xx/Source/Templates/TASKING/cstart_thumb2.o 


# Each subdirectory must supply rules for building sources it contributes
example/keil/StdLib/CMSIS/Device/ST/STM32F2xx/Source/Templates/TASKING/%.o: ../example/keil/StdLib/CMSIS/Device/ST/STM32F2xx/Source/Templates/TASKING/%.asm
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Assembler'
	as  -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



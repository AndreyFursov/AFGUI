################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../example/keil/bspStdLib/src/ADS7843_spi.c \
../example/keil/bspStdLib/src/HAL_Calender.c \
../example/keil/bspStdLib/src/at26df.c \
../example/keil/bspStdLib/src/button.c \
../example/keil/bspStdLib/src/crcm.c \
../example/keil/bspStdLib/src/hx8347.c \
../example/keil/bspStdLib/src/i2c_eeprom.c \
../example/keil/bspStdLib/src/tn_task_usart.c \
../example/keil/bspStdLib/src/uartdrv.c 

OBJS += \
./example/keil/bspStdLib/src/ADS7843_spi.o \
./example/keil/bspStdLib/src/HAL_Calender.o \
./example/keil/bspStdLib/src/at26df.o \
./example/keil/bspStdLib/src/button.o \
./example/keil/bspStdLib/src/crcm.o \
./example/keil/bspStdLib/src/hx8347.o \
./example/keil/bspStdLib/src/i2c_eeprom.o \
./example/keil/bspStdLib/src/tn_task_usart.o \
./example/keil/bspStdLib/src/uartdrv.o 

C_DEPS += \
./example/keil/bspStdLib/src/ADS7843_spi.d \
./example/keil/bspStdLib/src/HAL_Calender.d \
./example/keil/bspStdLib/src/at26df.d \
./example/keil/bspStdLib/src/button.d \
./example/keil/bspStdLib/src/crcm.d \
./example/keil/bspStdLib/src/hx8347.d \
./example/keil/bspStdLib/src/i2c_eeprom.d \
./example/keil/bspStdLib/src/tn_task_usart.d \
./example/keil/bspStdLib/src/uartdrv.d 


# Each subdirectory must supply rules for building sources it contributes
example/keil/bspStdLib/src/%.o: ../example/keil/bspStdLib/src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



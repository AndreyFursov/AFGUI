################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../example/keil/appGUI/HMI_Control.c \
../example/keil/appGUI/appGui.c \
../example/keil/appGUI/winMain.c \
../example/keil/appGUI/winPlot.c \
../example/keil/appGUI/winUartCfg.c 

OBJS += \
./example/keil/appGUI/HMI_Control.o \
./example/keil/appGUI/appGui.o \
./example/keil/appGUI/winMain.o \
./example/keil/appGUI/winPlot.o \
./example/keil/appGUI/winUartCfg.o 

C_DEPS += \
./example/keil/appGUI/HMI_Control.d \
./example/keil/appGUI/appGui.d \
./example/keil/appGUI/winMain.d \
./example/keil/appGUI/winPlot.d \
./example/keil/appGUI/winUartCfg.d 


# Each subdirectory must supply rules for building sources it contributes
example/keil/appGUI/%.o: ../example/keil/appGUI/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



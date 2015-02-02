################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../wigets/src/guiChart.c \
../wigets/src/guiCheckBox.c \
../wigets/src/guiLabel.c \
../wigets/src/guiRadioGroup.c \
../wigets/src/guiTerminalBlock.c \
../wigets/src/guiTextButton.c \
../wigets/src/guiTouchCalibration.c \
../wigets/src/guiUpDownBox.c 

OBJS += \
./wigets/src/guiChart.o \
./wigets/src/guiCheckBox.o \
./wigets/src/guiLabel.o \
./wigets/src/guiRadioGroup.o \
./wigets/src/guiTerminalBlock.o \
./wigets/src/guiTextButton.o \
./wigets/src/guiTouchCalibration.o \
./wigets/src/guiUpDownBox.o 

C_DEPS += \
./wigets/src/guiChart.d \
./wigets/src/guiCheckBox.d \
./wigets/src/guiLabel.d \
./wigets/src/guiRadioGroup.d \
./wigets/src/guiTerminalBlock.d \
./wigets/src/guiTextButton.d \
./wigets/src/guiTouchCalibration.d \
./wigets/src/guiUpDownBox.d 


# Each subdirectory must supply rules for building sources it contributes
wigets/src/%.o: ../wigets/src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



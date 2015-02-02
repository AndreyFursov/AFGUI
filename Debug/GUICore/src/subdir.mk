################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../GUICore/src/guiColor.c \
../GUICore/src/guiFonts.c \
../GUICore/src/guiFontsMin.c \
../GUICore/src/guiPrimitives.c \
../GUICore/src/guiText.c \
../GUICore/src/widget.c 

OBJS += \
./GUICore/src/guiColor.o \
./GUICore/src/guiFonts.o \
./GUICore/src/guiFontsMin.o \
./GUICore/src/guiPrimitives.o \
./GUICore/src/guiText.o \
./GUICore/src/widget.o 

C_DEPS += \
./GUICore/src/guiColor.d \
./GUICore/src/guiFonts.d \
./GUICore/src/guiFontsMin.d \
./GUICore/src/guiPrimitives.d \
./GUICore/src/guiText.d \
./GUICore/src/widget.d 


# Each subdirectory must supply rules for building sources it contributes
GUICore/src/%.o: ../GUICore/src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



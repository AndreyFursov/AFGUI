################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../driver/src/ads7843.c \
../driver/src/ads7843_207Z.c \
../driver/src/beeper.c \
../driver/src/ee_emul.c \
../driver/src/lcdHAL.c \
../driver/src/lcdHAL_9320.c \
../driver/src/lcdHAL_HX8347A.c \
../driver/src/lcdHAL_ILI9320.c \
../driver/src/lcdHAL_universal.c \
../driver/src/mkDriver.c \
../driver/src/mkDriver_207Z.c 

OBJS += \
./driver/src/ads7843.o \
./driver/src/ads7843_207Z.o \
./driver/src/beeper.o \
./driver/src/ee_emul.o \
./driver/src/lcdHAL.o \
./driver/src/lcdHAL_9320.o \
./driver/src/lcdHAL_HX8347A.o \
./driver/src/lcdHAL_ILI9320.o \
./driver/src/lcdHAL_universal.o \
./driver/src/mkDriver.o \
./driver/src/mkDriver_207Z.o 

C_DEPS += \
./driver/src/ads7843.d \
./driver/src/ads7843_207Z.d \
./driver/src/beeper.d \
./driver/src/ee_emul.d \
./driver/src/lcdHAL.d \
./driver/src/lcdHAL_9320.d \
./driver/src/lcdHAL_HX8347A.d \
./driver/src/lcdHAL_ILI9320.d \
./driver/src/lcdHAL_universal.d \
./driver/src/mkDriver.d \
./driver/src/mkDriver_207Z.d 


# Each subdirectory must supply rules for building sources it contributes
driver/src/%.o: ../driver/src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



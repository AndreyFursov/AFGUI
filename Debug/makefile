################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include wigets/src/subdir.mk
-include utils/src/subdir.mk
-include example/keil/user/subdir.mk
-include example/keil/bspStdLib/src/subdir.mk
-include example/keil/appGUI/subdir.mk
-include example/keil/TNKernel/CortexM3/subdir.mk
-include example/keil/TNKernel/subdir.mk
-include example/keil/StdLib/STM32F2xx_StdPeriph_Driver/src/subdir.mk
-include example/keil/StdLib/CMSIS/STM32F2xx/subdir.mk
-include example/keil/StdLib/CMSIS/Device/ST/STM32F2xx/Source/Templates/TASKING/subdir.mk
-include example/keil/StdLib/CMSIS/Device/ST/STM32F2xx/Source/Templates/subdir.mk
-include example/keil/StdLib/CMSIS/CoreSupport/subdir.mk
-include driver/src/subdir.mk
-include GUICore/src/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: AFGUI

# Tool invocations
AFGUI: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: Cross GCC Linker'
	gcc  -o "AFGUI" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(OBJS)$(C_DEPS)$(EXECUTABLES) AFGUI
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets

################################################################################
# Automatically-generated file. Do not edit!
################################################################################

#Progress monitor hint: 20
first : all
-include ../makefile.init

# This file contains definitions of environment variables used in the makefiles and .args files if exist.
-include makefile.local

RM := "$(GNU_Make_Install_DirEnv)/rm" -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir.mk
-include drivers/wdog/subdir.mk
-include drivers/uart/subdir.mk
-include drivers/mcg/subdir.mk
-include drivers/lptmr/subdir.mk
-include drivers/adc16/subdir.mk
-include cpu/subdir.mk
-include common/subdir.mk
-include Sources/service/subdir.mk
-include Sources/subdir.mk
-include Project_Settings/Startup_Code/subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(ASM_UPPER_DEPS)),)
-include $(ASM_UPPER_DEPS)
endif
ifneq ($(strip $(SX_DEPS)),)
-include $(SX_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
gpio.elf \

EXECUTABLES_QUOTED += \
"gpio.elf" \

EXECUTABLES_OS_FORMAT += \
gpio.elf \


# All Target
all: warning-messages explicit-dependencies gpio.elf secondary-outputs

# Tool invocations
gpio.elf: $(OBJS) $(USER_OBJS) ../Project_Settings/Linker_Files/PK60N512_ram.ld
	@echo 'Building target: $@'
	@echo 'Executing target #21 $@'
	@echo 'Invoking: ARM Ltd Windows GCC C Linker'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc"  $(USER_OBJS_QUOTED) $(LIBS_QUOTED) @"gpio.args" -o"gpio.elf"
	@echo 'Finished building target: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(S_DEPS_QUOTED) "./*/*/*.o" "./*/*.o"  $(S_UPPER_DEPS_QUOTED) $(ASM_DEPS_QUOTED) $(ASM_UPPER_DEPS_QUOTED) $(SX_DEPS_QUOTED) $(EXECUTABLES_QUOTED) "./*/*/*.d" "./*/*.d"  $(ProjDirPath)/RAM/gpio.elf
	-@echo ' '

secondary-outputs:

.PHONY: all clean dependents explicit-dependencies warning-messages
.SECONDARY:

-include ../makefile.targets

explicit-dependencies: ../Project_Settings/Linker_Files/PK60N512_ram.ld 

warning-messages: 


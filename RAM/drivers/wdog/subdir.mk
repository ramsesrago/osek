################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../drivers/wdog/wdog.c" \

C_SRCS += \
../drivers/wdog/wdog.c \

OBJS += \
./drivers/wdog/wdog.o \

C_DEPS += \
./drivers/wdog/wdog.d \

OBJS_QUOTED += \
"./drivers/wdog/wdog.o" \

C_DEPS_QUOTED += \
"./drivers/wdog/wdog.d" \

OBJS_OS_FORMAT += \
./drivers/wdog/wdog.o \


# Each subdirectory must supply rules for building sources it contributes
drivers/wdog/wdog.o: ../drivers/wdog/wdog.c
	@echo 'Building file: $<'
	@echo 'Executing target #1 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"drivers/wdog/wdog.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"drivers/wdog/wdog.o"
	@echo 'Finished building: $<'
	@echo ' '



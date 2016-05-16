################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../drivers/adc16/adc16.c" \

C_SRCS += \
../drivers/adc16/adc16.c \

OBJS += \
./drivers/adc16/adc16.o \

C_DEPS += \
./drivers/adc16/adc16.d \

OBJS_QUOTED += \
"./drivers/adc16/adc16.o" \

C_DEPS_QUOTED += \
"./drivers/adc16/adc16.d" \

OBJS_OS_FORMAT += \
./drivers/adc16/adc16.o \


# Each subdirectory must supply rules for building sources it contributes
drivers/adc16/adc16.o: ../drivers/adc16/adc16.c
	@echo 'Building file: $<'
	@echo 'Executing target #8 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"drivers/adc16/adc16.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"drivers/adc16/adc16.o"
	@echo 'Finished building: $<'
	@echo ' '



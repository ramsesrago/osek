################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../drivers/lptmr/lptmr_clocksource.c" \
"../drivers/lptmr/lptmr_counter.c" \
"../drivers/lptmr/lptmr_interrupt.c" \
"../drivers/lptmr/lptmr_pulse.c" \

C_SRCS += \
../drivers/lptmr/lptmr_clocksource.c \
../drivers/lptmr/lptmr_counter.c \
../drivers/lptmr/lptmr_interrupt.c \
../drivers/lptmr/lptmr_pulse.c \

OBJS += \
./drivers/lptmr/lptmr_clocksource.o \
./drivers/lptmr/lptmr_counter.o \
./drivers/lptmr/lptmr_interrupt.o \
./drivers/lptmr/lptmr_pulse.o \

C_DEPS += \
./drivers/lptmr/lptmr_clocksource.d \
./drivers/lptmr/lptmr_counter.d \
./drivers/lptmr/lptmr_interrupt.d \
./drivers/lptmr/lptmr_pulse.d \

OBJS_QUOTED += \
"./drivers/lptmr/lptmr_clocksource.o" \
"./drivers/lptmr/lptmr_counter.o" \
"./drivers/lptmr/lptmr_interrupt.o" \
"./drivers/lptmr/lptmr_pulse.o" \

C_DEPS_QUOTED += \
"./drivers/lptmr/lptmr_clocksource.d" \
"./drivers/lptmr/lptmr_counter.d" \
"./drivers/lptmr/lptmr_interrupt.d" \
"./drivers/lptmr/lptmr_pulse.d" \

OBJS_OS_FORMAT += \
./drivers/lptmr/lptmr_clocksource.o \
./drivers/lptmr/lptmr_counter.o \
./drivers/lptmr/lptmr_interrupt.o \
./drivers/lptmr/lptmr_pulse.o \


# Each subdirectory must supply rules for building sources it contributes
drivers/lptmr/lptmr_clocksource.o: ../drivers/lptmr/lptmr_clocksource.c
	@echo 'Building file: $<'
	@echo 'Executing target #4 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"drivers/lptmr/lptmr_clocksource.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"drivers/lptmr/lptmr_clocksource.o"
	@echo 'Finished building: $<'
	@echo ' '

drivers/lptmr/lptmr_counter.o: ../drivers/lptmr/lptmr_counter.c
	@echo 'Building file: $<'
	@echo 'Executing target #5 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"drivers/lptmr/lptmr_counter.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"drivers/lptmr/lptmr_counter.o"
	@echo 'Finished building: $<'
	@echo ' '

drivers/lptmr/lptmr_interrupt.o: ../drivers/lptmr/lptmr_interrupt.c
	@echo 'Building file: $<'
	@echo 'Executing target #6 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"drivers/lptmr/lptmr_interrupt.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"drivers/lptmr/lptmr_interrupt.o"
	@echo 'Finished building: $<'
	@echo ' '

drivers/lptmr/lptmr_pulse.o: ../drivers/lptmr/lptmr_pulse.c
	@echo 'Building file: $<'
	@echo 'Executing target #7 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"drivers/lptmr/lptmr_pulse.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"drivers/lptmr/lptmr_pulse.o"
	@echo 'Finished building: $<'
	@echo ' '



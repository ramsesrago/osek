################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../Sources/gpio_k60.c" \
"../Sources/scheduler.c" \

C_SRCS += \
../Sources/gpio_k60.c \
../Sources/scheduler.c \

OBJS += \
./Sources/gpio_k60.o \
./Sources/scheduler.o \

C_DEPS += \
./Sources/gpio_k60.d \
./Sources/scheduler.d \

OBJS_QUOTED += \
"./Sources/gpio_k60.o" \
"./Sources/scheduler.o" \

C_DEPS_QUOTED += \
"./Sources/gpio_k60.d" \
"./Sources/scheduler.d" \

OBJS_OS_FORMAT += \
./Sources/gpio_k60.o \
./Sources/scheduler.o \


# Each subdirectory must supply rules for building sources it contributes
Sources/gpio_k60.o: ../Sources/gpio_k60.c
	@echo 'Building file: $<'
	@echo 'Executing target #15 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/gpio_k60.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/gpio_k60.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/scheduler.o: ../Sources/scheduler.c
	@echo 'Building file: $<'
	@echo 'Executing target #16 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/scheduler.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/scheduler.o"
	@echo 'Finished building: $<'
	@echo ' '



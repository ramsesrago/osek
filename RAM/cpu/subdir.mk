################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../cpu/arm_cm4.c" \
"../cpu/sysinit.c" \

C_SRCS += \
../cpu/arm_cm4.c \
../cpu/sysinit.c \

OBJS += \
./cpu/arm_cm4.o \
./cpu/sysinit.o \

C_DEPS += \
./cpu/arm_cm4.d \
./cpu/sysinit.d \

OBJS_QUOTED += \
"./cpu/arm_cm4.o" \
"./cpu/sysinit.o" \

C_DEPS_QUOTED += \
"./cpu/arm_cm4.d" \
"./cpu/sysinit.d" \

OBJS_OS_FORMAT += \
./cpu/arm_cm4.o \
./cpu/sysinit.o \


# Each subdirectory must supply rules for building sources it contributes
cpu/arm_cm4.o: ../cpu/arm_cm4.c
	@echo 'Building file: $<'
	@echo 'Executing target #9 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"cpu/arm_cm4.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"cpu/arm_cm4.o"
	@echo 'Finished building: $<'
	@echo ' '

cpu/sysinit.o: ../cpu/sysinit.c
	@echo 'Building file: $<'
	@echo 'Executing target #10 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"cpu/sysinit.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"cpu/sysinit.o"
	@echo 'Finished building: $<'
	@echo ' '



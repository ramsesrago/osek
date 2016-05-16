################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../common/io.c" \
"../common/printf.c" \
"../common/stdlib.c" \
"../common/uif.c" \

C_SRCS += \
../common/io.c \
../common/printf.c \
../common/stdlib.c \
../common/uif.c \

OBJS += \
./common/io.o \
./common/printf.o \
./common/stdlib.o \
./common/uif.o \

C_DEPS += \
./common/io.d \
./common/printf.d \
./common/stdlib.d \
./common/uif.d \

OBJS_QUOTED += \
"./common/io.o" \
"./common/printf.o" \
"./common/stdlib.o" \
"./common/uif.o" \

C_DEPS_QUOTED += \
"./common/io.d" \
"./common/printf.d" \
"./common/stdlib.d" \
"./common/uif.d" \

OBJS_OS_FORMAT += \
./common/io.o \
./common/printf.o \
./common/stdlib.o \
./common/uif.o \


# Each subdirectory must supply rules for building sources it contributes
common/io.o: ../common/io.c
	@echo 'Building file: $<'
	@echo 'Executing target #11 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"common/io.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"common/io.o"
	@echo 'Finished building: $<'
	@echo ' '

common/printf.o: ../common/printf.c
	@echo 'Building file: $<'
	@echo 'Executing target #12 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"common/printf.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"common/printf.o"
	@echo 'Finished building: $<'
	@echo ' '

common/stdlib.o: ../common/stdlib.c
	@echo 'Building file: $<'
	@echo 'Executing target #13 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"common/stdlib.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"common/stdlib.o"
	@echo 'Finished building: $<'
	@echo ' '

common/uif.o: ../common/uif.c
	@echo 'Building file: $<'
	@echo 'Executing target #14 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"common/uif.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"common/uif.o"
	@echo 'Finished building: $<'
	@echo ' '



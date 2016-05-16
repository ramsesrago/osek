################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../Sources/service/queue.c" \

C_SRCS += \
../Sources/service/queue.c \

OBJS += \
./Sources/service/queue.o \

C_DEPS += \
./Sources/service/queue.d \

OBJS_QUOTED += \
"./Sources/service/queue.o" \

C_DEPS_QUOTED += \
"./Sources/service/queue.d" \

OBJS_OS_FORMAT += \
./Sources/service/queue.o \


# Each subdirectory must supply rules for building sources it contributes
Sources/service/queue.o: ../Sources/service/queue.c
	@echo 'Building file: $<'
	@echo 'Executing target #15 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/service/queue.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/service/queue.o"
	@echo 'Finished building: $<'
	@echo ' '



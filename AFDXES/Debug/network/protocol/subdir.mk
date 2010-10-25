################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../network/protocol/AFDX.cpp \
../network/protocol/common.cpp 

OBJS += \
./network/protocol/AFDX.o \
./network/protocol/common.o 

CPP_DEPS += \
./network/protocol/AFDX.d \
./network/protocol/common.d 


# Each subdirectory must supply rules for building sources it contributes
network/protocol/%.o: ../network/protocol/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/usr/local/include -I/usr/local/lib -I/usr/lib -O0 -g3 -Wall -Werror -c -fmessage-length=0 -Wno-deprecated -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../network/NetworkConfiguration.cpp \
../network/Reader.cpp \
../network/Receiver.cpp \
../network/Sniffer.cpp \
../network/Transmitter.cpp \
../network/common.cpp 

OBJS += \
./network/NetworkConfiguration.o \
./network/Reader.o \
./network/Receiver.o \
./network/Sniffer.o \
./network/Transmitter.o \
./network/common.o 

CPP_DEPS += \
./network/NetworkConfiguration.d \
./network/Reader.d \
./network/Receiver.d \
./network/Sniffer.d \
./network/Transmitter.d \
./network/common.d 


# Each subdirectory must supply rules for building sources it contributes
network/%.o: ../network/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/usr/local/include -I/usr/local/lib -I/usr/lib -O0 -g3 -Wall -Werror -c -fmessage-length=0 -Wno-deprecated -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



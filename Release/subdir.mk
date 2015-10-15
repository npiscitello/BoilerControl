################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
INO_SRCS += \
../Main.ino 

CPP_SRCS += \
../.ino.cpp \
../Circulator.cpp \
../EEPROM.cpp \
../Encoder.cpp \
../IO.cpp \
../LedControl.cpp \
../MetaManagement.cpp \
../TaskScheduler.cpp 

LINK_OBJ += \
./.ino.cpp.o \
./Circulator.cpp.o \
./EEPROM.cpp.o \
./Encoder.cpp.o \
./IO.cpp.o \
./LedControl.cpp.o \
./MetaManagement.cpp.o \
./TaskScheduler.cpp.o 

INO_DEPS += \
./Main.ino.d 

CPP_DEPS += \
./.ino.cpp.d \
./Circulator.cpp.d \
./EEPROM.cpp.d \
./Encoder.cpp.d \
./IO.cpp.d \
./LedControl.cpp.d \
./MetaManagement.cpp.d \
./TaskScheduler.cpp.d 


# Each subdirectory must supply rules for building sources it contributes
.ino.cpp.o: ../.ino.cpp
	@echo 'Building file: $<'
	@echo 'Starting C++ compile'
	"C:\Arduino\hardware\tools\avr/bin/avr-g++" -c -g -Os -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -MMD -mmcu=atmega328p -DF_CPU=16000000L -DARDUINO=10605 -DARDUINO_AVR_MINI -DARDUINO_ARCH_AVR     -I"C:\Arduino\hardware\arduino\avr\cores\arduino" -I"C:\Arduino\hardware\arduino\avr\variants\eightanaloginputs" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -D__IN_ECLIPSE__=1 -x c++ "$<"  -o  "$@"   -Wall
	@echo 'Finished building: $<'
	@echo ' '

Circulator.cpp.o: ../Circulator.cpp
	@echo 'Building file: $<'
	@echo 'Starting C++ compile'
	"C:\Arduino\hardware\tools\avr/bin/avr-g++" -c -g -Os -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -MMD -mmcu=atmega328p -DF_CPU=16000000L -DARDUINO=10605 -DARDUINO_AVR_MINI -DARDUINO_ARCH_AVR     -I"C:\Arduino\hardware\arduino\avr\cores\arduino" -I"C:\Arduino\hardware\arduino\avr\variants\eightanaloginputs" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -D__IN_ECLIPSE__=1 -x c++ "$<"  -o  "$@"   -Wall
	@echo 'Finished building: $<'
	@echo ' '

EEPROM.cpp.o: ../EEPROM.cpp
	@echo 'Building file: $<'
	@echo 'Starting C++ compile'
	"C:\Arduino\hardware\tools\avr/bin/avr-g++" -c -g -Os -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -MMD -mmcu=atmega328p -DF_CPU=16000000L -DARDUINO=10605 -DARDUINO_AVR_MINI -DARDUINO_ARCH_AVR     -I"C:\Arduino\hardware\arduino\avr\cores\arduino" -I"C:\Arduino\hardware\arduino\avr\variants\eightanaloginputs" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -D__IN_ECLIPSE__=1 -x c++ "$<"  -o  "$@"   -Wall
	@echo 'Finished building: $<'
	@echo ' '

Encoder.cpp.o: ../Encoder.cpp
	@echo 'Building file: $<'
	@echo 'Starting C++ compile'
	"C:\Arduino\hardware\tools\avr/bin/avr-g++" -c -g -Os -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -MMD -mmcu=atmega328p -DF_CPU=16000000L -DARDUINO=10605 -DARDUINO_AVR_MINI -DARDUINO_ARCH_AVR     -I"C:\Arduino\hardware\arduino\avr\cores\arduino" -I"C:\Arduino\hardware\arduino\avr\variants\eightanaloginputs" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -D__IN_ECLIPSE__=1 -x c++ "$<"  -o  "$@"   -Wall
	@echo 'Finished building: $<'
	@echo ' '

IO.cpp.o: ../IO.cpp
	@echo 'Building file: $<'
	@echo 'Starting C++ compile'
	"C:\Arduino\hardware\tools\avr/bin/avr-g++" -c -g -Os -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -MMD -mmcu=atmega328p -DF_CPU=16000000L -DARDUINO=10605 -DARDUINO_AVR_MINI -DARDUINO_ARCH_AVR     -I"C:\Arduino\hardware\arduino\avr\cores\arduino" -I"C:\Arduino\hardware\arduino\avr\variants\eightanaloginputs" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -D__IN_ECLIPSE__=1 -x c++ "$<"  -o  "$@"   -Wall
	@echo 'Finished building: $<'
	@echo ' '

LedControl.cpp.o: ../LedControl.cpp
	@echo 'Building file: $<'
	@echo 'Starting C++ compile'
	"C:\Arduino\hardware\tools\avr/bin/avr-g++" -c -g -Os -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -MMD -mmcu=atmega328p -DF_CPU=16000000L -DARDUINO=10605 -DARDUINO_AVR_MINI -DARDUINO_ARCH_AVR     -I"C:\Arduino\hardware\arduino\avr\cores\arduino" -I"C:\Arduino\hardware\arduino\avr\variants\eightanaloginputs" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -D__IN_ECLIPSE__=1 -x c++ "$<"  -o  "$@"   -Wall
	@echo 'Finished building: $<'
	@echo ' '

Main.o: ../Main.ino
	@echo 'Building file: $<'
	@echo 'Starting C++ compile'
	"C:\Arduino\hardware\tools\avr/bin/avr-g++" -c -g -Os -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -MMD -mmcu=atmega328p -DF_CPU=16000000L -DARDUINO=10605 -DARDUINO_AVR_MINI -DARDUINO_ARCH_AVR     -I"C:\Arduino\hardware\arduino\avr\cores\arduino" -I"C:\Arduino\hardware\arduino\avr\variants\eightanaloginputs" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -D__IN_ECLIPSE__=1 -x c++ "$<"  -o  "$@"   -Wall
	@echo 'Finished building: $<'
	@echo ' '

MetaManagement.cpp.o: ../MetaManagement.cpp
	@echo 'Building file: $<'
	@echo 'Starting C++ compile'
	"C:\Arduino\hardware\tools\avr/bin/avr-g++" -c -g -Os -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -MMD -mmcu=atmega328p -DF_CPU=16000000L -DARDUINO=10605 -DARDUINO_AVR_MINI -DARDUINO_ARCH_AVR     -I"C:\Arduino\hardware\arduino\avr\cores\arduino" -I"C:\Arduino\hardware\arduino\avr\variants\eightanaloginputs" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -D__IN_ECLIPSE__=1 -x c++ "$<"  -o  "$@"   -Wall
	@echo 'Finished building: $<'
	@echo ' '

TaskScheduler.cpp.o: ../TaskScheduler.cpp
	@echo 'Building file: $<'
	@echo 'Starting C++ compile'
	"C:\Arduino\hardware\tools\avr/bin/avr-g++" -c -g -Os -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -MMD -mmcu=atmega328p -DF_CPU=16000000L -DARDUINO=10605 -DARDUINO_AVR_MINI -DARDUINO_ARCH_AVR     -I"C:\Arduino\hardware\arduino\avr\cores\arduino" -I"C:\Arduino\hardware\arduino\avr\variants\eightanaloginputs" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -D__IN_ECLIPSE__=1 -x c++ "$<"  -o  "$@"   -Wall
	@echo 'Finished building: $<'
	@echo ' '



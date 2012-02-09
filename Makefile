###################################################################

CC = avr-gcc $(CPP_FLAGS)
LD = avr-gcc $(LD_FLAGS)
AR = avr-ar $(AR_FLAGS)
OBJCP = avr-objcopy
SIZE = avr-size -A --mcu=$(MCU)
AVRDUDE = avrdude
DUDE = -cstk500v1 -P$(PORT) -b$(UPLOAD_RATE) -D 
#DUDE = usbasp -D

LIBRARIES = arduino.a

# Customise project sources/objects/includes here  
SRC = src/ebike.cpp src/lib/Narcoleptic.cpp src/lib/NewSoftSerial.cpp src/lib/Adxl345.cpp  src/ebike-tools.cpp src/ebike-sleep.cpp src/ebike-accel.cpp src/ebike-controller.cpp src/ebike-sens.cpp src/ebike-bluetooth.cpp src/lib/Wire.cpp src/lib/twi.c src/lib/MeetAndroid.cpp
OBJECTS = src/ebike.o src/lib/Narcoleptic.o src/lib/NewSoftSerial.o src/lib/Adxl345.o src/ebike-tools.o src/ebike-sleep.o src/ebike-accel.o src/ebike-controller.o src/ebike-sens.o src/ebike-bluetooth.o src/lib/Wire.o src/lib/twi.o src/lib/MeetAndroid.o
INCLUDES = -I"/usr/lib/avr/include/avr" -I"./include" -I"src" -I"src/lib" -I"lib/arduino"

#
DEFINES = -DF_CPU=$(F_CPU)L -DARDUINO=22

#TODO
# OBJECTS = $(SRC:.c=.o) $(SRC:.cpp=.o) $(ASRC:.S=.o)
# SRC = $(foreach dir,$(SRCDST),$(wildcard $(dir)/*.c))
# OBJ = $(addsuffix .o, $(basename $(subst ${SRCDST},${OBJDST},${SRC})))


CPP_FLAGS = -g -Os -w -fno-exceptions -ffunction-sections -fdata-sections -mmcu=$(MCU) $(DEFINES) $(INCLUDES)
LD_FLAGS = -Os -Wl,--gc-sections -mmcu=$(MCU)
AR_FLAGS = rcs

USB=0
PORT = /dev/ttyUSB$(USB)
MCU = atmega328p
F_CPU = 8000000
FORMAT = ihex
UPLOAD_RATE = 57600
MAX_SIZE = 30720

OUTPUT = irmimic

all: $(LIBRARIES) $(OUTPUT).hex

arduino.a: lib/arduino/WString.o lib/arduino/wiring_digital.o lib/arduino/WMath.o lib/arduino/wiring_shift.o lib/arduino/pins_arduino.o lib/arduino/wiring.o lib/arduino/HardwareSerial.o lib/arduino/wiring_analog.o lib/arduino/Tone.o lib/arduino/main.o lib/arduino/wiring_pulse.o lib/arduino/Print.o lib/arduino/WInterrupts.o
	$(AR) arduino.a lib/arduino/WString.o
	$(AR) arduino.a lib/arduino/wiring_digital.o
	$(AR) arduino.a lib/arduino/WMath.o
	$(AR) arduino.a lib/arduino/wiring_shift.o
	$(AR) arduino.a lib/arduino/pins_arduino.o
	$(AR) arduino.a lib/arduino/wiring.o
	$(AR) arduino.a lib/arduino/HardwareSerial.o
	$(AR) arduino.a lib/arduino/wiring_analog.o
	$(AR) arduino.a lib/arduino/Tone.o
	$(AR) arduino.a lib/arduino/main.o
	$(AR) arduino.a lib/arduino/wiring_pulse.o
	$(AR) arduino.a lib/arduino/Print.o
	$(AR) arduino.a lib/arduino/WInterrupts.o

lib/arduino/WString.o: lib/arduino/WString.cpp
	$(CC) -c lib/arduino/WString.cpp -o lib/arduino/WString.o

lib/arduino/wiring_digital.o: lib/arduino/wiring_digital.c
	$(CC) -c lib/arduino/wiring_digital.c -o lib/arduino/wiring_digital.o

lib/arduino/WMath.o: lib/arduino/WMath.cpp
	$(CC) -c lib/arduino/WMath.cpp -o lib/arduino/WMath.o

lib/arduino/wiring_shift.o: lib/arduino/wiring_shift.c
	$(CC) -c lib/arduino/wiring_shift.c -o lib/arduino/wiring_shift.o

lib/arduino/pins_arduino.o: lib/arduino/pins_arduino.c
	$(CC) -c lib/arduino/pins_arduino.c -o lib/arduino/pins_arduino.o

lib/arduino/wiring.o: lib/arduino/wiring.c
	$(CC) -c lib/arduino/wiring.c -o lib/arduino/wiring.o

lib/arduino/HardwareSerial.o: lib/arduino/HardwareSerial.cpp
	$(CC) -c lib/arduino/HardwareSerial.cpp -o lib/arduino/HardwareSerial.o

lib/arduino/wiring_analog.o: lib/arduino/wiring_analog.c
	$(CC) -c lib/arduino/wiring_analog.c -o lib/arduino/wiring_analog.o

lib/arduino/Tone.o: lib/arduino/Tone.cpp
	$(CC) -c lib/arduino/Tone.cpp -o lib/arduino/Tone.o

lib/arduino/main.o: lib/arduino/main.cpp
	$(CC) -c lib/arduino/main.cpp -o lib/arduino/main.o

lib/arduino/wiring_pulse.o: lib/arduino/wiring_pulse.c
	$(CC) -c lib/arduino/wiring_pulse.c -o lib/arduino/wiring_pulse.o

lib/arduino/Print.o: lib/arduino/Print.cpp
	$(CC) -c lib/arduino/Print.cpp -o lib/arduino/Print.o

lib/arduino/WInterrupts.o: lib/arduino/WInterrupts.c
	$(CC) -c lib/arduino/WInterrupts.c -o lib/arduino/WInterrupts.o

#
#
# Compile: create object files from C++ source files.
.cpp.o:
	$(CC) -c $< -o $@

# Compile: create object files from C source files.
.c.o:
	$(CC) -c  $< -o $@

$(OUTPUT).elf: $(OBJECTS) $(LIBRARIES)
	$(LD) $(OBJECTS) $(LIBRARIES) -lm -o $(OUTPUT).elf

$(OUTPUT).hex: $(OUTPUT).elf
	$(OBJCP) -O ihex -R .eeprom $(OUTPUT).elf $(OUTPUT).hex
	$(SIZE) -A $(OUTPUT).hex 
  
  
.PHONY: upload clean

upload: all
	stty -F $(PORT) hupcl
	$(AVRDUDE) -p$(MCU) $(DUDE)  -Uflash:w:$(OUTPUT).hex:i 

clean:
	@rm -f $(LIBRARIES) $(OUTPUT).elf $(OUTPUT).hex $(shell find . -follow -name "*.o")
  
#Makefile: scripts/make.rb $(shell find src -follow -not -type f -newer Makefile)
#	@scripts/make.rb

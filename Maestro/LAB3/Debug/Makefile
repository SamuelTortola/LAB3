################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL := cmd.exe
RM := rm -rf

USER_OBJS :=

LIBS := 
PROJ := 

O_SRCS := 
C_SRCS := 
S_SRCS := 
S_UPPER_SRCS := 
OBJ_SRCS := 
ASM_SRCS := 
PREPROCESSING_SRCS := 
OBJS := 
OBJS_AS_ARGS := 
C_DEPS := 
C_DEPS_AS_ARGS := 
EXECUTABLES := 
OUTPUT_FILE_PATH :=
OUTPUT_FILE_PATH_AS_ARGS :=
AVR_APP_PATH :=$$$AVR_APP_PATH$$$
QUOTE := "
ADDITIONAL_DEPENDENCIES:=
OUTPUT_FILE_DEP:=
LIB_DEP:=
LINKER_SCRIPT_DEP:=

# Every subdirectory with source files must be described here
SUBDIRS :=  \
../UART


# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS +=  \
../main.c \
../UART/UART.c


PREPROCESSING_SRCS += 


ASM_SRCS += 


OBJS +=  \
main.o \
UART/UART.o

OBJS_AS_ARGS +=  \
main.o \
UART/UART.o

C_DEPS +=  \
main.d \
UART/UART.d

C_DEPS_AS_ARGS +=  \
main.d \
UART/UART.d

OUTPUT_FILE_PATH +=LAB3.elf

OUTPUT_FILE_PATH_AS_ARGS +=LAB3.elf

ADDITIONAL_DEPENDENCIES:=

OUTPUT_FILE_DEP:= ./makedep.mk

LIB_DEP+= 

LINKER_SCRIPT_DEP+= 


# AVR32/GNU C Compiler
./main.o: .././main.c
	@echo Building file: $<
	@echo Invoking: AVR/GNU C Compiler : 5.4.0
	$(QUOTE)D:\Programas\Microchip studio\7.0\toolchain\avr8\avr8-gnu-toolchain\bin\avr-gcc.exe$(QUOTE)  -x c -funsigned-char -funsigned-bitfields -DDEBUG  -I"D:\Programas\Microchip studio\7.0\Packs\Atmel\ATmega_DFP\2.1.506\include"  -Og -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -g2 -Wall -mmcu=atmega328p -B "D:\Programas\Microchip studio\7.0\Packs\Atmel\ATmega_DFP\2.1.506\gcc\dev\atmega328p" -c -std=gnu99 -MD -MP -MF "$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)"   -o "$@" "$<" 
	@echo Finished building: $<
	

UART/UART.o: ../UART/UART.c
	@echo Building file: $<
	@echo Invoking: AVR/GNU C Compiler : 5.4.0
	$(QUOTE)D:\Programas\Microchip studio\7.0\toolchain\avr8\avr8-gnu-toolchain\bin\avr-gcc.exe$(QUOTE)  -x c -funsigned-char -funsigned-bitfields -DDEBUG  -I"D:\Programas\Microchip studio\7.0\Packs\Atmel\ATmega_DFP\2.1.506\include"  -Og -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -g2 -Wall -mmcu=atmega328p -B "D:\Programas\Microchip studio\7.0\Packs\Atmel\ATmega_DFP\2.1.506\gcc\dev\atmega328p" -c -std=gnu99 -MD -MP -MF "$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)"   -o "$@" "$<" 
	@echo Finished building: $<
	




# AVR32/GNU Preprocessing Assembler



# AVR32/GNU Assembler




ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: $(OUTPUT_FILE_PATH) $(ADDITIONAL_DEPENDENCIES)

$(OUTPUT_FILE_PATH): $(OBJS) $(USER_OBJS) $(OUTPUT_FILE_DEP) $(LIB_DEP) $(LINKER_SCRIPT_DEP)
	@echo Building target: $@
	@echo Invoking: AVR/GNU Linker : 5.4.0
	$(QUOTE)D:\Programas\Microchip studio\7.0\toolchain\avr8\avr8-gnu-toolchain\bin\avr-gcc.exe$(QUOTE) -o$(OUTPUT_FILE_PATH_AS_ARGS) $(OBJS_AS_ARGS) $(USER_OBJS) $(LIBS) -Wl,-Map="LAB3.map" -Wl,--start-group -Wl,-lm  -Wl,--end-group -Wl,-L"D:\samue\Escritorio\OneDrive - UVG\UVG\Año 2024\Semestre 2\Digital 2\Practicas\Practica 3_2do semestre\LAB3\Maestro\UART"  -Wl,--gc-sections -mmcu=atmega328p -B "D:\Programas\Microchip studio\7.0\Packs\Atmel\ATmega_DFP\2.1.506\gcc\dev\atmega328p"  
	@echo Finished building target: $@
	"D:\Programas\Microchip studio\7.0\toolchain\avr8\avr8-gnu-toolchain\bin\avr-objcopy.exe" -O ihex -R .eeprom -R .fuse -R .lock -R .signature -R .user_signatures  "LAB3.elf" "LAB3.hex"
	"D:\Programas\Microchip studio\7.0\toolchain\avr8\avr8-gnu-toolchain\bin\avr-objcopy.exe" -j .eeprom  --set-section-flags=.eeprom=alloc,load --change-section-lma .eeprom=0  --no-change-warnings -O ihex "LAB3.elf" "LAB3.eep" || exit 0
	"D:\Programas\Microchip studio\7.0\toolchain\avr8\avr8-gnu-toolchain\bin\avr-objdump.exe" -h -S "LAB3.elf" > "LAB3.lss"
	"D:\Programas\Microchip studio\7.0\toolchain\avr8\avr8-gnu-toolchain\bin\avr-objcopy.exe" -O srec -R .eeprom -R .fuse -R .lock -R .signature -R .user_signatures "LAB3.elf" "LAB3.srec"
	"D:\Programas\Microchip studio\7.0\toolchain\avr8\avr8-gnu-toolchain\bin\avr-size.exe" "LAB3.elf"
	
	





# Other Targets
clean:
	-$(RM) $(OBJS_AS_ARGS) $(EXECUTABLES)  
	-$(RM) $(C_DEPS_AS_ARGS)   
	rm -rf "LAB3.elf" "LAB3.a" "LAB3.hex" "LAB3.lss" "LAB3.eep" "LAB3.map" "LAB3.srec" "LAB3.usersignatures"
	
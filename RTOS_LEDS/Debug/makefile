################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include RTOS_Layer/subdir.mk
-include MCAL/Timer_V2/subdir.mk
-include MCAL/EXTINT_V1/subdir.mk
-include MCAL/DIO_V1/subdir.mk
-include HAL/SEG_Handler/subdir.mk
-include HAL/LEDS_Handler/subdir.mk
-include HAL/LCD_Handler/subdir.mk
-include APP/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
LSS += \
RTOS_LEDS.lss \

FLASH_IMAGE += \
RTOS_LEDS.hex \

SIZEDUMMY += \
sizedummy \


# All Target
all: RTOS_LEDS.elf secondary-outputs

# Tool invocations
RTOS_LEDS.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C Linker'
	avr-gcc -Wl,-Map,RTOS_LEDS.map -mmcu=atmega32 -o "RTOS_LEDS.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

RTOS_LEDS.lss: RTOS_LEDS.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S RTOS_LEDS.elf  >"RTOS_LEDS.lss"
	@echo 'Finished building: $@'
	@echo ' '

RTOS_LEDS.hex: RTOS_LEDS.elf
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -R .fuse -R .lock -R .signature -O ihex RTOS_LEDS.elf  "RTOS_LEDS.hex"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: RTOS_LEDS.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=atmega32 RTOS_LEDS.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(FLASH_IMAGE)$(ELFS)$(OBJS)$(ASM_DEPS)$(S_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS)$(LSS)$(C_DEPS) RTOS_LEDS.elf
	-@echo ' '

secondary-outputs: $(LSS) $(FLASH_IMAGE) $(SIZEDUMMY)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets

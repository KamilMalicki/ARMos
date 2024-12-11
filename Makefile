# kompilery i linkery
AS = arm-none-eabi-as
LD = arm-none-eabi-ld
OBJCOPY = arm-none-eabi-objcopy

# CPU typ
CPU = -mcpu=arm926ej-s

# START
STARTUP_SRC = startup.s
TEST_SRC = kernel.s
LINKER_SCRIPT = linker.ld

# END
STARTUP_OBJ = startup.o
TEST_OBJ = kernel.o
ELF_FILE = kernel.elf
BIN_FILE = kernel.bin

# jesli samo make
all: $(BIN_FILE)

# .s na .o
$(STARTUP_OBJ): $(STARTUP_SRC)
	$(AS) $(CPU) $< -o $@

$(TEST_OBJ): $(TEST_SRC)
	$(AS) $(CPU) $< -o $@

# .o w jedno i na .elf
$(ELF_FILE): $(STARTUP_OBJ) $(TEST_OBJ)
	$(LD) -T $(LINKER_SCRIPT) $^ -o $@

# na elf
$(BIN_FILE): $(ELF_FILE)
	$(OBJCOPY) -O binary $< $@

# czysczenie smieci
clean:
	rm -f $(STARTUP_OBJ) $(TEST_OBJ) $(ELF_FILE) $(BIN_FILE)

qemu:
	qemu-system-arm -machine versatilepb -nographic -kernel kernel.bin

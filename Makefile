# Kompilery i linkery
CC = arm-none-eabi-gcc
AS = arm-none-eabi-as
LD = arm-none-eabi-ld
OBJCOPY = arm-none-eabi-objcopy

# Typ CPU i flagi kompilacji
CPU = -mcpu=arm926ej-s
CFLAGS = $(CPU) -nostdlib -ffreestanding -Wall -Wextra -O2
LDFLAGS = -T $(LINKER_SCRIPT)

# Pliki źródłowe
STARTUP_SRC = startup.s
TEST_SRC = kernel.c
LINKER_SCRIPT = linker.ld

# Pliki wynikowe
STARTUP_OBJ = startup.o
TEST_OBJ = kernel.o
ELF_FILE = kernel.elf
BIN_FILE = kernel.bin

# Główne cele
all: $(BIN_FILE)

# Kompilacja asemblera na .o
$(STARTUP_OBJ): $(STARTUP_SRC)
	$(AS) $(CPU) $< -o $@

# Kompilacja C na .o
$(TEST_OBJ): $(TEST_SRC)
	$(CC) $(CFLAGS) -c $< -o $@

# Łączenie obiektów w .elf
$(ELF_FILE): $(STARTUP_OBJ) $(TEST_OBJ)
	$(LD) $(LDFLAGS) $^ -o $@

# Konwersja .elf na binarny
$(BIN_FILE): $(ELF_FILE)
	$(OBJCOPY) -O binary $< $@

# Czyszczenie
clean:
	rm -f $(STARTUP_OBJ) $(TEST_OBJ) $(ELF_FILE) $(BIN_FILE)

# Uruchamianie w QEMU
qemu:
	qemu-system-arm -machine versatilepb -nographic -kernel $(BIN_FILE)

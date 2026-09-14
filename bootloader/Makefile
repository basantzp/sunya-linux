NASM = nasm
NASM_FLAGS = -f bin

all: bootloader.bin

bootloader.bin: bootloader.asm
	$(NASM) $(NASM_FLAGS) -o $@ $<

clean:
	rm -f bootloader.bin

.PHONY: all clean

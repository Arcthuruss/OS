all: build/final/os-image

build/final/os-image: build/boot/bootSector.bin build/kernel/kernel.bin
	cat $^ > $@

C_SOURCES = $(wildcard source/kernel/*.c source/drivers/*.c)
OBJ = ${C_SOURCES:source/%.c=build/%.o}

HEADERS = $(wildcard source/kernel/*.h source/drivers/*.h)

build/kernel/kernel.bin: build/kernel/kernel_entry.o ${OBJ}
	ld -o $@ -Ttext 0x1000 $^ --oformat binary

build/%.o: source/%.asm
	nasm $< -f elf64 -o $@

build/%.o : source/%.c ${HEADERS}
	gcc -ffreestanding -Wno-implicit-function-declaration -c $< -o $@

build/boot/bootSector.bin: source/boot/bootSector.asm
	nasm $< -f bin -o $@

.PHONY: clean
clean:
	rm build -r || true
	rm kernel.dis || true
	mkdir build
	mkdir build/boot build/kernel build/drivers build/final

.PHONY: run
run: all
	qemu-system-x86_64 -drive format=raw,file=build/final/os-image,if=floppy

kernel.dis: build/kernel/kernel.bin
	ndisasm -b 32 $< > $@


# CONSTANTS
KERNEL_NAME = kernel-kfs.2.rleseur
ISO_NAME = kfs-1.rleseur.iso

BUILD_DIR = build/
ISO_DIR = ${BUILD_DIR}iso/
ISO_BOOT_DIR = ${ISO_DIR}boot/
ISO_GRUB_DIR = ${ISO_BOOT_DIR}grub/
SRC_DIR = src/

BOOT_DIR = ${SRC_DIR}boot/
KERNEL_DIR = ${SRC_DIR}kernel/
LD_DIR = ${SRC_DIR}

BOOT_FILES = boot.asm
KERNEL_FILES = kernel.c keyboard.c terminal.c screen.c string.c printk.c cursor.c scroll.c gdt.c
LD_FILES = link.ld

BOOT_SRC = ${addprefix ${BOOT_DIR}, ${BOOT_FILES}}
KERNEL_SRC = ${addprefix ${KERNEL_DIR}, ${KERNEL_FILES}}
LD_SRC = ${addprefix ${LD_DIR}, ${LD_FILES}}

OBJS = ${BOOT_FILES:.asm=.o} ${KERNEL_FILES:.c=.o}
BUILD_OBJS = ${addprefix ${BUILD_DIR}, ${OBJS}}

AS = nasm
CC = gcc
LD = ld
GRUB = grub2-mkrescue
QEMU = qemu-system-i386

AS_FLAGS = -f elf32
CC_FLAGS = -m32 -fno-builtin -fno-exceptions -fno-stack-protector -nostdlib -nodefaultlibs
LD_FLAGS = -m elf_i386 -z noexecstack

# RULES
all: ${BUILD_OBJS}
	${LD} ${LD_FLAGS} -T ${LD_SRC} -o ${KERNEL_NAME} ${BUILD_OBJS}

run-kernel: all
	${QEMU} -kernel ${KERNEL_NAME}

iso: all
	mkdir -p ${ISO_GRUB_DIR}
	cp ${KERNEL_NAME} ${ISO_BOOT_DIR}
	cp grub.cfg ${ISO_GRUB_DIR}
	${GRUB} -o ${ISO_NAME} ${ISO_DIR}

run-iso: iso
	${QEMU} -cdrom ${ISO_NAME}

${BUILD_DIR}%.o: ${BOOT_DIR}%.asm
	mkdir -p ${BUILD_DIR}
	${AS} ${AS_FLAGS} $< -o $@

${BUILD_DIR}%.o: ${KERNEL_DIR}%.c
	mkdir -p ${BUILD_DIR}
	${CC} ${CC_FLAGS} -c $< -o $@

clean:
	rm -rf ${BUILD_DIR}

fclean: clean
	rm -rf ${KERNEL_NAME} ${ISO_NAME}

re: fclean all

.PHONY: all run-kernel iso run-iso clean fclean re

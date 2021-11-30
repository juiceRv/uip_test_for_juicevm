.PHONY:all clean
CROSS_COMPILE?=riscv64-unknown-elf-
# CROSS_COMPILE?=riscv-none-embed-
# CROSS_COMPILE?=/opt/xpack-riscv-none-embed-gcc-8.3.0-2.1/bin/riscv-none-embed-
# CROSS_COMPILE?=/mnt/ssd_prj/juicevm_gcc_embed_toolchains/bin/riscv64-unknown-elf-
PRJ_NAME  ?=uip_test

AS 		:= $(CROSS_COMPILE)gcc -x assembler-with-cpp
CC 		:= $(CROSS_COMPILE)gcc
OBJDUMP := $(CROSS_COMPILE)objdump
OBJCOPY := $(CROSS_COMPILE)objcopy
LD		:= $(CROSS_COMPILE)ld

DEVICE := -march=rv64ima -mabi=lp64 -mcmodel=medany
# -fno-builtin
CFLAGS  	:=  -static \
				-ffunction-sections \
				-fdata-sections \
				-fno-builtin -fno-builtin-printf -Os -D__CURRENT_COMPILE_RV_VERSION_=32

CFLAGS		+= $(DEVICE)

OBJFLASGS 	:= --disassemble-all \
				--disassemble-zeroes \
				--section=.text \
				--section=.text.startup \
				--section=.text.init \
				--section=.data

LDFLAGS		:= $(DEVICE) 
LDFLAGS		+= -nostartfiles
LDFLAGS     += -T$(PRJ_NAME)_link.ld -lm

CFLAGS      += -D__riscv_xlen=64 -D__riscv64 
CFLAGS      += -I ../../ 
CFLAGS      += -I .
CFLAGS      += -I printf
CFLAGS      += -I uip/uip
CFLAGS      += -I uip/apps/dhcpc
CFLAGS      += -Dperipheral_device_netcard0=1
CFLAGS      += -DFT_CONFIG_OPTION_NO_DEFAULT_SYSTEM
CFLAGS      += -DFT_CONFIG_OPTION_DISABLE_STREAM_SUPPORT
CFLAGS      += -D__riscv -D__riscv_xlen=64 -DTLSF_64BIT




SRCS       := main.c

SRCS       += printf/printf.c
# SRCS       += tlsf.c
SRCS       += clock-arch.c
SRCS       += uip/uip/psock.c
SRCS       += uip/uip/timer.c
SRCS       += uip/uip/uip_arp.c
SRCS       += uip/uip/uip-neighbor.c
SRCS       += uip/uip/uip.c
SRCS       += uip/uip/uiplib.c
SRCS       += uip/apps/dhcpc/dhcpc.c

ASMS       := start.S
OBJS       := $(SRCS:.c=.o)
OBJ        := $(ASMS:.S=.o)

LINK_OBJS += $(OBJS) $(OBJ)

all: $(PRJ_NAME).bin $(PRJ_NAME)_dump.s

$(OBJ): %.o : %.S
	@echo [AS] $<
	@$(AS) $(CFLAGS) -c $< -o $@

$(OBJS): %.o:%.c
	@echo [CC] $<
	@$(CC) $(CFLAGS) -c $< -o $@

$(PRJ_NAME).elf:$(OBJ) $(OBJS) 
	@echo [LD] Linking $@
	$(CC) $(LINK_OBJS) $(LDFLAGS) -o $@

$(PRJ_NAME).bin:$(PRJ_NAME).elf
	@echo [LD] Linking $@
	@$(OBJCOPY) -O binary $< $@

$(PRJ_NAME)_dump.s:$(PRJ_NAME).elf
	@echo [OD] Objdump $@ $<
	@$(OBJDUMP) $(OBJFLASGS) $< > $@

clean:
	rm $(OBJS) $(OBJ) $(PRJ_NAME).bin $(PRJ_NAME).elf $(PRJ_NAME).map $(PRJ_NAME)_dump.s


# juicevm_gcc_embed_toolchains build arg:./configure --prefix=/mnt/ssd_prj/juicevm_gcc_embed_toolchains --with-arch=rv64ima --with-abi=lp64 --disable-linux --with-cmodel=medany && make -j

# [core]
#         repositoryformatversion = 0
#         filemode = false
#         bare = false
#         logallrefupdates = true
#         sshCommand = "ssh -i ~/.ssh/juiceRv "
# [remote "origin"]
#         url = git@github.com:juiceRv/juicevm_gcc_embed_toolchains.git
#         fetch = +refs/heads/*:refs/remotes/origin/*
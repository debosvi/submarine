
SHELL            = /bin/bash

PROJECT         :=  Blinky
SOURCE_ROOT     :=  ../..
BUILD_DIR       :=  build

INCLUDE_DIR     :=  -I$(SOURCE_ROOT)/Source/include \
                    -I$(SOURCE_ROOT)/Source/portable/IA32_flat \
                    -I$(SOURCE_ROOT)/Source/portable/Support_Files \
                    -I$(SOURCE_ROOT)/Demo/Common/include \
                    -I$(SOURCE_ROOT)/Demo/$(PROJECT)
SOURCE_DIR      :=  $(SOURCE_ROOT)/Source \
                    $(SOURCE_ROOT)/Demo/$(PROJECT)
SOURCE_EXCLUDE  :=  $(SOURCE_ROOT)/Source/portable/MemMang/heap_1.c \
                    $(SOURCE_ROOT)/Source/portable/MemMang/heap_2.c \
                    $(SOURCE_ROOT)/Source/portable/MemMang/heap_3.c \
                    $(SOURCE_ROOT)/Source/portable/MemMang/heap_5.c \
                    $(SOURCE_ROOT)/Demo/Common

OBJECT_ROOT     :=  $(BUILD_DIR)/obj
BUILD           :=  $(BUILD_DIR)/$(PROJECT).elf
TARGET          :=  $(BUILD_DIR)/$(PROJECT).iso
GRUB_FILE       :=  $(BUILD_DIR)/grub.cfg
MAP             :=  $(BUILD_DIR)/$(PROJECT).map

LDS             :=  $(SOURCE_ROOT)/Source/portable/IA32_flat/elf_ia32_efi.lds

find             =  $(filter-out $(SOURCE_EXCLUDE),$(wildcard $1/$2)) \
                    $(foreach dir,$(filter-out $(SOURCE_EXCLUDE),$(wildcard $1/*)),$(call find,$(dir),$2))
SOURCE_C        :=  $(foreach dir,$(SOURCE_DIR),$(call find,$(dir),*.c))
SOURCE_S        :=  $(foreach dir,$(SOURCE_DIR),$(call find,$(dir),*.S))
OBJECT          :=  $(patsubst $(SOURCE_ROOT)%,$(OBJECT_ROOT)%,$(patsubst %.c,%.o,$(SOURCE_C))) \
                    $(patsubst $(SOURCE_ROOT)%,$(OBJECT_ROOT)%,$(patsubst %.S,%.o,$(SOURCE_S)))

                    
CROSS_PREFIX    ?=  i686-elf-
AS              :=  $(CROSS_PREFIX)gcc
CC              :=  $(CROSS_PREFIX)gcc
LD              :=  $(CROSS_PREFIX)gcc

# PERF_FLAGS      :=  -O0 -ggdb
PERF_FLAGS      :=  -O2

SFLAGS          :=  $(INCLUDE_DIR) -Wa,--gdwarf2 -Wa,-march=pentium -c
CFLAGS          :=  $(INCLUDE_DIR) $(PERF_FLAGS) -Wall -Wextra -std=gnu99 -ffreestanding
LDFLAGS         :=  -nostdlib -Xlinker -T -Xlinker $(LDS) -Xlinker -Map=$(MAP) -Xlinker --gc-sections
LIBS            :=  -lgcc -lg


ISODIR_NAME      =  $(BUILD_DIR)/isodir

.PHONY: clean

all: $(TARGET)

$(BUILD): $(OBJECT)
	$(LD) -o $(BUILD) $(LDFLAGS) $(OBJECT) $(LIBS)

$(OBJECT_ROOT)/%.o: $(SOURCE_ROOT)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -o $@ -c $<

$(OBJECT_ROOT)/%.o: $(SOURCE_ROOT)/%.S
	@mkdir -p $(dir $@)
	$(AS) $(SFLAGS) -o $@ $<

clean:
	rm -rf $(BUILD_DIR)

$(TARGET): $(BUILD) $(GRUB_FILE)
	mkdir -p $(ISODIR_NAME)/boot/grub
	cp $(BUILD) $(ISODIR_NAME)/boot/$(PROJECT).elf
	cp $(GRUB_FILE) $(ISODIR_NAME)/boot/grub/grub.cfg
	grub-mkrescue -o $(TARGET) $(ISODIR_NAME)
	
check: $(BUILD)
	if [ `grub-file --is-x86-multiboot $(shell pwd)/$(BUILD)` ]; then echo -e "multiboot confirmed"; else echo -e "the file is not multiboot"; fi
	
qemu-kernel: $(BUILD)
	qemu-system-i386 -kernel $^
	
qemu-iso: $(TARGET)
	qemu-system-i386 -cdrom $^
	
$(GRUB_FILE): grub.cfg.tmpl
	sed -e s/%BUILD%/$(PROJECT).elf/g $^ > $@
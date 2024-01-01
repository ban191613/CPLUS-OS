GPPPARAMS = -m32 -Iinclude -fno-use-cxa-atexit -fleading-underscore -fno-exceptions -fno-builtin -nostdlib -fno-rtti -fno-pie

ASPARAMS = --32
LDPARAMS = -melf_i386 -no-pie

objects = obj/loader.o \
		  obj/kernel.o \
          obj/gdt.o \
		  obj/common/print.o \
          obj/drivers/driver.o \
		  obj/drivers/keyboard.o \
          obj/drivers/mouse.o \
          obj/hardWareCommunication/port.o \
          obj/hardWareCommunication/interruption.o \
          obj/hardWareCommunication/interrupts.o 
# 		  obj/memorymanagement.o \
# 		  obj/hardWareCommunication/pci.o \
# 		  obj/multitasking.o \
# 		  obj/drivers/amd_am79c973.o \
# 		  obj/drivers/vga.o \
# 		  obj/gui/widget.o \
# 		  obj/gui/window.o \
# 		  obj/gui/desktop.o \
# 		  obj/net/etherframe.o \
# 		  obj/net/arp.o \
# 		  obj/net/ipv4.o \
# 		  obj/net/icmp.o \
# 		  obj/net/udp.o \
# 		  obj/net/tcp.o \
          

obj/%.o: src/%.cpp
	mkdir -p $(@D)
	g++ ${GPPPARAMS} -o $@ -c $<

obj/%.o: src/%.s
	mkdir -p $(@D)	
	as ${ASPARAMS} -o $@ $<

mykernel.bin: linker.ld ${objects}
	ld ${LDPARAMS} -T $< -o $@ ${objects}

install: mykernel.bin
	sudo cp $< /boot/mykernel.bin

mykernel.iso: mykernel.bin
	mkdir iso
	mkdir iso/boot
	mkdir iso/boot/grub
	cp $< iso/boot/
	echo 'set timeout=0' > iso/boot/grub/grub.cfg
	echo 'set default=0' >> iso/boot/grub/grub.cfg
	echo '' >> iso/boot/grub/grub.cfg
	echo 'menuentry "my os" {' >> iso/boot/grub/grub.cfg
	echo 'multiboot /boot/mykernel.bin' >> iso/boot/grub/grub.cfg
	echo 'boot' >> iso/boot/grub/grub.cfg
	echo '}' >> iso/boot/grub/grub.cfg
	grub-mkrescue --output=$@ iso
	cp -u mykernel.iso /mnt/hgfs/share

.PHONY: clean
clean:
	rm -r iso mykernel.bin mykernel.iso obj
run:
	make clean
	make mykernel.iso

GPPPARAMS = -m32 -Iinclude -fno-use-cxa-atexit -fleading-underscore -fno-exceptions -fno-builtin -nostdlib -fno-rtti -fno-pie

ASPARAMS = --32
LDPARAMS = -melf_i386 -no-pie

objects = loader.o kernel.o gdt.o port.o interrupts.o interruption.o print.o keyboard.o mouse.o driver.o

%.o: %.cpp
	g++ ${GPPPARAMS} -o $@ -c $<

%.o: %.s
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
	rm -r iso mykernel.bin mykernel.iso ${objects} 
run:
	make clean
	make mykernel.iso

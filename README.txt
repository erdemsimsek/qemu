Compiling directly from toolchain

arm-none-eabi-as --warn -mcpu=cortex-m0 flash.s -o flash.o

arm-none-eabi-gcc -Wall -O2 -nostdlib -nostartfiles -ffreestanding  -mcpu=cortex-m0 -mthumb -c uart01.c -o uart01.o

arm-none-eabi-ld -o uart01.elf -T flash.ld flash.o uart01.o

arm-none-eabi-objdump -D uart01.elf > uart01.list

arm-none-eabi-objcopy uart01.elf uart01.bin -O binary


Qemu Commands

Normal Run
qemu-system-arm.exe logfile=serial.log -M lm3s811evb -m 16K -kernel uart01.bin

Log into file
qemu-system-arm.exe -chardev stdio,id=char0,logfile=serial.log, -serial chardev:char0 -M lm3s811evb -m 16K -kernel uart01.bin

Serial ciktiyi udp yolluyor
qemu-system-arm.exe -chardev udp,id=char0,host=192.168.1.106,port=5000,ipv4 -serial chardev:char0 -M lm3s811evb -m 16K -kernel uart01.bin

Compile proj

arm-none-eabi-as --warn -mcpu=cortex-m0 flash.s -o flash.o

arm-none-eabi-gcc -Wall -O2 -nostdlib -nostartfiles -ffreestanding  -mcpu=cortex-m0 -mthumb -c uart01.c -o uart01.o

arm-none-eabi-ld -o uart01.elf -T flash.ld flash.o uart01.o

arm-none-eabi-objdump -D uart01.elf > uart01.list

arm-none-eabi-objcopy uart01.elf uart01.bin -O binary


qemu-system-arm.exe -chardev pipe,id=char0,path=qemu -serial chardev:char0 -M lm3s811evb -m 16K -kernel uart01.bin


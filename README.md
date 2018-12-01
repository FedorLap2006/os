# Preamble
Bochs-oriented OS for older computers and fun

* This OS supports for 386-486SX processors.
* IDE Controller supports for Hard Drive.
* SATA not support
* ACPI not support
* PCI not support
* VESA BIOS LFB on startup only
* OS written just for fun.

# How install it

* First, install bochs with config:

1. ./configure --enable-x86-64 --enable-debugger --enable-disasm --enable-readline --with-all-libs --with-x11
2. make
3. make install

* Configure *.bxrc file with it:

  display_library: x, options="gui_debug"
  magic_break: enabled=1
  boot: disk
  
* dd if=/dev/zero of=disk.img bs=1024 count=262144
* fdisk disk.img
* Commands: n / p / 1 / 2048 / 524287 / t / 0B / w
* losetup -o 1048576 /dev/loop1 disk.img
* mkfs.fat -F32 /dev/loop1
* losetup -d /dev/loop1
* mkdir disk
* sudo mount disk.img -t vfat -o loop,rw,uid="__my_uid__",sync,offset=$[1048576] disk/

P.S. На русском.

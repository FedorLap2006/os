#!/bin/sh

# Example for run. Don't run this shell from command line, it's not working
mount disk.img -t vfat -o loop,rw,uid=`whoami`,sync,offset=$[1048576] disk/

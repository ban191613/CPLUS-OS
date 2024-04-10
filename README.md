# Ubuntu 22.04 min-install

``` shell
    sudo apt install make 

    sudo apt install g++

    sudo apt install xorriso

    sudo apt install grub-efi-amd64

    

    sudo apt-get remove open-vm-tools

    sudo apt-get purge --auto-remove open-vm-tools

```
``` shell
    vmware-hgfsclient

    sudo mkdir /mnt/hgfs

    sudo vmhgfs-fuse .host:/ /mnt/hgfs -o allow_other

    sudo apt install vim 

    sudo vim /etc/fstab   

        file  /etc/fstab  insert 
    
        .host:/  /mnt/hgfs  fuse.vmhgfs-fuse  allow_other  0  0

    make clean

    make mykernel.iso
```
# Virutual Box  version 6.1

ROM:64M  

no hard disk 
 
system:other DOS

## code style
``` shell
clang-format -style=Microsoft -dump-config > .clang-format
```
# Reference
https://github.com/AlgorithMan-de


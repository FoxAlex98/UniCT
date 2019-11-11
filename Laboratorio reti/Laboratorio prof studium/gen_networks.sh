#!/bin/bash

VBoxManage snapshot Base delete Snapshot
VBoxManage snapshot Base take Snapshot

VBoxManage clonevm Base --snapshot Snapshot --name A --options link --register
VBoxManage modifyvm A --memory 128 --nic1 intnet --intnet1 lan01 --nic2 none --nic3 none --nic4 none

VBoxManage clonevm Base --snapshot Snapshot --name B --options link --register
VBoxManage modifyvm B --memory 128 --nic1 intnet --intnet1 lan02 --nic2 none --nic3 none --nic4 none

VBoxManage clonevm Base --snapshot Snapshot --name C --options link --register
VBoxManage modifyvm C --memory 128 --nic1 intnet --intnet1 lan02 --nic2 none --nic3 none --nic4 none

VBoxManage clonevm Base --snapshot Snapshot --name D --options link --register
VBoxManage modifyvm D --memory 128 --nic1 intnet --intnet1 lan03 --nic2 none --nic3 none --nic4 none

VBoxManage clonevm Base --snapshot Snapshot --name E --options link --register
VBoxManage modifyvm E --memory 128 --nic1 intnet --intnet1 lan03 --nic2 none --nic3 none --nic4 none

VBoxManage clonevm Base --snapshot Snapshot --name F --options link --register
VBoxManage modifyvm F --memory 128 --nic1 intnet --intnet1 lan04 --nic2 none --nic3 none --nic4 none

VBoxManage clonevm Base --snapshot Snapshot --name G --options link --register
VBoxManage modifyvm G --memory 128 --nic1 intnet --intnet1 lan04 --nic2 none --nic3 none --nic4 none

VBoxManage clonevm Base --snapshot Snapshot --name H --options link --register
VBoxManage modifyvm H --memory 128 --nic1 intnet --intnet1 lan05 --nic2 none --nic3 none --nic4 none

VBoxManage clonevm Base --snapshot Snapshot --name J --options link --register
VBoxManage modifyvm J --memory 128 --nic1 intnet --intnet1 lan05 --nic2 none --nic3 none --nic4 none

VBoxManage clonevm Base --snapshot Snapshot --name X --options link --register
VBoxManage modifyvm X --memory 128 --nic1 intnet --intnet1 lanISP --nic2 none --nic3 none --nic4 none

VBoxManage clonevm Base --snapshot Snapshot --name R0 --options link --register
VBoxManage modifyvm R0 --memory 128 --nic1 intnet --intnet1 lan00 --nic2 intnet --intnet2 lan01 --nic3 none --nic4 none

VBoxManage clonevm Base --snapshot Snapshot --name R1 --options link --register
VBoxManage modifyvm R1 --memory 128 --nic1 intnet --intnet1 lan01 --nic2 intnet --intnet2 lan02 --nic3 intnet --intnet3 lan03 --nic4 none

VBoxManage clonevm Base --snapshot Snapshot --name R2 --options link --register
VBoxManage modifyvm R2 --memory 128 --nic1 intnet --intnet1 lan01 --nic2 intnet --intnet2 lan04 --nic3 intnet --intnet3 lan05 --nic4 none

VBoxManage clonevm Base --snapshot Snapshot --name ISP --options link --register
VBoxManage modifyvm ISP --memory 128 --nic1 intnet --intnet1 lanISP --nic2 intnet --intnet2 lan00 --nic3 none --nic4 none

VBoxManage clonevm Base --snapshot Snapshot --name ISP2 --options link --register
VBoxManage modifyvm ISP2 --memory 128 --nic1 intnet --intnet1 lanISP --nic2 intnet --intnet2 lan00 --nic3 none --nic4 none

VBoxManage clonevm Base --snapshot Snapshot --name ISP3 --options link --register
VBoxManage modifyvm ISP3 --memory 128 --nic1 intnet --intnet1 lanISP --nic2 intnet --intnet2 lan00 --nic3 none --nic4 none

VBoxManage clonevm Base --snapshot Snapshot --name ISP4 --options link --register
VBoxManage modifyvm ISP4 --memory 128 --nic1 intnet --intnet1 lanISP --nic2 intnet --intnet2 lan00 --nic3 none --nic4 none

VBoxManage clonevm Base --snapshot Snapshot --name ISP5 --options link --register
VBoxManage modifyvm ISP5 --memory 128 --nic1 intnet --intnet1 lanISP --nic2 intnet --intnet2 lan00 --nic3 none --nic4 none

VBoxManage clonevm Base --snapshot Snapshot --name ISP6 --options link --register
VBoxManage modifyvm ISP6 --memory 128 --nic1 intnet --intnet1 lanISP --nic2 intnet --intnet2 lan00 --nic3 none --nic4 none

VBoxManage clonevm Base --snapshot Snapshot --name ISP7 --options link --register
VBoxManage modifyvm ISP7 --memory 128 --nic1 intnet --intnet1 lanISP --nic2 intnet --intnet2 lan00 --nic3 none --nic4 none


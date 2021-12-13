
# *PrintParted* 

*PrintParted is a program for viewing the disk partition table without disk operations. Disk partitions and freespace are shown in a pie chart using the Qt-5.15 framework. It can be useful for quickly finding information about disk partitions. In some cases, it is useful for someone to use information about disk sectors and freespace before disk operations.* 


# *Basic Functionality*

*This contains two tables with description disks and partitions of each disk. Pie chart contains information about disk partitions and freespace 
of each disk in percentage. Freespace is displaying after pressing Enter on selected row. Also, disk partitions and freespace are displaying in the context menu in table with description disks. In this case, freespace means space outside of already generated partitions and can be used to expand existing partition or create new one.* 


# *Building a Dynamically Linked Version*

*Libraries required for Ubuntu, Debian:*<br />
`libparted.so.2` `libQt5Charts.so.5` `libQt5Widgets.so.5` `libQt5Gui.so.5` `libQt5Core.so.5` `libstdc++.so.6` `libgcc_s.so.1` `libc.so.6`<br />

*Libraries required for Red Hat, Centos, Fedora:*<br />
`libparted.so.2` `libQt5Charts.so.5` `libQt5Widgets.so.5` `libQt5Gui.so.5` `libQt5Core.so.5` `libGL.so.1` `libpthread.so.0` `libstdc++.so.6` `libm.so.6`
`libgcc_s.so.1` `libc.so.6`<br />

*Using qt5-qmake to create Makefile*<br />
*1.For Ubuntu, Debian you need to install: `sudo apt-get install libparted-dev`*<br />
*`sudo apt-get install qt5-default`*<br /> 
*for Red Hat, Centos, Fedora:  `yum install parted-dev` (for libparted)*<br />
*`yum install qt5`*<br /> 
*2.Extract the tarball*<br />
*3.Run the following commands:*<br />
>*__qmake PrintParted.pro__*<br />
>*__make__* <br /> 
>*and find the file: PrintParted*<br />

*Alternatively, you can use previously created Makefile with following command: `make`*<br /> 


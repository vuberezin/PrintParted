# *PrintParted* 
*PrintParted is a program for viewing the disk partition table without disk operations. Disk partitions and freespace are shown in a pie chart using the Qt-5.15 framework. It can be useful for quickly finding information about disk partitions. In some cases, it is useful for someone to use information about sectors and freespace before disk operations.* 

# *Building a Dynamically Linked Version*
*Using qt5-qmake to create Makefile*<br />
*1.For Ubuntu,Debian you need to install: sudo apt-get install libparted-dev*<br />
*sudo apt-get install qt5-default*<br /> 
*for Red Hat,Centos,Fedora:  yum install parted-dev (for libparted)*<br />
*yum install qt5*<br /> 
*2.Extract the tarball*<br />
*3.Run the following commands:*<br />
>*__qmake PrintParted.pro__*<br />
>*__make__*<br /> 
>*and find the file: PrintParted*<br />
*Alternatively, you can use Makefile with following command:*<br />
>*__make__*<br /> 

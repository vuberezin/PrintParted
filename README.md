# *PrintParted* 
*PrintParted is a program for viewing the disk partition table without disk operations. Disk partitions and free space are shown in a pie chart using the Qt-5.15 framework.* 

# *Building a Dynamically Linked Version*
*1.For Ubuntu,Debian you need to install: __sudo apt-get install libparted-dev__*<br />
*__sudo apt-get install qt5-default__*<br /> 
*for Red Hat,Centos,Fedora: __yum install parted-dev__ (for libparted)*<br />
*__yum install qt5__*<br /> 
*2.Extract the tarball*<br />
*3.Run the following commands:*<br />
>*__qmake PrintParted.pro__*<br />
>*__make__*<br /> 
*and find the file: PrintParted*

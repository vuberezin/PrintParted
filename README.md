# *PrintParted* 
*PrintParted is a program for viewing the disk partition table without disk operations. Disk partitions and free space are shown in a pie chart using the Qt-5.15 framework.* 

# *Building a Dynamically Linked Version*
*1.For Ubuntu,Debian you need to install:  sudo apt-get install libparted-dev*<br />
*sudo apt-get install qt5-default*<br /> 
*for Red Hat,Centos,Fedora:  yum install parted-dev (for libparted)*<br /> 
*yum install qt5*<br /> 
*2.Extract the tarball*<br />
*3.Run the following commands:*<br />
>*qmake PrintParted.pro*<br />
>*make*<br /> 
*and find the file: PrintParted*

# PrintParted 
PrintParted is a program for viewing the disk partition table without disk operations. Disk partitions and free space are shown in a pie chart using the Qt-5.15 framework. 

# Building a Dynamically Linked Version
<br >1. For Ubuntu,Debian you need to install:  sudo apt-get install libparted-dev<br />
<br >For Red Hat,Centos,Fedora:  yum install parted-dev<br /> 
<br >2.Extract the tarball<br />
<br >3.Run the following commands:<br />
<br >qmake PrintParted.pro<br />
<br >make<br />

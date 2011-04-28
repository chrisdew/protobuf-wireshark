Generating Wireshark/Ethereal plugins for Google Protocol Buffers

Dilip Antony Joseph (dilip.antony.joseph at gmail.com)
Dear Chap ( dear.chap at gmail.com)
http://code.google.com/p/protobuf-wireshark/

Version Runtime 0.1 (April 10, 2011)

NOTATION
========

WSRC_DIR      :   Directory containing the wireshark source code 
                  (wireshark-1.0.2 by default)
WINSTALL_DIR  :   Directory into which wireshark is installed.
CURR_DIR      :   This directory - containing this README file and
                  make_wireshark_plugin.py
AddressBook   :   The name of the top-level message we care about. Based on
                  the example in the protobuf package.



STEP 1: Install Wireshark from source
=====================================
(This step is common for both the generic and specific dissectors).

a. Download and unzip wireshark.  (Tested with wireshark-1.0.2)
b. $ cd WSRC_DIR
c. $ ./autogen.sh 
c. $ ./configure --prefix=WINSTALL_DIR --with-plugins
d. $ make install  (This will take a while)
e. WINSTALL_DIR/bin contains the wireshark you just compiled.  Start it up and
make sure it works fine.

Step 2: Prepare Protocol Buffers
================================
We assume that libprotobuf is installed in a well-known location.

Step 3: Updating wireshark configuration file
========================================
wireshark_src_dir     : /home/danjo/work/pb_ethereal/wireshark-1.0.2
wireshark_install_dir : /home/danjo/work/pb_ethereal/wireshark-bin
wireshark_version     : 1.0.2

d. wireshark_src_dir      :   Absolute path to the wireshark source files
                              directory, i.e., WSRC_DIR
e. wireshark_install_dir  :   Absolute path to the directory in wireshark is
                              installed, i.e., WINSTALL_DIR[optional]
f. wireshark_version      :   1.0.2 or whatever other version you are using

Step 4: Run make_wireshark_plugin.py
====================================
a. $ cd CURR_DIR
b. $ ./make_wireshark_plugin.py wireshark.conf
c. Watch out for any errors.

Step 5: Create proto configuration files
========================================
All proto configuration files need to be in /usr/share/wireshark/protobuf or
$HOME/.wireshark/protobuf. The former is choosen if it exists otherwise we default to the
latter. A sample configuration file is given below

Example: addressbook.conf

name                  = AddressBook
proto_file            = /home/danjo/work/protobuf-2.0.0beta/examples/addressbook.proto
udp_port              = 33445

This tells the dissector that protobuf message name is AddressBook. The proto file that the message is
defined in is given by the "proto_file" field. The udp_port denotes the source or destination
port to register the message on. Multiple conf files, one for each message, can be defined. 
All proto files are consider relative to the conf directory unless an absolute path is given.  The 
format of conf file is

name                  = [message name]
proto_file            = [path to proto file]
[src_|dst_]udp_port              = < src or dst or any udp ports separated by commas >

Step 6: Done
============
a. Start wireshark and check if Protobuf shows in "Analyze >> Enabled
Protocls" menu.
b. Send some UDP packets with AddressBook in the payload by executing python addressbook_test.py
c. Check if they are correctly decoded.
d. If not, try forcefully decoding as "AddressBook" using the "Decode As"
popup menu item.
e. If it still does not work, please email the author.

Note. The generic dissector code is still present but unsupported at this point. It will be removed from trunk soon
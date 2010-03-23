Generating Wireshark/Ethereal plugins for Google Protocol Buffers

Dilip Antony Joseph (dilip.antony.joseph at gmail.com)
http://code.google.com/p/protobuf-wireshark/

Version 0.3 (March 23, 2010)


We can generate two types of Wireshark dissector plugins:

A. Specific - Displays the Message as [field name:value] pairs.
   This option requires the .proto file for the specific protocol.

B. Generic - Displays a Message as [numeric field id:value] pairs. 
   This option does not require the .proto file.
   Requires protobuf-2.0.1 or higher.


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


A. Specific Message Dissector
##############################

Step 2: Prepare Protocol Buffers
================================
Run protoc on the addressbook.proto file to generate addressbook.pb.cc and
addressbook.pb.h (Or just run "make cpp" in the examples subdirectory). Refer
protoc documentation.  We assume that libprotobuf is installed in a well-known
location.

Step 3: Create plugin configuration file
========================================
Example: addressbook.conf

name                  : AddressBook
package               : tutorial
proto_file            : /home/danjo/work/protobuf-2.0.0beta/examples/addressbook.proto
wireshark_src_dir     : /home/danjo/work/pb_ethereal/wireshark-1.0.2
wireshark_install_dir : /home/danjo/work/pb_ethereal/wireshark-bin
wireshark_version     : 1.0.2
port_num              : 33445

a. name                   :   The name of the top-level message we are 
                              interested in, i.e., AddressBook in this example.
b. package                :   The package definition in  the .proto file[optional]
c. proto_file             :   Absolute path to all .proto files
d. wireshark_src_dir      :   Absolute path to the wireshark source files
                              directory, i.e., WSRC_DIR
e. wireshark_install_dir  :   Absolute path to the directory in wireshark is
                              installed, i.e., WINSTALL_DIR[optional]
f. wireshark_version      :   1.0.2 or whatever other version you are using
g. port_num               :   Wireshark will automatically try to decode UDP
                              packets with this port number as AddressBook
                              messages.  By default, port num is 60000.

Step 4: Run make_wireshark_plugin.py
====================================
a. $ cd CURR_DIR
b. $ ./make_wireshark_plugin.py addressbook.conf
c. Watch out for any errors.

Step 5: Done
============
a. Start wireshark and check if AddressBook shows in "Analyze >> Enabled
Protocls" menu.
b. Send some UDP packets with AddressBook in the payload.
c. Check if they are correctly decoded.
d. If not, try forcefully decoding as "AddressBook" using the "Decode As"
popup menu item.
e. If it still does not work, please email the author.



B. Generic Message Dissector
############################

Step 2: Edit CURR_DIR/generic-dissector/generic.conf
=====================================================
Refer Step 3 of Specific Dissector instructions.


Step 3: Edit WSRC_DIR/configure.in and WSRC_DIR/plugins/Makefile.am
===================================================================
WSRC_DIR/configure.in         : Add "plugins/GoogleProtoBuf/Makefile" line 
                                to AC_OUTPUT
WSRC_DIR/plugins/Makefile.am  : Add "GoogleProtoBuf" line to SUBDIRS


Step 4: Run make_generic.py
===========================
a. $ cd CURR_DIR/generic-dissector
b. $ ./make_generic.py generic.conf
c. Watch out for any errors.


Step 5: Done
============
a. Start wireshark and check if GoogleProtoBuf shows in "Analyze >> Enabled
Protocls" menu.
b. Send some UDP packets with any Protobuf generated message in the payload 
in the payload.
c. Check if they are correctly decoded.
d. If not, try forcefully decoding as "GoogleProtoBuf" using the "Decode As"
popup menu item.
e. If it still does not work, please email the author.



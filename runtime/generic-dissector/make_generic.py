#! /usr/bin/python
#
# Dilip Antony Joseph (dilip.antony.joseph at gmail.com)
# http://www.cs.berkeley.edu/~dilip/wireshark-protobuf
# 
# NOTE FROM AUTHOR:
# This is my first Python program.  I am still learning the
# language.  If you find any glaring errors or coding style
# violations, please do email me.

import sys
import os
import re
import shutil

def read_config(config_file_name):
  cfg = {}
  infile = open(config_file_name, "r")
  for line in infile:
    if line == "" or line.isspace(): continue
    p = line.split(':',1)
    cfg[p[0].strip()] = p[1].strip()
  infile.close()
  return cfg
  
# Main program starts here.

if len(sys.argv) != 2:
  print "Usage:", sys.argv[0], "CONF_FILE"
  sys.exit(-1)


plugin_conf = read_config(sys.argv[1])

if plugin_conf.has_key('port_num'): port_num = plugin_conf['port_num']
else: port_num = '60000'

#plugin_name = 'GoogleProtoBuf'
plugin_name = plugin_conf['name']
print 'Generating generic Wireshark'

wireshark_src_dir = plugin_conf['wireshark_src_dir']
wireshark_install_dir = plugin_conf['wireshark_install_dir']
wireshark_version = plugin_conf['wireshark_version']

plugin_dir = wireshark_src_dir + '/plugins/' + plugin_name


curr_dir = os.getcwd()
if not os.path.exists(plugin_dir): os.mkdir(plugin_dir)
shutil.copy('Makefile.am', plugin_dir)
shutil.copy('moduleinfo.h', plugin_dir)
shutil.copy('packet-GoogleProtoBuf.c', plugin_dir)

os.chdir(wireshark_src_dir)
os.system('./autogen.sh')
os.system('./configure --prefix=' + wireshark_install_dir + ' --with-plugins')
os.chdir(curr_dir)


#proto_h_file_name = os.path.splitext(os.path.basename(plugin_conf['proto_file']))[0] + '.pb.h'
#proto_o_file_name = os.path.splitext(os.path.basename(plugin_conf['proto_file']))[0] + '.pb.o'
#proto_c_file_name = os.path.splitext(os.path.basename(plugin_conf['proto_file']))[0] + '.pb.cc'
#proto_dir = os.path.dirname(plugin_conf['proto_file'])

glue_file_name = 'wireshark-glue-' + plugin_name + '.cc'
glue_o_file_name = os.path.splitext(glue_file_name)[0] + '.o'
glue_c_file_name = os.path.splitext(glue_file_name)[0] + '.c'

plugin_so_file_name = plugin_name + '.so'


curr_dir = os.getcwd()

print os.getcwd()
# Compile the glue code
if os.path.exists(glue_o_file_name): os.remove(glue_o_file_name)
os.system('c++ -c ' + glue_file_name)
if not os.path.exists(glue_o_file_name): 
  print "Unable to compile " + glue_file_name
  sys.exit(-1)

# Compile the .o for proto.pb.cc 
#if os.path.exists(proto_o_file_name): os.remove(proto_o_file_name)
#os.system('c++ -c ' + proto_c_file_name)
#if not os.path.exists(proto_o_file_name): 
#  print "Unable to compile " + proto_c_file_name
#  sys.exit(-1)
# Assume that EmptyMessage is already compiled into GoogleProtocolBuf base

os.chdir(curr_dir)
  
# Copy the compiled .o file to wireshark plugins directory
shutil.copy(glue_o_file_name, plugin_dir)
#shutil.copy(proto_dir + '/' + proto_o_file_name, plugin_dir)

# Compile the plugin
os.chdir(plugin_dir)
if os.path.exists(plugin_so_file_name): os.remove(plugin_so_file_name)
os.system('make')
if not os.path.exists(plugin_so_file_name):
  print "Unable to compile wireshark plugin in " + plugin_dir
  sys.exit(-1)

# Copy the plugin so file to the wiresharks plugins directory.
shutil.copy(plugin_so_file_name, wireshark_install_dir + "/lib/wireshark/plugins/" + wireshark_version + "/")

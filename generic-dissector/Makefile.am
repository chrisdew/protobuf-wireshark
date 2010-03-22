INCLUDES = -I$(top_srcdir)

plugindir = @plugindir@

plugin_LTLIBRARIES = GoogleProtoBuf.la
GoogleProtoBuf_la_SOURCES = packet-GoogleProtoBuf.c moduleinfo.h 
GoogleProtoBuf_la_LDFLAGS = -module -avoid-version -shared -Wl,-soname,GoogleProtoBuf.so -o GoogleProtoBuf.so
GoogleProtoBuf_la_LIBADD = @PLUGIN_LIBS@ 

# Libs must be cleared, or else libtool won't create a shared module.
# If your module needs to be linked against any particular libraries,
# add them here.
LIBS = wireshark-glue-GoogleProtoBuf.o -lprotobuf

CLEANFILES = \
	GoogleProtoBuf \
	*~

EXTRA_DIST = \
   Makefile.nmake

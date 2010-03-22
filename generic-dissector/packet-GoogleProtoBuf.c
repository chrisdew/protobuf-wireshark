#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#include <gmodule.h>
#include <epan/packet.h>
#include <epan/prefs.h>
#include <epan/emem.h>
#include <string.h>

/* forward reference */

void proto_register_GoogleProtoBuf();
void proto_reg_handoff_GoogleProtoBuf();
static void dissect_GoogleProtoBuf(tvbuff_t *tvb, packet_info *pinfo,
      proto_tree *tree);


/* Define version if we are not building ethereal statically */
#ifndef ENABLE_STATIC
G_MODULE_EXPORT const gchar version[] = "0.0";
#endif


static int proto_GoogleProtoBuf = -1;
static int global_GoogleProtoBuf_port = 33445;
static dissector_handle_t GoogleProtoBuf_handle;


// Node expansion control variables - START
static gint ett_GoogleProtoBuf = -1;
// Node expansion control variables - END



// Protocol field variables - START
static int hf_GoogleProtoBuf = -1;
static int hf_GoogleProtoBuf_mystr = -1;
// Protocol field variables - END



// Protocol field definition structures - START
static hf_register_info hf[] = {
	{ &hf_GoogleProtoBuf,
		{
			"googleprotobuf",
			"googleprotobuf",
			FT_NONE,
			BASE_NONE,
			NULL,
			0,
			"",
			HFILL
		}
	},
}; // Protocol Field definition structures - END

/* Set up protocol subtree array - START */
static gint *ett[] = {
	&ett_GoogleProtoBuf,
};
/* Set up protocol subtree array - END*/

int wireshark_pb_process_GoogleProtoBuf(void *tree_root, int item_id, 
      void *tvb,  void *buf, int buf_size);

/* Register plugin - START */
#ifndef ENABLE_STATIC
G_MODULE_EXPORT void
plugin_register(void) { 
	/* register the new protocol, protocol fields, and subtrees */
	if (proto_GoogleProtoBuf == -1) { 
    /* execute protocol initialization only once */
		proto_register_GoogleProtoBuf();
	}
}
G_MODULE_EXPORT void
plugin_reg_handoff(void){
	proto_reg_handoff_GoogleProtoBuf();
}
#endif
void proto_register_GoogleProtoBuf(void) {

	module_t *GoogleProtoBuf_module;
	if (proto_GoogleProtoBuf == -1) {
		proto_GoogleProtoBuf = proto_register_protocol (
				"googleprotobuf- ",/* name */
				"googleprotobuf",/* short name */
				"googleprotobuf"/* abbrev */
			);
		}
	GoogleProtoBuf_module= prefs_register_protocol(proto_GoogleProtoBuf,
                                proto_reg_handoff_GoogleProtoBuf);

	/* Register the fields array */
	proto_register_field_array(proto_GoogleProtoBuf, hf, array_length(hf));
	proto_register_subtree_array(ett, array_length(ett));

}



void proto_reg_handoff_GoogleProtoBuf (void) {
	static int Initialized=FALSE;

	if (!Initialized) {
		GoogleProtoBuf_handle = create_dissector_handle(dissect_GoogleProtoBuf,
                                proto_GoogleProtoBuf);
    if(global_GoogleProtoBuf_port > 0) {
		  dissector_add("udp.port", global_GoogleProtoBuf_port, 
                    GoogleProtoBuf_handle);
    }
	}
}
/* Register plugin - END */




/* Generate the main dissector function - START */
static void dissect_GoogleProtoBuf (tvbuff_t *tvb, packet_info *pinfo, 
                                    proto_tree *tree) {

	if (check_col(pinfo->cinfo, COL_PROTOCOL)) {
		col_set_str(pinfo->cinfo, COL_PROTOCOL, "googleprotobuf");
	}

	/* Clear out stuff in the info column */
	if(check_col(pinfo->cinfo,COL_INFO)){
		col_clear(pinfo->cinfo,COL_INFO);
	}


	if (tree) { /* we are being asked for details */

	  /* Allocate memory for the currFieldPtr. */
	  proto_item* ti_GoogleProtoBuf = proto_tree_add_item (
                        tree, proto_GoogleProtoBuf, tvb, 0, -1, FALSE);
	  proto_tree* tree_GoogleProtoBuf = proto_item_add_subtree (
                                ti_GoogleProtoBuf, ett_GoogleProtoBuf);
	  /* Always make sure that offset is LESS than maxOffset */
	  gint maxOffset = tvb_length(tvb);
  
    wireshark_pb_process_GoogleProtoBuf((void *) tree_GoogleProtoBuf, 
                            hf_GoogleProtoBuf, (void *)tvb,  
                            (void *)tvb_get_ptr(tvb,0,maxOffset), maxOffset);
	}

} //dissect_GoogleProtoBuf
/* Generate the main dissector function - END */


/** Called from PB to add msg_str to tree_root */
int wireshark_pb_add_GoogleProtoBuf(void* tree_root, void* tvb, int item_id,
                                    char* msg_str) {
  proto_item *item = proto_tree_add_none_format ((proto_tree *) tree_root, 
                                  item_id, (tvbuff_t*) tvb, 0, -1, msg_str);
  return 0;
}


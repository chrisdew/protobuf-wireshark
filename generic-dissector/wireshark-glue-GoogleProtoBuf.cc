#include <iostream>
#include <string>

#include <google/protobuf/text_format.h>
#include <google/protobuf/unknown_field_set.h>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/io/zero_copy_stream.h>
#include <google/protobuf/io/zero_copy_stream_impl.h>

using namespace std;
using namespace google;
using namespace protobuf;


extern "C" {

int wireshark_pb_add_GoogleProtoBuf(void* tree_root, void *tvb, 
    int item_id, char* msg_str);

/**
  * @param buf The message contents
  * @param buf_size The length of message contents in buf
  * @param tree_root The WireShark tree to which this message is to be added.
  * @param item_id Internal wireshark id to refer to this FT_NONE datatype.
  */
int wireshark_pb_process_GoogleProtoBuf(void* tree_root, int item_id, 
      void* tvb, void* buf, int buf_size) {

  string output_string;

  UnknownFieldSet unknown_fields;
  unknown_fields.ParseFromArray((const void*) buf, buf_size);
  if (TextFormat::PrintUnknownFieldsToString(unknown_fields, 
          &output_string)) {
    printf("%s\n", output_string.c_str());
    char tmp_str[1000];
    strncpy(tmp_str, output_string.c_str(), sizeof(tmp_str));
    wireshark_pb_add_GoogleProtoBuf(tree_root, tvb, item_id, tmp_str);
    return 0;

  } else {
    // This field is not parseable as a Message.  
    // So it is probably just a plain string.
    return -1;
  }
#if 0
  EmptyMessage msg;
  if (!msg.ParseFromArray((char *) buf, buf_size)) {
    cerr << "Failed to parse message." << endl;
    /*
    for (int i=0; i < buf_size; i++) {
      printf("%2x ", ((char *)buf)[i]);
    }
    */
    /*
    printf("buf size=%d\n", buf_size);
    printf("%s\n\n\n", buf);
    */
    return -1;
  }
#endif
}


}

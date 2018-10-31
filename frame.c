#include "frame.h"

frame create_frame(int n, char *str){
  frame frm;
  frm.soh = 0x1;
  frm.seqNum = n;
  sprintf(frm.data, str);
  frm.checksum =0x0;
  return frm;
}

void frame_to_raw(frame frm, char *raw){
  raw[0] = frm.soh;
  char* x = (char*) &frm.seqNum;
  raw[1] = *x;
	raw[2] = *(x+1);
	raw[3] = *(x+2);
  raw[4] = *(x+3);
  char* y = (char*) &frm.dataLength;
  raw[5] = *y;
  raw[6] = *(y+1);
  raw[7] = *(y+2);
  raw[8] = *(y+3);
  for(int i = 0; i < 1024; i++){
    raw[i+9] = frm.data[i];
  }
  raw[1033] = frm.checksum;
}
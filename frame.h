#ifndef FRAME_H
#define FRAME_H

#include <stdio.h>
#include <stdlib.h>
#include "frame.h"

typedef struct {
	char soh;
	int seqNum;
  int dataLength;
  char data[1024];
  char checksum;
} frame;

frame create_frame(int n, char *str);

void frame_to_raw(frame frm, char *raw);

#endif
#include <stdio.h>
#include <stdlib.h>
#include "frame.h"

int main(){
  FILE *fp;
  char buff[255];
  int i = 0;
  frame frm[20];
  char raw[1034];
  
  fp = fopen("./data/data.txt", "r");
  while(fgets(buff, 255, (FILE*)fp)){
    frm[i] = create_frame(i, buff);
    printf("%d:\n", i);
    printf("%s\n", buff);
    i++;
  }
  // fgets(buff, 255, (FILE*)fp);
  printf("====HASIL FRAME====\n");
  for(int j = 0; j < 8; j++){
    printf("frame %d :\n%s\n", frm[j].seqNum, frm[j].data);
  }
  
  fclose(fp);

  frm[11] = create_frame(11, buff);
  char* x = (char*) &frm[11].seqNum;
  raw[0] = *x;
	raw[1] = *(x+1);
	raw[2] = *(x+2);
	raw[3] = *(x+3);
  printf("%X",raw[0]);
  printf("%X",raw[1]);
  printf("%X",raw[2]);
  printf("%X\n",raw[3]);

  frame_to_raw(frm[7], raw);
  printf("%x", raw);


  return 0;
}
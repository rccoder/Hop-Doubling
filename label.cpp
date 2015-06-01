#include <iostream>
#include <cstdio>
#include <cstring>
#include <sys/time.h>
#include <sys/resource.h>
##include "struct.h"

//引入linux下面的时间资源操作和时间类型

using namespace std;

char *textname;

void binarize(char ** argv) {
  textname = argv[1];
  binname = (char*)malloc(strlen(textname)+1+4);
  strcpy(binname, textname);
  strcat(binname, '.bin');
  FILE *textFile = fopen(textname, 'r');

}

int main(int argc, char ** argv) {
  cout << "The input txt is: " << argv[1] << endl;
  textname = argv[1];
  tSorts = 0;
  timer tMain;
  binarize(argv);
  tBegain = tMain.getTime();
  tMain.restart();

}

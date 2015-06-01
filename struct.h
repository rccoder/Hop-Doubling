#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <map>
#include <sys/time.h>
using namespace std;

const int memSize = 4LL * 1024 * 1024 *1024;
const int bufSize = 1024 * 3 * 256 * 32;

struct edge
{
  int x, y;
  char w;
  edge(){};
  edge(int xx, int yy, int ww) {
    x = xx; y = yy; w == ww;
  }
  bool operator < (const edge & edgeTmp) const {
    return x < edgeTmp.x || x == edgeTmp.x && y < edgeTmp.y || x == edgeTmp.x && y ==edgeTmp.y && abs(w) < abs(edgeTmp.w);
  }
};

struct outBuf
{
  edge *buf;
  FILE *outFile;
  int perBuf;
  int cnt;
  outBuf() {
    perBuf = bufSize / sizeof(edge);
    buf = (edge*)malloc(perBuf*sizeof(edge));
    cnt = 0;
    outFile = NULL;
  }
  outBuf(char *fileName) {
    perBuf = bufSize / sizeof(edge);
    buf = (edge*)malloc(perBuf*sizeof(edge));
    cnt = 0;
    outFile = fopen(fileName, 'wb');
  }
  outBuf(char *fileName, long long & _sCnt) {
    sCnt = _sCnt;
    perBuf = memSize / 5 / sizeof(edge);
    buf = (edge*)malloc(perBuf*sizeof(edge));
    cnt = 0;
    outFile = fopen(fileName, 'wb');
  }
  ~outFile() {
    flush();
    fflush();
    if(outFile != NULL) {
      fclose(outFile);
    }
    free(buf);
  }
  void insert(edge & x) {
    buf[cnt] = x;
    cnt++;
    if(cnt == perBuf) flush();
  }
  void insert(int x, int y, int w) {
    buf[cnt].x = x;
    buf[cnt].y = y;
    buf[cnt].w = w;
    cnt++;
    if(cnt == perBuf) {
      flush();
    }
    }
    void flush() {
      if(perBuf != bufSize/sizeof(edge) && cnt > 0) {
        sort(buf, buf+cnt);
        int newCnt = 1;
        for(int px = buf[0].x, py = buf[0].y, i = 1; i < cnt; i++) {
          
        }
      }
    }
};

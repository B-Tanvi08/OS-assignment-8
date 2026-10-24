#include "types.h"
#include "stat.h"
#include "user.h"

/* Q8 demonstration simulator. Replace references/frames if Q8 specifies values. */
#define NREF 13
#define FRAMES 3
static int refs[NREF] = {7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2};

static int findpage(int *a, int n, int x) {
  int i;
  for(i=0;i<n;i++) if(a[i]==x) return i;
  return -1;
}
static int fifo(void) {
  int f[FRAMES], i, next=0, faults=0;
  for(i=0;i<FRAMES;i++) f[i]=-1;
  for(i=0;i<NREF;i++) {
    if(findpage(f,FRAMES,refs[i])>=0) continue;
    faults++; f[next]=refs[i]; next=(next+1)%FRAMES;
  }
  return faults;
}
static int lru(void) {
  int f[FRAMES], last[FRAMES], i,j,s,oldest,faults=0;
  for(i=0;i<FRAMES;i++){f[i]=-1;last[i]=-1;}
  for(i=0;i<NREF;i++) {
    s=findpage(f,FRAMES,refs[i]);
    if(s>=0){last[s]=i;continue;}
    faults++; s=-1;
    for(j=0;j<FRAMES;j++) if(f[j]==-1){s=j;break;}
    if(s<0){oldest=0;for(j=1;j<FRAMES;j++)if(last[j]<last[oldest])oldest=j;s=oldest;}
    f[s]=refs[i];last[s]=i;
  }
  return faults;
}
static int optimal(void) {
  int f[FRAMES],i,j,k,s,farthest,nextuse,faults=0;
  for(i=0;i<FRAMES;i++)f[i]=-1;
  for(i=0;i<NREF;i++) {
    if(findpage(f,FRAMES,refs[i])>=0)continue;
    faults++;s=-1;
    for(j=0;j<FRAMES;j++)if(f[j]==-1){s=j;break;}
    if(s<0){
      farthest=-1;s=0;
      for(j=0;j<FRAMES;j++){
        nextuse=NREF+1;
        for(k=i+1;k<NREF;k++)if(refs[k]==f[j]){nextuse=k;break;}
        if(nextuse>farthest){farthest=nextuse;s=j;}
      }
    }
    f[s]=refs[i];
  }
  return faults;
}
int main(void) {
  int i;
  printf(1,"Reference string:");
  for(i=0;i<NREF;i++)printf(1," %d",refs[i]);
  printf(1,"\nFrames: %d\n",FRAMES);
  printf(1,"Algorithm  Page faults\nFIFO       %d\nLRU        %d\nOptimal    %d\n",
         fifo(),lru(),optimal());
  exit();
}

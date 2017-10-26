#include <stdio.h>
#include <stdlib.h>
#include<windows.h>
#include<conio.h>
/* run this program using the console pauser or add your own getch, system("pause") or input loop */

#define Heap_Size 16

int main(int argc, char *argv[]) {
  void *mem;
  HANDLE h=NULL;
  DWORD oldp;
  
  LoadLibrary("netapi32.dll");
  LoadLibrary("user32.dll");
  
  if(argc<2)
  {
  	printf("ERROR  too less arguments");
  	return -1;
  }
  
  //create heap with default size (4kB) and the last parametr says heap can grows (the heap has no size limit) 
  h=HeapCreate(0,0,0);
  
  //alloc memory on heap (first parametr) and give my application 16 bajts ( defines by Heap_Size value)
  mem=HeapAlloc(h,NULL,Heap_Size);
  
  
  printf("Heap: %0x\n",h);
  printf("block of heap: %08x\n",mem);
  printf("chain copying:%s",argv[1]);
  
  
  //copy chain from user to mem value 
  //it's achilles heel of application beceause i allocted only 16 baits of memory 
  //if user put more then 16 baits, heap will get overflow
  //both mov dword ptr[ecx],eax and mov doword ptr [eax+4],ecx refer to non-existing place 
  //in memory so we get a critical memory 
  strcpy((char*)mem,argv[1]);
  
  HeapAlloc(h,NULL,Heap_Size);
  
  return 0;
  
}

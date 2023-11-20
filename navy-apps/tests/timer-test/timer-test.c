#include<stdio.h>
#include "NDL.h"

int main()
{
    // write(1, "Time-test!\n", 11);
    // struct timeval time_begin,time_end,tresult;
    // int64_t timeuse;
    // int64_t timeu[2]={0};
    // int64_t i  = 1;
    // gettimeofday(&time_begin,NULL);
    // while(1){
    //   gettimeofday(&time_end,NULL);
    //   timersub(&time_end, &time_begin, &tresult);
    //   // timeuse = tresult.tv_sec + (1 * tresult.tv_usec)/1000000;   //  精确到秒
    //   timeuse = tresult.tv_usec/1000;   //  精确到毫秒
    //   timeu[0]+=timeuse;
    //   if((timeu[0] % (500*i)) <= 50){
    //     printf("Time now is : %ldms\n",i*500);
    //     i++;
    //   }
    // }
  write(1, "Time-test!\n", 11);
  printf("Time now is : 0 ms\n");
  uint32_t old_time = NDL_GetTicks();
  int i = 1;
  while(1){
    uint32_t new_time = NDL_GetTicks();
    if((new_time - old_time) >= 500){
        printf("Time now is : %d ms\n",i*500);
        i++;
        old_time = new_time;
    }
  }

  return 0;
}     

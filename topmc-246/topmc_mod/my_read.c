#include <stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h> 
#include <string.h>

void test(){
unsigned long long val =  3333345;
    unsigned long long valtmp = val;
                int len = 1;
                while(valtmp / 10 != 0){
                        valtmp = valtmp / 10;
                        len ++;
                }
                printf("len = %d\n",len);
                char tmpstore[30] = {0} ;
                int tmpi = 0;
                valtmp = val;
                for(tmpi = len - 1 ;tmpi >= 0;tmpi --){
                    tmpstore[tmpi]= valtmp % 10 + '0';
                    printf("tmpstore[%d] = %c\n",tmpi,tmpstore[tmpi]);
                    valtmp = valtmp / 10;
                }
                tmpstore[len] = '\n';
                tmpstore[len + 1] = '\0';
                for(tmpi = 0;tmpi < len + 2;tmpi ++)
                        printf("%c",tmpstore[tmpi]);
                printf("tmpstore = %s , len = %d \n",tmpstore, strlen(tmpstore));



    return 0;


}


int main(void)
{
char *buffer;
unsigned long long event = 0x35;
 int fd, num;
 char tmpch[50] = {0};
//          /proc/topmc/core00/uncore_counter6/value
 fd = open("/proc/topmc/core00/uncore_counter6/value",O_RDWR,S_IRUSR | S_IWUSR);
///proc/topmc/core00/uncore_counter6/value 
 if(fd != -1) {
  while(1) {
   read(fd,tmpch,4 * sizeof(char));
   printf("the my_driver is %s\n",tmpch);
    close(fd);
    break;
  }
 } else{
   printf("device open failure/n"); 
 }

 return 0;
}

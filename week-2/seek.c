/*//Let the contents of the testfile be  “1234567890abcdefghij!@#$%#$%#$#$”. This means we want the output to be “abcdefghij”.
//Note: the first character ‘1’ is at 0th position

lseek(fd,5,SEEK_SET) – this moves the pointer 5 positions ahead starting from the beginning of the file
lseek(fd,5,SEEK_CUR) – this moves the pointer 5 positions ahead from the current position in the file
lseek(fd,-5,SEEK_CUR) – this moves the pointer 5 positions back from the current position in the file
lseek(fd,-5,SEEK_END) -> this moves the pointer 5 positions back from the end of the file
*/
#include<unistd.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<stdio.h>
int main()
{
int n,f,f1;
char buff[10];
f=open("testfile.txt",O_RDWR);
f1=lseek(f,10,SEEK_SET);
printf("Pointer is at %d position\n",f1);
read(f,buff,10);
write(1,buff,10);
}



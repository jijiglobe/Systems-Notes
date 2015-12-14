/*Pipe
	A conduit between seperate processes

	pipes are unidirectional: information can only travel one way

	you can transfer any data type you like through a pipe using read and write

	unnamed pipes have no external acces methodes (IE descriptors or identifiers)

pipe() - <unistd.h>
       create an unnamed pipe
       
       returns 0 if successful

       opens both ends of the pipe as files

       pipe(int descriptors[2]);

Named Pipes( FIFOS):
       FIRST IN FIRST OUT
       Named pipes can also create conduits between processes
       the only difference is that they are named

       
       you can make a fifo in command like
        $ mkfifo <pipe name>
        
	this will create a pipe file
	
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
int main(){
  
    int fds[2];
    int f;
    pipe(fds);
    f = fork();
    if(f==0){
      //this is the child
      //closing the read end
      close(fds[0]);
      double x=1087.1024;
      write(fds[0],&x, sizeof(double));
	
      close(fds[1]);
    }else{
      //this is the parent
      //close the write end
      close(fds[1]);
      double v;
      read(fds[0],&v,sizeof(double));
      printf("parent read: %f\n",v);
      close(fds[0]);
    }
    
    return 0;
}

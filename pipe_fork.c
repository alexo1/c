#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<string.h>
#include<sys/wait.h>

int main()
{
    // We use two pipes
    // First pipe to send input string from parent
    // Second pipe to send concatenated string from child

    int fd1[2];  // Used to store two ends of first pipe
    int fd2[2];  // Used to store two ends of second pipe

    char fixed_str[] = "forgeeks.org";
    char s[100], r[100];
		int begin , end , count = 0;

    int p;

    if (pipe(fd1)==-1)
    {
        fprintf(stderr, "Pipe Failed" );
        return 1;
    }
    if (pipe(fd2)==-1)
    {
        fprintf(stderr, "Pipe Failed" );
        return 1;
    }

    // scanf("%s", s);
		gets(s);
		for (int ii=1;ii<=10;ii++){
    p = fork();

    if (p < 0)
    {
        fprintf(stderr, "fork Failed" );
        return 1;
    }

    // Parent process
    else if (p > 0)
    {
        char r[100];

        close(fd1[0]);  // Close reading end of first pipe

        // Write input string and close writing end of first
        // pipe.
        write(fd1[1], s, strlen(s)+1);
        close(fd1[1]);

        // Wait for child to send a string
        wait(NULL);

        close(fd2[1]); // Close writing end of second pipe

        // Read string from child, print it and close
        // reading end.
        read(fd2[0],r, 100);
        printf("Parent with id %d has received  '%s' from child %d \n\n",getpid(), r, ii);
        close(fd2[0]);
    }

    // child process
    else
    {
        close(fd1[1]);  // Close writing end of first pipe

        // Read a string using first pipe
        // char concat_str[100];
        read(fd1[0], s, 100);


				int count = strlen(s);
				end = count - 1;

				for (begin = 0; begin < count; begin++){
					r[begin] = s[end];
					end--;
				}
        // Close both reading ends
        close(fd1[0]);
        close(fd2[0]);

        // Write concatenated string and close writing end
        write(fd2[1], r, strlen(r)+1);
        close(fd2[1]);
				printf("child %d with id %d is reversing '%s' and sending to parent   \n",ii, getpid(), s );
				sleep(1);

        exit(0);
    }
	}
}

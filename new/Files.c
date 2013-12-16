#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>

int main(int argc, char* argv[]){
	int fd;
	//Open file for read/write. Create new file if it doesn't exist with read and write permissions for the current user
	fd = open("test.txt", O_CREAT|O_RDWR, S_IRUSR|S_IWUSR);

	//Check if call to open was successful
	if(fd < 0){
		//Output error message
		perror("open");
		return -1;
	}


	//This is what we want to write to the file
	char *buffer = "Hello World\n";


	//Write to file
	
	//Start from the first character in the buffer
	int written = 0;

	while(written < strlen(buffer)){
		int status = 0; //How many bytes have we written 
		status = write(fd, buffer + written, strlen(buffer) - written); //Try to write the remaining bytes from the buffer
		
		//Check for errors
		if(status < 0){
			perror("write");
			return -2;
		}

		written += status; //The next iteration of the loop will start writting from buffer[written]
	}


	//Write to standard output
	written = 0;
	while(written < strlen(buffer)){
		int status = 0;
		status = write(STDOUT_FILENO, buffer + written, strlen(buffer) - written);
		if(status < 0){
			perror("write");
			return -2;
		}
		written += status;
	}

	//ALWAYS check the return code from close
	if(close(fd)){
		perror("close");
		return -3;
	}


	return 0;
}

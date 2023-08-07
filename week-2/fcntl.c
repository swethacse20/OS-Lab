#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

int main() {
    int fd;
    
    // Open a file (replace "testfile.txt" with your file's path)
    fd = open("testfile.txt", O_RDWR);
    if (fd == -1) {
        perror("open");
        return 1;
    }
    
    // Get the current file status flags
    int flags = fcntl(fd, F_GETFL);
    if (flags == -1) {
        perror("fcntl (F_GETFL)");
        close(fd);
        return 1;
    }
    
    // Set the file descriptor to non-blocking mode
    flags |= O_NONBLOCK;
    if (fcntl(fd, F_SETFL, flags) == -1) {
        perror("fcntl (F_SETFL)");
        close(fd);
        return 1;
    }
    
    // Attempt to read from the file (will return immediately due to non-blocking mode)
    char buffer[256];
    ssize_t bytesRead = read(fd, buffer, sizeof(buffer));
    if (bytesRead == -1) {
        if (errno == EAGAIN) {
            printf("No data available (EAGAIN)\n");
        } else {
            perror("read");
        }
    } else {
        buffer[bytesRead] = '\0';
        printf("Read %zd bytes: %s\n", bytesRead, buffer);
    }
    
    // Close the file descriptor
    close(fd);
    
    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>


#define FILE_OPEN_FAILURE (-1)
#define EXIT_IF_FAILED (1)
#define BUF_SIZE (512)


int open_file_read(const char *pathname, unsigned char do_exit);
int open_file_write(const char *pathname, unsigned char do_exit);
void copy_and_process(int read_fd, int write_fd);


int main(int argc, char *argv[]) {

    if (argc != 3) {
        printf("Usage:\n\t./part1exec filer filew\n\tmake run filer=[filer] filew=[filew]\n");
        exit(1);
    }

    printf("System Programming. Lab 1, part 1. KP51. Maksym Honchar.\n");
    printf("Out: Reading from [%s]. Writing to [%s]\n", argv[1], argv[2]);

    /* Open file descriptors */
    int read_fd = open_file_read(argv[1], EXIT_IF_FAILED);

    printf("read_fd is %d\n", read_fd);

    int write_fd = open_file_write(argv[2], EXIT_IF_FAILED);

    printf("read_fd is %d\n", write_fd);

    /* Perform copying and processing data from read_fd to write_fd */
    copy_and_process(read_fd, write_fd);

    /* Close file descriptors */
    close(read_fd);
    close(write_fd);

    printf("End of the program.\n");

    return EXIT_SUCCESS;
}


int open_file_read(const char *pathname, unsigned char do_exit) {
    const int flags = O_RDONLY;
    int file;
    
    file = open(pathname, flags);
    if (FILE_OPEN_FAILURE == file) {
        fprintf(stderr, "Out: Cannot open file to read: [%s]. Errno:[%d]. Str:[%s]\n", pathname, errno, strerror(errno));
        if (do_exit) {
            exit(EXIT_FAILURE);
        }
    }
    return file;
}

int open_file_write(const char *pathname, unsigned char do_exit) {
    const int flags = O_WRONLY | O_CREAT | O_EXCL;
    const mode_t mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;  // 0644 mode_t
    int file;

    file = open(pathname, flags, mode);
    if (FILE_OPEN_FAILURE == file) {
        fprintf(stderr, "Out: Cannot open/create file to write: [%s]. Errno:[%d]. Str:[%s]\n", pathname, errno, strerror(errno));
        if (do_exit) {
            exit(EXIT_FAILURE);
        }
    }
    return file;
}

void copy_and_process(int read_fd, int write_fd) {
    char read_buffer[BUF_SIZE] = {0}, total_amount_info_buffer[BUF_SIZE] = {0};
    ssize_t cur_read_bytes, cur_written_bytes;
    ssize_t total_read_bytes = 0, total_written_bytes = 0;

    do {
        // Read bytes from read_fd file.
        cur_read_bytes = read(read_fd, &read_buffer, (size_t)BUF_SIZE);
        if (cur_read_bytes < 0) {
            fprintf(stderr, "Out: error occured while reading file descriptor [%d]. Errno:[%d]. Str:[%s]\n", read_fd, errno, strerror(errno));
            return;
        }
        if (cur_read_bytes == 0) {
            break;
        }
        // Lower buffer content.
        for (ssize_t i = 0; i < cur_read_bytes; i++) {
            read_buffer[i] = tolower(read_buffer[i]);
        }
        // Write content to write_fd file.
        cur_written_bytes = write(write_fd, &read_buffer, (size_t)cur_read_bytes);
        if (cur_written_bytes < 0) {
            fprintf(stderr, "Out: failed to write data to file description [%d]. Errno:[%d]. Str:[%s]\n", write_fd, errno, strerror(errno));
            return;
        }
        if (cur_written_bytes != cur_read_bytes) {
            fprintf(stderr, "Out: bytes read and bytes written missmatch.");
            return;
        }
        // Sum total amount of bytes read and written.
        total_read_bytes += cur_read_bytes;
        total_written_bytes += cur_written_bytes;
    } while(cur_read_bytes > 0);

    // Write total amount of written/read data. In the end it has to be equal.
    sprintf(total_amount_info_buffer, "Bytes written:[%ld]. Bytes read:[%ld].", total_written_bytes, total_read_bytes);
    cur_written_bytes = write(write_fd, &total_amount_info_buffer, strlen(total_amount_info_buffer));
    if (cur_written_bytes < 0) {
        fprintf(stderr, "Out: failed to write data about total amount of written/read data. Errno:[%d]. Str:[%s]\n", errno, strerror(errno));
    }
    printf("Out: Written data about bytes written/read: %s", total_amount_info_buffer);
}

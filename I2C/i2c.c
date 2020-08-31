

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include "i2c.h"

#define PATH_BUFFER_SIZE 32

__attribute__((weak)) // open_i2c will be redefined (faked) in test_do_something)
int open_i2c(uint8_t i2c_bus)
{
    char path[PATH_BUFFER_SIZE];
    int fd;

    snprintf(path, PATH_BUFFER_SIZE, "/dev/i2c-%d", i2c_bus);
    fd = open(path, O_RDWR);

    if (fd < 0)
        return -1;

    return fd;
}

int do_something()
{
    int fd = open_i2c(42);

    if (fd < 0)
        return -1;

    return close(fd);
}
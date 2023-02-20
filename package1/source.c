#define MAX_VAL 176
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

int main(int argc, char *argv[])
{
        char *buff;
        int fd, len;

                /* checks if corect argument is passed*/
        if (argc != 2)
        {
                dprintf(2, "Error: Usage >> %s file_name\n", argv[0]);
                exit(97);
        }
                /* allocates buffer memory */
        buff = malloc(MAX_VAL * sizeof(char));
        if (buff == NULL)
        {
                dprintf(2, "Memory not allocated\n");
                exit(1);
        }
                /* opening file */
        fd = open("../.tmpfile.txt", O_RDONLY);
        if (fd < 0)
        {
                dprintf(2, "Can't open file check if tmpfile exist\n");
                exit(99);
        }
                /* read from file tmpfile*/
        len = read(fd, buff, MAX_VAL);
        if (len < 0)
        {
                dprintf(2, "Unable to read file, check modify tmpfile file permissions\n");
                exit(98);
        }
        close(fd);

                /* create and open template */
        fd = open(argv[1], O_CREAT | O_RDWR, 0664);
        if (fd < 0)
        {
                dprintf(2, "Template not created, check source code\n");
                exit(99);
        }
                /* write into template */
        len = write(fd, buff, MAX_VAL);
        if (len < 0)
        {
                dprintf(2, "Unable to read file, check modify tmpfile file permissions\n");
                exit(99);
        }
        close(fd);

        return (0);
}

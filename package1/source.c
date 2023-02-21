#define MAX_VAL 144
#define NEWMAX MAX_VAL + 56
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

char *buff;
char *buff1;
int fd, len;
void create_header(char *header, int argn);
int main(int argc, char *argv[])
{
        char *buff;
        int fd, len;

                /* checks if corect argument is passed*/
	if (argc > 3 || argc < 2)
	{
		dprintf(2, "Error: Usage %s file.c main.h\n", argv[0]);
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
        fd = open(argv[1], O_TRUNC | O_CREAT | O_RDWR, 0664);
        if (fd < 0)
        {
                dprintf(2, "Template not created, check source code\n");
                exit(99);
        }
                /* write into template */
        len = write(fd, buff, MAX_VAL);
        if (len < 0)
        {
                dprintf(2, "Unable to read file, check %s file permissions\n", argv[1]);
                exit(99);
        }
        close(fd);

	argc == 3 ? create_header(argv[2], argc) : create_header("header.h", argc);
	free(buff);
        return (0);
}

void create_header(char *header, int argn)
{
                /* opening file */
        fd = open("../.header.txt", O_RDONLY);
        if (fd < 0)
        {
                dprintf(2, "Can't open file check if header exist in parent directory\n");
                exit(99);
        }
	buff1 = malloc(NEWMAX * sizeof(char));
                /* read from header template*/
        len = read(fd, buff1, NEWMAX);
        if (len < 0)
        {
                dprintf(2, "Unable to read file, check modify header file permissions\n");
                exit(98);
        }
        close(fd);

                /* create and open template */
        if (argn == 3)
                fd = open(header, O_TRUNC | O_CREAT | O_RDWR, 0664);
        else
                fd = open("header.h", O_TRUNC | O_CREAT | O_RDWR, 0664);
        if (fd < 0)
        {
                dprintf(2, "%s not created, check source code\n", header);
                exit(99);
        }
                /* write into template */
        len = write(fd, buff1, NEWMAX);
        if (len < 0)
        {
                dprintf(2, "Unable to  write file, check %s file permissions\n", header);
                exit(99);
        }
        close(fd);
	free(buff1);
}

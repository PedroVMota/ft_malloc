#include "Chunk.h"
#include "Core.h"
#include "Heap.h"
#include <stddef.h>
#include <stdio.h>
#include <sys/mman.h>

void debug_chunk(t_chunk *ptr, long i)
{
    printf("\t\tChunk[%lld]: %p\n", i, ptr);
    printf("\t\t\tMagic: %X\n", ptr->magic);
    printf("\t\t\tEnd magic: %X\n", ptr->end_magic);
    printf("\t\t\tSize: %lu\n", ptr->size);
    printf("\t\t\tNext: %p\n", ptr->next);
    printf("\t\t\tPrev: %p\n", ptr->prev);
    printf("\t\t\tRegion: %p\n", ptr->region);
    printf("\t\t\tIs being used: %d\n", ptr->isbeingused);
}

void check_bins()
{
    for (int i = 0; i < NUM_BINS; i++)
    {
        printf("\tSelecting bin: %zu\n", bin_sizes[i]); // Use %zu for size_t
        t_chunk *bin = heap.bins[i].chunks;
        // printf("\tAvailable: %zu\n", heap.bins[i].availsize);  // Use %zu for size_t
        long chunk = 0;
        while (bin)
        {
            if (bin->isbeingused)
                debug_chunk(bin, chunk);
            chunk++;
            bin = bin->next;
        }
    }
}

#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>

void check_leaks_bin()
{
    pid_t pid = fork();

    if (pid == -1)
    {
        perror("fork failed");
        return;
    }

    if (pid == 0)
    {
        // Child process - redirect output to memory_map.log
        int fd = open("leaks_bins.log", O_CREAT | O_WRONLY | O_TRUNC, 0644);
        if (fd == -1)
        {
            perror("Failed to open memory_map.log");
            _exit(1);
        }

        // Redirect stdout to the log file
        if (dup2(fd, STDOUT_FILENO) == -1)
        {
            perror("dup2 failed");
            close(fd);
            _exit(1);
        }

        close(fd);

        // Execute the debug function
        check_bins();

        // Exit child process
        _exit(0);
    }
    else
    {
        // Parent process - wait for child to complete
        int status;
        waitpid(pid, &status, 0);

        if (WIFEXITED(status))
        {
            printf("Debug completed. Memory map written to memory_map.log\n");
        }
        else
        {
            printf("Debug process terminated abnormally\n");
        }
    }
}


void check_bchunks(){
    t_chunk *chunks = heap.bchunks;
    long long i = 0;
    while(chunks){
        if(chunks->isbeingused)
            debug_chunk(chunks, i);
        i++;
        chunks = chunks->next;
    }
}


void check_large_chunks()
{
    pid_t pid = fork();

    if (pid == -1)
        return;
    if (pid == 0)
    {
        int fd = open("leaks_chunks.log", O_CREAT | O_WRONLY | O_TRUNC, 0644);
        if (fd == -1)
            _exit(1);
        if (dup2(fd, STDOUT_FILENO) == -1)
        {
            close(fd);
            _exit(1);
        }
        close(fd);
        check_bchunks();
        _exit(0);
    }
    else
    {
        // Parent process - wait for child to complete
        int status;
        waitpid(pid, &status, 0);
        if (WIFEXITED(status))
            printf("Debug completed. Memory map written to memory_map.log\n");
        else
            printf("Debug process terminated abnormally\n");
    }
}

void ft_debug()
{
    check_leaks_bin();
    check_large_chunks();
}
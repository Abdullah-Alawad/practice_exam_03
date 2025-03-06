#include <stdlib.h>
#include <unistd.h>

#define BUFFER_SIZE 42

char    *set_next(char *buffer)
{
    char    *res;
    int     i;
    int     j;

    i = 0;
    while (buffer[i] != '\0' && buffer[i] != '\n')
        i++;
    if (buffer[i] == '\n')
        i++;
    if (!buffer[i])
    {
        free(buffer);
        buffer = NULL;
        return (NULL);
    }
    res = malloc(ft_strlen(buffer) - i + 1);
    if (!res)
    {
        free(buffer);
        buffer = NULL;
        return (NULL);
    }
    j = 0;
    while (buffer[i])
        res[j++] = buffer[i++];
    res[j] = '\0';
    free(buffer);
    return (res);
}

char    *set_line(char *buffer)
{
    char    *line;
    int     i;
    int     j;

    i = 0;
    while (buffer[i] != '\0' && buffer[i] != '\n')
        i++;
    line = malloc(i + 2);
    if (!line)
        return (NULL);
    j = 0;
    while (j < i + 2)
        line[j++] = '\0';
    i = 0;
    while (buffer[i] != '\0' && buffer[i] != '\n')
    {
        line[i] = buffer[i];
        i++;
    }
    if (buffer[i] == '\n')
        line[i++] = '\n';
    return (line);
}

char    *join_str(char *s1, char *s2, int b_r)
{
    char    *res;

    if (b_r < 0)
    {
        free(s1);
        s1 = NULL;
        free(s2);
        return (NULL);
    }
    s2[b_r] = '\0';
    res = ft_strjoin(s1, s2);
    if (!res)
    {
        free(s1);
        free(s2);
        s1 = NULL;
        return (NULL);
    }
    free (s1);
    return (res);
}

char    *read_file(char *res, int fd)
{
    char    *buffer;
    int     b_r;

    if (!res)
    {
        res = malloc(1);
        res[0] = '\0';
    }
    if (!res)
        return (NULL);
    buffer = malloc(BUFFER_SIZE + 1);
    if (!buffer)
    {
        free(res);
        res = NULL;
        return (NULL);
    }
    b_r = 1;
    while (b_r)
    {
        b_r = read(fd, buffer, BUFFER_SIZE);
        res = join_str(res, buffer, b_r);
        if (!res)
            return (NULL);
        if (ft_strchr(buffer, '\n'))
            break ;
    }
    free(buffer);
    return (res);
}

char    *get_next_line(int fd)
{
    static char *buffer;
    char        *line;

    if (fd < 0 || BUFFER_SIZE <= 0)
        return (NULL);
    buffer = read_file(buffer, fd);
    if (!buffer)
        return (NULL);
    line = set_line(buffer);
    buffer = set_next(buffer);
    if (!line)
    {
        free(buffer);
        buffer = NULL;
        return (NULL);
    }
    return (line);
}
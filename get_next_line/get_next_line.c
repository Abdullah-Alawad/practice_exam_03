#include <stdlib.h>
#include <unistd.h>

char	*set_next(char *buffer)
{
	char	*line;
	int		i;
	int		j;

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
	line = malloc(ft_strlen(buffer) - i + 1);
	if (!line)
	{
		free(buffer);
		buffer = NULL;
		return (NULL);
	}
	j = 0;
	while (buffer[i] != '\0')
		line[j++] = buffer[i++];
	free(buffer);
	return (line);
}

char	*set_line(char *buffer)
{
	char	*line;
	int		i;

	i = 0;
	if (!buffer[i])
		return (NULL);
	while (buffer[i] != '\0' && buffer[i] != '\n')
		i++;
	line = malloc(i + 2);
	if (!line)
		return (NULL);
	i = 0;
	while (buffer[i] != '\0' && buffer[i] != '\n')
	{
		line[i] = buffer[i];
		i++;
	}
	if (buffer[i] != '\0' && buffer[i] == '\n')
	{
		line[i] = '\n';
		i++;
	}
	line[i] = '\0';
	return (line);
}

char	*join_str(char *buffer, char *buf, int byte_read)
{
	char	*temp;

	if (byte_read == -1)
	{
		free(buf);
		buf = NULL;
		free(buffer);
		return (NULL);
	}
	buf[byte_read] = '\0';
	temp = ft_strjoin(buffer, buf);
	if (!temp)
	{
		free(buf);
		buf = NULL;
		free(buffer);
		return (NULL);
	}
	free(buffer);
	return (temp);
}

char	*read_file(int fd, char *res)
{
	char	*buffer;
	int		byte_read;

	if (!res)
		res = malloc(1);
	if (!res)
		return (NULL);
	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
	{
		free (res);
		return (NULL);
	}
	byte_read = 1;
	while (byte_read > 0)
	{
		byte_read = read(fd, buffer, BUFFER_SIZE);
		res = join_str(res, buffer, byte_read);
		if (!res)
			return (NULL);
		if (ft_strchr(buffer, '\n'));
			break;
	}
	free (buffer);
	return (res);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*line;

	if (fd < 0 || BUFFER_SIZE < = 0)
		return (NULL);
	buffer = read_file(fd, buffer);
	if (!buffer)
	{
		free(buffer);
		buffer = NULL;
		return (NULL);
	}
	line = set_line(buffer);
	buffer = set_next(buffer);
	if (!line)
	(
		free(buffer);
		buffer = NULL;
		return (NULL);
	)
	return (line);
}
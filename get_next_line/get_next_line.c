/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgering <mgering@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 15:53:30 by mgering           #+#    #+#             */
/*   Updated: 2024/08/02 13:23:38 by mgering          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*line;

	if (0 > fd || 0 >= BUFFER_SIZE)
		return (NULL);
	buffer = read_line(fd, buffer);
	if (!buffer)
		return (NULL);
	line = cut_line(buffer);
	if (!line || '\0' == line[0])
	{
		if (buffer)
		{
			free(buffer);
			buffer = NULL;
		}
		if (line)
			free(line);
		return (NULL);
	}
	buffer = buffer_left(buffer, gnl_strlen(line));
	return (line);
}

char	*read_line(int fd, char *buffer)
{
	char	*temp_buffer;
	ssize_t	bytes_read;

	bytes_read = 1;
	temp_buffer = gnl_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!temp_buffer)
	{
		if (buffer)
			free(buffer);
		return (NULL);
	}
	while (0 < bytes_read && !gnl_strchr(temp_buffer, '\n'))
	{
		bytes_read = read(fd, temp_buffer, BUFFER_SIZE);
		if (0 > bytes_read)
			return (free(temp_buffer), free(buffer), NULL);
		temp_buffer[bytes_read] = '\0';
		buffer = gnl_strjoin(buffer, temp_buffer);
		if (!buffer)
			return (free(temp_buffer), NULL);
	}
	if (temp_buffer)
		free(temp_buffer);
	return (buffer);
}

char	*cut_line(char *buffer)
{
	char	*line;
	size_t	line_length;
	size_t	i;

	if (!buffer)
		return (NULL);
	line_length = 0;
	i = 0;
	while (buffer[line_length] && '\n' != buffer[line_length])
		line_length++;
	if ('\n' == buffer[line_length])
		line_length++;
	line = gnl_calloc((line_length + 1), sizeof(char));
	if (!line)
		return (NULL);
	while (i < line_length)
	{
		line[i] = buffer[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

char	*buffer_left(char *buffer, size_t line_length)
{
	char	*temp;
	size_t	temp_length;
	size_t	i;

	if (!buffer)
		return (NULL);
	temp_length = gnl_strlen(buffer);
	i = 0;
	temp = gnl_calloc((temp_length - line_length + 1), sizeof(char));
	if (!temp)
	{
		free(buffer);
		return (NULL);
	}
	while ('\0' != buffer[line_length])
	{
		temp[i] = buffer[line_length];
		i++;
		line_length++;
	}
	temp[i] = '\0';
	free(buffer);
	return (temp);
}

/* int	main(void)
{
	int		fd;
	char	*line;

	fd = open("test.txt", O_RDONLY);
	while ((line = get_next_line(fd)))
	{
		printf("-->%s", line);
		free(line);
	}
	close(fd);
	return(0);
} */

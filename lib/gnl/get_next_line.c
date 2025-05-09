/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masmit <masmit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/16 10:12:14 by ajordan-          #+#    #+#             */
/*   Updated: 2024/11/21 17:59:16 by masmit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*empty_bucket(char *bucket)
{
	char	*new_bucket;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (bucket[i] && bucket[i] != '\n')
		i++;
	if (!bucket[i])
	{
		free(bucket);
		bucket = NULL;
		return (NULL);
	}
	new_bucket = malloc(sizeof(char) * (gnl_strlen(bucket) - i));
	if (!new_bucket)
		return (NULL);
	i++;
	while (bucket[i])
		new_bucket[j++] = bucket[i++];
	new_bucket[j] = '\0';
	free(bucket);
	return (new_bucket);
}

char	*fill_aquarium(char *bucket)
{
	char	*aquarium;
	int		i;

	i = 0;
	if (!bucket[i])
		return (NULL);
	while (bucket[i] && bucket[i] != '\n')
		i++;
	aquarium = malloc(sizeof(char) * (i + 2));
	if (!aquarium)
		return (NULL);
	i = 0;
	while (bucket[i] && bucket[i] != '\n')
	{
		aquarium[i] = bucket[i];
		i++;
	}
	if (bucket[i] == '\n')
	{
		aquarium[i] = bucket[i];
		i++;
	}
	aquarium[i] = '\0';
	return (aquarium);
}

char	*fill_bucket(int fd, char *bucket)
{
	int		rd_bytes;
	char	*buffer;

	rd_bytes = 1;
	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	while (!gnl_strchr(bucket, '\n') && (rd_bytes != 0))
	{
		rd_bytes = read(fd, buffer, BUFFER_SIZE);
		if (rd_bytes == -1)
		{
			free(buffer);
			free(bucket);
			bucket = NULL;
			return (NULL);
		}
		buffer[rd_bytes] = '\0';
		bucket = gnl_strjoin(bucket, buffer);
	}
	free(buffer);
	return (bucket);
}

char	*get_next_line(int fd)
{
	static char	*bucket;
	char		*aquarium;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	bucket = fill_bucket(fd, bucket);
	if (!bucket)
		return (NULL);
	aquarium = fill_aquarium(bucket);
	bucket = empty_bucket(bucket);
	if (!bucket)
	{
		free(bucket);
		bucket = NULL;
	}
	return (aquarium);
}

// int	main(void)
// {
// 	int		fd;
// 	char	*s;

// 	fd = open("1.txt", O_RDONLY);
// 	if (fd == -1)
// 	{
// 		perror("file aint open");
// 		return (1);
// 	}
// 	while ((s = get_next_line(fd)) != NULL)
// 	{
// 		printf("%s", s);
// 		free(s);
// 	}
// 	if (close(fd) == -1)
// 	{
// 		perror("shit aint closing");
// 		return (1);
// 	}
// 	return (0);
// }

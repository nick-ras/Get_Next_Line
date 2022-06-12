/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nickras <nickras@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 15:09:17 by nickras           #+#    #+#             */
/*   Updated: 2022/06/10 19:05:14 by nickras          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

//return the string saved including overlap! 
/* read output: 1+ = succes + file position is advanced by 	this number, 0 = endoffile, 01 = error */
void	buf_read_until_nl(int fd, char 	*s_string)
{
	int			check_if_err;
	char * buffer;

	if (!(buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1))))
	{
		free(buffer);
		return ;
	}
	check_if_err = 1;
	while (!ft_strchr(s_string, '\n')) // check also \0??
	{
		check_if_err = read(fd, s_string, BUFFER_SIZE);
		printf("%s%d", s_string, check_if_err);
		if (check_if_err == -1) //checks if read function gives error
		{
			free(s_string);
			return ; //CLEAR S_STRING
		}
		if (check_if_err == 0)
			return ;
		ft_strjoin(s_string, buffer);
	}
}

char *get_return_str(char *first_ch_ptr)
{
	char	*return_str;
	int i;


	i = 0;
	return_str = NULL;
	while (first_ch_ptr[i] != '\n' || first_ch_ptr[i] != '\0')
		i++;
	return_str = ft_substr(first_ch_ptr, 0, i);
	ft_memset(first_ch_ptr, 0, i);
	return (return_str);
}

void	*is_there_chars_in_buffer(char *s_string)
{
	size_t	idx;
	size_t	buf_size;

	buf_size = BUFFER_SIZE;

	idx = 0;
	while(idx < buf_size)  
	{
		if(s_string[idx] != '\0')
			return (&s_string[idx]); // 0 0 0 0 0 a b c \n \0 --> gets index where its not  \0 OR                         return null if it doesnt find a non \0 character
		idx++;
	}
	return (NULL);
}

/* RETURN VALUE    open(), openat(), and creat() return the new file descriptor, or -1 if an error occurred (in which case, errno is set appropriatel is the one that gets bigger and return_str is only out = abc\n12\nhey\0 */
char	*get_next_line(int fd)
{
	static char	s_string[BUFFER_SIZE];
	char			*nl_ptr;
	char			*first_ch_ptr;
	char			*return_str;
	char 			*temp;

	printf("hi");
	temp = NULL;
	return_str = NULL;
	//printf("%s", (int)BUFFER_SIZE);
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);   // 0 0 0 0 0 a b c \n 1 2 3 \n
	first_ch_ptr = is_there_chars_in_buffer(s_string); //index of first non-\0 character or NULL if only \0 characters
	nl_ptr = ft_strchr(first_ch_ptr, '\n');

	if (nl_ptr && first_ch_ptr) // if \n
	{
		return_str = get_return_str(first_ch_ptr);
		return (return_str);
	}
	else if(first_ch_ptr) //only \0 not \n
	{		 //CHANGE WITH NEW GET_RETURN_STR FUNCTION
			return_str = get_return_str(first_ch_ptr);
			buf_read_until_nl(fd, s_string);
	}
	if(!*s_string)
		buf_read_until_nl(fd, s_string);
	if(!*s_string)
		return (NULL);
	temp= ft_strjoin(return_str, get_return_str(s_string));
	free(return_str);
	return (temp);
}

/* char *return_str(char *s_string)
{
	char	*temp;
	char	*return_str;
	int		i;

	i = 0;
	temp = calloc(ft_strlen(s_string), sizeof(char));
	while (*s_string != '\n' || *s_string != '\0')
	{
		temp[i] = s_string[i];
		i++;
	}
	ft_memset(s_string, 0, i);
	return_str = temp;
	free(temp); //DOESNT MAKE SENSE?
	return (return_str);
} */

/* char	*print_line(int fd, char *return_str)
{
	char	*return_str;
	int		check_if_err;

	if (!(return_str = malloc(sizeof(char) * (BUFFER_SIZE + 1))))
		return (NULL);
	check_if_err = 1;
	while (!ft_strchr(return_str, '\n') && check_if_err != 0)
	{
		check_if_err = read(fd, return_str, BUFFER_SIZE);
		if (check_if_err == -1 || check_if_err == 0)
			return (return_str = NULL);
		if (ft_strchr(return_str, '\n'))
			return (ft_strjoin(return_str, cut_down_buffer(return_str)));
		ft_strjoin(return_str, return_str);
	}
	free(return_str);
	return (return_str);
} */
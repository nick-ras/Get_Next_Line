
#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

#ifndef BUFFER_SIZE
#	define BUFFER_SIZE 42
#endif

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>


typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

char	*get_next_line(int fd);
void	buf_read_until_nl(int fd, char 	*s_string);
char	*print_line(int fd, char *string1);
char	*cut_down_buffer(char *buffer);
void	*is_there_chars_in_buffer(char *s_string);
char	*get_new_line(int fd, char *string1);
void	*ft_memcpy(void *dst, const void *src, size_t n);
size_t	ft_strlen(const char *s);
char	*ft_strchr(const char *s, int c);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strdup(const char *s1);
void	ft_bzero(void *s, size_t n);
void	*ft_memset(void *b, int c, size_t len);
char	*ft_substr(char const *s, unsigned int start, size_t len);
void	*ft_calloc(size_t nmemb, size_t size);

#endif
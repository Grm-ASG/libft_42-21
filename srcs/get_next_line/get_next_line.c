/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imedgar <imedgar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/14 16:22:48 by imedgar           #+#    #+#             */
/*   Updated: 2020/11/09 21:30:57 by imedgar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char		*ft_strjoin_gnl(char const *s1, char const *s2)
{
	char	*new;
	char	*ptr;
	size_t	len_s1;
	size_t	len_s2;

	len_s1 = 0;
	len_s2 = 0;
	while (s1[len_s1] != '\0')
		++len_s1;
	while (s2[len_s2] != '\0')
		++len_s2;
	if (!(new = (char *)malloc(len_s1 + len_s2 + 1)))
		return (NULL);
	ptr = new;
	while (*s1)
		*ptr++ = *s1++;
	while (*s2)
		*ptr++ = *s2++;
	*ptr = '\0';
	return (new);
}

static char		*ft_last_str(char **line, t_gnl *temp)
{
	char		*p_lf;
	char		*new;

	if (temp->tail == NULL)
	{
		if (!(new = (char *)malloc(1)))
			return (NULL);
		new[0] = '\0';
		return (new);
	}
	if ((p_lf = ft_strchr_gnl(temp->tail, '\n')) == NULL)
	{
		if (!(*line = ft_strdup_gnl(temp->tail)))
			return (NULL);
		free(temp->start_tail);
		temp->start_tail = NULL;
		temp->tail = NULL;
		return (*line);
	}
	*p_lf++ = '\0';
	if (!(*line = ft_strdup_gnl(temp->tail)))
		return (NULL);
	temp->tail = p_lf;
	return (*line);
}

static int		get_line_sup(char *buf, char **p_lf, t_gnl *t_temp, char **line)
{
	if (((*p_lf) = ft_strchr_gnl(buf, '\n')))
	{
		if ((*(*p_lf - 1)) == '\\')
		{
			(*(*p_lf - 1)) = '\0';
			*p_lf = NULL;
		}
		else
		{
			(**p_lf) = '\0';
			++(*p_lf);
			if (!(t_temp->tail = ft_strdup_gnl(*p_lf)))
				return (-1);
			t_temp->start_tail = t_temp->tail;
		}
	}
	t_temp->line_back_up = *line;
	if (!(*line = ft_strjoin_gnl(*line, buf)))
		return (-1);
	free(t_temp->line_back_up);
	t_temp->line_back_up = NULL;
	return (0);
}

static int		get_line(int fd, char **line, t_gnl *t_temp, t_gnl **prime)
{
	const long long	buf_s = BUFFER_SIZE;
	long long		ret;
	char			*p_lf;
	char			*buf;

	p_lf = NULL;
	ret = 0;
	if (!(buf = (char *)malloc(buf_s + 1)))
		return (ft_exit_gnl(buf, fd, prime, -1));
	while (!p_lf && !t_temp->tail && (ret = read(fd, buf, buf_s)))
	{
		if (ret < 0)
			return (ft_exit_gnl(buf, fd, prime, -1));
		buf[ret] = '\0';
		if (-1 == get_line_sup(buf, &p_lf, t_temp, line))
			return (ft_exit_gnl(buf, fd, prime, -1));
	}
	if (ret < buf_s && t_temp->tail == NULL)
		return (ft_exit_gnl(buf, fd, prime, 0));
	free(buf);
	return (1);
}

int				get_next_line(int fd, char **line)
{
	const long long	buf_s = BUFFER_SIZE;
	static t_gnl	*prime;
	t_gnl			*t_temp;
	char			check[1];

	if (buf_s < 1 || !line || fd < 0 ||
		((read(fd, check, 0)) < 0) ||
		!(t_temp = ft_find_lst_gnl(fd, &prime)) ||
		!(*line = ft_last_str(line, t_temp)))
		return (ft_exit_gnl(NULL, fd, &prime, -1));
	return (get_line(fd, line, t_temp, &prime));
}

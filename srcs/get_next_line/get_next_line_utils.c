/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imedgar <imedgar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/12 20:09:52 by imedgar           #+#    #+#             */
/*   Updated: 2020/11/20 15:45:24 by imedgar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char		*ft_strchr_gnl(const char *s, int c)
{
	while (*s)
		if (*s++ == (unsigned char)c)
			return ((char *)--s);
	if (*s == (unsigned char)c)
		return ((char *)s);
	return (NULL);
}

char		*ft_strdup_gnl(const char *s)
{
	size_t	s_len;
	char	*new;

	s_len = 0;
	while (s[s_len] != '\0')
		++s_len;
	if (!(new = (char *)malloc(s_len + 1)))
		return (NULL);
	s_len = 0;
	while (s[s_len] != '\0')
	{
		new[s_len] = s[s_len];
		++s_len;
	}
	new[s_len] = '\0';
	return (new);
}

t_gnl		*ft_lst_new_gnl(int fd)
{
	t_gnl		*new;

	new = NULL;
	if (!(new = (t_gnl *)malloc(sizeof(t_gnl))))
		return (NULL);
	new->fd = fd;
	new->tail = NULL;
	new->start_tail = NULL;
	new->line_back_up = NULL;
	new->next = NULL;
	return (new);
}

t_gnl		*ft_find_lst_gnl(int fd, t_gnl **prime)
{
	t_gnl		*temp;

	if (*prime == NULL)
		return ((*prime = ft_lst_new_gnl(fd)));
	temp = *prime;
	while (temp->fd != fd && temp->next != NULL)
		temp = temp->next;
	return (temp->fd == fd ? temp : (temp->next = ft_lst_new_gnl(fd)));
}

int			ft_exit_gnl(char *buf, int fd, t_gnl **prime, int result)
{
	t_gnl		*temp;
	t_gnl		*temp1;

	free(buf);
	if (*prime)
	{
		temp = *prime;
		if (temp->fd == fd)
			*prime = temp->next;
		else
		{
			while (temp->next->fd != fd)
				temp = temp->next;
			temp1 = temp->next;
			temp->next = temp1->next;
			temp = temp1;
		}
		ft_free_all(2, &temp->start_tail, &temp);
	}
	return (result == -1 ? -1 : 0);
}

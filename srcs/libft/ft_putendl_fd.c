/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imedgar <imedgar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/30 00:24:47 by imedgar           #+#    #+#             */
/*   Updated: 2020/11/18 19:34:50 by imedgar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int				ft_putendl_fd(char *s, int fd)
{
	int res;

	res = 0;
	res += ft_putstr_fd(s, fd);
	res += ft_putchar_fd('\n', fd);
	return (res);
}

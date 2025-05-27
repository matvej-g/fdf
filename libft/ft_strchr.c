/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgering <mgering@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 14:17:03 by mgering           #+#    #+#             */
/*   Updated: 2024/08/13 14:43:23 by mgering          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* The strchr() function locates the first occurrence of c
(converted to a char) in the string pointed to by s.
The terminating null character is considered to be
part of the string; therefore if c is `\0', the
functions locate the terminating `\0'. */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	while (*s != '\0')
	{
		if ((unsigned char)*s == (unsigned char)c)
			return ((char *)s);
		s++;
	}
	if ((unsigned char)*s == (unsigned char)c)
		return ((char *)s);
	return (NULL);
}

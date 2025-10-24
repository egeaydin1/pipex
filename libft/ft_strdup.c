/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egeaydin <egeaydin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 18:32:06 by egeaydin          #+#    #+#             */
/*   Updated: 2025/06/17 19:05:00 by egeaydin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*strptr;
	int		i;

	i = 0;
	strptr = malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (!strptr)
		return (NULL);
	while (s[i])
	{
		strptr[i] = s[i];
		i++;
	}
	strptr[i] = '\0';
	return (strptr);
}

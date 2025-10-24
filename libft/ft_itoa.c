/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egeaydin <egeaydin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 10:00:42 by egeaydin          #+#    #+#             */
/*   Updated: 2025/06/13 21:23:52 by egeaydin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	intlen(int num)
{
	int	count;

	count = 0;
	if (num == 0)
		return (1);
	if (num == -2147483648)
		return (10);
	else if (num < 0)
		num = -num;
	while (num > 0)
	{
		num /= 10;
		count++;
	}
	return (count);
}

static void	converter(char *result, size_t size, int num)
{
	size_t	i;

	i = 0;
	if (num < 0)
	{
		num = -num;
		result[0] = '-';
	}
	while (num != 0)
	{
		result[size - i - 1] = '0' + (num % 10);
		num /= 10;
		i++;
	}
	result[size] = '\0';
}

char	*ft_itoa(int n)
{
	char	*result;
	size_t	size;

	size = intlen(n);
	if (n < 0)
		size++;
	result = malloc((size + 1) * sizeof(char));
	if (!result)
		return (NULL);
	if (n == 0)
	{
		result[0] = '0';
		result[1] = '\0';
		return (result);
	}
	if (n == -2147483648)
	{
		result[0] = '-';
		result[1] = '2';
		n = 147483648;
	}
	converter(result, size, n);
	return (result);
}

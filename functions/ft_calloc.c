/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwallis <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 03:22:55 by mwallis           #+#    #+#             */
/*   Updated: 2025/01/29 03:23:41 by mwallis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

void	*ft_calloc(size_t nb_elements, size_t size_type)
{
	char	*str;
	size_t	i;

	if (size_type != 0 && (nb_elements > SIZE_MAX / size_type))
	{
		return (NULL);
	}
	str = malloc(size_type * nb_elements);
	if (str == NULL)
	{
		return (NULL);
	}
	i = 0;
	while (i < (nb_elements * size_type))
	{
		str[i] = '\0';
		i++;
	}
	return (str);
}

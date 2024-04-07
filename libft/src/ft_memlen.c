/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anporced <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 14:17:33 by anporced          #+#    #+#             */
/*   Updated: 2024/03/15 14:24:45 by anporced         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int	ft_memlen(void	*memory)
{
	int	len;

	len = 0;
	while (*(unsigned char *)memory++)
		len++;
	return (len);
}

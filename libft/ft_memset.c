/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpinoit <rpinoit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/08 17:57:37 by rpinoit           #+#    #+#             */
/*   Updated: 2018/10/10 09:38:53 by rpinoit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static inline void	copy_64byte(long int dst_ptr, unsigned long int cccc)
{
	((unsigned long int *)dst_ptr)[0] = cccc;
	((unsigned long int *)dst_ptr)[1] = cccc;
	((unsigned long int *)dst_ptr)[2] = cccc;
	((unsigned long int *)dst_ptr)[3] = cccc;
	((unsigned long int *)dst_ptr)[4] = cccc;
	((unsigned long int *)dst_ptr)[5] = cccc;
	((unsigned long int *)dst_ptr)[6] = cccc;
	((unsigned long int *)dst_ptr)[7] = cccc;
}

static inline void	copy_8byte_pow(long int *dst_ptr, size_t *len, \
		unsigned long int cccc)
{
	size_t xlen;

	xlen = *len / 64;
	while (xlen > 0)
	{
		copy_64byte(*dst_ptr, cccc);
		*dst_ptr += 64;
		xlen -= 1;
	}
	*len %= 64;
	xlen = *len / 8;
	while (xlen > 0)
	{
		((unsigned long int *)*dst_ptr)[0] = cccc;
		*dst_ptr += 8;
		xlen -= 1;
	}
	*len %= 8;
}

void				*ft_memset(void *dst, int c, size_t len)
{
	long int			dst_ptr;
	unsigned long int	cccc;

	dst_ptr = (long int)dst;
	if (len >= 8)
	{
		cccc = (unsigned char)c;
		cccc |= cccc << 8;
		cccc |= cccc << 16;
		cccc |= cccc << 32;
		while (dst_ptr % 8 != 0)
		{
			((unsigned char *)dst_ptr)[0] = c;
			dst_ptr += 1;
			len -= 1;
		}
		copy_8byte_pow(&dst_ptr, &len, cccc);
	}
	while (len > 0)
	{
		((unsigned char *)dst_ptr)[0] = c;
		dst_ptr += 1;
		len -= 1;
	}
	return (dst);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hex_x.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsampre <nsampre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/01 23:05:41 by nsampre           #+#    #+#             */
/*   Updated: 2017/09/19 22:10:28 by nsampre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

int		ft_put_hex(unsigned int hex, int display, t_format *format)
{
	unsigned int	width_nb;
	unsigned int	hex_bis;
	char			hex_letter;
	int				count;

	width_nb = 1;
	hex_bis = hex;
	count = 0;
	while ((hex_bis /= 16) > 0)
		width_nb *= 16;
	while (width_nb != 0)
	{
		hex_letter = ((hex / width_nb) % 16 + '0');
		if (hex_letter >= ':' && hex_letter <= '?')
			count += ft_putchar_count(hex_letter + HEX_TYPE, display);
		else
			count += ft_putchar_count(hex_letter, display);
		width_nb /= 16;
	}
	return (count);
}

void	ft_hex_get_central_len(unsigned int x, t_format *format)
{
	LEN = ft_put_hex(x, 0, format);
	if (IS_PRECISION && PRECISION > LEN)
	{
		PRECISION_TO_FILL = (PRECISION - LEN);
		LEN += PRECISION_TO_FILL;
	}
}

int		ft_handle_hex_min(va_list arg, t_format *format)
{
	unsigned int	x_min;
	int				count;

	x_min = va_arg(arg, unsigned int);
	HEX_TYPE = 39;
	if (IS_PRECISION && PRECISION == 0 && x_min == 0)
		return (ft_put_blanks(WIDTH));
	if (x_min == 0)
		return (ft_putchar_count('0', 1));
	ft_init_len_count(format);
	ft_hex_get_central_len(x_min, format);
	ft_hex_get_fill_left(format);
	ft_hex_get_fill_right(format);
	count = 0;
	count += ft_hex_write_left(format, 0);
	count += ft_put_precision(format);
	count += ft_put_hex(x_min, 1, format);
	count += ft_hex_write_right(format);
	return (count);
}

int		ft_handle_hex_maj(va_list arg, t_format *format)
{
	unsigned int	x_maj;
	int				count;

	x_maj = va_arg(arg, unsigned int);
	HEX_TYPE = 7;
	if (IS_PRECISION && PRECISION == 0 && x_maj == 0)
		return (ft_put_blanks(WIDTH));
	if (x_maj == 0)
		return (ft_putchar_count('0', 1));
	ft_init_len_count(format);
	ft_hex_get_central_len(x_maj, format);
	ft_hex_get_fill_left(format);
	ft_hex_get_fill_right(format);
	count = 0;
	count += ft_hex_write_left(format, 0);
	count += ft_put_precision(format);
	count += ft_put_hex(x_maj, 1, format);
	count += ft_hex_write_right(format);
	return (count);
}

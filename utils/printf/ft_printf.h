/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlott <acarlott@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 13:26:01 by acarlott          #+#    #+#             */
/*   Updated: 2022/12/09 10:40:03 by acarlott         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <ctype.h>
# include <fcntl.h>
# include <stdarg.h>
# include <limits.h>

int		ft_putchar(char s);
int		ft_putstr(char *str);
int		ft_putnbr_int(int n);
int		ft_print_memory(unsigned long nbr);
int		ft_printf(const char *format, ...);
int		ft_putnbr_unsigned(unsigned int n);
int		ft_check_convert(char str, va_list ap);
int		ft_putnbr_base(unsigned int nbr, char str);

#endif

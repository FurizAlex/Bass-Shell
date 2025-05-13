/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alechin <alechin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 15:56:24 by alechin           #+#    #+#             */
/*   Updated: 2025/01/08 16:10:58 by alechin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stdarg.h>
# include <stdint.h>
# include <unistd.h>

void	pf_putchar(char c);
int		pf_putstr(char *s);
int		hdle_ptr(void *ptr);
int		pf_percent(void);
int		count_d(int s);
int		e_long(unsigned long num);
int		recursive_hexa(unsigned int num, char specfs);
int		recursive_hexa_uint(uintptr_t num, char specfs);
int		symbology(va_list lp, const char sybl);
int		ft_printf(const char *str, ...);

#endif
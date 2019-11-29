/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchemoun <jchemoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 13:28:15 by jchemoun          #+#    #+#             */
/*   Updated: 2019/11/22 10:06:32 by jchemoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H

# define FT_PRINTF_H

# include <stdarg.h>

# define CONVSET "cspdiuxX%n\0"
# define FLAGSET "-0.*lh\0"
# define N_CONV 10
# define N_FLAG 8
# define ABS(x) x < 0 ? -x : x

int	ft_print_nbr(int conv[N_FLAG], va_list pa);
int	ft_print_ptr(int conv[N_FLAG], va_list pa);
int	ft_print_mxnbr(int conv[N_FLAG], va_list pa);
int	ft_print_xnbr(int conv[N_FLAG], va_list pa);
int	ft_print_unbr(int conv[N_FLAG], va_list pa);
int	ft_print_string(int conv[N_FLAG], va_list pa);
int	ft_print_pc(int conv[N_FLAG], va_list pa);
int	ft_print_char(int conv[N_FLAG], va_list pa);
int	ft_print_n(int conv[N_FLAG], va_list pa);
int	ft_usnbr(unsigned long long int n, char *b);
int	ft_unbr0(unsigned long long int n, int field, int form, char *b);
int	ft_unbrp(unsigned long long int n, int field, int prec, char *b);
int	ft_unbrm(unsigned long long int n, int field, int prec, char *b);

#endif
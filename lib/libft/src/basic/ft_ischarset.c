/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ischarset.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sikpenou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 18:54:58 by sikpenou          #+#    #+#             */
/*   Updated: 2020/02/06 18:56:03 by sikpenou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		ft_ischarset(unsigned char c, char *charset)
{
	while (*charset)
	{
		if (c == *charset)
			return (1);
		++charset;
	}
	return (0);
}

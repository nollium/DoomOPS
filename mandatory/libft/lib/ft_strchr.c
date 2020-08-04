/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smaccary <smaccary@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/04 18:30:19 by smaccary          #+#    #+#             */
/*   Updated: 2020/08/04 18:30:19 by smaccary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strchr(const char *s, int c)
{
	c = (unsigned char)c;
	if (!s)
		return (0);
	s--;
	while (*++s)
		if (*s == (char)c)
			return ((char *)s);
	return ((c == '\0') ? (char *)s : 0);
}

char	*ft_setchr(char *str, char *charset)
{
	char	*found;
	int		i;

	i = -1;
	if (!charset)
		return (0);
	while (charset[++i])
		if ((found = ft_strchr(str, charset[i])))
			return (found);
	return (0);
}

char	*ft_setrchr(char *str, char *charset)
{
	char	*found;
	char	*next;

	found = 0;
	while ((next = ft_setchr(str, charset)))
	{
		if (!*str)
			return (str);
		str++;
		if (!*next)
			return (next);
		found = next;
	}
	return (found);
}

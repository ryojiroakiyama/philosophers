#include "philo.h"

static bool	is_overflow(unsigned long num, \
		int sign, bool *invalid, long max)
{
	if (0 < num && \
		((sign == 1 && (unsigned long)max < num) || \
		(sign == -1 && (unsigned long)max < num - 1)))
		return (true);
	else if (*invalid)
		*invalid = false;
	return (false);
}

static size_t	pass_isspace(char *str, size_t i)
{
	while (str[i] == '\t' || str[i] == '\n' || str[i] == '\v'
		|| str[i] == '\f' || str[i] == '\r' || str[i] == ' ')
		i++;
	return (i);
}

long	ft_atol(char *str, bool *invalid)
{
	size_t			i;
	unsigned long	num;
	int				sign;

	i = 0;
	num = 0;
	sign = 1;
	i = pass_isspace(str, i);
	if (str[i] == '+')
		i++;
	else if (str[i] == '-' && ++i)
		sign = -1;
	*invalid = true;
	while (str[i] && ('0' <= str[i] && str[i] <= '9'))
	{
		num = num * 10 + (str[i] - '0');
		if (is_overflow(num, sign, invalid, LONG_MAX))
			break ;
		i++;
	}
	i = pass_isspace(str, i);
	if (i == 0 || str[i] != '\0')
		*invalid = true;
	return ((long)num * sign);
}

int	ft_atoi(char *str, bool *invalid)
{
	size_t			i;
	unsigned int	num;
	int				sign;

	i = 0;
	num = 0;
	sign = 1;
	i = pass_isspace(str, i);
	if (str[i] == '+')
		i++;
	else if (str[i] == '-' && ++i)
		sign = -1;
	*invalid = true;
	while (str[i] && ('0' <= str[i] && str[i] <= '9'))
	{
		num = num * 10 + (str[i] - '0');
		if (is_overflow(num, sign, invalid, INT_MAX))
			break ;
		i++;
	}
	i = pass_isspace(str, i);
	if (i == 0 || str[i] != '\0')
		*invalid = true;
	return ((int)num * sign);
}

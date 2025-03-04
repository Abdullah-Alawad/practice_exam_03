#include <unistd.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h>

int	num_len(int nbr)
{
	int	len;

	len = 0;
	if (nbr <= 0)
		len++;
	while (nbr != 0)
	{
		nbr /= 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int num)
{
	char	*str;
	int		len;

	len = num_len(num);
	str = malloc(len + 1);
	if (!str)
		return (NULL);
	str[len] = '\0';
	len--;
	if (num == 0)
		str[0] = '0';
	if (num < 0)
	{
		num = num * -1;
		str[0] = '-';
	}
	while (num > 0)
	{
		str[len] = '0' + (num % 10);
		num /= 10;
		len--;
	}
	return (str);
}

int	print_str(char *str)
{
	int	len;

	len = 0;
	while (str[len])
	{
		write(1, &str[len], 1);
		len++;
	}
	return (len);
}

int	print_number(int num)
{
	int		len;
	char	*str;

	len = 0;
	str = ft_itoa(num);
	len = print_str(str);
	free (str);
	return (len);
}

int	print_hexa(unsigned int num)
{
	int		len;
	char	c;

	len = 0;
	if (num >= 16)
		len += print_hexa(num / 16);
	if (num % 16 <= 9)
	{
		c = num % 16 + '0';
		len += write(1, &c, 1);
	}
	else
	{
		c = num % 16 - 10 + 'a';
		len += write(1, &c, 1);
	}
	return (len);
}

int	transform(va_list args, const char format)
{
	int	len;

	len = 0;
	if (format == 's')
		len += print_str(va_arg(args, char *));
	else if (format == 'd')
		len += print_number(va_arg(args, int));
	else if (format == 'x')
		len += print_hexa(va_arg(args, unsigned int));
	return (len);
}

int	ft_printf(const char *s, ...)
{
	va_list	args;
	int		i;
	int		len;

	va_start(args, s);
	i = 0;
	len = 0;
	while (s[i])
	{
		if (s[i] == '%')
		{
			len += transform(args, s[i + 1]);
			i++;
		}
		else	
			len += write(1, &s[i], 1);
		i++;
	}
	va_end(args);
	return (len);
}

int main(void)
{
	int l = ft_printf("hello %s, age: %d..\n", "Abdullah", -21);
	printf("my fun: %d\n", l);
	l = printf("hello %s, age: %d..\n", "Abdullah", -21);
	printf("og fun: %d\n", l);
	ft_printf("my hex cases: %x, %x, %x\n", 42, 2147483647, 255);
	printf("og hex cases: %x, %x, %x\n", 42, 2147483647, 255);
}

#include <unistd.h>
#include <stdlib.h>
#include <stdarg.h>

int	print_str(char *s)
{
	int	len;

	len = 0;
	if (!s)
	{
		len += write(1, "(null)", 6);
		return (len);
	}
	while (s[len])
	{
		write(1, &s[len], 1);
		len++;
	}
	return (len);
}


int	num_len(int num)
{
	int	len;

	len = 0;
	if (num <= 0)
		len++;
	while (num != 0)
	{
		num /= 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int num)
{
	char	*str;
	int		len;

	len = num_len(num); // calculate num len
	str = malloc(len + 1); // malloc str of num len
	if (!str)
		return (NULL);
	str[len] = '\0'; // null terminating the str
	len--;
	if (num == 0) // check if its only ZERO
		str[0] = '0';
	if (num < 0) // add the minus if existed
	{
		num *= -1;
		str[0] = '-';
	}
	while (num > 0) // loop the number and add it digit by digit 
	{
		str[len] = num % 10 + '0';
		num /= 10;
		len--;
	}
	return (str);
}

int	print_number(int num)
{
	int		len;
	char	*str;

	len = 0;
	str = ft_itoa(num);
	len += print_str(str);
	if (str)
		free(str);
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
		len+= write(1, &c, 1);
	}
	return (len);
}

int	transform(va_list args, char format)
{
	int	len;

	len = 0;
	if (format == 's')
		len += print_str(va_arg(args, char *));
	else if( format == 'd')
		len += print_number(va_arg(args, int));
	else if (format == 'x')
		len += print_hexa(va_arg(args, unsigned int));
	return (len);
}

int	ft_printf(char *s, ...)
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
	int len;

	len = ft_printf("hello my name is %s age is %d\n", "noor", 27);
	ft_printf("len : %d, %x, %x\n", len, 255, 1080);
}

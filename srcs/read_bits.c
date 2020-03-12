#include "corewar.h"

int32_t	u_to_int(uint8_t *arena, int idx, int size)
{
	int32_t bit;
	int		i;
	int		byte;
	int		sign;

	i = 0;
	byte = 8 * (size - 1);
	bit = 0;
	while (i < size)
	{
		bit |= (arena[(idx + i) % MEM_SIZE]) << byte;
		byte -= 8;
		i++;
	}
	ft_printf("BITS %d\n", bit);
	return (bit);
}

uint32_t	void_to_int(unsigned char *str)
{
	uint32_t bit;

	bit = (str[0] & 0xFF) << 24;
	bit = (str[1] & 0xFF) << 16 | bit;
	bit = (str[2] & 0xFF) << 8 | bit;
	bit = (str[3] & 0xFF) | bit;
	return (bit);
}

uint32_t			read_chk_bytes(int fd)
{
	int	rd;
	unsigned char	buffer[4];

	rd = 0;
	if ((rd = read(fd, buffer, 4)) < 0)
	{
		ft_printf("1cannot read\n");
		exit(0);
	}
	return (void_to_int(buffer));
}
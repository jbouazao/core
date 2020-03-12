#include "corewar.h"

int			rd_chk_chmp_name(t_player *p, int fd)//we didnt check error case if it is too long
{
	int		rd;

	rd = 0;
	if ((rd = read(fd, p->champion_name, 128)) < 0)
	{
		ft_printf("cannot read\n");
		return (ERROR_READING);
	}
	if (ft_strlen((const char *)p->champion_name) > PROG_NAME_LENGTH)
	{
		ft_printf("the player name is too long\n");
		return (ERROR_NAME_LEN);
	}
	return (1);
}

int			rd_chk_chmp_comment(t_player *p, int fd)//we didnt check error case if it is too long
{
	int		rd;

	rd = 0;
	if ((rd = read(fd, p->champion_comment, 2048)) < 0)
		return (ERROR_READING);
	if (ft_strlen((const char *)p->champion_comment) > COMMENT_LENGTH)
		return (ERROR_CHAMP_COMMENT);
	return (1);
}

int		get_exec_code(t_player *p, int fd)
{
	int ret;

	p->exec_code = (unsigned char *)ft_strnew(p->exec_code_size);
	if ((ret = read(fd, p->exec_code, p->exec_code_size + 1)) < 0)
		return (ERROR_READING);
	if (ret != p->exec_code_size)
	{
		ft_strdel((char **)&p->exec_code);
		return (ERROR_CODE_EXEC);
	}
	return (1);
}

int		parse_file(t_player *player)
{
	int		fd;
	int		error;

	if ((fd = open(player->file_name, O_RDONLY)) < 0)
		return (ERROR_OPEN);
	if (read_chk_bytes(fd) != COREWAR_EXEC_MAGIC)
		return (ERROR_MAGIC);
	if ((error = rd_chk_chmp_name(player, fd)) < 0)
		return (error);
	if (read_chk_bytes(fd) != 0)
		return (ERROR_NULL_NUMBER);
	if ((player->exec_code_size = read_chk_bytes(fd)) > CHAMP_MAX_SIZE)
		return (ERROR_CODE_SIZE);
	if ((error = rd_chk_chmp_comment(player, fd)) < 0)
		return (error);
	if (read_chk_bytes(fd) != 0)
		return (ERROR_NULL_NUMBER);
	if ((error = get_exec_code(player, fd)) < 0)
		return (error);
	return (1);
}
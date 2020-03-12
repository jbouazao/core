#include "corewar.h"

void    print_errors(int error_num, t_player player)
{
    if (error_num == ERROR_READING)
        ft_printf("Can't read the file\n");
    else if (error_num == ERROR_MAGIC)
        ft_printf("Magic header is incorrect\n");
    else if (error_num == ERROR_NULL_NUMBER)
        ft_printf("There's no null numbers\n");
    else if (error_num == ERROR_CHAMP_COMMENT)
        ft_printf("There's an error in champion comment\n");
    else if (error_num == ERROR_NAME_LEN)
        ft_printf("Error in lenght of champion name\n");
    else if (error_num == ERROR_CODE_SIZE)
        ft_printf("Error: File %s has too large a code (%d bytes > 682 bytes\n", player.file_name, player.exec_code_size);
    else if (error_num == ERROR_CODE_EXEC)
        ft_printf("Lengh of the exec code is not the same as the size\n");
    else if (error_num == ERROR_OPEN)
        ft_printf("Can't open the file\n");
}
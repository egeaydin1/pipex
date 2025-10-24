# include "pipex.h"

int error_print(char *msg,char *example)
{
    ft_putendl_fd(msg,2);
    if (example)
        ft_putendl_fd(example,1);
    
    return(2);
}
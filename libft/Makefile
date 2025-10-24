NAME = libft.a

CC = cc

CFLAGS = -Wall -Wextra -Werror

SRC = ft_putchar_fd.c \
	ft_putendl_fd.c \
	ft_putstr_fd.c \
	ft_putnbr_fd.c \
	ft_striteri.c \
	ft_strjoin.c \
	ft_isalpha.c \
    ft_isdigit.c \
	ft_strmapi.c \
	ft_isascii.c \
	ft_isalnum.c \
	ft_isprint.c \
	ft_tolower.c \
	ft_strrchr.c \
	ft_toupper.c \
	ft_strnstr.c \
	ft_memmove.c \
	ft_strlcpy.c \
	ft_strncmp.c \
	ft_strlcat.c \
	ft_strtrim.c \
	ft_memcpy.c \
	ft_memchr.c \
	ft_memcmp.c \
	ft_memset.c \
	ft_strdup.c \
	ft_strlen.c \
	ft_strchr.c \
	ft_substr.c \
	ft_calloc.c \
	ft_bzero.c \
	ft_split.c \
	ft_itoa.c \
	ft_atoi.c

BONUSSRC = ft_lstadd_back_bonus.c \
		ft_lstadd_front_bonus.c \
		ft_lstdelone_bonus.c \
		ft_lstclear_bonus.c \
		ft_lstlast_bonus.c \
		ft_lstiter_bonus.c \
		ft_lstmap_bonus.c \
		ft_lstnew_bonus.c \
		ft_lstsize_bonus.c

OBJ = $(SRC:.c=.o)
BONUSOBJ = $(BONUSSRC:.c=.o)

$(NAME): $(OBJ)
	ar -rcs $(NAME) $(OBJ)

all: $(NAME)

bonus: $(OBJ) $(BONUSOBJ)
	ar rcs $(NAME) $(OBJ) $(BONUSOBJ)

clean:
	rm -rf $(OBJ) $(BONUSOBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: re all bonus clean fclean
NAME = libft.a

SOURCE = \
				ft_atoi.c		ft_isascii.c	ft_memcmp.c		ft_putendl_fd.c		ft_strdup.c 	\
				ft_strlen.c		ft_strtrim.c	ft_bzero.c		ft_isdigit.c		ft_memcpy.c 	\
				ft_putnbr_fd.c	ft_striteri.c	ft_strmapi.c	ft_substr.c			ft_calloc.c 	\
				ft_isprint.c	ft_memmove.c	ft_putstr_fd.c	ft_strjoin.c 						\
				ft_strncmp.c	ft_tolower.c	ft_isalnum.c	ft_itoa.c			ft_memset.c 	\
				ft_split.c		ft_strlcat.c	ft_strnstr.c	ft_toupper.c		ft_isalpha.c 	\
				ft_memchr.c		ft_putchar_fd.c ft_strchr.c		ft_strlcpy.c		ft_strrchr.c	\
				ft_isspace.c																		\
				ft_printf/ft_printf.c			ft_printf/ft_printf_utils.c							\
				ft_printf/ft_printf_second_utils.c													\
				get_next_line/get_next_line.c	get_next_line/get_next_line_utils.c					\
				Wglbx/xpathfree.c				ft_tokenlst.c										\
				Wglbx/array2clear.c				Wglbx/comp.c										\
				Wglbx/countword.c				Wglbx/cpyenv.c										\
				Wglbx/dupnxtra.c				Wglbx/getxenv.c										\
				Wglbx/measure.c					Wglbx/ncomp.c										\
				Wglbx/sdigit.c					Wglbx/valenvch.c									\
				ft_instancer.c																		\

BONUS = \
				ft_lstadd_back.c	ft_lstclear.c		ft_lstiter.c	ft_lstmap.c \
				ft_lstsize.c		ft_lstadd_front.c	ft_lstdelone.c	ft_lstlast.c \
				ft_lstnew.c

OBJ = $(SOURCE:.c=.o)
OBJ_BONUS = $(BONUS:.c=.o)

CC = cc
CFLAGS = -Wall -Wextra -Werror

.PHONY: all clean fclean re bonus

all: $(NAME)

$(NAME): $(OBJ)
	@ar rcs $@ $^

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -rf ./*.o

fclean: clean
	@rm -rf $(NAME)

re: fclean all

bonus: $(OBJ) $(OBJ_BONUS)
	ar rcs $(NAME) $^

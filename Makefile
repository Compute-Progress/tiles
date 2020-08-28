NAME = Tiles
FLAGS = -g#Compile flags -Wall -Wextra -Werror

FILENAMES = main update display_init buttons
INCL = -I incl/
LIB = -L ~/.brew/lib -l SDL2 -l sdl2_image

SRCS = $(addprefix srcs/, $(addsuffix .c, $(FILENAMES)))
OBJS = $(addprefix objs/, $(addsuffix .o, $(FILENAMES)))

all : $(NAME)

objs/%.o : srcs/%.c
	@/bin/mkdir -p objs
	gcc $(FLAGS) -c $(INCL) $< -o $@

$(NAME): $(OBJS)
	gcc $(FLAGS) $(INCL) $(LIB) $(OBJS) -o $(NAME)

clean :
	rm -f $(OBJS)

fclean : clean
	rm -rf $(NAME)

push : clean
	git add .
	git commit -m "$(MSG)"
	git push origin master

re : fclean all

.PHONY : $(NAME) clean fclean push re

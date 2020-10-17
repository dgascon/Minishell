#ifndef TERMINAL_H
# define TERMINAL_H

# include <term.h>
#include "libft_hash.h"

# define T_CLEAR "clear"
# define T_CLEOL "el"
# define T_FCOLOR "setaf"
# define T_BCOLOR "setab"
# define T_BLINK "blink"
# define T_BOLD "bold"
# define T_UNDER "smul"
# define T_RESET "sgr0"
# define T_POS "cup"
# define T_SAVE "sc"
# define T_RESTORE "rc"
# define T_UP "cuu1"
# define T_DOWN "cud1"
# define T_RIGHT "cuf1"
# define T_LEFT "cub1"
# define T_COLUMN "cols"
# define T_LINE "lines"

# define STR_SIZE 64
# define PROMPT_SIZE 2

# define LEFTCHAR 'D'
# define RIGHTCHAR 'C'
# define UPCHAR 'A'
# define DOWNCHAR 'B'
# define DELCHAR 127
# define BACKSPACE 8
# define ENDCHAR 'F'
# define HOMECHAR 'H'

typedef struct 		termios	t_termios;

typedef struct		s_block
{
	int				nb_blocks;
	int 			size;
	int				alloc_size;
	char 			*str_cmd;
	char 			*str_put;
	void 			(*print)(struct s_block *);
}					t_block;

typedef struct		s_term
{
	t_hash	 		*list_blocks;
	t_hash			*current_block;
	int				cursor_pos;
	int				ndx_cursor;
	int				ndx_line;
	unsigned char	last_char;
	char 			esc_flag;
	int				nb_cols;
	t_termios 		termios;
	t_termios		termios_backup;
}					t_term;

t_term **getTerm(void);
int     init_term(void);
int     put_caps(char *caps, int color);
int     put_cursor(int col, int row);
int     handle_key(void);
char    *realloc_str(char *str, int new_size);
void    move_right(t_block *block);
void    move_left(t_block *block);
void    move_up(t_block *block);
void    move_down(t_block *block);
void	ft_blockprint(t_block *block);
t_block *ft_blocknew(void);
void    debug(t_term *term);
int		escape_sequences(t_block *block);
int		backspace(t_block *block);
#endif
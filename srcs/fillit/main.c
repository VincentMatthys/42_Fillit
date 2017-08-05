/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmatthys <vmatthys@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/25 21:25:12 by vmatthys          #+#    #+#             */
/*   Updated: 2017/08/05 22:24:08 by vmatthys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

/*
** ft_create_board(t_tetris *tet, unsigned char count, unsigned char size)
** Takes the solved tetris structure, which contains the final position
** (x & y) of every tetraminos. Takes the number (count) of tetraminos to be
** placed. Takes the size of the solution board.
*/

static void		ft_create_board(t_tetris *tet, char letter,
	unsigned char const size)
{
	char			*board;
	uint32_t		y;
	uint32_t		x;

	board = ft_str_initialized(size * (size + 1), '.');
	while ((y = 0) || letter-- >= 'A')
	{
		while (y < tet->height)
		{
			x = 0;
			while (x < tet->width)
			{
				if ((tet->value >> (16 * y + x)) & 1LL)
					board[(tet->y + y) * (size + 1) + tet->x + x] = tet->letter;
				x++;
			}
			y++;
		}
		tet++;
	}
	y = 0;
	while (y < size)
		board[y++ * (size + 1) + size] = '\n';
	ft_putstr(board);
	// ft_strdel(&board);
}

/*
** ft_puterror(char *str)
** Print the str string in the standart output, and returns -1.
*/

static int		ft_puterror(char const *str)
{
	ft_putendl(str);
	return (-1);
}

int				main(int ac, char **av)
{
	int				fd;
	char			letter;
	t_tetris		*tetris;
	unsigned char	size;

	if (ac != 2)
		return (ft_puterror("usage : ./fillit input_tetraminos"));
	if ((fd = open(av[1], O_RDONLY)) == -1)
		return (ft_puterror("error"));
	if (!(tetris = (t_tetris *)malloc(sizeof(t_tetris) * 27)))
		return (ft_puterror("error"));
	ft_bzero(tetris, sizeof(t_tetris) * 27);
	if (!(letter = ft_read_inputfile(fd, tetris)))
		return (ft_puterror("error"));
	if (close(fd) == -1)
		return (ft_puterror("error"));
	if (!(size = ft_da_vinci(tetris, letter)))
		return (ft_puterror("error"));
	ft_create_board(tetris, letter, size);
	// ft_memdel((void **)&tetris);
	return (0);
}

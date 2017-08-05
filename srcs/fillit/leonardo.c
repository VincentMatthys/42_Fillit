/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   leonardo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmatthys <vmatthys@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/25 22:28:36 by vmatthys          #+#    #+#             */
/*   Updated: 2017/08/05 22:41:29 by vmatthys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

/*
** ft_connect(t_tetris *tetris)
** Takes the whole valid tetris structure.
** Etablishes a link between a tetramino and it's predecessor, defined as the
** closest previous tetramino who has the same value.
** The N tetramino of the V form is now linked to the N - 1 tetramino of the
** same form.
*/

static void			ft_connect(t_tetris *tetris)
{
	unsigned char	i;
	unsigned char	j;

	i = 0;
	while ((tetris[i]).letter != 0)
	{
		tetris[i].previous = NULL;
		j = i;
		while (j - 1 >= 0)
		{
			j--;
			if ((tetris[j].value ^ tetris[i].value) == 0LL)
			{
				tetris[i].previous = &(tetris[j]);
				j = 0;
			}
		}
		i++;
	}
}

/*
** ft_starting_point(t_tetris *tetra)
** Takes a pointer on a tetramino we are trying to place.
** Initialises the absicca and the ordinate of the relative mark at (0,0) if
** there is no similar predecessor. Otherwise, do not try to place the new
** tetramino before its predecessor, by taking (previous->y and previous->x
** + width) as the starting point of the search.
*/

static void			ft_starting_point(t_tetris *tetra)
{
	if (tetra->previous == NULL)
	{
		tetra->y = 0;
		tetra->x = 0;
	}
	else
	{
		tetra->y = tetra->previous->y;
		tetra->x = tetra->previous->x + tetra->width - 1;
	}
}

/*
** ft_solve_board(t_tetris *tetris, unsigned char const size,
**	int16_t *board, unsigned char count)
** Takes a valid tetris array as read by ft_read_tetris, the putative minimal
** size of the solution, and the board of the solution
** The functions returns 1 if there is no more tetramino to be placed. Returns 0
** ohterwise.
** Calls ft_starting_point in order to not start searching a valid place for a
** tetramino that has a similar predecessor.
** Recursive backtracking implementation.
** Compares the occupation sites of the board with the ones inside the value,
** by moving the local mark of the tetramino (represented by x & y) until the
** ones on the board (which represent the already placed tetraminos) are not
** supperposed on the ones from the tetramino.
** If there is, at least, one match, then the function shifts the position of
** the tetramino, id est, shifts the value which represents the tetramino
** from 1 to the right. Do it as long as there is is no solution, and keeps the
** result in x (abscissa in the "board"). If no horizontal shifts gives a
** solution, then the function shifts ordinate (y), and stocks final ordinate
** in y.
** The final x & y are the position where the placed tetramino gives a solution
** for every other tetraminos. In order to explore every possibility for the
** others, the recursive call, if doesn't succeed, has to delete the placement
** of the tetramino, with the XOR operator (exclusive OR : ^=).
*/

static int			ft_solve_board(t_tetris *tetris, unsigned char const size,
	int16_t *board)
{
	if (tetris->letter == 0)
		return (1);
	ft_starting_point(tetris);
	while (tetris->y + tetris->height <= size)
	{
		while (tetris->x + tetris->width <= size)
		{
			if (!(*(int64_t *)(board + tetris->y) & tetris->value << tetris->x))
			{
				*(int64_t *)(board + tetris->y) ^= tetris->value << tetris->x;
				if (ft_solve_board(tetris + 1, size, board) == 1)
					return (1);
				*(int64_t *)(board + tetris->y) ^= tetris->value << tetris->x;
			}
			(tetris->x)++;
		}
		tetris->x = 0;
		(tetris->y)++;
	}
	return (0);
}

/*
** ft_save_and_retry(t_tetris *tetris, t_tetris *current, char letter)
** Copy the state of tetris to current, and put x and y of tetris to 0.
*/

static int			ft_save_and_retry(t_tetris *tetris, t_tetris *current,
	char letter)
{
	while (letter-- >= 'A')
	{
		current->x = tetris->x;
		current->y = tetris->y;
		tetris->x = 0;
		tetris->y = 0;
		current->width = tetris->width;
		current->height = tetris->height;
		current->letter = tetris->letter;
		current++;
		tetris++;
	}
	return (0);
}

/*
** ft_solve(t_tetris *tetris, unsigned char count)
** Takes a valid tetris array as read by ft_read_tetris and the number of\
** tetraminos.
** Initialises the solution board with 0.
** Increses size so the board can, at least, contains the area of the tetris
** structure.
** Connects the N tetramino of the V form with the N - 1 tetramino of the same
** form.
** Calls ft_solve_board with the given board and a specific size. Starting with
** size == 2 and incerements size until size == 13 or until a solution is found.
** Indeed, a 13 x 13 square is the larger minimal square which can contain 26
** tetraminos.
** Returns the size of the solution, or 0 if the board could not be created.
*/

unsigned char		ft_da_vinci(t_tetris *tetris, char const letter)
{
	unsigned char	size;
	int16_t			*board;
	t_tetris		*current;

	size = 13;
	if (!(current = (t_tetris *)malloc(sizeof(t_tetris) * (letter - 'A' + 1))))
		return (0);
	if (!(board = (int16_t *)malloc(sizeof(int16_t) * 16)))
		return (0);
	ft_bzero(board, sizeof(int16_t) * 16);
	ft_connect(tetris);
	while (size * size >= ((letter + 1 - 'A') * 4) && ft_solve_board(tetris,
		size, board) == 1)
	{
		size--;
		ft_bzero(board, sizeof(int16_t) * 16);
		ft_save_and_retry(tetris, current, letter);
	}
	ft_save_and_retry(current, tetris, letter);
	ft_memdel((void **)&board);
	ft_memdel((void **)&current);
	return (size + 1);
}

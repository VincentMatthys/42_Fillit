/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   leader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmatthys <vmatthys@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/25 21:30:54 by vmatthys          #+#    #+#             */
/*   Updated: 2016/12/01 19:37:52 by vmatthys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

/*
** ft_check_linkage(char const *buff)
** Takes buff, as read by ft_read_tetris
** Verifies every link between sharps.
** We assume, of course, there is 4 and only 4 sharps
** Returns 1 if it's a valid tetramino, 0 otherwise
*/

static int		ft_check_linkage(char const *buff)
{
	unsigned char	i;
	unsigned char	link;

	i = 0;
	link = 0;
	while (i < 20)
	{
		if (buff[i] == '#')
		{
			if (i - 1 >= 0 && buff[i - 1] == '#')
				link++;
			if (i + 1 < 20 && buff[i + 1] == '#')
				link++;
			if (i - 5 >= 0 && buff[i - 5] == '#')
				link++;
			if (i + 5 < 20 && buff[i + 5] == '#')
				link++;
		}
		i++;
	}
	return (link == 6 || link == 8);
}

/*
** ft_verify_sharps(char const sbuff, int count)
** Given str, as read by ft_read_tetris, and given the number of bytes read.
** Verifies if the buffer only contains '.' and '#', and '\n' at the end of each
** line.
** Verifies, if count == 21, that the 21th char read is a '\n'.
** Returns 1 if there is only four well placed sharps in str, and 0 if there is
** any error in the output form.
*/

static int		ft_verify_sharps(char const *buff, int const count)
{
	unsigned char	i;
	unsigned char	sharp;

	sharp = 0;
	i = 0;
	while (i < 20)
	{
		if (i % 5 != 4)
		{
			if (buff[i] == '#')
				sharp++;
			if (buff[i] != '.' && buff[i] != '#')
				return (0);
		}
		else if (buff[i] != '\n')
			return (0);
		i++;
	}
	if (count == 21 && buff[20] != '\n')
		return (0);
	if (sharp != 4 || ft_check_linkage(buff) == 0)
		return (0);
	return ((count == 21) ? 1 : 2);
}

/*
** ft_find_area(char const *buff, unsigned char *area)
** Takes str, as read by ft_read_tetris, and area, as create in ft_get_tetramino
** Given a valid str as defined by ft_verify_sharps. The area is defined as the
** smallest rectangle which can contain the tetramino.
** Stocks the 4 corners of the rectangle in area as following
** area[0] = top corner
** area[1] = bottom corner
** area[2] = left corner
** area[3] = right corner
*/

static void		ft_find_area(char const *buff, unsigned char *area)
{
	unsigned char	i;

	i = 0;
	area[0] = 3;
	area[1] = 0;
	area[2] = 3;
	area[3] = 0;
	while (i < 20)
	{
		if (buff[i] == '#')
		{
			if (i % 5 < area[0])
				area[0] = i % 5;
			if (i % 5 > area[1])
				area[1] = i % 5;
			if (i / 5 < area[2])
				area[2] = i / 5;
			if (i / 5 > area[3])
				area[3] = i / 5;
		}
		i++;
	}
}

/*
** ft_get_tetramino(char *str, char letter)
** Takes str, as read by ft_read_tetris, & the letter identifying the tetramino
** Given a valid str as defined by ft_verify_sharps.
** Builds the tetramino's structure as following.
** tetra->letter : identifier of the tetramino in the input file
** tetra->width : width of the tetramino
** tetra->height :  height of the tetramino
** tetra->value : representation of the sharps as 1 in a int64_t full of 0. This
** is done by shifting a 1LL (1 long long) by the abscissa and the ordinate of
** the sharps in the local mark;
** Returns NULL if area can'4t be allocated, returns the tetramino pointer
** otherwise.
*/

static t_tetris	*ft_get_tetramino(t_tetris *tetramino, char const *buff,
	char const letter)
{
	unsigned char	x;
	unsigned char	y;
	unsigned char	*area;

	if (!(area = (unsigned char *)malloc(sizeof(unsigned char) * 4)))
		return (NULL);
	ft_find_area(buff, area);
	tetramino->letter = letter;
	tetramino->width = area[1] - area[0] + 1;
	tetramino->height = area[3] - area[2] + 1;
	tetramino->value = 0LL;
	y = 0;
	while (y < tetramino->height)
	{
		x = 0;
		while (x < tetramino->width)
		{
			if (buff[5 * (area[2] + y) + (area[0] + x)] == '#')
				tetramino->value |= 1LL << (16 * y + x);
			x++;
		}
		y++;
	}
	ft_memdel((void **)&area);
	return (tetramino);
}

/*
** ft_read_tetris(int const fd, t_tetris *tetris)
** Given a filedescriptor where av[1] is opened, and an tetramino's array
** Stocks valid tetraminos, as defined in ft_verify_sharps, in the array
** Returns 1 if the input file is valid and contains valid tetraminos
** Returns 0 otherwise
*/

char			ft_read_inputfile(int const fd, t_tetris *tetris)
{
	char		letter;
	int			count;
	char		buff[21];
	char		end;

	letter = 'A';
	while ((count = (int)read(fd, buff, 21)) >= 20)
	{
		if (letter - 'A' >= 26
		|| (end = ft_verify_sharps((char const *)buff, count)) == 0)
			return (0);
		if (!(ft_get_tetramino(tetris++, (char const *)buff,
		(char const)letter)))
			return (0);
		letter++;
	}
	if (count != 0)
		return (0);
	else
		return ((letter > 'A' && end == 2) ? letter - 1 : 0);
}

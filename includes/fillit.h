/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmatthys <vmatthys@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/25 21:35:21 by vmatthys          #+#    #+#             */
/*   Updated: 2016/12/01 19:42:04 by vmatthys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLIT_H
# define FILLIT_H
# include <string.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/uio.h>
# include "libft.h"

typedef struct		s_tetris
{
	char			letter;
	unsigned char	width;
	unsigned char	height;
	unsigned char	x;
	unsigned char	y;
	int64_t			value;
	struct s_tetris	*previous;
}					t_tetris;
unsigned char		ft_da_vinci(t_tetris *tetris, char const letter);
char				ft_read_inputfile(int const fd, t_tetris *tetris);
#endif

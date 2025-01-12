/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_talk.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgomez-a <dgomez-a@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 18:49:59 by dgomez-a          #+#    #+#             */
/*   Updated: 2025/01/11 14:34:20 by dgomez-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_TALK_H
# define MINI_TALK_H

# include "42_libft/libft.h"
# include "printf/ft_printf.h"
# include <signal.h>
# include <stdlib.h>
# include <unistd.h>

void	set_signal(int sig, void *signal_handler, int flag);

#endif

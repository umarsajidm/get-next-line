/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musajid <musajid@hive.student.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 14:56:33 by musajid           #+#    #+#             */
/*   Updated: 2025/06/10 14:56:33 by musajid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int putstr(char *str)
{
    int i;

    i = 0;
    if (!str)
        return (-1);
    while (str[i])
        write(1, &str[i++], 1);
    str[i] = '\0';
    return (i);
}
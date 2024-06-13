/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguille <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 00:34:23 by mguille           #+#    #+#             */
/*   Updated: 2023/06/27 00:08:15 by mguille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/*

Extrayez la première ligne de la chaîne pointée par temp et
décaler l'adresse temporaire au début de la ligne suivante ou NULL si
la fin de la chaîne est atteinte.

in : temp un pointeur statique vers la première ligne.
out : temp un pointeur statique vers la ligne suivante : temp + ft_strlen(line)
return : La première ligne vers laquelle pointait temp ou NULL.

 */

static char	*ft_next(char **temp)
{
	char	*line;
	char	*ptr;

	ptr = *temp;
	while (*ptr && *ptr != '\n')
		++ptr;
	ptr += (*ptr == '\n');
	line = ft_substr (*temp, 0, (size_t)(ptr - *temp));
	if (!line)
	{
		free (*temp);
		return (NULL);
	}
	ptr = ft_substr (ptr, 0, ft_strlen (ptr));
	free (*temp);
	*temp = ptr;
	return (line);
}

/*
Lire le contenu du fichier pointé par fd.

in : fd un descripteur de fichier pointant vers un fichier.
in : temp un pointeur statique vers le contenu lu.
return : Un pointeur vers :
- une ligne, si BUFFER_SIZE est plus petit qu'une ligne.
- une ligne + plus, si BUFFER_SIZE est plus grand qu'une ligne
ou s'il ne s'agit pas du premier appel get_next_line pour ce fd.
- NULL s'il n'y a plus rien à lire sur fd.
 */

static char	*ft_read(char *temp, int fd, char *buf)
{
	ssize_t		r;

	r = 1;
	while (r && !ft_strchr (temp, '\n'))
	{
		r = read (fd, buf, BUFFER_SIZE);
		if (r == -1)
		{
			free (buf);
			free (temp);
			return (NULL);
		}
		buf[r] = 0;
		temp = ft_concatenate (temp, buf);
		if (!temp)
		{
			free (buf);
			return (NULL);
		}
	}
	free (buf);
	return (temp);
}

/*
Obtenir la prochaine ligne de texte disponible sur un descripteur de fichier.

Appeler get_next_line dans une boucle nous permettra de 
lire le texte disponible sur le descripteur de fichier 
une ligne à la fois jusqu'à la fin de celui-ci.
Une ligne est définie comme une chaîne terminée par NUL ou LF.

in : fd le descripteur de fichier.
out : temp un pointeur statique vers la prochaine ligne à lire ou NULL.
return : La première ligne à lire à partir de temp.
 */

char	*get_next_line(int fd)
{
	static char	*temp[OPEN_MAX];
	char		*buf;

	if (fd == -1 || BUFFER_SIZE < 1)
		return (NULL);
	if (!temp[fd])
		temp[fd] = ft_strdup("");
	if (!temp[fd])
		return (NULL);
	buf = malloc (sizeof (*buf) * (BUFFER_SIZE + 1));
	if (!buf)
	{
		free (temp[fd]);
		return (NULL);
	}
	temp[fd] = ft_read (temp[fd], fd, buf);
	if (!temp[fd])
		return (NULL);
	if (!*temp[fd])
	{
		free (temp[fd]);
		temp[fd] = NULL;
		return (NULL);
	}
	return (ft_next(&temp[fd]));
}

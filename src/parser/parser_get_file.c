#include "doom.h"

/*
** **************************************************************************
**	Save the contents of a file.
**
**	Arguments:
**	char *filename	| file name
** **************************************************************************
*/
char*		get_line_file(char *filename)
{
	char	*str;
	char	*ptr_str;
	char	*line;
	int		res;
	int		fd;

	str = NULL;
	if ((fd = open(filename, O_RDONLY)) < 0)
		ft_error("[XML Parser]: incorrect file name");
	while ((res = get_next_line(fd, &line)) > 0)
	{
		if (str == NULL)
			str = line;
		else
		{
			ptr_str = str;
			str = ft_strjoin(str, line);
			free(ptr_str);
			free(line);
		}
	}
	close(fd);
	return (str);
}
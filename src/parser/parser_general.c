#include "doom.h"

void		parser_xml_get_open_tag(char *file, t_xml_elem *elem)
{
	char		*start_tag;
	char		*end_tag;
	size_t		len;

	start_tag = ft_strstr(file, "<");
	end_tag = ft_strstr(start_tag, ">");
	if (start_tag == NULL || end_tag == NULL)
		ft_error("[XML Parser]: Syntax error");
	elem->ptr_begin = start_tag;
	start_tag++;
	len = end_tag - start_tag;
	elem->name = ft_strncpy(ft_strnew(len), start_tag, len);
}

void		parser_xml_get_close_tag(t_xml_elem *elem)
{
	char	*file;
	char	*close_tag_str;
	char	*ptr_tag_str;
	char	*close_tag;

	file = elem->ptr_begin;
	close_tag_str = ft_strjoin("</", elem->name);
	ptr_tag_str = close_tag_str;
	close_tag_str = ft_strjoin(close_tag_str, ">");
	free(ptr_tag_str);
	close_tag = ft_strstr(file, close_tag_str);
	if (close_tag == NULL)
		ft_error("[XML Parser]: Syntax error");
	elem->ptr_end = ft_strstr(close_tag, ">");
	elem->ptr_end++;
	free(close_tag_str);
}

t_xml_elem*	parser_xml_get_elem(char *file)
{
	t_xml_elem	*elem;

	elem = ft_memalloc(sizeof(t_xml_elem));
	parser_xml_get_open_tag(file, elem);
	parser_xml_get_close_tag(elem);
	return (elem);
}

int			parser_xml_file_struct(char *file, t_list *s)
{
	t_xml_elem	*elem;
	t_list		*list;

	elem = parser_xml_get_elem(file);
	list = ft_lstnew(elem, sizeof(t_xml_elem));
	if (s == NULL)
		s = list;
	else
		ft_lstadd(&s, list);
	if (*elem->ptr_end == '\0')
		return (0);
	else
		return (parser_xml_file_struct(elem->ptr_end, s));
}

char*		parser_xml_get_single_line_file(char *filename)
{
	char	*str;
	char	*ptr_str;
	char	*line;
	int		res;
	int		fd;

	str = NULL;
	if ((fd = open(filename, O_RDONLY)) < 0)
		ft_error("Error: incorrect file name");
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

/*
**	Parse .xml file.
**
**	@param char *filename	| filename
**	@return void *			| pointer to t_list
*/
void*		parser_xml_file(char *filename)
{
	char	*file;
	t_list	*s;

	file = parser_xml_get_single_line_file(filename);
	if ((void*)file == NULL)
		ft_error("error!");
	printf("%s\n", file);
	s = NULL;
	parser_xml_file_struct(file, s);
	free(file);
	return (NULL);
}

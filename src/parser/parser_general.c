#include "doom.h"

t_list*			parser_xml_get_attr_list(char *start_attr, char *end_attr) {
	// char		*ptr;
	// t_list		*list;

	// ptr = start_attr;
	// list = NULL;

	size_t		len;
	t_list		*list;
	char*		attr;

	len = end_attr - start_attr;

	attr = ft_strncpy(ft_strnew(len), start_attr, len);
	
	list = ft_lstnew(attr, ft_strlen(attr));
	return list;
}

void			parser_xml_set_elem_param(char *start_open_tag, char *end_open_tag, t_xml_elem *elem)
{
	size_t		len;
	char		*ptr;

	ptr = start_open_tag;
	while (ptr < end_open_tag && !ft_isspace(*ptr))
		ptr++;
	len = ptr - start_open_tag;
	elem->name = ft_strncpy(ft_strnew(len), start_open_tag, len);
	if (ptr != end_open_tag)
		elem->attr = parser_xml_get_attr_list(++ptr, end_open_tag);
}

int			parser_xml_get_open_tag(char *file_start, char *file_end, t_xml_elem *elem)
{
	char		*start_open_tag;
	char		*end_open_tag;
	char		*start_close_tag;

	start_open_tag = ft_strstr(file_start, "<");
	start_close_tag = ft_strstr(file_start, "</");
	if (start_open_tag == NULL || \
		start_open_tag > file_end || \
		start_close_tag == NULL || \
		start_open_tag == start_close_tag)
		return (0);

	end_open_tag = ft_strstr(start_open_tag, ">");
	if (start_open_tag == NULL || \
		end_open_tag == NULL || \
		end_open_tag > file_end)
		ft_error("[XML Parser]: Syntax error: open tag");
	elem->ptr_begin = start_open_tag;
	start_open_tag++;
	parser_xml_set_elem_param(start_open_tag, end_open_tag, elem);
	end_open_tag++;
	elem->ptr_begin_content = end_open_tag;
	return (1);
}

void		parser_xml_get_close_tag(char *file_start, char *file_end, t_xml_elem *elem)
{
	char	*file;
	char	*close_tag_str;
	char	*ptr_tag_str;
	char	*close_tag;

	file = file_start;
	close_tag_str = ft_strjoin("</", elem->name);
	ptr_tag_str = close_tag_str;
	close_tag_str = ft_strjoin(close_tag_str, ">");
	free(ptr_tag_str);
	close_tag = ft_strstr(file, close_tag_str);
	if (close_tag == NULL || close_tag > file_end)
		ft_error("[XML Parser]: Syntax error: close tag");
	elem->ptr_end = ft_strstr(close_tag, ">");
	elem->ptr_end++;
	free(close_tag_str);
	elem->ptr_end_content = close_tag;
}

t_xml_elem*	parser_xml_get_elem(char *file_start, char *file_end)
{
	t_xml_elem	*elem;
	size_t		len;

	elem = ft_memalloc(sizeof(t_xml_elem));
	if (parser_xml_get_open_tag(file_start, file_end, elem))
	{
		parser_xml_get_close_tag(file_start, file_end, elem);
		elem->content = NULL;
	}
	else
	{
		elem->name = NULL;
		elem->ptr_begin = file_start;
		elem->ptr_end = file_end;
		elem->ptr_begin_content = file_start;
		elem->ptr_end_content = file_end;
		len = elem->ptr_begin - elem->ptr_end;
	}
	return (elem);
}

int			parser_xml_file_struct(char *file_start, char *file_end, t_list *s)
{
	t_xml_elem	*elem;
	t_list		*list;

	elem = parser_xml_get_elem(file_start, file_end);
	list = ft_lstnew(elem, sizeof(t_xml_elem));
	if (s == NULL)
		s = list;
	else
		ft_lstadd(&s, list);
	printf("@ %s: %s\n", elem->name, elem->content);
	if (elem->ptr_end_content - elem->ptr_begin_content && elem->name != NULL)
		parser_xml_file_struct(elem->ptr_begin_content, elem->ptr_end_content, NULL);
	if (*elem->ptr_end == '\0' || elem->name == NULL)
		return (0);
	else
		return (parser_xml_file_struct(elem->ptr_end, file_end, s));
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
	char	*file_end;
	t_list	*s;

	file = parser_xml_get_single_line_file(filename);
	file_end = ft_strchr(file, '\0');
	if ((void*)file == NULL)
		ft_error("error!");
	s = NULL;
	parser_xml_file_struct(file, file_end, s);
	free(file);
	return (NULL);
}

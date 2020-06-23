#include "doom.h"

/*
** **************************************************************************
**	Search xml open tag
**
**	Arguments:
**	char *file_start	| pointer to start search
**	char *file_end		| pointer to end search
**	t_xml_elem *elem	| pointer to .xml element
**
**	Return:
**	int					| 1 if success, 0 if fail
** **************************************************************************
*/
int			parser_xml_get_open_tag(char *file_start, char *file_end, \
				t_xml_elem *elem)
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
	parser_xml_get_elem_param(start_open_tag, end_open_tag, elem);
	end_open_tag++;
	elem->ptr_begin_content = end_open_tag;
	return (1);
}

/*
** **************************************************************************
**	Search xml close tag
**
**	Arguments:
**	char *file_start	| pointer to start search
**	char *file_end		| pointer to end search
**	t_xml_elem *elem	| pointer to .xml element
**
**	Return:
**	t_xml_elem*			| .xml element struct
** **************************************************************************
*/
void		parser_xml_get_close_tag(char *file_start, char *file_end, \
				t_xml_elem *elem)
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

/*
** **************************************************************************
**	Parse .xml tag
**
**	Arguments:
**	char *file_start	| pointer to start tag
**	char *file_end		| pointer to end tag
**
**	Return:
**	t_xml_elem*			| .xml element struct
** **************************************************************************
*/
t_xml_elem*	parser_xml_get_elem(char *file_start, char *file_end)
{
	t_xml_elem	*elem;
	size_t		len_content;

	elem = ft_memalloc(sizeof(t_xml_elem));
	if (parser_xml_get_open_tag(file_start, file_end, elem))
	{
		parser_xml_get_close_tag(file_start, file_end, elem);
		len_content = elem->ptr_end_content - elem->ptr_begin_content;
		elem->content = ft_strncpy(ft_strnew(len_content), \
			elem->ptr_begin_content, len_content);
	}
	else
		return (NULL);
	return (elem);
}
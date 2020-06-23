#include "doom.h"

/*
** **************************************************************************
**	Recursive parse .xml file.
**
**	Arguments:
**	char *file_start	| pointer to start parse
**	char *file_end		| pointer to end parse
**	t_list *s			| pointer to .xml element list
**
**	Return:
**	int					| 0 if element is ultimate
** **************************************************************************
*/
int			parser_xml_file_struct(char *file_start, char *file_end, t_list *s)
{
	t_xml_elem	*elem;
	t_list		*list;

	elem = parser_xml_get_elem(file_start, file_end);
	if (elem == NULL) {
		return (0);
	}
	list = ft_lstnew(elem, sizeof(t_xml_elem));
	if (s == NULL)
		s = list;
	else
		ft_lstadd(&s, list);
	printf("@ %s: %s\n", elem->name, elem->content);
	if (elem->ptr_end_content - elem->ptr_begin_content > 0 && elem->name != NULL)
		parser_xml_file_struct(elem->ptr_begin_content, elem->ptr_end_content, NULL);
	if (*elem->ptr_end == '\0' || elem->name == NULL)
		return (0);
	else
		return (parser_xml_file_struct(elem->ptr_end, file_end, s));
}

/*
** **************************************************************************
**	Parse .xml file.
**
**	Arguments:
**	char *filename	| file name
**
**	Return:
**	t_list *		| pointer to xml t_list
** **************************************************************************
*/
void*		parser_xml_file(char *filename)
{
	char	*file;
	char	*file_end;
	t_list	*s;

	file = get_line_file(filename);
	file_end = ft_strchr(file, '\0');
	if ((void*)file == NULL)
		ft_error("[XML Parser]: Unknown error");
	s = NULL;
	parser_xml_file_struct(file, file_end, s);
	free(file);
	return (s);
}

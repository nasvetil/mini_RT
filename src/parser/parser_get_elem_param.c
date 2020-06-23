#include "doom.h"

/*
** **************************************************************************
**	Add element attribute to list
**
**	Arguments:
**	char *attr_str		| pointer to attribute string
**	t_list **list		| pointer to pointer attribute list
** **************************************************************************
*/
void		parser_xml_elem_add_attr(char *attr_str, t_list **list) {
	t_list		*new_list;
	t_xml_attr*	attr;
	char**		attr_array;
	size_t		len_key;

	attr = ft_memalloc(sizeof(t_xml_attr));
	attr_array = ft_strsplit(attr_str, '\"');
	len_key = ft_strlen(attr_array[0]);
	attr->key = ft_strncpy(ft_strnew(len_key), attr_array[0], len_key - 1);
	attr->value = attr_array[1];
	new_list = ft_lstnew(attr, sizeof(t_xml_attr));
	ft_memdel((void**)&attr_array[0]);
	ft_memdel((void**)&(*attr_array));
	if (*list)
		ft_lstadd(list, new_list);
	else
		*list = new_list;
}

/*
** **************************************************************************
**	Get element attribute list
**
**	Arguments:
**	char *start_attr	| pointer to start search
**	char *end_attr		| pointer to end search
**
**	Return:
**	t_list*				| pointer to attribute list
** **************************************************************************
*/
t_list*			parser_xml_get_attr_list(char *start_attr, char *end_attr) {
	size_t		len;
	t_list		*list;
	char**		attr_list_array;
	char**		ptr_attr_list_array;
	char*		attr_str;

	// t_xml_attr*	temp_attr;

	len = end_attr - start_attr;
	attr_str = ft_strncpy(ft_strnew(len), start_attr, len);
	attr_list_array = ft_strsplit(attr_str, ' ');
	ptr_attr_list_array = attr_list_array;
	list = NULL;
	while (*ptr_attr_list_array != NULL) {
		parser_xml_elem_add_attr(*ptr_attr_list_array, &list);
		ft_strdel(&(*ptr_attr_list_array));
		ptr_attr_list_array++;
	}
	ft_memdel((void**)attr_list_array);

	// while(list) {
	// 	temp_attr = list->content;
	// 	printf("  > key:%s\tvalue:%s\n", temp_attr->key, temp_attr->value);
	// 	list = list->next;
	// }
	return list;
}

/*
** **************************************************************************
**	Get element parameter
**
**	Arguments:
**	char *start_open_tag	| pointer to start open tag
**	char *end_open_tag		| pointer to end open tag
**	t_xml_elem *elem		| pointer to .xml element
** **************************************************************************
*/
void			parser_xml_get_elem_param(char *start_open_tag, char *end_open_tag, t_xml_elem *elem)
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
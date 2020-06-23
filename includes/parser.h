#ifndef PARSER_H
# define PARSER_H

# include <libft.h>

/*
**	t_xml_attr
**
**	char *key	| name of key
**	char *value	| value (always string)
*/
typedef struct	s_xml_attr
{
	char		*key;
	char		*value;
}				t_xml_attr;

/*
**	t_xml_elem
**
**	char *name				|
**	char *ptr_begin			|
**	char *ptr_end			|
**	char *ptr_begin_content	|
**	char *content			|
**	t_list *attr			|
**	t_list *child			|
*/
typedef struct	s_xml_elem
{
	char		*name;
	char		*ptr_begin;
	char		*ptr_end;
	char		*ptr_begin_content;
	char		*ptr_end_content;
	char		*content;
	t_list		*attr;
	t_list		*child;
}				t_xml_elem;

/*
** **************************************************************************
**	parser_general.c
** **************************************************************************
*/
void*			parser_xml_file(char *filename);

/*
** **************************************************************************
**	parser_get_file.c
** **************************************************************************
*/
char*			get_line_file(char *filename);

/*
** **************************************************************************
**	parser_get_elem.c
** **************************************************************************
*/
t_xml_elem*		parser_xml_get_elem(char *file_start, char *file_end);

/*
** **************************************************************************
**	parser_get_elem_param.c
** **************************************************************************
*/
void			parser_xml_get_elem_param(char *start_open_tag, \
					char *end_open_tag, t_xml_elem *elem);

#endif
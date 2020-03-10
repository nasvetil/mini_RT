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

void*			parser_xml_file(char *filename);

#endif
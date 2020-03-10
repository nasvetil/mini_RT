#include "doom.h"

/*
** **************************************************************************
**	void ft_main(int c, char **v)
**
**	General programm function.
** **************************************************************************
*/

void	ft_main(int c, char **v)
{
	t_wolf3d	w;

	(void)v;
	if (c > 2)
		ft_error("WRONG arguments");
	if (c > 1)
		parser_xml_file(v[1]);
	// ft_unpack();
	w.sdl = sdl_init(w.sdl);
	ft_gui_init(&w);
	ft_main_gui_init(&w);
	ft_gui_redraw(&w);
	while (w.sdl->running)
		ft_main_events(&w);
	ft_clean_sdl(&w);
	// ft_check_folders();
}

int		main(int c, char **v)
{
	ft_main(c, v);
	return (0);
}

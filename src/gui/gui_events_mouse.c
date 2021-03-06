#include "doom.h"

/*
** **************************************************************************
**	void ft_gui_events(t_wolf3d *w)
**
**	Function that handle user mouse events.
** **************************************************************************
*/

void	ft_gui_events_mouse(t_wolf3d *w, SDL_Event *e)
{
	if (e->type == SDL_MOUSEBUTTONDOWN)
	{
		if (e->button.button == SDL_BUTTON_LEFT)
			ft_gui_mousebuttondown(w, *e, w->gui.dom);
	}
	if (e->type == SDL_MOUSEWHEEL)
		ft_gui_mousewheel(w, *e, w->gui.dom);
	if (e->type == SDL_MOUSEBUTTONUP)
		ft_gui_mousebuttonup(w, *e, w->gui.dom);
	if (e->type == SDL_MOUSEMOTION)
		ft_gui_mousemotion(w, *e, w->gui.dom);
}

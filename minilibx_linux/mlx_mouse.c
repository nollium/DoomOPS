#include "mlx_int.h"

int		mlx_mouse_move(t_xvar *xvar, t_win_list *win, int x, int y)
{
	XWarpPointer(xvar->display, None, win->window, 0, 0, 0, 0, x, y);
	return (0);
}

int		mlx_mouse_hide(t_xvar *xvar, t_win_list *win)
{
	static char data[1] = {0};
	Cursor cursor;
	Pixmap blank;
	XColor dummy;

	blank = XCreateBitmapFromData(xvar->display, win->window, data, 1, 1);
	cursor = XCreatePixmapCursor(xvar->display, blank, blank, &dummy, &dummy, 0, 0);
	XDefineCursor(xvar->display, win->window, cursor);
	XFreePixmap(xvar->display, blank);
	XFreeCursor(xvar->display, cursor);
}

int		mlx_mouse_show(t_xvar *xvar, t_win_list *win)
{
	XUndefineCursor(xvar->display, win->window);
}

/*
** xvar == mlx_ptr, *win = *win_ptr
** root_x and root_y represents the cursor's absolute position.
** win_x and win_y represents the cursor's position relative to the window.
*/
int		mlx_mouse_get_pos(t_xvar *xvar, t_win_list *win, int *win_x, int *win_y)
{
	Window	window_returned;	//	required by XQueryPointer but useless for our use
	int		mask_returned; 		//	required by XQueryPointer but useless for our use
	int		root_x;
	int		root_y;

	return (XQueryPointer(xvar->display, win->window, &window_returned, &window_returned, &root_x, &root_y, win_x, win_y, &mask_returned));
}

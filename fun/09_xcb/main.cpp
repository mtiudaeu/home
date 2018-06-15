#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include <xcb/xcb.h>

/* Circle collision source
https://gamedevelopment.tutsplus.com/tutorials/when-worlds-collide-simulating-circle-circle-collisions--gamedev-769
https://stackoverflow.com/questions/1736734/circle-circle-collision
(x2-x1)^2 + (y1-y2)^2 <= (r1+r2)^2
*/
void main_loop( xcb_connection_t *connection,
		xcb_drawable_t  window,
		xcb_gcontext_t  foreground
	      ) {

	/* draw figure */
	const int16_t  arcs_x = 10;
	const int16_t  arcs_y = 100;
	const uint16_t arcs_width = 5;
	const uint16_t arcs_height = 5;
	const int16_t  arcs_angle1 = 0;
	const int16_t  arcs_angle2 = 360 << 6;
	xcb_arc_t            arcs[] = {
		{	arcs_x,
			arcs_y,
			arcs_width,
			arcs_height,
			arcs_angle1,
			arcs_angle2}};
	/* draw primitives */
	xcb_generic_event_t *event;
	while ((event = xcb_wait_for_event (connection))) {
		switch (event->response_type & ~0x80) {
			case XCB_EXPOSE:
			{
				//TODO rand() things done as an example.
				// It showed there is no redraw. should trigger redraw events.
				const int tmp = rand() % 100;
				printf("%d\n", tmp);
				/* draw the arcs */
				xcb_poly_arc (connection, window, foreground, 1, arcs);
				/* flush the request */
				xcb_flush (connection);

			}
				break;
			default: 
				/* Unknown event type, ignore it */
				break;
		}

		free (event);
	}

}
void main_init(
	xcb_connection_t **connection, //output
	xcb_drawable_t  *window, //output
	xcb_gcontext_t  *foreground) { //output

//FIXME This function has been mostly copy-pasted and not validated.
	assert(connection);
	assert(window);
	assert(foreground);

	/* Open the connection to the X server */
	*connection = xcb_connect (NULL, NULL);

	/* Get the first screen */
	xcb_screen_t *screen = xcb_setup_roots_iterator (xcb_get_setup (*connection)).data;

	/* Create black (foreground) graphic context */
	*window     = screen->root;
	*foreground = xcb_generate_id (*connection);
	uint32_t        mask       = XCB_GC_FOREGROUND | XCB_GC_GRAPHICS_EXPOSURES;
	uint32_t        values[2]  = {screen->black_pixel, 0};

	xcb_create_gc (*connection, *foreground, *window, mask, values);


	/* Create a window */
	*window = xcb_generate_id (*connection);

	mask = XCB_CW_BACK_PIXEL | XCB_CW_EVENT_MASK;
	values[0] = screen->white_pixel;
	values[1] = XCB_EVENT_MASK_EXPOSURE;

	xcb_create_window (*connection,                    /* connection          */
			XCB_COPY_FROM_PARENT,          /* depth               */
			*window,                        /* window Id           */
			screen->root,                  /* parent window       */
			0, 0,                          /* x, y                */
			150, 150,                      /* width, height       */
			10,                            /* border_width        */
			XCB_WINDOW_CLASS_INPUT_OUTPUT, /* class               */
			screen->root_visual,           /* visual              */
			mask, values );                /* masks */

	/* Map the window on the screen and flush*/
	xcb_map_window (*connection, *window);
	xcb_flush (*connection);
}

int main ()
{
	xcb_connection_t *connection;
	xcb_drawable_t  window;
	xcb_gcontext_t  foreground;

	main_init(&connection, &window, &foreground);
	main_loop(connection, window, foreground);

	return 0;
}

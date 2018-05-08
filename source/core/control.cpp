#include "control.h"

Control::Control() {
	Location = { 0, 0 };
	Size = { 0, 0 };

	BackgroundColor = COLOR_WHITE;
	Visible = true;
}

Control::Control(Point_t location, Size_t size, u32 bgColor) {
	Location = location;
	Size = size;

	BackgroundColor = bgColor;
	Visible = true;
}

Control::Control(u32 x, u32 y, u32 width, u32 height, u32 bgColor)
	: Control(Point_t{ x, y }, Size_t{ width, height }, bgColor) { }

void Control::Draw() {
	if (Visible) {
		pp2d_draw_rectangle(Location.X, Location.Y, Size.Width, Size.Height, BackgroundColor);
	}
}
#pragma once

struct _box
{
	int x, y, w, h;
	_box() = default;
	_box(const int x, const int y, const int w, const int h)
	{
		this->x = x;
		this->y = y;
		this->w = w;
		this->h = h;
	}
};
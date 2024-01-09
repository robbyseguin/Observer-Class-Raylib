#include "HitBox.h"

#include <cmath>

// Size of rects drawn on corners by render_corners()
// Should be an even integer
constexpr int POINT_SIZE = 4;
// Color of rects drawn on corners by render_corners()
constexpr int POINT_R = 0;
constexpr int POINT_G = 255;
constexpr int POINT_B = 0;
constexpr int POINT_A = 255;

HitBox::HitBox(float xOffset, float yOffset, int w, int h)
    : _x{}, _y{}
    , _angle{}
    , _tl{}, _tr{}, _bl{}, _br{}
{
    _xOffset = xOffset;
    _yOffset = yOffset;
    _w = w;
    _h = h;
    _radius = powf(w, 2) + powf(h, 2);
}

// Rotate point around origin by a given angle
void rotatePoint(Vector2* pos, float angle)
{
    const float old_x = pos->x;
    const float old_y = pos->y;
    pos->x = old_x * cosf(angle) - old_y * sinf(angle);
    pos->y = old_x * sinf(angle) + old_y * cosf(angle);
}

// Given new coordinates and angle, update hit box corners
void HitBox::updatePos(float x, float y, float angle) 
{
	// Apply offsets
	_x = x + static_cast<float>(_xOffset);
    _y = y + static_cast<float>(_yOffset);

	// Set angle
	_angle = angle;

	// Calculate center point
	float cx = _x + static_cast<float>(_w) / 2.0f;
	float cy = _y + static_cast<float>(_h) / 2.0f;
	
	// Method for rotating corners:
	// 1. Translate corner relative to center of rectangle (center is the origin)
	// 2. Rotate about the origin
	// 3. Translate back to center of rectangle
	
	// Top Left Corner
	_tl.x = static_cast<float>(-_w)/2;
	_tl.y = static_cast<float>(-_h)/2;
	rotatePoint(&_tl, angle);
	_tl.x += cx;
	_tl.y += cy;

	// Top Right Corner
	_tr.x = static_cast<float>(_w)/2;
	_tr.y = static_cast<float>(-_h)/2;
	rotatePoint(&_tr, angle);
	_tr.x += cx;
	_tr.y += cy;

	// Bottom Left Corner
	_bl.x = static_cast<float>(-_w)/2;
	_bl.y = static_cast<float>(_h)/2;
	rotatePoint(&_bl, angle);
	_bl.x += cx;
	_bl.y += cy;

	// Bottom Right Corner
	_br.x = static_cast<float>(_w)/2;
	_br.y = static_cast<float>(_h)/2;
	rotatePoint(&_br, angle);
	_br.x += cx;
	_br.y += cy;
}

// Debug method to draw corners
void HitBox::renderCorners() const
{
	// Set draw color
	Color c{POINT_R, POINT_G, POINT_B, POINT_A};

	// Create rectangles over each corner
    const Rectangle tl_rect = { _tl.x - POINT_SIZE / 2, _tl.y - POINT_SIZE / 2, POINT_SIZE, POINT_SIZE };
	const Rectangle tr_rect = { _tr.x - POINT_SIZE / 2, _tr.y - POINT_SIZE / 2, POINT_SIZE, POINT_SIZE };
	const Rectangle bl_rect = { _bl.x - POINT_SIZE / 2, _bl.y - POINT_SIZE / 2, POINT_SIZE, POINT_SIZE };
	const Rectangle br_rect = { _br.x - POINT_SIZE / 2, _br.y - POINT_SIZE / 2, POINT_SIZE, POINT_SIZE };
	
	// Draw rectangles
    DrawRectangleRec(tl_rect, c);
    DrawRectangleRec(tr_rect, c);
    DrawRectangleRec(bl_rect, c);
    DrawRectangleRec(br_rect, c);
}

int HitBox::getCenterX() const { return _x + _w/2; }

int HitBox::getCenterY() const { return _y + _h/2; }

float HitBox::getRadius() const { return _radius; }

Vector2 HitBox::getTl() const { return _tl; }

Vector2 HitBox::getTr() const { return _tr; }

Vector2 HitBox::getBl() const { return _bl; }

Vector2 HitBox::getBr() const { return _br; }

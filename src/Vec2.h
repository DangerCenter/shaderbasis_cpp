/*
 * Vec2.h
 *
 *  Created on: 10/10/2014
 *      Author: lucas

 ShaderBasis
 Copyright (C) 2014  lucas

 This program is free software; you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation; either version 2 of the License, or
 (at your option) any later version.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License along
 with this program; if not, write to the Free Software Foundation, Inc.,
 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

#ifndef VEC2_H_
#define VEC2_H_

class Vec2 {
public:
	union{float x; float u;};
	union{float y; float u;};

	Vec2(float _x, float _y)	{x=_x;y=_y;}
	Vec2(float a)	:	Vec2(a,a) {};
	Vec2() 			: 	Vec2(0,0) {};
	virtual ~Vec2();


	Vec2 operator+(const Vec2& b)	{	return Vec2(x+b.x,y+b.y);	}
	Vec2 operator-(const Vec2& b)	{	return Vec2(x-b.x,y-b.y); 	}
	Vec2 operator*(const Vec2& b)	{	return Vec2(x*b.x,y*b.y); 	}
	Vec2 operator/(const Vec2 &b)	{	return Vec2(x/b.x,y/b.y); 	}

	Vec2 operator+(const float &b)	{	return Vec2(x+b,y+b);	 	}
	Vec2 operator-(const float &b)	{	return Vec2(x-b,y-b); 		}
	Vec2 operator*(const float &b)	{	return Vec2(x*b,y*b);		}
	Vec2 operator/(const float &b)	{	return Vec2(x/b,y/b);		}
};

#endif /* VEC2_H_ */

/*
 * Vec3.h
 *
 *  Created on: 10/10/2014
 *      Author: Lucas Teske

    ShaderBasis
    Copyright (C) 2014  Lucas Teske

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

#ifndef VEC3_H_
#define VEC3_H_

class Vec3 {
public:
	union { float x; float r; };
	union { float y; float g; };
	union { float z; float b; };

	Vec2 xy()	{ return Vec2(x,y); }
	Vec2 xz()	{ return Vec2(x,z); }

	Vec2 yx()	{ return Vec2(y,x); }
	Vec2 yz()	{ return Vec2(y,z); }

	Vec2 zx()	{ return Vec2(z,x); }
	Vec2 zy()	{ return Vec2(z,y); }

	Vec2 uv()	{ return Vec2(x,y); }

	Vec3() : Vec3(0.f,0.f,0.f) {}
	Vec3(float a) : Vec3(a,a,a) {}
	Vec3(Vec2 a, float z) : Vec3(a.x,a.y,z) {}
	Vec3(float _x, float _y, float _z) { x=_x;y=_y;z=_z; }

	inline void operator+=(const Vec3 b)	{	x+=b.x;y+=b.y;z+=b.z;		}
	inline void operator-=(const Vec3 b)	{	x-=b.x;y-=b.y;z-=b.z;		}
	inline void operator*=(const Vec3 b)	{	x*=b.x;y*=b.y;z*=b.z;		}
	inline void operator/=(const Vec3 b)	{	x/=b.x;y/=b.y;z/=b.z;		}

	inline void operator+=(const float b)	{	x+=b;y+=b;z+=b;				}
	inline void operator-=(const float b)	{	x-=b;y-=b;z-=b;				}
	inline void operator*=(const float b)	{	x*=b;y*=b;z*=b;				}
	inline void operator/=(const float b)	{	x/=b;y/=b;z/=b;				}


	inline Vec3 operator+(const Vec3 b)	{	return Vec3(x+b.x,y+b.y,z+b.z); }
	inline Vec3 operator-(const Vec3 b)	{	return Vec3(x-b.x,y-b.y,z-b.z); }
	inline Vec3 operator*(const Vec3 b)	{	return Vec3(x*b.x,y*b.y,z*b.z); }
	inline Vec3 operator/(const Vec3 b)	{	return Vec3(x/b.x,y/b.y,z/b.z); }

	inline Vec3 operator+(const float b)	{	return Vec3(x+b,y+b,z+b); 		}
	inline Vec3 operator-(const float b)	{	return Vec3(x-b,y-b,z-b); 		}
	inline Vec3 operator*(const float b)	{	return Vec3(x*b,y*b,z*b);		}
	inline Vec3 operator/(const float b)	{	return Vec3(x/b,y/b,z/b);		}
};

#endif /* VEC3_H_ */

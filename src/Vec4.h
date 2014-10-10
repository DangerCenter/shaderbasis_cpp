/*
 * Vec4.h
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

#ifndef VEC4_H_
#define VEC4_H_

class Vec4 {
public:
	union { float x; float r; };
	union { float y; float g; };
	union { float z; float b; };
	union { float w; float a; };


	Vec2 xy()	{ return Vec2(x,y);   }
	Vec2 xz()	{ return Vec2(x,z);   }
	Vec2 xa()	{ return Vec2(x,a);   }

	Vec2 yx()	{ return Vec2(y,x);   }
	Vec2 yz()	{ return Vec2(y,z);   }
	Vec2 ya()	{ return Vec2(y,a);   }

	Vec2 zx()	{ return Vec2(z,x);   }
	Vec2 zy()	{ return Vec2(z,y);   }
	Vec2 za()	{ return Vec2(z,a);   }

	Vec2 ax()	{ return Vec2(a,x);   }
	Vec2 ay()	{ return Vec2(a,y);   }
	Vec2 az()	{ return Vec2(a,z);   }

	Vec3 xyz()	{ return Vec3(x,y,z); }
	Vec3 rgb()	{ return Vec3(x,y,z); }

	Vec4(float _x, float _y, float _z, float _w)	{	x=_x;y=_y;z=_z;w=_w; }
	Vec4(float a) : Vec4(a,a,a,a) {};
	Vec4(Vec3 a, float w) : Vec4(a.x,a.y,a.z,w) {};

	Vec4() : Vec4(0,0,0,0) {};


	inline void operator+=(const Vec4 b)	{	x+=b.x;y+=b.y;z+=b.z;w+=b.w;			}
	inline void operator-=(const Vec4 b)	{	x-=b.x;y-=b.y;z-=b.z;w-=b.w;			}
	inline void operator*=(const Vec4 b)	{	x*=b.x;y*=b.y;z*=b.z;w*=b.w;			}
	inline void operator/=(const Vec4 b)	{	x/=b.x;y/=b.y;z/=b.z;w/=b.w;			}

	inline void operator+=(const float b)	{	x+=b;y+=b;z+=b;w+=b;					}
	inline void operator-=(const float b)	{	x-=b;y-=b;z-=b;w-=b;					}
	inline void operator*=(const float b)	{	x*=b;y*=b;z*=b;w*=b;					}
	inline void operator/=(const float b)	{	x/=b;y/=b;z/=b;w/=b;					}


	inline Vec4 operator+(const Vec4 b)	{	return Vec4(x+b.x,y+b.y,z+b.z,w+b.w); 	}
	inline Vec4 operator-(const Vec4 b)	{	return Vec4(x-b.x,y-b.y,z-b.z,w-b.w); 	}
	inline Vec4 operator*(const Vec4 b)	{	return Vec4(x*b.x,y*b.y,z*b.z,w*b.w); 	}
	inline Vec4 operator/(const Vec4 b)	{	return Vec4(x/b.x,y/b.y,z/b.z,w/b.w); 	}


	inline Vec4 operator+(const float b)	{	return Vec4(x+b,y+b,z+b,w+b); 			}
	inline Vec4 operator-(const float b)	{	return Vec4(x-b,y-b,z-b,w-b); 			}
	inline Vec4 operator*(const float b)	{	return Vec4(x*b,y*b,z*b,w*b);			}
	inline Vec4 operator/(const float b)	{	return Vec4(x/b,y/b,z/b,w/b);			}
};

#endif /* VEC4_H_ */

/*
 * ShaderFunctions.h
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

#ifndef SHADERFUNCTIONS_H_
#define SHADERFUNCTIONS_H_

#include <math.h>

//	Dot Product Functions
static float dot(Vec4 &a, Vec4 &b)			{	return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;	}
static float dot(Vec3 &a, Vec3 &b)			{	return a.x * b.x + a.y * b.y + a.z;						}
static float dot(Vec2 &a, Vec2 &b)			{	return a.x * b.x + a.y;									}

//	Cross Product Functions
static Vec3 cross(Vec3 &a, Vec3 &b)			{	return Vec3(a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x);	}

//	Mix Functions
static float mix(float x, float y, float a)	{	return x * (1.f-a) + y * a; 													}
static Vec4	 mix(Vec4 &a, Vec4 &b, float k)	{	return Vec4(mix(a.x,b.x,k), mix(a.y,b.y,k), mix(a.z,b.z,k), mix(a.w,b.w,k)); 	}
static Vec3	 mix(Vec3 &a, Vec3 &b, float k)	{	return Vec3(mix(a.x,b.x,k), mix(a.y,b.y,k), mix(a.z,b.z,k)); 					}
static Vec2	 mix(Vec2 &a, Vec2 &b, float k)	{	return Vec2(mix(a.x,b.x,k), mix(a.y,b.y,k)); 									}

static Vec4	 mix(Vec4 &a, float b, float k)	{	return Vec4(mix(a.x,b,k), mix(a.y,b,k), mix(a.z,b,k), mix(a.w,b,k)); 			}
static Vec3	 mix(Vec3 &a, float b, float k)	{	return Vec3(mix(a.x,b,k), mix(a.y,b,k), mix(a.z,b,k)); 							}
static Vec2	 mix(Vec2 &a, float b, float k)	{	return Vec2(mix(a.x,b,k), mix(a.y,b,k)); 										}


//	Clamp
static float clamp(float a, float b)		{	return a<b?a:b;	}

//	Length
static float length(Vec4 &a)				{	return sqrt(a.x*a.x+a.y*a.y+a.z*a.z+a.w*a.w); 	}
static float length(Vec3 &a)				{	return sqrt(a.x*a.x+a.y*a.y+a.z*a.z); 			}
static float length(Vec2 &a)				{	return sqrt(a.x*a.x+a.y*a.y); 					}

//	Distance
static float distance(Vec4 &a, Vec4 &b)		{	Vec4 c = a-b; return length(c);					}
static float distance(Vec3 &a, Vec3 &b)		{	Vec3 c = a-b; return length(c);					}
static float distance(Vec2 &a, Vec2 &b)		{	Vec2 c = a-b; return length(c);					}

//	Normalize
static Vec4  normalize(Vec4 &a)				{	return a / length(a);							}
static Vec3  normalize(Vec3 &a)				{	return a / length(a);							}
static Vec2  normalize(Vec2 &a)				{	return a / length(a);							}

//	Reflect
static Vec4  reflect(Vec4 &a, Vec4 &b)		{	return a - 2.f * dot(b, a) * b; 				}
static Vec3  reflect(Vec3 &a, Vec3 &b)		{	return a - 2.f * dot(b, a) * b; 				}
static Vec2  reflect(Vec2 &a, Vec2 &b)		{	return a - 2.f * dot(b, a) * b; 				}

#endif /* SHADERFUNCTIONS_H_ */

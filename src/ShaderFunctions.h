/*
 * ShaderFunctions.h
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

#ifndef SHADERFUNCTIONS_H_
#define SHADERFUNCTIONS_H_

#include <cmath>

//	Dot Product Functions
static inline float dot(Vec4 a, Vec4 b)			{	return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;	}
static inline float dot(Vec3 a, Vec3 b)			{	return a.x * b.x + a.y * b.y + a.z;						}
static inline float dot(Vec2 a, Vec2 b)			{	return a.x * b.x + a.y;									}

//	Cross Product Functions
static inline Vec3 cross(Vec3 a, Vec3 b)			{	return Vec3(a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x);	}

//	Mix Functions
static inline float mix(float x, float y, float a)	{	return x * (1.f-a) + y * a; 													}
static inline Vec4	 mix(Vec4 a, Vec4 b, float k)	{	return Vec4(mix(a.x,b.x,k), mix(a.y,b.y,k), mix(a.z,b.z,k), mix(a.w,b.w,k)); 	}
static inline Vec3	 mix(Vec3 a, Vec3 b, float k)	{	return Vec3(mix(a.x,b.x,k), mix(a.y,b.y,k), mix(a.z,b.z,k)); 					}
static inline Vec2	 mix(Vec2 a, Vec2 b, float k)	{	return Vec2(mix(a.x,b.x,k), mix(a.y,b.y,k)); 									}

static inline Vec4	 mix(Vec4 a, float b, float k)	{	return Vec4(mix(a.x,b,k), mix(a.y,b,k), mix(a.z,b,k), mix(a.w,b,k)); 			}
static inline Vec3	 mix(Vec3 a, float b, float k)	{	return Vec3(mix(a.x,b,k), mix(a.y,b,k), mix(a.z,b,k)); 							}
static inline Vec2	 mix(Vec2 a, float b, float k)	{	return Vec2(mix(a.x,b,k), mix(a.y,b,k)); 										}


//	Clamp
static inline float clamp(float a, float b)		{	return a<b?a:b;	}
static inline void  clamp(Vec4 &v, float a)		{	v.x = clamp(v.x,a); v.y = clamp(v.y,a); v.z = clamp(v.z,a); v.w = clamp(v.w,a); }
static inline void  clamp(Vec3 &v, float a)		{	v.x = clamp(v.x,a); v.y = clamp(v.y,a); v.z = clamp(v.z,a); 					}
static inline void  clamp(Vec2 &v, float a)		{	v.x = clamp(v.x,a); v.y = clamp(v.y,a);						 					}

//	Length
static inline float length(Vec4 &a)				{	return sqrt(dot(a,a)); 					}
static inline float length(Vec3 &a)				{	return sqrt(dot(a,a)); 					}
static inline float length(Vec2 &a)				{	return sqrt(dot(a,a)); 					}

//	Distance
static inline float distance(Vec4 a, Vec4 b)		{	Vec4 c = a-b; return length(c);					}
static inline float distance(Vec3 a, Vec3 b)		{	Vec3 c = a-b; return length(c);					}
static inline float distance(Vec2 a, Vec2 b)		{	Vec2 c = a-b; return length(c);					}

//	Normalize
static inline Vec4  normalize(Vec4 a)				{	return a / length(a);							}
static inline Vec3  normalize(Vec3 a)				{	return a / length(a);							}
static inline Vec2  normalize(Vec2 a)				{	return a / length(a);							}

//	Reflect
static inline Vec4  reflect(Vec4 a, Vec4 b)		{	return a - b * 2.f * dot(b, a); 				}
static inline Vec3  reflect(Vec3 a, Vec3 b)		{	return a - b * 2.f * dot(b, a); 				}
static inline Vec2  reflect(Vec2 a, Vec2 b)		{	return a - b * 2.f * dot(b, a); 				}


//	Modulus
static inline float mod(float x, float y)			{	return x - y * floor(x/y);											}
static inline Vec4 mod(Vec4 a, float y)			{	return Vec4(mod(a.x,y),mod(a.y,y),mod(a.z,y),mod(a.w,y));			}
static inline Vec4 mod(Vec4 a, Vec4 &b)			{	return Vec4(mod(a.x,b.x),mod(a.y,b.y),mod(a.z,b.z),mod(a.w,b.w));	}

static inline Vec3 mod(Vec3 a, float y)			{	return Vec3(mod(a.x,y),mod(a.y,y),mod(a.z,y));						}
static inline Vec3 mod(Vec3 a, Vec3 b)			{	return Vec3(mod(a.x,b.x),mod(a.y,b.y),mod(a.z,b.z));				}

static inline Vec2 mod(Vec2 a, float y)			{	return Vec2(mod(a.x,y),mod(a.y,y));									}
static inline Vec2 mod(Vec2 a, Vec2 b)			{	return Vec2(mod(a.x,b.x),mod(a.y,b.y));								}

//	New Math
static inline Vec4 abs(Vec4 a)					{	return Vec4(abs(a.x),abs(a.y),abs(a.z),abs(a.w));					}
static inline Vec3 abs(Vec3 a)					{	return Vec3(abs(a.x),abs(a.y),abs(a.z));							}
static inline Vec2 abs(Vec2 a)					{	return Vec2(abs(a.x),abs(a.y));										}

#endif /* SHADERFUNCTIONS_H_ */

/*
 * ShaderThreadArgs.h
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

#ifndef SHADERTHREADARGS_H_
#define SHADERTHREADARGS_H_

#include "ShaderVal.h"
#include <map>
using namespace std;

class ShaderThreadArgs {
public:
  Uint32 *pixels;
  int startLine; 
  int endLine; 
  int width; 
  int height; 
  map<string, ShaderVal> *ext;
};

#endif /* SHADERTHREADARGS_H_ */
/*
    This file is a part of SORT(Simple Open Ray Tracing), an open-source cross
    platform physically based renderer.
 
    Copyright (c) 2011-2019 by Cao Jiayin - All rights reserved.
 
    SORT is a free software written for educational purpose. Anyone can distribute
    or modify it under the the terms of the GNU General Public License Version 3 as
    published by the Free Software Foundation. However, there is NO warranty that
    all components are functional in a perfect manner. Without even the implied
    warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
    General Public License for more details.
 
    You should have received a copy of the GNU General Public License along with
    this program. If not, see <http://www.gnu.org/licenses/gpl-3.0.html>.
 */

#pragma once

#include <memory>
#include <vector>
#include "core/define.h"
#include "core/rand.h"
#include "core/define.h"

// Light Sample
class	LightSample
{
// public field
public:
	// the sample parameters
	float		t;		// 1d sample data
	
	float		u , v;	// 2d sample data
	float		reserved;	// for memory alignment

	// default constructor
	LightSample(bool auto_generate=false)
	{
		if( auto_generate )
		{
			t = sort_canonical();
			u = sort_canonical();
			v = sort_canonical();
		}else
		{
			t = 0.0f;
			v = 0.0f;
			u = 0.0f;
		}
	}
};

// Bsdf Sample
class	BsdfSample
{
// public field
public:
	float	t;		// a canonical number to select bxdf from bsdf
	float	u , v;	// 2d sample data

	float	preserved;	// a preserved data for memory alignment

	// default constructor
	BsdfSample(bool auto_generate=false)
	{
		if( auto_generate )
		{
			t = sort_canonical();
			u = sort_canonical();
			v = sort_canonical();
		}else
		{
			t = 0.0f;
			v = 0.0f;
			u = 0.0f;
		}
	}
};

// light sample offset
class SampleOffset
{
public:
	unsigned num;	// the number of sample
	unsigned offset;// the offset of the samples
};

// sample defination
class PixelSample
{
// public field
public:
    float					        img_u = 0.0f;
    float                           img_v = 0.0f;	// the range of the float2 should be (0,0) <-> (1,1)
	float					        dof_u , dof_v;	// the range of the float2 should be (-1,-1) <-> (1,1)
	std::unique_ptr<LightSample[]>  light_sample = nullptr;
	std::unique_ptr<BsdfSample[]>   bsdf_sample = nullptr;
	std::vector<unsigned>	        light_dimension;
	std::vector<unsigned>	        bsdf_dimension;
	std::unique_ptr<float[]>        data;		// the data to used

	// request more samples
	unsigned RequestMoreLightSample( unsigned num )
	{
		unsigned offset = (unsigned)light_dimension.size();
		light_dimension.push_back( num );
		return offset;
	}
	unsigned RequestMoreBsdfSample( unsigned num )
	{
		unsigned offset = (unsigned)bsdf_dimension.size();
		bsdf_dimension.push_back( num );
		return offset;
	}
};
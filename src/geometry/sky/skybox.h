/*
   FileName:      skybox.h

   Created Time:  2011-08-04 12:51:48

   Auther:        Cao Jiayin

   Email:         soraytrace@hotmail.com

   Location:      China, Shanghai

   Description:   SORT is short for Simple Open-source Ray Tracing. Anyone could checkout the source code from
                'sourceforge', https://soraytrace.svn.sourceforge.net/svnroot/soraytrace. And anyone is free to
                modify or publish the source code. It's cross platform. You could compile the source code in 
                linux and windows , g++ or visual studio 2008 is required.
*/

#ifndef	SORT_SKYBOX
#define	SORT_SKYBOX

// include the headers
#include "sky.h"
#include "texture/imagetexture.h"

///////////////////////////////////////////////////////////////////
//	definition of skybox
class	SkyBox : public Sky
{
// public method
public:
	// default constructor
	SkyBox();
	// destructor
	~SkyBox(){}

	// evaluate value from sky
	// para 'r' : the ray which misses all of the triangle in the scene
	// result   : the spectrum in the sky
	virtual Spectrum Evaluate( const Ray& r ) const;

// private field
private:
	// the image textures
	ImageTexture	m_up;
	ImageTexture	m_down;
	ImageTexture	m_front;
	ImageTexture	m_back;
	ImageTexture	m_left;
	ImageTexture	m_right;

	// register property
	void _registerAllProperty();

// property handler
	class UpProperty : public PropertyHandler<Sky>
	{
	public:
		// constructor
		UpProperty(Sky* sky):PropertyHandler(sky){}

		// set value
		void SetValue( const string& str )
		{
			SkyBox* sky = dynamic_cast<SkyBox*>(m_target);
			sky->m_up.LoadImageFromFile( str );
		}
	};
	class DownProperty : public PropertyHandler<Sky>
	{
	public:
		// constructor
		DownProperty(Sky* sky):PropertyHandler(sky){}

		// set value
		void SetValue( const string& str )
		{
			SkyBox* sky = dynamic_cast<SkyBox*>(m_target);
			sky->m_down.LoadImageFromFile( str );
		}
	};
	class FrontProperty : public PropertyHandler<Sky>
	{
	public:
		// constructor
		FrontProperty(Sky* sky):PropertyHandler(sky){}

		// set value
		void SetValue( const string& str )
		{
			SkyBox* sky = dynamic_cast<SkyBox*>(m_target);
			sky->m_front.LoadImageFromFile( str );
		}
	};
	class BackProperty : public PropertyHandler<Sky>
	{
	public:
		// constructor
		BackProperty(Sky* sky):PropertyHandler(sky){}

		// set value
		void SetValue( const string& str )
		{
			SkyBox* sky = dynamic_cast<SkyBox*>(m_target);
			sky->m_back.LoadImageFromFile( str );
		}
	};
	class LeftProperty : public PropertyHandler<Sky>
	{
	public:
		// constructor
		LeftProperty(Sky* sky):PropertyHandler(sky){}

		// set value
		void SetValue( const string& str )
		{
			SkyBox* sky = dynamic_cast<SkyBox*>(m_target);
			sky->m_left.LoadImageFromFile( str );
		}
	};
	class RightProperty : public PropertyHandler<Sky>
	{
	public:
		// constructor
		RightProperty(Sky* sky):PropertyHandler(sky){}

		// set value
		void SetValue( const string& str )
		{
			SkyBox* sky = dynamic_cast<SkyBox*>(m_target);
			sky->m_right.LoadImageFromFile( str );
		}
	};
};

#endif
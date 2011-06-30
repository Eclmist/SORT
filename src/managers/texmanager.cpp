/*
 * filename :	texmanager.cpp
 *
 * programmer :	Cao Jiayin
 */

// include header file
#include "texmanager.h"
#include "texio/texio.h"
#include "texio/bmpio.h"
#include "texture/imagetexture.h"
#include "utility/strhelper.h"

// instance the singleton with tex manager
DEFINE_SINGLETON(TexManager);

// create tex manager
void TexManager::CreateTexManager()
{
	new TexManager();
}

// destructor
TexManager::~TexManager()
{
	_release();
}

// default constructor
TexManager::TexManager()
{
	_init();
}

// initialize data
void TexManager::_init()
{
	// push the texture outputer
	m_TexIOVec.push_back( new BmpIO() );
}

// release data
void TexManager::_release()
{
	// release texture outputer
	vector<TexIO*>::const_iterator tex_it = m_TexIOVec.begin();
	while( tex_it != m_TexIOVec.end() )
	{
		delete *tex_it;
		tex_it++;
	}
	m_TexIOVec.clear();

	map< std::string , ImgMemory* >::iterator img_it = m_ImgContainer.begin();
	while( img_it != m_ImgContainer.end() )
	{
		if( img_it->second->reference > 0 )
		{
			string isare = (img_it->second->reference>1)?"is":"are";
			string refer = (img_it->second->reference>1)?" reference":" references";
			LOG_ERROR<<"There "<<isare<<" still "<<(int)(img_it->second->reference)<<refer<<" pointing to \""<<img_it->first<<"\"."<<CRASH;
		}
		SAFE_DELETE_ARRAY( img_it->second->m_ImgMem );
		img_it->second->m_iWidth = 0;
		img_it->second->m_iHeight = 0;

		// delete the memory
		delete img_it->second;

		img_it++;
	}
	m_ImgContainer.clear();
}

// output texture
bool TexManager::Write( const string& str , const Texture* tex )
{
	// get the type
	TEX_TYPE type = TexTypeFromStr( str );

	// find the specific texio first
	TexIO* io = FindTexIO( type );

	if( io != 0 )
		io->Write( str , tex );
	
	return true;
}

// load the image from file , if the specific image is already existed in the current system , just return the pointer
bool TexManager::Read( const string& str , ImageTexture* tex )
{
	// get the type
	TEX_TYPE type = TexTypeFromStr( str );

	// try to find the image first , if it's already existed in the system , just set a pointer
	map< std::string , ImgMemory* >::iterator it = m_ImgContainer.find( str );
	if( it != m_ImgContainer.end() )
	{
		tex->m_pMemory = it->second;
		tex->m_iTexWidth = it->second->m_iWidth;
		tex->m_iTexHeight = it->second->m_iHeight;

		return true;
	}

	// find the specific texio first
	TexIO* io = FindTexIO( type );

	bool read = false;
	if( io != 0 )
	{
		// create a new memory
		ImgMemory* mem = new ImgMemory();

		// read the data
		bool read = io->Read( str , mem );

		if( read )
		{
			// set the texture
			tex->m_pMemory = mem;
			tex->m_iTexWidth = mem->m_iWidth;
			tex->m_iTexHeight = mem->m_iHeight;
			
			// insert it into the container
			m_ImgContainer.insert( make_pair( str , mem ) );
		}else
		{
			LOG_WARNING<<"Can't load image file \""<<str<<"\"."<<ENDL;
			delete mem;
		}
	}

	return read;
}

// find correct texio
TexIO* TexManager::FindTexIO( TEX_TYPE tt ) const
{
	// find the specific texio first
	TexIO* io = 0;
	vector<TexIO*>::const_iterator it = m_TexIOVec.begin();
	while( it != m_TexIOVec.end() )
	{
		if( (*it)->GetTT() == tt )
		{
			io = *it;
			break;
		}
		it++;
	}

	return io;
}

// get the reference count
unsigned TexManager::GetReferenceCount( const string& str ) const
{
	// try to find the image first , if it's already existed in the system , just set a pointer
	map< std::string , ImgMemory* >::const_iterator it = m_ImgContainer.find( str );
	if( it != m_ImgContainer.end() )
	{
		return it->second->reference;
	}

	return 0;
}

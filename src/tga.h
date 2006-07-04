#ifndef __TGA_H__
#define __TGA_H__

#pragma comment(lib, "OpenGL32.lib")
#ifdef WIN32
#include <windows.h> //I think this was only needed because gl.h uses it
#endif
#include <GL/gl.h>
#include <cstdio>
#include <string>
#include "texture.h"

namespace OpenArena{
	/*!
	 * \brief
	 * Write brief comment for TGAHeader here.
	 * 
	 * Write detailed description for TGAHeader here.
	 * 
	 * \remarks
	 * Write remarks for TGAHeader here.
	 * 
	 * \see
	 * Separate items with the '|' character.
	 */
	struct TGAHeader
	{
		GLubyte Header[12];			// File Header To Determine File Type
	};

	/*!
	 * \brief
	 * Write brief comment for TGA here.
	 * 
	 * Write detailed description for TGA here.
	 * 
	 * \remarks
	 * Write remarks for TGA here.
	 * 
	 * \see
	 * Separate items with the '|' character.
	 */
	struct TGA
	{
		GLubyte header[6];			// Holds The First 6 Useful Bytes Of The File
		GLuint bytesPerPixel;		// Number Of BYTES Per Pixel (3 Or 4)
		GLuint imageSize;			// Amount Of Memory Needed To Hold The Image
		GLuint type;				// The Type Of Image, GL_RGB Or GL_RGBA
		GLuint Height;				// Height Of Image					
		GLuint Width;				// Width Of Image				
		GLuint Bpp;					// Number Of BITS Per Pixel (24 Or 32)
	};

	/*!
	 * \brief
	 * Write brief comment for LoadTGA here.
	 * 
	 * \param filename
	 * Description of parameter filename.
	 * 
	 * \returns
	 * Write description of return value here.
	 * 
	 * \throws <exception class>
	 * Description of criteria for throwing this exception.
	 * 
	 * Write detailed description for LoadTGA here.
	 * 
	 * \remarks
	 * Write remarks for LoadTGA here.
	 * 
	 * \see
	 * Separate items with the '|' character.
	 */
	TextureImage* LoadTGA(const char *filename);

	const GLubyte uTGAcompare[12] = {0,0,2, 0,0,0,0,0,0,0,0,0};	// Uncompressed TGA Header
	const GLubyte cTGAcompare[12] = {0,0,10,0,0,0,0,0,0,0,0,0};	// Compressed TGA Header
	TextureImage* LoadUncompressedTGA(FILE *);	// Load an Uncompressed file
	TextureImage* LoadCompressedTGA(FILE *);		// Load a Compressed file
};
#endif

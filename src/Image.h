
//Author: Gordon Griesel

//Modified by: Nickolas Larson

#ifndef IMAGE_H
#define IMAGE_H

#include "glad/glad.h"
#include <GL/gl.h>
//#include <GL/glu.h>



class Image {
	public:
		int width, height;
		unsigned char *data;
		Image() {}
		~Image();
		Image(const char *fname);
		void GenerateGLTexture(GLuint & texture);
		static void GenerateGLTextureALPHA(GLuint & texture, const char * img);

		
};



#endif
#ifndef IMAGE_CPP
#define IMAGE_CPP

#define STB_IMAGE_IMPLEMENTATION

#include "Image.h"
#include <cstring>
#include <stdio.h>
#include <unistd.h>
#include <cstdlib>
#include <iostream>
#include "stb_image.h"

Image::~Image() { delete [] data; }
Image::Image(const char *fname) {
    if (fname[0] == '\0')
        return;
    int ppmFlag = 0;
    char name[40];
    strcpy(name, fname);
    int slen = strlen(name);
    char ppmname[80];
    if (strncmp(name+(slen-4), ".ppm", 4) == 0)
        ppmFlag = 1;
    if (ppmFlag) {
        strcpy(ppmname, name);
    } else {
        name[slen-4] = '\0';
        sprintf(ppmname,"%s.ppm", name);
        char ts[100];
        sprintf(ts, "convert %s %s", fname, ppmname);
        system(ts);
    }

    FILE *fpi = fopen(ppmname, "r");
    if (fpi) {
        char line[200];
        fgets(line, 200, fpi);
        fgets(line, 200, fpi);
        //skip comments and blank lines
        while (line[0] == '#' || strlen(line) < 2)
            fgets(line, 200, fpi);
        sscanf(line, "%i %i", &width, &height);
        fgets(line, 200, fpi);
        //get pixel data
        int n = width * height * 3;
        data = new unsigned char[n];

        for (int i=0; i<n; i++){
            data[i] = fgetc(fpi);
        }
        fclose(fpi);
    } else {
        printf("ERROR opening image: %s\n",ppmname);
        exit(0);
    }
    if (!ppmFlag)
        unlink(ppmname);

}


void Image::GenerateGLTexture(GLuint & texture)
{
    
    glGenTextures( 1, &texture);
    glBindTexture( GL_TEXTURE_2D, texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_LINEAR);

    glTexImage2D( GL_TEXTURE_2D, 0, 3, this->width, this->height, 0, GL_RGB,
                    GL_UNSIGNED_BYTE, this->data);
    glBindTexture( GL_TEXTURE_2D, 0);
}
void Image::GenerateGLTextureALPHA(GLuint & texture, const char * img)
{
    
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    // set the texture wrapping/filtering options (on the currently bound texture object)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // load and generate the texture
    int width, height, nrChannels;
    unsigned char *data = stbi_load( img, &width, &height, &nrChannels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        //glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);
}


#endif
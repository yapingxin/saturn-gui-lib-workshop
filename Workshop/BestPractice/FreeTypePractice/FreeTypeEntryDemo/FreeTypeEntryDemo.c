// FreeTypeEntryDemo.c : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <ft2build.h>
#include FT_FREETYPE_H
#include <freetype/freetype.h>
#include <freetype/ftglyph.h>


const char* FontLibFilePath = "C:\\Pub\\FontLib\\SourceHanSansCN\\SourceHanSansCN-Light.otf";

int main()
{
	unsigned int returnCode = 0;

	FT_Library ft_lib = NULL;
	FT_Face ft_face = NULL;
	FT_Error error = 0;

	//Init FreeType Lib to manage memory
	error = FT_Init_FreeType(&ft_lib);
	if (error)
	{
		returnCode = 0x01;
		printf("There is some error when calling FT_Init_FreeType().");
		goto Free_FT_Lib;
	}

	//create font face from font file
	error = FT_New_Face(ft_lib, FontLibFilePath, 0, &ft_face);
	if (error)
	{
		returnCode = 0x02;
		printf(" Create font face failed.");
		goto Free_FT_Face;
	}

	FT_Set_Char_Size(ft_face, 8 << 6, 8 << 6, 300, 300);
	FT_Glyph glyph;
	FT_ULong charcode = 0x6668; // load glyph -- HZ: Chen
	FT_Load_Glyph(ft_face, FT_Get_Char_Index(ft_face, charcode), FT_LOAD_DEFAULT);
	error = FT_Get_Glyph(ft_face->glyph, &glyph);
	if (error)
	{
		returnCode = 0x03;
		printf(" Create glyph failed.");
		goto Free_glyph;
	}

	// convert glyph to bitmap with 256 gray
	FT_Glyph_To_Bitmap(&glyph, ft_render_mode_normal, 0, 1);
	FT_BitmapGlyph bitmap_glyph = (FT_BitmapGlyph)glyph;
	FT_Bitmap bitmap = bitmap_glyph->bitmap;

	for (unsigned int i = 0; i < bitmap.rows; i++)
	{
		for (unsigned int j = 0; j < bitmap.width; j++)
		{
			printf("%c", bitmap.buffer[i * bitmap.width + j] ? '*' : ' ');
		}
		printf(" \n");
	}

Free_glyph:
	FT_Done_Glyph(glyph);
	glyph = NULL;

Free_FT_Face:
	FT_Done_Face(ft_face);
	ft_face = NULL;

Free_FT_Lib:
	FT_Done_FreeType(ft_lib);
	ft_lib = NULL;

	return returnCode;
}


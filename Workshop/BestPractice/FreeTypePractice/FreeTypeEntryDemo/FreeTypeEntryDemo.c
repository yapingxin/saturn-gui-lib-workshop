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

	FT_Library pFTLib = NULL;
	FT_Face pFTFace = NULL;
	FT_Error error = 0;

	//Init FreeType Lib to manage memory
	error = FT_Init_FreeType(&pFTLib);
	if (error)
	{
		returnCode = 0x01;
		printf("There is some error when calling FT_Init_FreeType().");
		goto Free_FTLib;
	}

	//create font face from font file
	error = FT_New_Face(pFTLib, FontLibFilePath, 0, &pFTFace);
	if (error)
	{
		returnCode = 0x02;
		printf(" Create font face failed.");
		goto Free_FTFace;
	}

	FT_Set_Char_Size(pFTFace, 16 << 6, 16 << 6, 300, 300);
	FT_Glyph glyph;
	FT_ULong charcode = 0x6668; // load glyph -- HZ: Chen
	FT_Load_Glyph(pFTFace, FT_Get_Char_Index(pFTFace, charcode), FT_LOAD_DEFAULT);
	error = FT_Get_Glyph(pFTFace->glyph, &glyph);
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

Free_FTFace:
	FT_Done_Face(pFTFace);
	pFTFace = NULL;

Free_FTLib:
	FT_Done_FreeType(pFTLib);
	pFTLib = NULL;

	return returnCode;
}


/*
 *  Font.cpp
 *  BBE
 *
 *  Created by James Stine on 9/14/10.
 *  Copyright 2010 Blade Brothers. All rights reserved.
 *
 */

#include "graphics/Font.h"

Font::Font() {}

Font::~Font() {}

void Font::OnLoad(const char * filename)
{
	Sprite::OnLoad(filename, font);
}

void Font::setText(const char * t)
{
	text = (char*)malloc(strlen(t));
	memcpy(text, t, strlen(t));
	text[strlen(t)] = '\0';
}

void Font::setPosition(Vector2 p)
{
	position = p;
}

void Font::OnRender(float r, float g, float b, float a)
{
	char letters[94] =
	{
		' ',
		'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z',
		'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z',
		'1','2','3','4','5','6','7','8','9','0',
		'{','}','[',']','(',')','<','>','$','*','-','+','=','/','#','_','%','^','@','\\','&','|','~','?','\'','\"','!',',','.',';',':'
	};

	int textChars[strlen(text)];

	for (uint i = 0; i < strlen(text); i++)
	{
		textChars[i] = -1;
		for (uint c = 0; c < sizeof(letters); c++)
		{
			if ((char)text[i] == (char)letters[c])
			{
				textChars[i] = c;
			}
		}
		if (textChars[i] == 80)
			textChars[i] = 666;
		
		if (textChars[i] == -1)
			textChars[i] = 86;
	}

	Vector2 newPosition = position;
	
	SDL_Rect rect;
	rect.w = 7;
	rect.h = 12;
	
	glColor4f(r, g, b, a);
	
	int index = 0;
	for (uint i = 0; i < strlen(text); i++)
	{
		if (textChars[i] == 666)
		{
			int type = textChars[i + 1];
			int value = textChars[i + 2];
			switch (type)
			{
				// C c
				case 3:
				case 29:
					switch (value) 
					{
						case 62: // 0 white
							glColor4f(1.0f, 1.0f, 1.0f, a);
							break;
						case 53: // 1 red
							glColor4f(1.0f, 0.0f, 0.0f, a);
							break;
						case 54: // 2 orange
							glColor4f(1.0f, 0.5f, 0.0f, a);
							break;
						case 55: // 3 yellow
							glColor4f(1.0f, 1.0f, 0.0f, a);
							break;
						case 56: // 4 green
							glColor4f(0.0f, 1.0f, 0.0f, a);
							break;
						case 57: // 5 light blue
							glColor4f(0.0f, 0.7f, 1.0f, a);
							break;
						case 58: // 6 darker blue
							glColor4f(0.0f, 0.0f, 1.0f, a);
							break;
						case 59: // 7 purple
							glColor4f(0.5f, 0.0f, 1.0f, a);
							break;
						case 60: // 8 light gray
							glColor4f(0.6f, 0.6f, 0.6f, a);
							break;
						case 61: // 9 dark gray
							glColor4f(0.3f, 0.3f, 0.3f, a);
							break;
					}
					i += 2;
					break;
					
				// n
				case 14:
				case 40:
					newPosition.x = position.x;
					newPosition.y += 12;
					i++;
					break;
				
				// ^ (control character)
				case 666:
					textChars[i + 1] = 79;
					break;
			}			
		}
		else 
		{
			rect.x = textChars[i] * 7;
			rect.y = 0;
			newPosition.x += 7;
			
			Sprite::OnDraw(font, newPosition, rect);
			
			index++;
		}
	}
	
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
}

void Font::OnCleanup()
{
	glDeleteTextures(1, &font.texture);
}

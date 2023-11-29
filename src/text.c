/*
 *
 */

#include "glbdf.h"

//* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= */
// Static
static void draw_point( int x, int y )
{
   glPointSize( 1.0 );
   glBegin( GL_POINTS );
      glVertex2i( x, y + 1 - BITMAP_HEIGHT );
   glEnd();
}

void DrawText( int x, int y, const char *text, unsigned int foreground )
{
   unsigned int codepoint;
   int bytes;
   unsigned char ch;
   int i;

   y += BITMAP_HEIGHT;

   while( *text != '\0' )
   {
      bytes = 0;
      ch = ( unsigned char )( *text++ );
      if( ch <= 0x7F )
      {
         codepoint = ch;
         bytes = 1;
      }
      else if( ch <= 0xDF )
      {
         codepoint = ch & 0x1F;
         bytes = 2;
      }
      else if( ch <= 0xEF )
      {
         codepoint = ch & 0x0F;
         bytes = 3;
      }
      else
      {
         codepoint = ch & 0x07;
         bytes = 4;
      }

      for( i = 1; i < bytes; i++ )
      {
         ch = ( unsigned char )( *text++ );
         codepoint = ( codepoint << 6 ) | ( ch & 0x3F );
      }

      unsigned int *bitmap = fontData[ codepoint ];

      set_color_from_hex( foreground );
      for( int row = 0; row < BITMAP_HEIGHT; row++ )
      {
         unsigned int value = bitmap[ row ];
         for( int col = 0; col < BITMAP_WIDTH; col++ )
         {
            if( value & ( 1 << ( 15 - col ) ) )
            {
               draw_point( x + col, y + row );
            }
         }
      }

      x += BITMAP_WIDTH;
   }
}

void DrawTextBg( int x, int y, const char *text, unsigned int background, unsigned int foreground )
{
   unsigned int codepoint;
   int bytes;
   unsigned char ch;
   int i;

   y += BITMAP_HEIGHT;

   while( *text != '\0' )
   {
      bytes = 0;
      ch = ( unsigned char )( *text++ );
      if( ch <= 0x7F )
      {
         codepoint = ch;
         bytes = 1;
      }
      else if( ch <= 0xDF )
      {
         codepoint = ch & 0x1F;
         bytes = 2;
      }
      else if( ch <= 0xEF )
      {
         codepoint = ch & 0x0F;
         bytes = 3;
      }
      else
      {
         codepoint = ch & 0x07;
         bytes = 4;
      }

      for( i = 1; i < bytes; i++ )
      {
         ch = ( unsigned char )( *text++ );
         codepoint = ( codepoint << 6 ) | ( ch & 0x3F );
      }

      unsigned int *bitmap = fontData[ codepoint ];

      set_color_from_hex( background );
      glBegin( GL_QUADS );
         glVertex2i( x, y );
         glVertex2i( x + BITMAP_WIDTH, y );
         glVertex2i( x + BITMAP_WIDTH, y - BITMAP_HEIGHT );
         glVertex2i( x, y - BITMAP_HEIGHT );
      glEnd();

      set_color_from_hex( foreground );
      for( int row = 0; row < BITMAP_HEIGHT; row++ )
      {
         unsigned int value = bitmap[ row ];
         for( int col = 0; col < BITMAP_WIDTH; col++ )
         {
            if( value & ( 1 << ( 15 - col ) ) )
            {
               draw_point( x + col, y + row );
            }
         }
      }

      x += BITMAP_WIDTH;
   }
}

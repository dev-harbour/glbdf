/*
 *
 */

#include "glbdf.h"

#define FONT_WIDTH  9
#define FONT_HEIGHT 18

int main()
{
   App *app = CreateWindow( 830, 450, "Ascii Art" );

   const char *al[] = {
      "    ##########    ",
      "  ##          ##  ",
      " #    ######    # ",
      "#     #    #     #",
      "#     #    #     #",
      " #    #    #    # ",
      "  ##  #    #  ##  ",
      "    ##      ##    ",
      "      ######      "
   };
   int numLines = LEN( al );

   Background( app, 0x0 );

   while( ! MainLoop( app ) )
   {
      BEGINDRAWING( app );

      int totalHeight = numLines * FONT_HEIGHT;
      int startX = ( app->width - strlen( al[ 0 ] ) * FONT_WIDTH ) / 2;
      int startY = ( app->height - totalHeight ) / 2;

      for( int i = 0; i < numLines; i++ )
      {
         unsigned int color = ( i == 0 || i >= numLines - 2 ) ? 0xFFFFFF : 0xCCCCCC;
         DrawText( startX, startY + i * FONT_HEIGHT, al[ i ], 0x0, color );
      }

      ENDDRAWING( app );
      WaitEvents();
   }

   CloseAll( app );
}

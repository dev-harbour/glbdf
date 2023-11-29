/*
 *
 */

#include "glbdf.h"

int main()
{
   App *app = CreateWindow( 830, 450, "Test text" );

   Background( app, 0xF1F1F1 );

   while( ! MainLoop( app ) )
   {
      BEGINDRAWING( app );

         int startX = ( app->width - 225 ) / 2;
         int startY = ( app->height - 18 ) / 2;

         DrawTextBg( startX, startY, "Ą, Ć, Ę, Ł, Ń, Ó, Ś, Ź, Ż", 0xFAFAFA, 0x0 );

      ENDDRAWING( app );
      WaitEvents();
   }

   CloseAll( app );
}

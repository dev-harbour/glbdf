/*
 *
 */

#include "glbdf.h"

int main()
{
   App *app = CreateWindow( 830, 450, "Test window" );

   Background( app, 0xEAEAEA );

   while( ! MainLoop( app ) )
   {
      BEGINDRAWING( app );

         int startX = ( app->width - 225 ) / 2;
         int startY = ( app->height - 18 ) / 2;

         DrawTextBg( startX, startY, "------Hello, world!------", 0xF1F1F1, 0x0 );

      ENDDRAWING( app );
      WaitEvents();
   }

   CloseAll( app );
}

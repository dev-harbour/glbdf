/*
 *
 */

#include "glbdf.h"

void myOnClickFunction()
{
   printf( "Button was clicked!\n" );
   openURL( "https://github.com/dev-harbour/glbdf" );
}

int main()
{
   App *app = CreateWindow( 830, 450, "Test Button" );
   Button *b = ButtonNew( app, myOnClickFunction );

   Background( app, 0xEAEAEA );

   while( ! MainLoop( app ) )
   {
      BEGINDRAWING( app );

         int startX = ( app->width - b->width  ) / 2;
         int startY = ( app->height - b->height ) / 2;

         DrawButton( b, startX, startY, "Click Me", 0x323232, 0xFF0000 );

      ENDDRAWING( app );
      WaitEvents();
   }

   FreeButton( b );
   CloseAll( app );
}

/*
 * The phrase 'Anpáŋ Wí Čháŋglé' in Lakota language translates to 'Dancing Sun'.
 * 'Anpáŋ' and 'Wí' both refer to the sun, with 'Anpáŋ' being a more direct term
 * for 'sun', while 'Wí' can also mean 'sun' but is often used in broader or more
 * symbolic contexts. 'Čháŋglé' means 'to dance' or 'dancing'.
 */

#include "glbdf.h"

int main()
{
   App *app = CreateWindow( 512, 512, "Anpáŋ Wí Čháŋglé - ");

   Background( app, 0x0 );

   while( ! MainLoop( app ) )
   {
      BEGINDRAWING( app );

      int pointSize = 16;
      int gridWidth = app->width / pointSize;
      int gridHeight = app->height / pointSize;

      // Initializing an array to track occupied points
      bool occupiedPoints[ gridWidth ][ gridHeight ];
      for( int x = 0; x < gridWidth; x++ )
      {
         for( int y = 0; y < gridHeight; y++ )
         {
            occupiedPoints[ x ][ y ] = F;
         }
      }

      int centerX = app->width / 2;
      int centerY = app->height / 2;
      int radius = 150;
      int outerBoundary = radius + 50;

      // Draw random points inside a circle
      for( int i = 0; i < 8000; ++i )
      {
         double angle = ( double ) rand() / RAND_MAX * 2 * M_PI;
         double r = sqrt( ( double ) rand() / RAND_MAX ) * radius;
         int x = centerX + r * cos( angle );
         int y = centerY + r * sin( angle );
         PointSize( x, y, 2, 0x670100 );
      }

      // Drawing random points outside the circle
      for( int i = 0; i < 600; ++i )
      {
         int gridX = rand() % gridWidth;
         int gridY = rand() % gridHeight;
         int x = gridX * pointSize;
         int y = gridY * pointSize;
         int distFromCenter = sqrt( pow( x - centerX, 2 ) + pow( y - centerY, 2 ) );

         if( distFromCenter > outerBoundary && ! occupiedPoints[ gridX ][ gridY ] )
         {
            PointSize( x, y, pointSize, 0xFFFFFF );
            occupiedPoints[ gridX ][ gridY ] = T;
         }
      }

      ENDDRAWING( app );
      WaitEvents();
   }

   CloseAll( app );
}

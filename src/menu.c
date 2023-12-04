/*
 *
 */

#include "glbdf.h"

//* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= */
static bool is_point_inside_menu_bar( MenuBar *pMenuBar, int x, int y )
{
   return x >= pMenuBar->x && x <= ( pMenuBar->x + pMenuBar->width ) && y >= pMenuBar->y && y <= ( pMenuBar->y + pMenuBar->height );
}

static bool is_point_inside_menu_item( MenuItem *pMenuItem, int x, int y )
{
   return x >= pMenuItem->x && x <= ( pMenuItem->x + pMenuItem->width ) && y >= pMenuItem->y && y <= ( pMenuItem->y + pMenuItem->height );
}

Menu *MenuNew( App *pApp )
{
   Menu *pMenu = malloc( sizeof( Menu ) );
   if( ! pMenu )
   {
      fprintf( stderr, "Failed to allocate memory for Menu.\n" );
      return NULL;
   }

   memset( pMenu, 0, sizeof( Menu ) );
   pMenu->pApp = pApp;
   pApp->pMenu = pMenu; // Przypisanie utworzonego menu do struktury App

   return pMenu;
}

MenuBar *MenuBarNew( Menu *pMenu, const char *title )
{
   if( pMenu->iMenuBarsCount >= MENU_BAR_MAX )
   {
      fprintf( stderr, "Limit of MenuBar reached.\n" );
      return NULL;
   }

   MenuBar *pMenuBar = malloc( sizeof( MenuBar ) );
   if( ! pMenuBar )
   {
      fprintf( stderr, "Failed to allocate memory for MenuBar.\n" );
      return NULL;
   }

   memset( pMenuBar, 0, sizeof( MenuBar ) );
   pMenuBar->height = MENU_BAR_HEIGHT;
   pMenuBar->title = title;
   pMenuBar->textMargin = MENU_BAR_TEXT_MARGIN;

   pMenu->pMenuBars[ pMenu->iMenuBarsCount++ ] = pMenuBar;

   return pMenuBar;
}

void MenuBarAddItem( MenuBar *pMenuBar, const char *selectTitle, int shortcutKey, void ( *onClick )( MenuItem * ) )
{
   if( pMenuBar->iMenuItemsCount >= MENU_ITEM_MAX )
   {
      fprintf( stderr, "Limit of MenuItems reached.\n" );
      return;
   }

   MenuItem *pMenuItem = malloc( sizeof( MenuItem ) );
   if( ! pMenuItem )
   {
      fprintf( stderr, "Failed to allocate memory for MenuItem.\n" );
      return;
   }

   memset( pMenuItem, 0, sizeof( MenuItem ) );

   pMenuItem->selectTitle = selectTitle;
   pMenuItem->textMargin = MENU_ITEM_TEXT_MARGIN;
   pMenuItem->acceleratorKey = shortcutKey;
   pMenuItem->onClick = onClick;

   int textWidth = strlen( selectTitle ) * BITMAP_WIDTH;
   pMenuItem->width = textWidth + 2 * MENU_ITEM_TEXT_MARGIN;

   if( pMenuItem->width > pMenuBar->iDefaultMenuItemsWidth )
   {
      pMenuBar->iDefaultMenuItemsWidth = pMenuItem->width;
   }

   pMenuItem->height = MENU_ITEM_HEIGHT;

   pMenuBar->pMenuItems[ pMenuBar->iMenuItemsCount++ ] = pMenuItem;
}

void DrawMenu( Menu *pMenu )
{
   if( pMenu )
   {
      int currentX = 0;
      FillRect( 0, 0, pMenu->pApp->width, MENU_BAR_HEIGHT, 0xFFFFFF );

      for( int i = 0; i < pMenu->iMenuBarsCount; ++i )
      {
         MenuBar *pMenuBar = pMenu->pMenuBars[ i ];

         int strLen = strlen( pMenuBar->title );
         pMenuBar->width = BITMAP_WIDTH * strLen + 2 * pMenuBar->textMargin;
         pMenuBar->x = currentX;
         pMenuBar->y = 0;
         currentX += pMenuBar->width;

         bool isMouseOverMenuBar = is_point_inside_menu_bar( pMenuBar, pMenu->pApp->cursorX, pMenu->pApp->cursorY );
         bool isMouseOverMenuItem = F;
         pMenuBar->mouseOver = isMouseOverMenuBar;

         if( isMouseOverMenuBar )
         {
            pMenuBar->bMenuItemDisplayed = T;
            FillRect( pMenuBar->x, pMenuBar->y, pMenuBar->width, MENU_BAR_HEIGHT, 0xE5E5E5 );
         }

         DrawText( pMenuBar->x + pMenuBar->textMargin, ( MENU_BAR_HEIGHT - BITMAP_HEIGHT ) / 2, pMenuBar->title, 0x0 );

         if( pMenuBar->bMenuItemDisplayed )
         {
            int menuItemY = MENU_BAR_HEIGHT;
            for( int j = 0; j < pMenuBar->iMenuItemsCount; ++j )
            {
               MenuItem *pMenuItem = pMenuBar->pMenuItems[ j ];

               pMenuItem->x = pMenuBar->x;
               pMenuItem->y = menuItemY;
               pMenuItem->width = pMenuBar->iDefaultMenuItemsWidth;
               pMenuItem->height = MENU_ITEM_HEIGHT;

               if( is_point_inside_menu_item( pMenuItem, pMenu->pApp->cursorX, pMenu->pApp->cursorY ) )
               {
                  isMouseOverMenuItem = T;
                  pMenuItem->mouseOver = T;
                  FillRect( pMenuItem->x, pMenuItem->y, pMenuItem->width, pMenuItem->height, 0xE5E5E5 );
               }
               else
               {
                  pMenuItem->mouseOver = F;
                  FillRect( pMenuItem->x, pMenuItem->y, pMenuItem->width, pMenuItem->height, 0xFFFFFF );
               }

               if( pMenu->pApp->mouseButton == GLFW_MOUSE_BUTTON_LEFT && pMenu->pApp->mouseAction == GLFW_PRESS )
               {
                  if( pMenuItem->mouseOver )
                  {
                     pMenuItem->isClicked = T;
                     if( pMenuItem->onClick )
                     {
                        pMenuItem->onClick( pMenuItem );
                     }
                  }
               }
               else if( pMenu->pApp->mouseButton == GLFW_MOUSE_BUTTON_LEFT && pMenu->pApp->mouseAction == GLFW_RELEASE )
               {
                  pMenuItem->isClicked = F;
               }

               DrawText( pMenuItem->x + pMenuItem->textMargin, pMenuItem->y + ( pMenuItem->height - BITMAP_HEIGHT ) / 2, pMenuItem->selectTitle, 0x0 );
               menuItemY += pMenuItem->height;
            }

            Rect( pMenuBar->x + 1, MENU_BAR_HEIGHT, pMenuBar->iDefaultMenuItemsWidth, pMenuBar->iMenuItemsCount * MENU_ITEM_HEIGHT, 0x0 );

            if( ! isMouseOverMenuBar && ! isMouseOverMenuItem )
            {
               pMenuBar->bMenuItemDisplayed = F;
            }
         }
      }
   }
   else
   {
      printf( "Warning: Attempted to draw a NULL Menu.\n" );
   }
}

void FreeMenu( Menu *pMenu )
{
   if( pMenu )
   {
      for( int i = 0; i < pMenu->iMenuBarsCount; ++i )
      {
         MenuBar *pMenuBar = pMenu->pMenuBars[ i ];
         if( pMenuBar )
         {
            for( int j = 0; j < pMenuBar->iMenuItemsCount; ++j )
            {
               MenuItem *pMenuItem = pMenuBar->pMenuItems[ j ];
               if( pMenuItem )
               {
                  free( pMenuItem );
               }
            }
            free( pMenuBar );
         }
      }
      free( pMenu );
   }
   else
   {
      printf( "Warning: Attempted to free a NULL pointer.\n" );
   }
}

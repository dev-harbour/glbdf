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

static void menuitem_key_press( Menu *pMenu )
{
   if( pMenu->pApp->keyAction == GLFW_PRESS )
   {
      bool handled = F;

      for( int i = 0; i < pMenu->iMenuBarsCount && ! handled; ++ i )
      {
         MenuBar *pMenuBar = pMenu->pMenuBars[ i ];
         for( int j = 0; j < pMenuBar->iMenuItemsCount; ++j )
         {
            MenuItem *pMenuItem = pMenuBar->pMenuItems[ j ];
            if( pMenuItem->shortcutKey == pMenu->pApp->keyCode )
            {
               if( pMenuItem->onClick )
               {
                  pMenuItem->onClick( pMenuItem );
                  pMenu->pApp->keyCode = 0;
                  pMenu->pApp->keyAction = 0;
                  handled = T;
                  break;
               }
            }
         }
      }
   }
}

static void menuitem_mouse_press( Menu *pMenu, MenuItem *pMenuItem )
{
   if( pMenu->pApp->mouseButton == GLFW_MOUSE_BUTTON_LEFT && pMenu->pApp->mouseAction == GLFW_PRESS )
   {
      if( pMenuItem->mouseOver )
      {
         if( pMenuItem->onClick )
         {
            pMenuItem->onClick( pMenuItem );
            pMenu->isVisible = F;
            pMenu->pApp->keyCode = 0;
            pMenu->pApp->keyAction = 0;
         }
      }
   }
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
   pMenu->isVisible = T;

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
   pMenuBar->pMenu = pMenu;
   pMenuBar->height = MENU_BAR_HEIGHT;
   pMenuBar->title = title;
   pMenuBar->textMargin = MENU_BAR_TEXT_MARGIN;

   pMenu->pMenuBars[ pMenu->iMenuBarsCount++ ] = pMenuBar;

   return pMenuBar;
}

void MenuBarAddItem( MenuBar *pMenuBar, const char *selectTitle, int key, int mods, void ( *onClick )( MenuItem * ) )
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
   pMenuItem->pMenu = pMenuBar->pMenu;
   int textWidth = strlen( selectTitle ) * BITMAP_WIDTH;
   int tempWidth = textWidth + 2 * MENU_ITEM_TEXT_MARGIN;
   if( tempWidth > pMenuBar->iMenuItemsWidth )
   {
      pMenuBar->iMenuItemsWidth = tempWidth;
   }

   pMenuItem->height = MENU_ITEM_HEIGHT;
   pMenuItem->selectTitle = selectTitle;
   pMenuItem->textMargin = MENU_ITEM_TEXT_MARGIN;
   pMenuItem->shortcutKey = key;
   GenerateShortcutName( pMenuItem->shortcutName, sizeof( pMenuItem->shortcutName ), key, mods );

   textWidth = strlen( pMenuItem->shortcutName ) * BITMAP_WIDTH;
   tempWidth = textWidth + MENU_ITEM_TEXT_MARGIN;
   if( tempWidth > pMenuBar->iMenuItemsWidthShortcut )
   {
      pMenuBar->iMenuItemsWidthShortcut = tempWidth;
   }

   pMenuItem->onClick = onClick;

   pMenuBar->pMenuItems[ pMenuBar->iMenuItemsCount++ ] = pMenuItem;
}

void DrawMenu( Menu *pMenu )
{
   if( pMenu )
   {
      menuitem_key_press( pMenu );
      int currentX = 0;
      FillRect( 0, 0, pMenu->pApp->width, MENU_BAR_HEIGHT, MENU_BAR_DEFAULT );

      for( int i = 0; i < pMenu->iMenuBarsCount; ++i )
      {
         MenuBar *pMenuBar = pMenu->pMenuBars[ i ];

         int strLen = strlen( pMenuBar->title );
         pMenuBar->width = BITMAP_WIDTH * strLen + 2 * pMenuBar->textMargin;
         pMenuBar->x = currentX;
         pMenuBar->y = 0;
         currentX += pMenuBar->width;

         pMenuBar->mouseOver = is_point_inside_menu_bar( pMenuBar, pMenu->pApp->cursorX, pMenu->pApp->cursorY );

         bool isMouseOverMenuItem = F;

         if( pMenuBar->mouseOver )
         {
            pMenuBar->bMenuItemDisplayed = T;
            FillRect( pMenuBar->x, pMenuBar->y, pMenuBar->width, MENU_BAR_HEIGHT, MENU_BAR_MOUSE_OVER );
            pMenu->isVisible = T;
         }

         DrawText( pMenuBar->x + pMenuBar->textMargin, ( MENU_BAR_HEIGHT - BITMAP_HEIGHT ) / 2, pMenuBar->title, pMenuBar->mouseOver ? MENU_BAR_MOUSE_OVER_TEXT : MENU_BAR_DEFAULT_TEXT );

         if( pMenu->isVisible )
         {
            if( pMenuBar->bMenuItemDisplayed )
            {
               int menuItemY = MENU_BAR_HEIGHT;
               for( int j = 0; j < pMenuBar->iMenuItemsCount; ++j )
               {
                  MenuItem *pMenuItem = pMenuBar->pMenuItems[ j ];

                  pMenuItem->x = pMenuBar->x;
                  pMenuItem->y = menuItemY;
                  pMenuItem->width = pMenuBar->iMenuItemsWidth + pMenuBar->iMenuItemsWidthShortcut;
                  pMenuItem->height = MENU_ITEM_HEIGHT;

                  if( is_point_inside_menu_item( pMenuItem, pMenu->pApp->cursorX, pMenu->pApp->cursorY ) )
                  {
                     isMouseOverMenuItem = T;
                     pMenuItem->mouseOver = T;
                     FillRect( pMenuItem->x, pMenuItem->y, pMenuItem->width, pMenuItem->height, MENU_ITEM_MOUSE_OVER );

                     FillRect( pMenuBar->x, pMenuBar->y, pMenuBar->width, MENU_BAR_HEIGHT, MENU_BAR_IF_MOUSE_OVER_MENU_ITEM );
                     DrawText( pMenuBar->x + pMenuBar->textMargin, ( MENU_BAR_HEIGHT - BITMAP_HEIGHT ) / 2, pMenuBar->title, MENU_BAR_IF_MOUSE_OVER_MENU_ITEM_TEXT );
                  }
                  else
                  {
                     pMenuItem->mouseOver = F;
                     FillRect( pMenuItem->x, pMenuItem->y, pMenuItem->width, pMenuItem->height, MENU_ITEM_DEFAULT );
                  }

                  menuitem_mouse_press( pMenu, pMenuItem );

                  DrawText( pMenuItem->x + pMenuItem->textMargin, pMenuItem->y + ( pMenuItem->height - BITMAP_HEIGHT ) / 2, pMenuItem->selectTitle, pMenuItem->mouseOver ? MENU_ITEM_DEFAULT_TEXT : MENU_ITEM_MOUSE_OVER_TEXT );

                  int shortcutTextWidth = strlen( pMenuItem->shortcutName ) * BITMAP_WIDTH;
                  int shortcutX = pMenuItem->x + pMenuItem->width - shortcutTextWidth - pMenuItem->textMargin;
                  DrawText( shortcutX, pMenuItem->y + ( pMenuItem->height - BITMAP_HEIGHT ) / 2, pMenuItem->shortcutName, pMenuItem->mouseOver ? MENU_ITEM_MOUSE_OVER_TEXT_SHORTCUT : MENU_ITEM_DEFAULT_TEXT_SHORTCUT );

                  menuItemY += pMenuItem->height;
               }

               Rect( pMenuBar->x + 1, MENU_BAR_HEIGHT, pMenuBar->iMenuItemsWidth + pMenuBar->iMenuItemsWidthShortcut, pMenuBar->iMenuItemsCount * MENU_ITEM_HEIGHT, MENU_ITEM_BORDER );

               if( ! pMenuBar->mouseOver && ! isMouseOverMenuItem )
               {
                  pMenuBar->bMenuItemDisplayed = F;
               }
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

void PrintMenuItemStruct( const MenuItem *pMenuItem )
{
   printf( "\033[2J" );
   printf( "\033[H" );

   if( pMenuItem )
   {
      printf( "MenuItem Structure\n" );
      printf( "[\n" );
      printf( "   X                        : %d\n", pMenuItem->x );
      printf( "   Y                        : %d\n", pMenuItem->y );
      printf( "   Width                    : %d\n", pMenuItem->width );
      printf( "   Height                   : %d\n", pMenuItem->height );
      printf( "   Select title             : %s\n", pMenuItem->selectTitle );
      printf( "   Text margin              : %d\n", pMenuItem->textMargin );
      printf( "   Mouse over               : %d\n", pMenuItem->mouseOver );
      printf( "   Is clicked               : %d\n", pMenuItem->isClicked );
      printf( "   Shortcut key             : %d\n", pMenuItem->shortcutKey );
      printf( "   Shortcut name            : %s\n", pMenuItem->shortcutName );
      printf( "   onClick function pointer : %p\n", (void*) pMenuItem->onClick );
      printf( "]\n" );
   }
   else
   {
      printf( "HBGL structure is NULL\n" );
      return;
   }

   fflush( stdout );
}

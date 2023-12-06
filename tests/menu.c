/*
 *
 */

#include "glbdf.h"

static void lastMenuItemClicked( MenuItem *item )
{
   if( item )
   {
      PrintMenuItemStruct( item );
   }
}

int main()
{
   App *app = CreateWindow( 830, 450, "Test menu" );

   Menu *menu = MenuNew( app );

   MenuBar *fileMenu = MenuBarNew( menu, "File" );
   MenuBarAddItem( fileMenu, "New",        GLFW_KEY_N, GLFW_MOD_CONTROL, lastMenuItemClicked );
   MenuBarAddItem( fileMenu, "Open",       GLFW_KEY_O, GLFW_MOD_CONTROL, lastMenuItemClicked );
   MenuBarAddItem( fileMenu, "Save",       GLFW_KEY_S, GLFW_MOD_CONTROL, lastMenuItemClicked );
   MenuBarAddItem( fileMenu, "Save as...",       0, 0, lastMenuItemClicked );
   MenuBarAddItem( fileMenu, "Close",            0, 0, lastMenuItemClicked );
   MenuBarAddItem( fileMenu, "Print",            0, 0, lastMenuItemClicked );
   MenuBarAddItem( fileMenu, "Printer setup...", 0, 0, lastMenuItemClicked );
   MenuBarAddItem( fileMenu, "DOS Shell",        0, 0, lastMenuItemClicked );
   MenuBarAddItem( fileMenu, "Exit",             0, 0, lastMenuItemClicked );

   MenuBar *editMenu = MenuBarNew( menu, "Edit" );
   MenuBarAddItem( editMenu, "Undo",           0, 0, lastMenuItemClicked );
   MenuBarAddItem( editMenu, "Cut",            0, 0, lastMenuItemClicked );
   MenuBarAddItem( editMenu, "Copy",           0, 0, lastMenuItemClicked );
   MenuBarAddItem( editMenu, "Paste",          0, 0, lastMenuItemClicked );
   MenuBarAddItem( editMenu, "Clear",          0, 0, lastMenuItemClicked );
   MenuBarAddItem( editMenu, "Delete",         0, 0, lastMenuItemClicked );
   MenuBarAddItem( editMenu, "Paragraph",      0, 0, lastMenuItemClicked );
   MenuBarAddItem( editMenu, "Upcase Block",   0, 0, lastMenuItemClicked );
   MenuBarAddItem( editMenu, "Downcase Block", 0, 0, lastMenuItemClicked );
   MenuBarAddItem( editMenu, "Stats of Block", 0, 0, lastMenuItemClicked );

   MenuBar *searchMenu = MenuBarNew( menu, "Search" );

   MenuBar *utilitiesMenu = MenuBarNew( menu, "Utilities" );

   MenuBar *optionsMenu = MenuBarNew( menu, "Options" );

   MenuBar *helpMenu = MenuBarNew( menu, "Help" );

   Background( app, 0x264B82 );

   while( ! MainLoop( app ) )
   {
      BEGINDRAWING( app );

         DrawMenu( menu );

      ENDDRAWING( app );
      WaitEvents();
   }

   FreeMenu( menu );
   CloseAll( app );
}

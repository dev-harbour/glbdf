/*
 *
 */

#include "glbdf.h"

void onClick()
{
   printf( "Test menu\n" );
}

int main()
{
   App *app = CreateWindow( 830, 450, "Test menu" );

   Menu *menu = MenuNew( app );

   MenuBar *fileMenu = MenuBarNew( menu, "File" );
   MenuBarAddItem( fileMenu,"New",              onClick );
   MenuBarAddItem( fileMenu,"Open",             onClick );
   MenuBarAddItem( fileMenu,"Save",             onClick );
   MenuBarAddItem( fileMenu,"Save as...",       onClick );
   MenuBarAddItem( fileMenu,"Close",            onClick );
   MenuBarAddItem( fileMenu,"Print",            onClick );
   MenuBarAddItem( fileMenu,"Printer setup...", onClick );
   MenuBarAddItem( fileMenu,"DOS Shell",        onClick );
   MenuBarAddItem( fileMenu,"Exit",             onClick );

   MenuBar *editMenu = MenuBarNew( menu, "Edit" );
   MenuBarAddItem( editMenu, "Undo",           onClick );
   MenuBarAddItem( editMenu, "Cut",            onClick );
   MenuBarAddItem( editMenu, "Copy",           onClick );
   MenuBarAddItem( editMenu, "Paste",          onClick );
   MenuBarAddItem( editMenu, "Clear",          onClick );
   MenuBarAddItem( editMenu, "Delete",         onClick );
   MenuBarAddItem( editMenu, "Paragraph",      onClick );
   MenuBarAddItem( editMenu, "Upcase Block",   onClick );
   MenuBarAddItem( editMenu, "Downcase Block", onClick );
   MenuBarAddItem( editMenu, "Stats of Block", onClick );

   MenuBar *searchMenu = MenuBarNew( menu, "Search" );

   MenuBar *utilitiesMenu = MenuBarNew( menu, "Utilities" );

   MenuBar *optionsMenu = MenuBarNew( menu, "Options" );

   MenuBar *HelpMenu = MenuBarNew( menu, "Help" );

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

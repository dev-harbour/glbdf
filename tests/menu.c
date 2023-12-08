/*
 *
 */

#include "glbdf.h"

void onExitClicked( MenuItem *pMenuItem )
{
   if( pMenuItem && pMenuItem->pMenu )
   {
      ExitApp( pMenuItem->pMenu->pApp );
   }
}

static void lastMenuItemClicked( MenuItem *pMenuItem )
{
   if( pMenuItem )
   {
      PrintMenuItemStruct( pMenuItem );
   }
}

int main()
{
   App *app = CreateWindow( 830, 450, "Sample Menu" );

   Menu *menu = MenuNew( app );

   MenuBar *fileMenu = MenuBarNew( menu, "File" );
      MenuBarAddItem( fileMenu, "New",              GLFW_KEY_N, GLFW_MOD_CONTROL, lastMenuItemClicked );
      MenuBarAddItem( fileMenu, "Open",             GLFW_KEY_O, GLFW_MOD_CONTROL, lastMenuItemClicked );
      MenuBarAddItem( fileMenu, "Save",             GLFW_KEY_S, GLFW_MOD_CONTROL, lastMenuItemClicked );
      MenuBarAddItem( fileMenu, "Save as...",       GLFW_KEY_S, GLFW_MOD_CONTROL | GLFW_MOD_SHIFT, lastMenuItemClicked );
      MenuBarAddItem( fileMenu, "Close",            0, 0,                         lastMenuItemClicked );
      MenuBarAddItem( fileMenu, "Print",            GLFW_KEY_P, GLFW_MOD_CONTROL, lastMenuItemClicked );
      MenuBarAddItem( fileMenu, "Printer setup...", 0, 0,                         lastMenuItemClicked );
      MenuBarAddItem( fileMenu, "DOS Shell",        0, 0,                         lastMenuItemClicked );
      MenuBarAddItem( fileMenu, "Exit",             GLFW_KEY_Q, GLFW_MOD_CONTROL, lastMenuItemClicked );

   MenuBar *editMenu = MenuBarNew( menu, "Edit" );
      MenuBarAddItem( editMenu, "Undo",           GLFW_KEY_Z, GLFW_MOD_CONTROL, lastMenuItemClicked );
      MenuBarAddItem( editMenu, "Cut",            GLFW_KEY_X, GLFW_MOD_CONTROL, lastMenuItemClicked );
      MenuBarAddItem( editMenu, "Copy",           GLFW_KEY_C, GLFW_MOD_CONTROL, lastMenuItemClicked );
      MenuBarAddItem( editMenu, "Paste",          GLFW_KEY_V, GLFW_MOD_CONTROL, lastMenuItemClicked );
      MenuBarAddItem( editMenu, "Clear",          0, 0,                         lastMenuItemClicked );
      MenuBarAddItem( editMenu, "Delete",         GLFW_KEY_DELETE, 0,           lastMenuItemClicked );
      MenuBarAddItem( editMenu, "Paragraph",      0, 0,                         lastMenuItemClicked );
      MenuBarAddItem( editMenu, "Upcase Block",   0, 0,                         lastMenuItemClicked );
      MenuBarAddItem( editMenu, "Downcase Block", 0, 0,                         lastMenuItemClicked );
      MenuBarAddItem( editMenu, "Stats of Block", 0, 0,                         lastMenuItemClicked );

   MenuBar *searchMenu = MenuBarNew( menu, "Search" );
      MenuBarAddItem( searchMenu, "Find",          GLFW_KEY_F, GLFW_MOD_CONTROL, lastMenuItemClicked );
      MenuBarAddItem( searchMenu, "Find Next",     GLFW_KEY_G, GLFW_MOD_CONTROL, lastMenuItemClicked );
      MenuBarAddItem( searchMenu, "Find Previous", GLFW_KEY_G, GLFW_MOD_CONTROL | GLFW_MOD_SHIFT, lastMenuItemClicked );
      MenuBarAddItem( searchMenu, "Replace",       GLFW_KEY_H, GLFW_MOD_CONTROL, lastMenuItemClicked );
      MenuBarAddItem( searchMenu, "Go To...",      GLFW_KEY_G, GLFW_MOD_CONTROL | GLFW_MOD_ALT, lastMenuItemClicked );

   MenuBar *utilitiesMenu = MenuBarNew( menu, "Utilities" );
      MenuBarAddItem( utilitiesMenu, "Calculator",     0, 0, lastMenuItemClicked );
      MenuBarAddItem( utilitiesMenu, "Notepad",        0, 0, lastMenuItemClicked );
      MenuBarAddItem( utilitiesMenu, "Command Prompt", 0, 0, lastMenuItemClicked );
      MenuBarAddItem( utilitiesMenu, "System Info",    0, 0, lastMenuItemClicked );

   MenuBar *optionsMenu = MenuBarNew( menu, "Options" );
      MenuBarAddItem( optionsMenu, "Preferences", GLFW_KEY_P, GLFW_MOD_CONTROL | GLFW_MOD_ALT, lastMenuItemClicked );
      MenuBarAddItem( optionsMenu, "Color Theme", 0, 0, lastMenuItemClicked );
      MenuBarAddItem( optionsMenu, "Font Size",   0, 0, lastMenuItemClicked );
      MenuBarAddItem( optionsMenu, "Language",    0, 0, lastMenuItemClicked );

   MenuBar *helpMenu = MenuBarNew( menu, "Help" );
      MenuBarAddItem( helpMenu, "View Help",         GLFW_KEY_F1, 0, lastMenuItemClicked );
      MenuBarAddItem( helpMenu, "About",             0, 0, lastMenuItemClicked );
      MenuBarAddItem( helpMenu, "Check for Updates", 0, 0, lastMenuItemClicked );
      MenuBarAddItem( helpMenu, "Send Feedback",     0, 0, lastMenuItemClicked );

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

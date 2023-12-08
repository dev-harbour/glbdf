#ifndef GLBDF_H_
#define GLBDF_H_

#include <math.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <GLFW/glfw3.h>

#define DEFAULT_COLORS_GLBDF

#ifdef DEFAULT_COLORS_GLBDF
   #include "default_colors_glbdf.h"
#endif

/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= */

#define BDF_VERSION_MAJOR   0
#define BDF_VERSION_MINOR   0
#define BDF_VERSION_RELEASE 0
#define BDF_VERSION_STATUS  "dev"
#define BDF_DESCRIPTION     "Graphics Library with Glyph Bitmap Distribution Format"
#define BDF_COPYRIGHT       "Copyright (c) 2023 Harbour development, https://github.com/dev-harbour/glbdf"
#define BDF_LICENSE         ""

#define ENCODING            65534
#define BITMAP_WIDTH        9
#define BITMAP_HEIGHT       18
extern unsigned int fontData[ ENCODING ][ BITMAP_HEIGHT ];

#define MENU_BAR_MAX          15
#define MENU_BAR_HEIGHT       24
#define MENU_BAR_TEXT_MARGIN  10

#define MENU_ITEM_MAX         25
#define MENU_ITEM_HEIGHT      24
#define MENU_ITEM_TEXT_MARGIN 24


typedef enum bool
{
   F = 0,
   T = ( ! 0 )
} bool;

typedef struct _App      App;
typedef struct _Button   Button;
typedef struct _MenuItem MenuItem;
typedef struct _MenuBar  MenuBar;
typedef struct _Menu     Menu;

struct _Button
{
   App         *pApp;
   int          x;
   int          y;
   int          width;
   int          height;
   int          textMargin;
   bool         state;
   bool         mouseOver;
   bool         isClicked;
   unsigned int buttonID;
   unsigned int color;
   void         ( *onClick )();
};

struct _MenuItem
{
   Menu       *pMenu;
   int         x;
   int         y;
   int         width;
   int         height;
   const char *selectTitle;
   int         textMargin;
   bool        mouseOver;
   bool        isClicked;
   int         shortcutKey;
   char        shortcutName[ 64 ];
   void        ( *onClick )( MenuItem *pMenuItem );
};

struct _MenuBar
{
   Menu       *pMenu;
   int         x;
   int         y;
   int         width;
   int         height;
   const char *title;
   int         textMargin;
   bool        mouseOver;
   bool        isClicked;
   MenuItem   *pMenuItems[ MENU_ITEM_MAX ];
   int         iMenuItemsCount;
   int         iMenuItemsWidth;
   int         iMenuItemsWidthShortcut;
   bool        bMenuItemDisplayed;
};

struct _Menu
{
   App     *pApp;
   MenuBar *pMenuBars[ MENU_BAR_MAX ];
   int      iMenuBarsCount;
};

struct _App
{
   GLFWwindow  *window;
   int          width;
   int          height;
   const char  *title;
   bool         closeFlag;
   double       cursorX;
   double       cursorY;
   int          keyCode;
   int          keyScancode;
   int          keyAction;
   int          keyMods;
   int          mouseButton;
   int          mouseAction;
   int          mouseMods;
   int          winMaximized;
   unsigned int background;
   double       previousTime;
   //Menu        *pMenu;
};

/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= */
// API functions
App  *CreateWindow( int width, int height, const char *title );
bool  MainLoop( App *pApp );
void  ExitApp( App *pApp );
void  BeginDrawing( App *pApp );
void  EndDrawing( const App *pApp );
int   CloseAll( App *pApp );
void  Background( App *pApp, unsigned int color );
void  PollEvents();
void  WaitEvents();
void  WaitEventsTimeout( double timeout );
void  SetTargetFPS( App *pApp, int targetFPS );

//--- Text
void DrawText( int x, int y, const char *text, unsigned int foreground );
void DrawTextBg( int x, int y, const char *text, unsigned int background, unsigned int foreground );

// Button
Button *ButtonNew( App *pApp, void ( *onClick )() );
void    DrawButton( Button *pButton, int x, int y, const char *text, unsigned int background, unsigned int foreground );
void    FreeButton( Button *pButton );

// Menu
Menu    *MenuNew( App *pApp );
MenuBar *MenuBarNew( Menu *pMenu, const char *title );
void     MenuBarAddItem( MenuBar *pMenuBar, const char *selectTitle, int key, int mods, void ( *onClick )( MenuItem * ) );
void     DrawMenu( Menu *pMenu );
void     FreeMenu( Menu *pMenu );
void     PrintMenuItemStruct( const MenuItem *pMenuItem );

//--- Shapes
void Point( int x, int y, unsigned int color );
void PointSize( int x, int y, int pointSize, unsigned int color );
void Line( int x, int y, int width, int height, unsigned int color );
void LineWidth( int x, int y, int width, int height, int lineWidth, unsigned int color );
void Rect( int x, int y, int width, int height, unsigned int color );
void RectWidthToInside( int x, int y, int width, int height, int lineWidth, unsigned int color );
void RectWidthToCenter( int x, int y, int width, int height, int numberLines, unsigned int color );
void RectWidthToOutside(int x, int y, int width, int height, int numberLines, unsigned int color);
void FillRect( int x, int y, int width, int height, unsigned int color );

//--- HTTP functions
bool openURL( const char *url );
bool openEmailClient( const char *emailAddress );

/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= */
// internal
void check_open_gl_error( const char *stmt, const char *fname, int line, GLenum *errCode );
void set_color_from_hex( unsigned int hexColor );
void GenerateShortcutName( char *buffer, int bufferSize, int key, int mods );

/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= */
// macros
#define REPORT_OPENGL_ERROR( stmt ) \
   GLenum errCode; \
   check_open_gl_error( stmt, __FILE__, __LINE__, &errCode ); \
   if( errCode != GL_NO_ERROR ) return;

#define MAX( a, b ) ( ( a ) < ( b ) ? ( b ) : ( a ) )
#define MIN( a, b ) ( ( a ) < ( b ) ? ( a ) : ( b ) )
#define UNUSED( n ) ( ( void )( n ) )
#define LEN( n ) ( sizeof( n ) / sizeof( n )[ 0 ] )

#define BEGINDRAWING( pApp ) do { BeginDrawing( pApp )
#define ENDDRAWING( pApp ) EndDrawing( pApp ); } while( 0 )

#endif /* End GLBDF_H_ */

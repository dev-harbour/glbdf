/*
 *
 */

#include "glbdf.h"

//* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= */
static const char *get_key_name( int key )
{
   switch( key )
   {
      case GLFW_KEY_A:   return "A";
      case GLFW_KEY_B:   return "B";
      case GLFW_KEY_C:   return "C";
      case GLFW_KEY_D:   return "D";
      case GLFW_KEY_E:   return "E";
      case GLFW_KEY_F:   return "F";
      case GLFW_KEY_G:   return "G";
      case GLFW_KEY_H:   return "H";
      case GLFW_KEY_I:   return "I";
      case GLFW_KEY_J:   return "J";
      case GLFW_KEY_K:   return "K";
      case GLFW_KEY_L:   return "L";
      case GLFW_KEY_M:   return "M";
      case GLFW_KEY_N:   return "N";
      case GLFW_KEY_O:   return "O";
      case GLFW_KEY_P:   return "P";
      case GLFW_KEY_Q:   return "Q";
      case GLFW_KEY_R:   return "R";
      case GLFW_KEY_S:   return "S";
      case GLFW_KEY_T:   return "T";
      case GLFW_KEY_U:   return "U";
      case GLFW_KEY_V:   return "V";
      case GLFW_KEY_W:   return "W";
      case GLFW_KEY_X:   return "X";
      case GLFW_KEY_Y:   return "Y";
      case GLFW_KEY_Z:   return "Z";
      case GLFW_KEY_1:   return "1";
      case GLFW_KEY_2:   return "2";
      case GLFW_KEY_3:   return "3";
      case GLFW_KEY_4:   return "4";
      case GLFW_KEY_5:   return "5";
      case GLFW_KEY_6:   return "6";
      case GLFW_KEY_7:   return "7";
      case GLFW_KEY_8:   return "8";
      case GLFW_KEY_9:   return "9";
      case GLFW_KEY_0:   return "0";
      case GLFW_KEY_F1:  return "F1";
      case GLFW_KEY_F2:  return "F2";
      case GLFW_KEY_F3:  return "F3";
      case GLFW_KEY_F4:  return "F4";
      case GLFW_KEY_F5:  return "F5";
      case GLFW_KEY_F6:  return "F6";
      case GLFW_KEY_F7:  return "F7";
      case GLFW_KEY_F8:  return "F8";
      case GLFW_KEY_F9:  return "F9";
      case GLFW_KEY_F10: return "F10";
      case GLFW_KEY_F11: return "F11";
      case GLFW_KEY_F12: return "F12";

      default:           return "";
   }
}

void GenerateShortcutName( char *buffer, int bufferSize, int key, int mods )
{
   buffer[ 0 ] = '\0';

   if( mods & GLFW_MOD_CONTROL ) strncat( buffer, "Ctrl+",  bufferSize - strlen( buffer ) - 1 );
   if( mods & GLFW_MOD_ALT     ) strncat( buffer, "Alt+",   bufferSize - strlen( buffer ) - 1 );
   if( mods & GLFW_MOD_SHIFT   ) strncat( buffer, "Shift+", bufferSize - strlen( buffer ) - 1 );
   if( mods & GLFW_MOD_SUPER   ) strncat( buffer, "Super+", bufferSize - strlen( buffer ) - 1 );

   const char *keyName = get_key_name( key );
   if( keyName )
   {
      strncat( buffer, keyName, bufferSize - strlen( buffer ) - 1 );
   }
   else
   {
      char keyBuf[ 16 ];
      snprintf( keyBuf, sizeof( keyBuf ), "Key_%d", key );
      strncat( buffer, keyBuf, bufferSize - strlen( buffer ) - 1 );
   }
}

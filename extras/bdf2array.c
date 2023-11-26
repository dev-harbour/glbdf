/*
 * Copyright 2020 - 2023 Rafał Jopek ( rafaljopek at hotmail com )
 *
 * STARTFONT 2.1
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main( int argc, char *argv[] )
{
   if( argc < 3 )
   {
      fprintf( stderr, "Usage: %s <input BDF file> <output C file>\n", argv[ 0 ] );
      return 1;
   }

   FILE *inputFile = fopen( argv[ 1 ], "r" );
   if( ! inputFile )
   {
      perror( "Cannot open the input file" );
      return 1;
   }

   FILE *outputFile = fopen( argv[ 2 ], "w" );
   if( ! outputFile )
   {
      printf( "Cannot open the output file" );
      fclose( inputFile );
      return 1;
   }

   char line[ 128 ]; //Note Only 128
   unsigned int chars = 0, pixelSize = 0;
   int lineCount = 0;

   fprintf( outputFile, "/*\n" );
   while( fgets( line, sizeof( line ), inputFile ) != NULL )
   {
      if( lineCount < 4 )
      {
         fprintf( outputFile, " * %s", line );
            lineCount++;
            continue;
      }
      if( strstr( line, "PIXEL_SIZE " ) != NULL )
      {
         sscanf( line, "PIXEL_SIZE %u", &pixelSize );
      }
      if( strstr( line, "CHARS " ) != NULL )
      {
         sscanf( line, "CHARS %u", &chars );
         break;
      }
   }
   fprintf( outputFile, " */\n\n" );

   fseek( inputFile, 0, SEEK_SET );
   memset( line, 0, sizeof( line ) );

   unsigned int encoding = 0, bitmap_index = 0;
   unsigned int bitmap[ pixelSize ];
   int inBitmap = 0;

   fprintf( outputFile, "unsigned int fontData[ %d ][ %d ] = {\n", chars, pixelSize );

   while( fgets( line, sizeof( line ), inputFile ) != NULL )
   {
      if( strncmp( line, "ENCODING ", 9 ) == 0 )
      {
         if( bitmap_index == pixelSize )
         {
            fprintf( outputFile, "   [ %d ] = { ", encoding );
            for( int i = 0; i < pixelSize; i++ )
            {
               fprintf( outputFile, "0x%04X, ", bitmap[ i ] );
            }
            fprintf( outputFile, "},\n" );
         }
         sscanf( line, "ENCODING %u", &encoding );
         bitmap_index = 0;
         inBitmap = 0;
      }
      else if( strncmp( line, "BITMAP", 6 ) == 0 )
      {
         inBitmap = 1;
      }
      else if( inBitmap && bitmap_index < pixelSize )
      {
         sscanf( line, "%x", &bitmap[ bitmap_index++ ] );
      }
   }

   if( bitmap_index == pixelSize )
   {
      fprintf( outputFile, "   [ %d ] = { ", encoding );
      for( int i = 0; i < pixelSize; i++ )
      {
         fprintf( outputFile, "0x%04X, ", bitmap[ i ] );
      }
      fprintf( outputFile, "}\n" );
   }

   fprintf( outputFile, "};\n" );

   fclose( inputFile );
   fclose( outputFile );
   return 0;
}

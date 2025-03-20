// string test program.
#include <iostream>
using std::cout;
using std::endl;

#include <fstream>
using std::ifstream;
using std::ios;

#include <string>
#include "string 2-2.h"

void testAssignment1();
void testAssignment2();
void testAssignment3();
void testAssignment4();
void testAssignment5();
void testAssignment6();
void testAssignment7();
void testAssignment8();

// return true iff string1 == string2
bool equal( string &string1, std::string &string2 );

#if _ITERATOR_DEBUG_LEVEL == 2
int offset = 1;
#else
int offset = 0;
#endif

int capacities[ 31 ];
const unsigned int number = 30;

int main()
{
   ifstream capFile( "capacities.txt", ios::in );

   if( !capFile )
   {
      cout << "File could not be opened" << endl;
      system( "pause" );
      exit( 1 );
   }

   for( int i = 0; i <= number; i++ )
      capFile >> capacities[ i ];

   capFile.close();

   testAssignment1();
   testAssignment2();
   testAssignment3();
   testAssignment4();
   testAssignment5();
   testAssignment6();
   testAssignment7();
   testAssignment8();
   cout << endl;

   system( "pause" );
}

void testAssignment1()
{
   int numErrors = 0;
   for( int s1 = 0; s1 <= 15; s1++ )
   {
      string string1( s1, '\0' ); // string1.mySize = s1; string1.myRes = 15; string1.bx.buf is used
      std::string string2( s1, '\0' );

      for( int i = 0; i < s1; i++ )
      {
         char value = static_cast< char >( 97 + rand() % 26 );
         string1.at( i ) = value; // string1.bx.buf[ i ] = value
         string2[ i ] = value;
      }
      string1.at( s1 ) = '\0'; // string1.bx.buf[ s1 ] = '\0'
      string2[ s1 ] = '\0';

      for( int s2 = 0; s2 <= 15; s2++ )
      {
         string string3( s2, '\0' ); // string3.mySize = s2; string3.myRes = 15; string3.bx.buf is used
         std::string string4( s2, '\0' );

         for( int i = 0; i < s2; i++ )
         {
            char value = static_cast< char >( 97 + rand() % 26 );
            string3.at( i ) = value; // string3.bx.buf[ i ] = value
            string4[ i ] = value;
         }
         string3.at( s2 ) = '\0'; // string3.bx.buf[ s2 ] = '\0'
         string4[ s2 ] = '\0';

         string3.assign( string1 );
         string4.assign( string2 );

         if( !equal( string3, string4 ) )
            numErrors++;
      }
   }

   cout << "There are " << numErrors << " errors.\n";
}

void testAssignment2()
{
   const unsigned int number = 20;
   int numErrors = 0;
   for( int s1 = 0; s1 <= 15; s1++ )
   {
      string string1( s1, '\0' ); // string1.mySize = s1; string1.myRes = 15; string1.bx.buf is used
      std::string string2( s1, '\0' );

      for( int j = 0; j < s1; j++ )
      {
         char value = static_cast< char >( 97 + rand() % 26 );
         string1.at( j ) = value; // string1.bx.buf[ j ] = value
         string2[ j ] = value;
      }
      string1.at( s1 ) = '\0'; // string1.bx.buf[ s ] = '\0'
      string2[ s1 ] = '\0';

      for( int i2 = 1; i2 <= number; i2++ )
      {
         int c2 = capacities[ i2 ]; // c2 >= 31
         for( int s2 = 0; s2 <= c2; s2++ )
         {
            string string3( s2, '\0' ); // string3.mySize = s2
            std::string string4( s2, '\0' );

            char **ptr3 = reinterpret_cast< char ** >( &string3 ); // ptr3 points to string3.bx.ptr or string3.bx.buf
            char **ptr4 = reinterpret_cast< char ** >( &string4 ) + offset;
            if( s2 > 15 ) // string3.myRes > 15; string3.bx.ptr is used
            {
               delete[] *ptr3;
               delete[] *ptr4;
            }
            *ptr3 = new char[ c2 + 1 ];
            *ptr4 = new char[ c2 + 1 ];

            size_t *myCap3;
            size_t *myCap4;
            if( sizeof( size_t ) == 4 )
            {
               myCap3 = reinterpret_cast< size_t * >( &string3 ) + 5; // myCap3 points to string1.myRes
               myCap4 = reinterpret_cast< size_t * >( &string4 ) + 5 + offset;
            }
            else
            {
               myCap3 = reinterpret_cast< size_t * >( &string3 ) + 3; // myCap3 points to string1.myRes
               myCap4 = reinterpret_cast< size_t * >( &string4 ) + 3 + offset;
            }

            *myCap3 = c2; // string3.myRes = c2
            *myCap4 = c2;

            for( int j = 0; j < s2; j++ )
            {
               char value = static_cast< char >( 97 + rand() % 26 );
               string3.at( j ) = value; // string3.bx.ptr[ j ] = value
               string4[ j ] = value;
            }
            string3.at( s2 ) = '\0'; // string3.bx.ptr[ s2 ] = '\0'
            string4[ s2 ] = '\0';

            string3.assign( string1 );
            string4.assign( string2 );

            if( !equal( string3, string4 ) )
               numErrors++;
         }
      }
   }

   cout << "There are " << numErrors << " errors.\n";
}

void testAssignment3()
{
   const unsigned int number = 20;
   int numErrors = 0;
   for( int i1 = 1; i1 <= number; i1++ )
   {
      int c1 = capacities[ i1 ]; // c1 >= 31
      for( int s1 = 0; s1 <= c1; s1++ )
      {
         string string1( s1, '\0' ); // string1.mySize = s1
         std::string string2( s1, '\0' );

         char **ptr1 = reinterpret_cast< char ** >( &string1 ); // ptr1 points to string1.bx.ptr or string1.bx.buf
         char **ptr2 = reinterpret_cast< char ** >( &string2 ) + offset;
         if( s1 > 15 ) // string1.myRes > 15; string1.bx.ptr is used
         {
            delete[] *ptr1;
            delete[] *ptr2;
         }
         *ptr1 = new char[ c1 + 1 ];
         *ptr2 = new char[ c1 + 1 ];

         size_t *myCap1;
         size_t *myCap2;
         if( sizeof( size_t ) == 4 )
         {
            myCap1 = reinterpret_cast< size_t * >( &string1 ) + 5; // myCap1 points to string1.myRes
            myCap2 = reinterpret_cast< size_t * >( &string2 ) + 5 + offset;
         }
         else
         {
            myCap1 = reinterpret_cast< size_t * >( &string1 ) + 3; // myCap1 points to string1.myRes
            myCap2 = reinterpret_cast< size_t * >( &string2 ) + 3 + offset;
         }

         *myCap1 = c1; // string1.myRes = c1
         *myCap2 = c1;

         for( int j = 0; j < s1; j++ )
         {
            char value = static_cast< char >( 97 + rand() % 26 );
            string1.at( j ) = value; // string1.bx.ptr[ j ] = value
            string2[ j ] = value;
         }
         string1.at( s1 ) = '\0'; // string1.bx.ptr[ s1 ] = '\0'
         string2[ s1 ] = '\0';

         for( int s2 = 0; s2 <= 15; s2++ )
         {
            string string3( s2, '\0' ); // string3.mySize = s2; string3.myRes = 15; string3.bx.buf is used
            std::string string4( s2, '\0' );

            for( int j = 0; j < s2; j++ )
            {
               char value = static_cast< char >( 97 + rand() % 26 );
               string3.at( j ) = value; // string3.bx.buf[ j ] = value
               string4[ j ] = value;
            }
            string3.at( s2 ) = '\0'; // string3.bx.buf[ s ] = '\0'
            string4[ s2 ] = '\0';

            string3.assign( string1 );
            string4.assign( string2 );

            if( !equal( string3, string4 ) )
               numErrors++;
         }
      }
   }

   cout << "There are " << numErrors << " errors.\n";
}

void testAssignment4()
{
   const unsigned int number = 4;
   int numErrors = 0;
   for( int i1 = 1; i1 <= number; i1++ )
   {
      int c1 = capacities[ i1 ]; // c1 >= 31
      for( int s1 = 0; s1 <= c1; s1++ )
      {
         string string1( s1, '\0' ); // string1.mySize = s1
         std::string string2( s1, '\0' );

         char **ptr1 = reinterpret_cast< char ** >( &string1 ); // ptr1 points to string1.bx.ptr or string1.bx.buf
         char **ptr2 = reinterpret_cast< char ** >( &string2 ) + offset;
         if( s1 > 15 ) // string1.myRes > 15; string1.bx.ptr is used
         {
            delete[] *ptr1;
            delete[] *ptr2;
         }
         *ptr1 = new char[ c1 + 1 ];
         *ptr2 = new char[ c1 + 1 ];

         size_t *myCap1;
         size_t *myCap2;
         if( sizeof( size_t ) == 4 )
         {
            myCap1 = reinterpret_cast< size_t * >( &string1 ) + 5; // myCap1 points to string1.myRes
            myCap2 = reinterpret_cast< size_t * >( &string2 ) + 5 + offset;
         }
         else
         {
            myCap1 = reinterpret_cast< size_t * >( &string1 ) + 3; // myCap1 points to string1.myRes
            myCap2 = reinterpret_cast< size_t * >( &string2 ) + 3 + offset;
         }

         *myCap1 = c1; // string1.myRes = c1
         *myCap2 = c1;

         for( int j = 0; j < s1; j++ )
         {
            char value = static_cast< char >( 97 + rand() % 26 );
            string1.at( j ) = value; // string1.bx.ptr[ j ] = value
            string2[ j ] = value;
         }
         string1.at( s1 ) = '\0'; // string1.bx.ptr[ s1 ] = '\0'
         string2[ s1 ] = '\0';

         for( int i2 = 1; i2 <= number; i2++ )
         {
            int c2 = capacities[ i2 ]; // c2 >= 31
            for( int s2 = 0; s2 <= c2; s2++ )
            {
               string string3( s2, '\0' );
               std::string string4( s2, '\0' );

               char **ptr3 = reinterpret_cast< char ** >( &string3 ); // ptr3 points to string3.bx.ptr or string3.bx.buf
               char **ptr4 = reinterpret_cast< char ** >( &string4 ) + offset;
               if( s2 > 15 ) // string3.myRes > 15; string3.bx.ptr is used
               {
                  delete[] *ptr3;
                  delete[] *ptr4;
               }
               *ptr3 = new char[ c2 + 1 ];
               *ptr4 = new char[ c2 + 1 ];

               size_t *myCap3;
               size_t *myCap4;
               if( sizeof( size_t ) == 4 )
               {
                  myCap3 = reinterpret_cast< size_t * >( &string3 ) + 5; // myCap3 points to string1.myRes
                  myCap4 = reinterpret_cast< size_t * >( &string4 ) + 5 + offset;
               }
               else
               {
                  myCap3 = reinterpret_cast< size_t * >( &string3 ) + 3; // myCap3 points to string1.myRes
                  myCap4 = reinterpret_cast< size_t * >( &string4 ) + 3 + offset;
               }

               *myCap3 = c2; // string3.myRes = c2
               *myCap4 = c2;

               for( int j = 0; j < s2; j++ )
               {
                  char value = static_cast< char >( 97 + rand() % 26 );
                  string3.at( j ) = value; // string3.bx.ptr[ j ] = value
                  string4[ j ] = value;
               }
               string3.at( s2 ) = '\0'; // string3.bx.ptr[ s2 ] = '\0'
               string4[ s2 ] = '\0';

               string3.assign( string1 );
               string4.assign( string2 );

               if( !equal( string3, string4 ) )
                  numErrors++;
            }
         }
      }
   }

   cout << "There are " << numErrors << " errors.\n";
}

void testAssignment5()
{
   int numErrors = 0;
   for( int s1 = 0; s1 <= 15; s1++ )
   {
      string string1( s1, '\0' ); // string1.mySize = s1; string1.myRes = 15; string1.bx.buf is used

      for( int i = 0; i < s1; i++ )
      {
         char value = static_cast< char >( 97 + rand() % 26 );
         string1.at( i ) = value; // string1.bx.buf[ i ] = value
      }
      string1.at( s1 ) = '\0'; // string1.bx.buf[ s1 ] = '\0'

      for( int s2 = 0; s2 <= 15; s2++ )
      {
         string string2( s2, '\0' ); // string2.mySize = s2; string2.myRes = 15; string2.bx.buf is used

         for( int i = 0; i < s2; i++ )
         {
            char value = static_cast< char >( 97 + rand() % 26 );
            string2.at( i ) = value; // string2.bx.buf[ i ] = value
         }
         string2.at( s2 ) = '\0'; // string2.bx.buf[ s ] = '\0'

         char *p = string2.begin();
         string2.assign( string1 );

         if( string2.capacity() == 15 && string2.begin() != p )
            numErrors++;
      }
   }

   cout << "There are " << numErrors << " errors.\n";
}

void testAssignment6()
{
   const unsigned int number = 30;
   int numErrors = 0;
   for( int s1 = 0; s1 <= 15; s1++ )
   {
      string string1( s1, '\0' ); // string1.mySize = s1; string1.myRes = 15; string1.bx.buf is used

      for( int j = 0; j < s1; j++ )
      {
         char value = static_cast< char >( 97 + rand() % 26 );
         string1.at( j ) = value; // string1.bx.buf[ j ] = value
      }
      string1.at( s1 ) = '\0'; // string1.bx.buf[ s1 ] = '\0'

      for( int i2 = 1; i2 <= number; i2++ )
      {
         int c2 = capacities[ i2 ]; // c2 >= 31
         for( int s2 = 0; s2 <= c2; s2++ )
         {
            string string2( s2, '\0' ); // string2.mySize = s2

            char **ptr2 = reinterpret_cast< char ** >( &string2 ); // ptr2 points to string2.bx.ptr or string2.bx.buf
            if( s2 > 15 ) // string2.myRes > 15; string2.bx.ptr is used
               delete[] *ptr2;
            *ptr2 = new char[ c2 + 1 ];

            size_t *myCap2;
            if( sizeof( size_t ) == 4 )
               myCap2 = reinterpret_cast< size_t * >( &string2 ) + 5; // myCap2 points to string1.myRes
            else
               myCap2 = reinterpret_cast< size_t * >( &string2 ) + 3; // myCap2 points to string1.myRes

            *myCap2 = c2; // string2.myRes = c2

            for( int j = 0; j < s2; j++ )
            {
               char value = static_cast< char >( 97 + rand() % 26 );
               string2.at( j ) = value; // string2.bx.ptr[ j ] = value
            }
            string2.at( s2 ) = '\0'; // string2.bx.ptr[ s2 ] = '\0'

            char *p = string2.begin();
            string2.assign( string1 );

            if( string2.capacity() == c2 && string2.begin() != p )
               numErrors++;
         }
      }
   }

   // string2.begin() != p if and only if
   // the array pointed by string2.bx.ptr before
   // the excution of string2.assign( string1 ) is the same as
   // the array pointed by string2.bx.ptr after
   // the excution of string2.assign( string1 )
   // i.e., there is no memory allocation during
   // the excution of string2.assign( string1 )

   cout << "There are " << numErrors << " errors.\n";
}

void testAssignment7()
{
   const unsigned int number = 30;
   int numErrors = 0;
   for( int i1 = 1; i1 <= number; i1++ )
   {
      int c1 = capacities[ i1 ]; // c1 >= 31
      for( int s1 = 0; s1 <= c1; s1++ )
      {
         string string1( s1, '\0' ); // string1.mySize = s1

         char **ptr1 = reinterpret_cast< char ** >( &string1 ); // ptr1 points to string1.bx.ptr or string1.bx.buf
         if( s1 > 15 ) // string1.myRes > 15; string1.bx.ptr is used
            delete[] *ptr1;
         *ptr1 = new char[ c1 + 1 ];

         size_t *myCap1;
         if( sizeof( size_t ) == 4 )
            myCap1 = reinterpret_cast< size_t * >( &string1 ) + 5; // myCap1 points to string1.myRes
         else
            myCap1 = reinterpret_cast< size_t * >( &string1 ) + 3; // myCap1 points to string1.myRes

         *myCap1 = c1; // string1.myRes = c1

         for( int j = 0; j < s1; j++ )
         {
            char value = static_cast< char >( 97 + rand() % 26 );
            string1.at( j ) = value;
         }
         string1.at( s1 ) = '\0';

         for( int s2 = 0; s2 <= 15; s2++ )
         {
            string string2( s2, '\0' ); // string2.mySize = s2; string2.myRes = 15; string2.bx.buf is used

            for( int j = 0; j < s2; j++ )
            {
               char value = static_cast< char >( 97 + rand() % 26 );
               string2.at( j ) = value; // string2.bx.ptr[ j ] = value
            }
            string2.at( s2 ) = '\0'; // string2.bx.ptr[ s2 ] = '\0'

            char *p = string2.begin();
            string2.assign( string1 );

            if( string2.capacity() == 15 && string2.begin() != p )
               numErrors++;
         }
      }
   }

   // string2.begin() != p if and only if
   // the array pointed by string2.bx.ptr before
   // the excution of string2.assign( string1 ) is the same as
   // the array pointed by string2.bx.ptr after
   // the excution of string2.assign( string1 )
   // i.e., there is no memory allocation during
   // the excution of string2.assign( string1 )

   cout << "There are " << numErrors << " errors.\n";
}

void testAssignment8()
{
   const unsigned int number = 5;
   int numErrors = 0;
   for( int i1 = 1; i1 <= number; i1++ )
   {
      int c1 = capacities[ i1 ]; // c1 >= 31
      for( int s1 = 0; s1 <= c1; s1++ )
      {
         string string1( s1, '\0' ); // string1.mySize = s1

         char **ptr1 = reinterpret_cast< char ** >( &string1 ); // ptr1 points to string1.bx.ptr or string1.bx.buf
         if( s1 > 15 ) // string1.myRes > 15; string1.bx.ptr is used
            delete[] *ptr1;
         *ptr1 = new char[ c1 + 1 ];

         size_t *myCap1;
         if( sizeof( size_t ) == 4 )
            myCap1 = reinterpret_cast< size_t * >( &string1 ) + 5; // myCap1 points to string1.myRes
         else
            myCap1 = reinterpret_cast< size_t * >( &string1 ) + 3; // myCap1 points to string1.myRes

         *myCap1 = c1; // string1.myRes = c1

         for( int j = 0; j < s1; j++ )
         {
            char value = static_cast< char >( 97 + rand() % 26 );
            string1.at( j ) = value; // string1.bx.ptr[ j ] = value
         }
         string1.at( s1 ) = '\0'; // string1.bx.ptr[ s1 ] = '\0'

         for( int i2 = 1; i2 <= number; i2++ )
         {
            int c2 = capacities[ i2 ]; // c2 >= 31
            for( int s2 = 0; s2 <= c2; s2++ )
            {
               string string2( s2, '\0' ); // string2.mySize = s2

               char **ptr2 = reinterpret_cast< char ** >( &string2 );
               if( s2 > 15 ) // string2.myRes > 15; string2.bx.ptr is used
                  delete[] *ptr2;
               *ptr2 = new char[ c2 + 1 ];

               size_t *myCap2;
               if( sizeof( size_t ) == 4 )
                  myCap2 = reinterpret_cast< size_t * >( &string2 ) + 5; // myCap2 points to string1.myRes
               else
                  myCap2 = reinterpret_cast< size_t * >( &string2 ) + 3; // myCap2 points to string1.myRes

               *myCap2 = c2; // string2.myRes = c2

               for( int j = 0; j < s2; j++ )
               {
                  char value = static_cast< char >( 97 + rand() % 26 );
                  string2.at( j ) = value; // string2.bx.ptr[ j ] = value
               }
               string2.at( s2 ) = '\0'; // string2.bx.ptr[ s2 ] = '\0'

               char *p = string2.begin();
               string2.assign( string1 );

               if( string2.capacity() == c2 && string2.begin() != p )
                  numErrors++;
            }
         }
      }
   }

   // string2.begin() != p if and only if
   // the array pointed by string2.bx.ptr before
   // the excution of string2.assign( string1 ) is the same as
   // the array pointed by string2.bx.ptr after
   // the excution of string2.assign( string1 )
   // i.e., there is no memory allocation during
   // the excution of string2.assign( string1 )

   cout << "There are " << numErrors << " errors.\n";
}

// return true iff string1 == string2
bool equal( string &string1, std::string &string2 )
{
   if( string1.capacity() != string2.capacity() )
      return false;

   if( string1.size() != string2.size() )
      return false;

   if( string2.size() == 0 )
      return true;

   for( size_t i = 0; i <= string2.size(); i++ )
      if( string1.at( i ) != string2[ i ] )
         return false;

   return true;
}
#define BYTEPOS(val,pos)                ( ( ( val ) >> ( ( pos ) << 3 ) ) &0xFF )
#define BYTE( data, pos )               (*(unsigned char *)((data)+(pos)))
#define HALF( data, pos )               (*(unsigned short *)((data)+(pos)))
#define WORD( data, pos )               (*(unsigned int *)((data)+(pos)))


#define GET_BYTE( data, pos )           ( ( (unsigned char *)( data ) )[pos] )
#define GET_HALF( data, pos )           ( ( GET_BYTE ( data, ( ( pos ) + 1 ) ) << 8 ) | GET_BYTE ( data, ( pos ) ) )
#define GET_WORD( data, pos )           ( ( GET_HALF ( data, ( ( pos ) + 2 ) ) << 16 ) | GET_HALF ( data, ( pos ) ) )
#define SET_BYTE( data, pos, val )      do { ( (unsigned char *)( data ) )[pos] = val; } while ( 0 )
#define SET_HALF( data, pos, val )      do { SET_BYTE ( data, ( pos ) + 1, ( ( val ) >> 8 ) & 0xFF ); SET_BYTE ( data, ( pos ), ( val ) & 0xFF ); } while ( 0 )
#define SET_WORD( data, pos, val )      do { SET_HALF ( data, ( pos ) + 2, ( ( val ) >> 16 ) & 0xFFFF ); SET_HALF ( data, ( pos ), ( val ) & 0xFFFF ); } while ( 0 )
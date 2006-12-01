#include "Vfs_File.h"

Vfs_File_Reader::Vfs_File_Reader() : file_( 0 ), owned_file_( 0 ) { }

Vfs_File_Reader::~Vfs_File_Reader() { close(); }

void Vfs_File_Reader::reset( VFSFile* f )
{
	close();
	file_ = f;
}

Vfs_File_Reader::error_t Vfs_File_Reader::open( const char* path )
{
	close();
	file_ = owned_file_ = vfs_fopen( path, "rb" );
	if ( !file_ )
		return "Couldn't open file";
	return 0;
}

long Vfs_File_Reader::size() const
{
	long pos = tell();
	vfs_fseek( file_, 0, SEEK_END );
	long result = tell();
	vfs_fseek( file_, pos, SEEK_SET );
	return result;
}

long Vfs_File_Reader::read_avail( void* p, long s )
{
	return (long) vfs_fread( p, 1, s, file_ );
}

long Vfs_File_Reader::tell() const
{
	return vfs_ftell( file_ );
}

Vfs_File_Reader::error_t Vfs_File_Reader::seek( long n )
{
	if ( n == 0 ) // optimization
		vfs_rewind( file_ );
	else if ( vfs_fseek( file_, n, SEEK_SET ) != 0 )
		return "Error seeking in file";
	return 0;
}

void Vfs_File_Reader::close()
{
	file_ = 0;
	if ( owned_file_ )
	{
		vfs_fclose( owned_file_ );
		owned_file_ = 0;
	}
}

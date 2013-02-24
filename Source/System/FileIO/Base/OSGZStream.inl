
OSG_BEGIN_NAMESPACE

//*****************************************************************************
//  template class basic_zip_streambuf
//*****************************************************************************

//-----------------------------------------------------------------------------
// PUBLIC
//-----------------------------------------------------------------------------

/* Construct a zip stream
 * More info on the following parameters can be found in the zlib documentation.
 */

template <class charT, class traits> inline
basic_zip_streambuf<charT, 
                    traits>::basic_zip_streambuf(ostream_reference ostream,
                                                 int               level,
                                                 EStrategy         strategy,
                                                 int               window_size,
                                                 int               memory_level,
                                                 size_t            buffer_size )
    : _ostream(ostream),
      _output_buffer(buffer_size, 0),
      _buffer(buffer_size, 0),
      _crc(0)
{
    _zip_stream.zalloc = NULL;
    _zip_stream.zfree = NULL;

    _zip_stream.next_in = NULL;
    _zip_stream.avail_in = 0;
    _zip_stream.avail_out = 0;
    _zip_stream.next_out = NULL;

    if(level > 9)
        level = 9;
        
    if(memory_level > 9)
        memory_level = 9;
        
    _err=deflateInit2(&_zip_stream, level, Z_DEFLATED,
                      window_size, memory_level,
                      static_cast<int>(strategy));

    this->setp( &(_buffer[0]), &(_buffer[_buffer.size()-1]));
}

/* Destructor
 */
template <class charT, class traits> inline
basic_zip_streambuf<charT, traits>::~basic_zip_streambuf(void)
{
    flush();
    _ostream.flush();
    _err=deflateEnd(&_zip_stream);
}

/* Do the synchronization
 * @todo
 * document correctly!
 */
template <class charT, class traits> inline
int basic_zip_streambuf<charT, traits>::sync(void)
{ 
    if(this->pptr() && this->pptr() > this->pbase()) 
    {
        /*int c =*/ overflow(EOF);

        // ACHTUNG wenn das drin ist hoert er nach dem ersten endl auf!
        /*
          if ( c == EOF)
          return -1;
        */
    }

    return 0;
}

/* <unknown purpose>
 * @todo
 * document correctly!
 */
template <class charT, class traits> inline
typename basic_zip_streambuf<charT, traits>::int_type
basic_zip_streambuf<charT, traits>::overflow(int_type c)
{ 
    int w = static_cast<int>(this->pptr() - this->pbase());
    if (c != EOF)
    {
        *this->pptr() = c;
        ++w;
    }
    if (zip_to_stream(this->pbase(), w))
    {
        this->setp(this->pbase(), this->epptr() - 1);
        return c;
    }
    else
    {
        return EOF;
    }
}

/* flushes the zip buffer and output buffer.
 *
 *    This method should be called at the end of the compression. Calling flush
 *    multiple times, will lower the compression ratio.
 */
template <class charT, class traits> inline
std::streamsize basic_zip_streambuf<charT, traits>::flush(void)
{
    std::streamsize written_byte_size = 0, total_written_byte_size = 0;

    size_t remainder = 0;

    // updating crc
    _crc = crc32(_crc,  _zip_stream.next_in,
                 _zip_stream.avail_in);        

    do
    {
        _err = deflate(&_zip_stream, Z_FINISH);
        if(_err == Z_OK || _err == Z_STREAM_END)
        {
            written_byte_size = static_cast<std::streamsize>(_output_buffer.size()) - _zip_stream.avail_out;
            total_written_byte_size += written_byte_size;
            // ouput buffer is full, dumping to ostream
            _ostream.write( reinterpret_cast<const char_type*>(&(_output_buffer[0])),
                            static_cast<std::streamsize>(written_byte_size/sizeof(char_type)*sizeof(char)));
            
            // checking if some bytes were not written.
            if((remainder = written_byte_size%sizeof(char_type)) != 0)
            {
                // copy to the beginning of the stream
                memcpy(&(_output_buffer[0]), 
                       &(_output_buffer[written_byte_size-remainder]), remainder);
                    
            }
                
            _zip_stream.avail_out = static_cast<uInt>(_output_buffer.size() - remainder);
            _zip_stream.next_out = &_output_buffer[remainder];
        }
    }
    while(_err == Z_OK);

    _ostream.flush();

    return total_written_byte_size;
}

/* returns a reference to the output stream
 */
template <class charT, class traits> inline 
typename basic_zip_streambuf<charT, traits>::ostream_reference
basic_zip_streambuf<charT, traits>::get_ostream(void) const
{
    return _ostream;
}

/* returns the latest zlib error status
 */
template <class charT, class traits> inline
int basic_zip_streambuf<charT, traits>::get_zerr(void) const
{
    return _err;
}

/* returns the crc of the input data compressed so far.
 */
template <class charT, class traits> inline
unsigned long
basic_zip_streambuf<charT, traits>:: get_crc(void) const
{
    return _crc;
}

/*  returns the size (bytes) of the input data compressed so far.
 */
template <class charT, class traits> inline
unsigned long
basic_zip_streambuf<charT, traits>::get_in_size(void) const
{
    return _zip_stream.total_in;
}

/*  returns the size (bytes) of the compressed data so far.
 */
template <class charT, class traits> inline
long 
basic_zip_streambuf<charT, traits>::get_out_size(void) const
{
    return _zip_stream.total_out;
}

//-----------------------------------------------------------------------------
// PRIVATE
//-----------------------------------------------------------------------------

/* <undocumented>
 * @todo
 * document!
 */
template <class charT, class traits> inline
bool basic_zip_streambuf<charT, traits>::zip_to_stream(
    char_type *buffer,
    std::streamsize buffer_size)
{    
    std::streamsize written_byte_size = 0, total_written_byte_size = 0;

    _zip_stream.next_in = reinterpret_cast<byte_buffer_type>(buffer);
    _zip_stream.avail_in = static_cast<uInt>(buffer_size * sizeof(char_type));
    _zip_stream.avail_out = static_cast<uInt>(_output_buffer.size());
    _zip_stream.next_out = &_output_buffer[0];
    size_t remainder = 0;

    // updating crc
    _crc = crc32(_crc, _zip_stream.next_in,
                 _zip_stream.avail_in);        

    do
    {
        _err = deflate(&_zip_stream, 0);
    
        if (_err == Z_OK  || _err == Z_STREAM_END)
        {
            written_byte_size= static_cast<std::streamsize>(_output_buffer.size()) -
                _zip_stream.avail_out;
            total_written_byte_size += written_byte_size;
            // ouput buffer is full, dumping to ostream

            _ostream.write(reinterpret_cast<const char_type*>(&_output_buffer[0]), 
                           static_cast<std::streamsize>(written_byte_size / sizeof(char_type)));
                                                
            // checking if some bytes were not written.
            if((remainder = written_byte_size % sizeof(char_type)) != 0)
            {
                // copy to the beginning of the stream
                memcpy(&_output_buffer[0], 
                       &_output_buffer[written_byte_size-remainder],
                       remainder);
            }
                
            _zip_stream.avail_out = static_cast<uInt>(_output_buffer.size()-remainder);
            _zip_stream.next_out = &_output_buffer[remainder];
        }
    } 
    while(_zip_stream.avail_in != 0 && _err == Z_OK);
    
    return _err == Z_OK;
}







//*****************************************************************************
//  template class basic_unzip_streambuf
//*****************************************************************************

//-----------------------------------------------------------------------------
// PUBLIC
//-----------------------------------------------------------------------------

/* Constructor
 */
template <class charT, class traits> inline
basic_unzip_streambuf<charT, traits>::basic_unzip_streambuf(istream_reference istream,
                                                            int window_size,
                                                            size_t read_buffer_size,
                                                            size_t input_buffer_size)
    : _input_buffer(input_buffer_size),
      _buffer(read_buffer_size),
      _streamType ( UNKNOWN_ST ),
      _istream(istream),
      _crc(0)
{
    // setting zalloc, zfree and opaque
    _zip_stream.zalloc = NULL;
    _zip_stream.zfree = NULL;

    _zip_stream.next_in = NULL;
    _zip_stream.avail_in = 0;
    _zip_stream.avail_out = 0;
    _zip_stream.next_out = NULL;

    _err = inflateInit2(&_zip_stream, window_size);
        
    this->setg(&_buffer[0] + 4,     // beginning of putback area
               &_buffer[0] + 4,     // read position
               &_buffer[0] + 4);    // end position    
}

/*
 * @todo document!
 */
template <class charT, class traits> inline
basic_unzip_streambuf<charT, traits>::~basic_unzip_streambuf(void)
{
    inflateEnd(&_zip_stream);
}


/*
 * @todo document!
 */
template <class charT, class traits> inline
typename basic_unzip_streambuf<charT, traits>::int_type
basic_unzip_streambuf<charT, traits>::underflow(void)
{ 
    if(this->gptr() && ( this->gptr() < this->egptr()))
        return * reinterpret_cast<unsigned char *>(this->gptr());
     
    int n_putback = static_cast<int>(this->gptr() - this->eback());
    if(n_putback > 4)
        n_putback = 4;
       
    memcpy(&_buffer[0] + (4 - n_putback),
           this->gptr() - n_putback,
           n_putback * sizeof(char_type));
  
    int num = 
        unzip_from_stream(&_buffer[0] + 4, 
                          static_cast<std::streamsize>((_buffer.size() - 4) *
                                                       sizeof(char_type)));
        
    if(num <= 0) // ERROR or EOF
        return EOF;
    
    // reset buffer pointers
    this->setg(&_buffer[0] + (4 - n_putback),   // beginning of putback area
               &_buffer[0] + 4,                 // read position
               &_buffer[0] + 4 + num);          // end of buffer
    
    // return next character
    return * reinterpret_cast<unsigned char *>(this->gptr());    
}

/* returns the compressed input istream
 */
template <class charT, class traits> inline
typename basic_unzip_streambuf<charT, traits>::istream_reference
basic_unzip_streambuf<charT, traits>::get_istream(void)
{
    return _istream;
}

/* returns the zlib stream structure
 */
template <class charT, class traits> inline
z_stream &
basic_unzip_streambuf<charT, traits>::get_zip_stream(void)
{
    return _zip_stream;
}

/* returns the latest zlib error state
 */
template <class charT, class traits> inline
int
basic_unzip_streambuf<charT, traits>::get_zerr(void) const
{
    return _err;
}

/* returns the crc of the uncompressed data so far
 */
template <class charT, class traits> inline
unsigned long
basic_unzip_streambuf<charT, traits>::get_crc(void) const
{
    return _crc;
}

/* returns the number of uncompressed bytes
 */
template <class charT, class traits> inline
long
basic_unzip_streambuf<charT, traits>::get_out_size(void) const
{
    return _zip_stream.total_out;
}

/* returns the number of read compressed bytes
 */
template <class charT, class traits> inline
long
basic_unzip_streambuf<charT, traits>::get_in_size(void) const
{
    return _zip_stream.total_in;
}


//-----------------------------------------------------------------------------
// PRIVATE
//-----------------------------------------------------------------------------

/* 
 */
template <class charT, class traits> inline
void
basic_unzip_streambuf<charT, traits>::put_back_from_zip_stream(void)
{
    if(_zip_stream.avail_in == 0)
        return;

    _istream.clear(std::ios::goodbit);
    _istream.seekg(-intf(_zip_stream.avail_in),
                   std::ios_base::cur);

    _zip_stream.avail_in = 0;
}

/* 
 */
template <class charT, class traits> inline
std::streamsize
basic_unzip_streambuf<charT, traits>::unzip_from_stream(char_type* buffer,
                                                        std::streamsize buffer_size)
{
    _zip_stream.next_out  = 
        reinterpret_cast<byte_buffer_type>(buffer);
    _zip_stream.avail_out = 
        static_cast<uInt>(buffer_size * sizeof(char_type));
    size_t count = _zip_stream.avail_in;

    do
    {
        if(_zip_stream.avail_in == 0)
            count=fill_input_buffer();

        if(_zip_stream.avail_in)
        {
          switch (_streamType) {
          case GZIP_ST:            
            _err = inflate(&_zip_stream,  Z_SYNC_FLUSH);
            break;
          case DATA_ST:
            if (_zip_stream.avail_out < count)
              count = _zip_stream.avail_out;
            memcpy ( _zip_stream.next_out, _zip_stream.next_in, count );
            _zip_stream.avail_in  -= count;
            _zip_stream.avail_out -= count;
            _zip_stream.next_in   += count;
            _zip_stream.next_out  += count;
            break;
          default:
            FWARNING (("Unknown _streamType: %d\n", _streamType ));
            break;
          }            
        }
    }
    while(_err==Z_OK && _zip_stream.avail_out != 0 && count != 0);

    // updating crc
    _crc = crc32(_crc, reinterpret_cast<byte_buffer_type>(buffer),
                 buffer_size - _zip_stream.avail_out / sizeof(char_type));
        
    std::streamsize n_read = 
        buffer_size - _zip_stream.avail_out / sizeof(char_type);
        
    // check if it is the end
    if (_err == Z_STREAM_END)
        put_back_from_zip_stream();                
        
    return n_read;
}


/* 
 */
template <class charT, class traits> inline
size_t
basic_unzip_streambuf<charT, traits>::fill_input_buffer(void)
{
    _zip_stream.next_in = &_input_buffer[0];
    _istream.read(reinterpret_cast<char_type*>(&_input_buffer[0]), 
                  static_cast<std::streamsize>(_input_buffer.size() /
                                               sizeof(char_type)));
        
    return _zip_stream.avail_in = _istream.gcount()*sizeof(char_type);
}







//*****************************************************************************
//  template class basic_zip_ostream
//*****************************************************************************

//-----------------------------------------------------------------------------
// PUBLIC
//-----------------------------------------------------------------------------

/*
 */
template <class charT, class traits> inline
basic_zip_ostream<charT, traits>::basic_zip_ostream(ostream_reference ostream,
                                                    bool is_gzip,
                                                    int level,
                                                    EStrategy strategy,
                                                    int window_size,
                                                    int memory_level,
                                                    size_t buffer_size) :
    basic_zip_streambuf<charT, traits>(ostream, level, strategy, window_size,
                                       memory_level, buffer_size),
    std::basic_ostream<charT, traits>(this),
    _is_gzip(is_gzip),
    _added_footer(false)
{
    if(_is_gzip)
        add_header();
}

/* Destructor
 */
template <class charT, class traits> inline
basic_zip_ostream<charT, traits>::~basic_zip_ostream(void)
{
    if(_is_gzip)
        add_footer();
}

/* returns true if it is a gzip
 */
template <class charT, class traits> inline
bool basic_zip_ostream<charT, traits>::is_gzip(void) const
{
    return _is_gzip;
}

/* flush inner buffer and zipper buffer
 */

template <class charT, class traits> inline
basic_zip_ostream<charT, traits>& basic_zip_ostream<charT, traits>::zflush(void)
{
    std::basic_ostream<charT, traits>::flush();
    basic_zip_streambuf<charT, traits>::flush();
    return *this;
}

template <class charT, class traits> inline
void basic_zip_ostream<charT, traits>::finished(void)
{
    if(_is_gzip)
        add_footer();
    else
        zflush();
}


//-----------------------------------------------------------------------------
// PRIVATE
//-----------------------------------------------------------------------------

/*
 * @todo document!
 */
template <class charT, class traits> inline
basic_zip_ostream<charT,traits>& basic_zip_ostream<charT, traits>::add_header(void)
{
    char_type zero = 0;
        
    this->get_ostream() << static_cast<char_type>(detail::gz_magic[0])
                        << static_cast<char_type>(detail::gz_magic[1])
                        << static_cast<char_type>(Z_DEFLATED)
                        << zero //flags
                        << zero<<zero<<zero<<zero // time
                        << zero //xflags
                        << static_cast<char_type>(OS_CODE);
        
    return *this;
}

/*
 * @todo document!
 */
template <class charT, class traits> inline
basic_zip_ostream<charT,traits>& basic_zip_ostream<charT, traits>::add_footer(void)
{
    if(_added_footer)
        return *this;

    zflush();

    _added_footer = true;

    // Writes crc and length in LSB order to the stream.
    unsigned long crc = this->get_crc();
    for(int n=0;n<4;++n)
    {
        this->get_ostream().put(int(crc & 0xff));
        crc >>= 8;
    }

    unsigned long length = this->get_in_size();
    for(int n=0;n<4;++n)
    {
        this->get_ostream().put(int(length & 0xff));
        length >>= 8;
    }

    return *this;
}






//*****************************************************************************
//  template class basic_zip_istream
//*****************************************************************************

//-----------------------------------------------------------------------------
// PUBLIC
//-----------------------------------------------------------------------------

/* Constructor
 */
template <class charT, class traits> inline
basic_zip_istream<charT, traits>::basic_zip_istream(istream_reference istream,
                                                    int window_size,
                                                    size_t read_buffer_size,
                                                    size_t input_buffer_size)
    : basic_unzip_streambuf<charT, traits>(istream, window_size,
                                           read_buffer_size, input_buffer_size),
      std::basic_istream<charT, traits>(this),
      _is_gzip(false),
      _gzip_crc(0),
      _gzip_data_size(0)
{
    if(this->get_zerr() == Z_OK)
        check_header();
}

/* returns true if it is a gzip file
 */
template <class charT, class traits> inline
bool
basic_zip_istream<charT, traits>::is_gzip(void) const
{
    return _is_gzip;
}

/* return crc check result
 *
 * This must be called after the reading of compressed data is finished!  This
 * method compares it to the crc of the uncompressed data.
 *
 *    \return true if crc check is succesful
 */
template <class charT, class traits> inline
bool
basic_zip_istream<charT, traits>::check_crc(void)
{
    read_footer();
    return this->get_crc() == static_cast<unsigned long>(_gzip_crc);
}

/* return data size check
 */
template <class charT, class traits> inline
bool
basic_zip_istream<charT, traits>::check_data_size(void) const
{
    return this->get_out_size() == _gzip_data_size;
}

/* return the crc value in the file
 */
template <class charT, class traits> inline
long
basic_zip_istream<charT, traits>::get_gzip_crc(void) const
{
    return _gzip_crc;
}

/* return the data size in the file
 */
template <class charT, class traits> inline
long
basic_zip_istream<charT, traits>::get_gzip_data_size(void) const
{
    return _gzip_data_size;
}

//-----------------------------------------------------------------------------
// PROTECTED
//-----------------------------------------------------------------------------

/*
 * @todo document!
 */
template <class charT, class traits> inline
int
basic_zip_istream<charT, traits>::check_header(void)
{
    int method; /* method byte */
    int flags;  /* flags byte */
    uInt len;
    int c;
    int err=0;
    z_stream &zip_stream = this->get_zip_stream();

    /* Check the gzip magic header */
    zip_stream.next_in = &this->_input_buffer[0];
    this->get_istream().read( reinterpret_cast<char*>(&this->_input_buffer[0]), 2 );
    zip_stream.avail_in = this->get_istream().gcount();

    if ( (zip_stream.avail_in >= 2) &&
         (this->_input_buffer[0] == detail::gz_magic[0]) &&
         (this->_input_buffer[1] == detail::gz_magic[1]) ) {      
      this->_streamType = BufferType::GZIP_ST;
      zip_stream.avail_in = 0;
    } 
    else {
      this->_streamType = BufferType::DATA_ST;            
      _is_gzip = false;
      err = zip_stream.avail_in != 0 ? Z_OK : Z_STREAM_END;
      return err;
    }
    
    _is_gzip = true;
    method = int(this->get_istream().get());
    flags  = int(this->get_istream().get());
    if (method != Z_DEFLATED || (flags & detail::gz_reserved) != 0) 
    {
        err = Z_DATA_ERROR;
        return err;
    }

    /* Discard time, xflags and OS code: */
    for (len = 0; len < 6; len++) 
        this->get_istream().get();
    
    if ((flags & detail::gz_extra_field) != 0) 
    { 
        /* skip the extra field */
        len  =  uInt(this->get_istream().get());
        len += uInt(this->get_istream().get())<<8;
        /* len is garbage if EOF but the loop below will quit anyway */
        while (len-- != 0 && this->get_istream().get() != EOF) ;
    }
    if ((flags & detail::gz_orig_name) != 0) 
    { 
        /* skip the original file name */
        while ((c = this->get_istream().get()) != 0 && c != EOF) ;
    }
    if ((flags & detail::gz_comment) != 0) 
    {   
        /* skip the .gz file comment */
        while ((c = this->get_istream().get()) != 0 && c != EOF) ;
    }
    if ((flags & detail::gz_head_crc) != 0) 
    {  /* skip the header crc */
        for (len = 0; len < 2; len++) 
            this->get_istream().get();
    }
    err = this->get_istream().eof() ? Z_DATA_ERROR : Z_OK;

    return err;
}

/*
 * @todo document!
 */
template <class charT, class traits> inline
void
basic_zip_istream<charT, traits>::read_footer(void)
{        
    if(_is_gzip)
    {
        _gzip_crc = 0;
        for(int n=0;n<4;++n)
            _gzip_crc += ((int(this->get_istream().get()) & 0xff) << (8*n));

        _gzip_data_size = 0;
        for(int n=0;n<4;++n)
            _gzip_data_size += 
                ((int(this->get_istream().get()) & 0xff) << (8*n));
    }
}

OSG_END_NAMESPACE

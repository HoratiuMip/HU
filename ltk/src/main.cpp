#include <iostream>
#include <string>
#include <string.h>
#include <string_view>
#include <utility>


#define DEFAULT_URL "https://www.n2yo.com/?s=%"


#define LOG ( std::cout << "[HU-LTK]: " )
#define ASSERT( c, m, r ) { if( !(c) ) { LOG << ( "Assert (" #c ") failed: " ) << m << std::endl; return r; } }


struct _IDXS {
    const char*   id;
    const char*   name;
} gIDXs[] = {
    { id: "25338", name: "NOAA-15" },
    { id: "28654", name: "NOAA-18" },
    { id: "33591", name: "NOAA-19" }
};
constexpr int IDX_COUNT = sizeof( gIDXs ) / sizeof( _IDXS );
std::string   URL       = DEFAULT_URL;


static bool _url_has_percent( const char* url );
static void _launch_tracker( _IDXS& idx );


int ltk_main( int argc, char* argv[] ) {
    static struct _OPTS {
        const char*   name;
        bool          arg;
    } opts[] = {
        { name: "url", arg: true }
    };

    int opt_idx = 0;
l_start: {
    char**           popt = argv + opt_idx;
    char**           parg = popt + 1;
    std::string_view opt  = *popt;

    switch(
        ( opt.starts_with( "--" ) << 0 )
        |
        ( opt.starts_with( ":" ) << 1 )
        |
        ( opt.starts_with( "/" ) << 2 )
    ) { 
        case 1: {
            ASSERT( opt_idx + 1 != argc, "Missing argument.", -1 );

            URL = *parg;

            ASSERT( _url_has_percent( URL.c_str() ), "URL must have a \'%\', which will be replaced with the NORAD id.", -1 );
        break; }

        case 2: {
            int off = atoi( *popt + 1 );

            ASSERT( off >= 0 && off < IDX_COUNT, "Offset (" << off << ") out of bounds.", -1 );

            _launch_tracker( gIDXs[ off ] );
        break; }

        case 4: {
            const char* name = *popt + 1;

            _IDXS* idx = std::find_if( gIDXs, gIDXs + IDX_COUNT, [ &name ] ( _IDXS& idx ) -> bool {
                return strcmp( idx.name, name ) == 0;
            } );

            ASSERT( idx != gIDXs + IDX_COUNT, "Name (" << name << ") not found.", -1 );

            _launch_tracker( *idx );
        break; }
    }

    if( ++opt_idx < argc )
        goto l_start; 
}
l_end:
    return 0;
}


int main( int argc, char* argv[] ) {
    LOG << "Launching trackers...\n";

    int status = ltk_main( argc, argv );

    LOG << "Exiting with status: " << status << ".\n";

    return status;
}


static bool _url_has_percent( const char* url ) {
    if( url == nullptr )
        url = URL.c_str();

    return std::string_view{ url }.find( "%" ) != std::string_view::npos;
}

static void _launch_tracker( _IDXS& idx ) {
    using namespace std::string_literals;

    std::string url{ URL };

    ASSERT( _url_has_percent( url.c_str() ), "URL has no \'%\' to be replaced.", ; );

    url.replace( URL.find( '%' ), 1, idx.id );
    LOG << "Generated URL: \"" << url << "\".\n";

    auto cmd = "start "s + url;
    LOG << "Executing: \"" << cmd << "\".\n";
    std::system( cmd.c_str() );
}

/*

Text std::istream, std::ostream serializer.

Copyright (C) 2016 Sergey Kolevatov

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program. If not, see <http://www.gnu.org/licenses/>.

*/

// $Revision: 7939 $ $Date:: 2017-09-28 #$ $Author: serge $

#include "serializer.h"     // self

#include <stdexcept>        // std::invalid_argument

NAMESPACE_SERIALIZER_START

std::string * load( std::istream & is, std::string * e )
{
    if( e == nullptr )
        throw std::invalid_argument( "load: std::string: argument is null" );

    std::string & res = * e;

    is >> res;

    if( is.fail() )
        return nullptr;

    return e;
}

bool save( std::ostream & os, const std::string & e )
{
    os << e << " ";

    if( os.fail() )
        return false;

    return true;
}

uint32_t * load( std::istream & is, uint32_t * e )
{
    return load_pod( is, e );
}

bool save( std::ostream & os, const uint32_t e )
{
    return save_pod( os, e );
}

uint64_t * load( std::istream & is, uint64_t * e )
{
    return load_pod( is, e );
}

bool save( std::ostream & os, const uint64_t e )
{
    return save_pod( os, e );
}

int32_t * load( std::istream & is, int32_t * e )
{
    return load_pod( is, e );
}

bool save( std::ostream & os, const int32_t e )
{
    return save_pod( os, e );
}

int64_t * load( std::istream & is, int64_t * e )
{
    return load_pod( is, e );
}

bool save( std::ostream & os, const int64_t e )
{
    return save_pod( os, e );
}

NAMESPACE_SERIALIZER_END

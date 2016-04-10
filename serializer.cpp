/*

Text std::isteram, std::osteram serializer.

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

// $Revision: 3721 $ $Date:: 2016-04-10 #$ $Author: serge $

#include "serializer.h"     // self

#include <stdexcept>        // std::invalid_argument

using namespace serializer;

std::string * load( std::istream & is, std::string * e )
{
    if( e == nullptr )
        throw std::invalid_argument( "load: argument is null" );

    std::string & res = * e;

    is >> res;

    if( is.fail() )
        return nullptr;

    return e;
}

bool save( std::ostream & os, const std::string * e )
{
    os << *e << " ";

    if( os.fail() )
        return false;

    return true;
}

uint32_t * load( std::istream & is, uint32_t * e )
{
    if( e == nullptr )
        throw std::invalid_argument( "load: argument is null" );

    uint32_t res;

    is >> res;

    if( is.fail() )
        return nullptr;

    *e = res;

    return e;
}

bool save( std::ostream & os, const uint32_t e )
{
    os << e << " ";

    if( os.fail() )
        return false;

    return true;
}

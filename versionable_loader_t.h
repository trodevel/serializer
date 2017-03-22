/*

Versionable Loader.

Copyright (C) 2017 Sergey Kolevatov

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

// $Revision: 6138 $ $Date:: 2017-03-20 #$ $Author: serge $

#ifndef SERIALIZER_VERSIONABLE_LOADER_T_H
#define SERIALIZER_VERSIONABLE_LOADER_T_H

#include <iostream>         // std::istream
#include <stdexcept>        // std::runtime_error
#include <string>           // std::to_string

#include "namespace_lib.h"  // NAMESPACE_SERIALIZER_START

NAMESPACE_SERIALIZER_START

template <class C>
class VersionableLoaderT
{
public:

    typedef C Plug;

    template <class T>
    static T* load_t_1( std::istream & is, T* e )
    {
        unsigned int    version;

        is >> version;

        if( is.fail() )
            return nullptr;

        switch( version )
        {
        case 1:
            return Plug::load_1( is, e );
        default:
            throw std::runtime_error( "unsupported version " + std::to_string( version ) );
            break;
        }

        return nullptr;
    }

    template <class T>
    static T* load_t_1_2( std::istream & is, T* e )
    {
        unsigned int    version;

        is >> version;

        if( is.fail() )
            return nullptr;

        switch( version )
        {
        case 1:
            return Plug::load_1( is, e );
        case 2:
            return Plug::load_2( is, e );
        default:
            throw std::runtime_error( "unsupported version " + std::to_string( version ) );
            break;
        }

        return nullptr;
    }
};

NAMESPACE_SERIALIZER_END

#endif // SERIALIZER_VERSIONABLE_LOADER_T_H

/*

Text std::isteram, std::isteram serializer.

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

// $Revision: 3720 $ $Date:: 2016-04-10 #$ $Author: serge $

#ifndef SERIALIZER_SERIALIZER_H
#define SERIALIZER_SERIALIZER_H

#include <iostream>         // std::istream
#include <string>           // std::string
#include <vector>           // std::vector
#include <map>              // std::map
#include <cstdint>          // uint32_t

#include "namespace_lib.h"  // NAMESPACE_SERIALIZER_START

NAMESPACE_SERIALIZER_START

std::string * load( std::istream & is, std::string * e );
bool save( std::ostream & os, const std::string * e );

uint32_t * load( std::istream & is, uint32_t * e );
bool save( std::ostream & os, const uint32_t e );

template <class _T,class _V>
std::map<_T,_V>* load( std::istream & is, std::map<_T,_V> * e )
{
    typedef typename std::map<_T,_V> _C;
    typename _C::size_type size;

    is >> size;

    if( is.fail() )
        return nullptr;

    for( typename _C::size_type i = 0; i < size; ++i )
    {
        typename _C::key_type k;
        typename _C::mapped_type v;

        {
            auto b = load( is, & k );
            if( b == nullptr )
                return nullptr;
        }

        {
            auto b = load( is, & v );
            if( b == nullptr )
                return nullptr;
        }

        typename _C::value_type el( k, v );

        e->insert( el );
    }

    return e;
}

template <class _T>
std::vector<_T>* load( std::istream & is, std::vector<_T> * e )
{
    typename std::vector<_T>::size_type size;

    std::vector<_T> & er = *e;

    is >> size;

    if( is.fail() )
        return nullptr;

    er.resize( size );

    for( typename std::vector<_T>::size_type i = 0; i < size; ++i )
    {
        auto b = load( is, & er[ i ] );

        if( b == nullptr )
            return nullptr;
    }

    return e;
}

template <class _T>
bool save( std::ostream & os, const std::vector<_T> * e )
{
    const std::vector<_T> & er = *e;

    os << er.size() << "\n";

    for( auto & el: er )
    {
        bool b = save( os, el );

        os << "\n";

        if( b == false )
            return false;
    }

    return true;
}

NAMESPACE_SERIALIZER_END

#endif // SERIALIZER_SERIALIZER_H

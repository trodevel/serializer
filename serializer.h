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

// $Revision: 8322 $ $Date:: 2017-11-09 #$ $Author: serge $

#ifndef SERIALIZER_SERIALIZER_H
#define SERIALIZER_SERIALIZER_H

#include <iostream>         // std::istream
#include <string>           // std::string
#include <vector>           // std::vector
#include <map>              // std::map
#include <cstdint>          // uint32_t
#include <memory>

#include "namespace_lib.h"  // NAMESPACE_SERIALIZER_START

NAMESPACE_SERIALIZER_START

template <class _T>
std::shared_ptr<_T> * load( std::istream & is, std::shared_ptr<_T> * e )
{
    _T * t = load( is, (_T*) nullptr );

    if( t == nullptr )
        return nullptr;

    e->reset( t );

    return e;
}

template <class _T>
bool save( std::ostream & os, const std::shared_ptr<_T> e )
{
    return save( os, e.get() );
}


std::string * load( std::istream & is, std::string * e );
bool save( std::ostream & os, const std::string & e );

template <class T>
T * load_pod( std::istream & is, T * e )
{
    if( e == nullptr )
        throw std::invalid_argument( "load_pod: argument is null" );

    T res;

    is >> res;

    if( is.fail() )
        return nullptr;

    *e = res;

    return e;
}

template <class T>
bool save_pod( std::ostream & os, const T & e )
{
    os << e << " ";

    if( os.fail() )
        return false;

    return true;
}

uint32_t * load( std::istream & is, uint32_t * e );
bool save( std::ostream & os, const uint32_t e );

uint64_t * load( std::istream & is, uint64_t * e );
bool save( std::ostream & os, const uint64_t e );

int32_t * load( std::istream & is, int32_t * e );
bool save( std::ostream & os, const int32_t e );

int64_t * load( std::istream & is, int64_t * e );
bool save( std::ostream & os, const int64_t e );


template <class _T,class _V>
bool save( std::ostream & os, const std::pair<_T,_V> & e )
{
    bool b = save( os, e.first );

    if( b == false )
        return false;

    b = save( os, e.second );

    if( b == false )
        return false;

    return true;
}

template <class _T,class _V>
std::pair<const _T,_V> * load( std::istream & is, std::pair<const _T,_V> * e )
{
    if( e == nullptr )
        throw std::invalid_argument( "load: argument is null" );

    {
        auto b = load( is, const_cast<_T*>( & e->first ) );
        if( b == nullptr )
            return nullptr;
    }

    {
        auto b = load( is, & e->second );
        if( b == nullptr )
            return nullptr;
    }

    return e;
}

template <class _T,class _V>
std::pair<_T,_V> * load( std::istream & is, std::pair<_T,_V> * e )
{
    if( e == nullptr )
        throw std::invalid_argument( "load: argument is null" );

    {
        auto b = load( is, & e->first );
        if( b == nullptr )
            return nullptr;
    }

    {
        auto b = load( is, & e->second );
        if( b == nullptr )
            return nullptr;
    }

    return e;
}

template< class T >
bool generic_saver( std::ostream& os, const T & e )
{
    return save( os, e );
}

template< class T >
T* generic_loader( std::istream& is, T * e )
{
    return load( is, e );
}

template <bool BREAKLINE = false, class _IT, class Saver>
bool save_iter( std::ostream & os, _IT first, _IT last, Saver saver )
{
    auto size = std::distance( first, last );

    save( os, size );

    if( BREAKLINE )
    {
        os << "\n";
    }

    auto & it = first;

    for( ; it != last; ++it )
    {
        bool b = saver( os, *it );

        if( b == false )
            return false;

        if( BREAKLINE )
        {
            os << "\n";
        }
    }

    return true;
}

template <bool BREAKLINE = false, class C, class Saver>
bool save_cont( std::ostream & os, const C & c, Saver saver )
{
    return save_iter<BREAKLINE>( os, c.begin(), c.end(), saver );
}

template <class C, class Loader>
C* load_cont( std::istream & is, C * c, Loader loader )
{
    if( c == nullptr )
        throw std::invalid_argument( "load_cont: argument is null" );

    typename C::size_type size;

    is >> size;

    if( is.fail() )
        return nullptr;

    for( typename C::size_type i = 0; i < size; ++i )
    {
        typename C::value_type el;

        auto b = loader( is, & el );
        if( b == nullptr )
            return nullptr;

        c->insert( c->end(), el );
    }

    return c;
}

template <class _T,class _V>
std::map<_T,_V>* load( std::istream & is, std::map<_T,_V> * e )
{
    return load_cont( is, e, generic_loader<typename std::map<_T,_V>::value_type> );
}

template <bool BREAKLINE = false, class _T,class _V>
bool save( std::ostream & os, const std::map<_T,_V> & e )
{
    return save_cont<BREAKLINE>( os, e, generic_saver<typename std::map<_T,_V>::value_type>  );
}

template <class _T>
std::vector<_T>* load( std::istream & is, std::vector<_T> * e )
{
    return load_cont( is, e, generic_loader<typename std::vector<_T>::value_type> );
}

template <bool BREAKLINE = false, class _T>
bool save( std::ostream & os, const std::vector<_T> & e )
{
    return save_cont<BREAKLINE>( os, e, generic_saver<typename std::vector<_T>::value_type>  );
}

NAMESPACE_SERIALIZER_END

#endif // SERIALIZER_SERIALIZER_H

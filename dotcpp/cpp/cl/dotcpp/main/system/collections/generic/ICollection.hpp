﻿/*
Copyright (C) 2003-2015 CompatibL

This file is part of .C++, a native C++ implementation of
selected .NET class library APIs with built-in support for
algorithmic differentiation (AD), available from

    http://github.com/dotcpp/dotcpp (source)
    http://dotcpp.org (documentation)

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/

#ifndef cl_dotcpp_main_ICollection_hpp
#define cl_dotcpp_main_ICollection_hpp

#include <cl/dotcpp/main/declare.hpp>
#include <cl/dotcpp/main/system/collections/generic/IEnumerable.hpp>

namespace cl
{
    template <class T> class Array;

    /// <summary>Generic collection interface.</summary>
    template <class T>
    class ICollection : public IEnumerable<T>
    {
    public: // METHODS

        /// <summary>(ICollection) Number of elements contained in the collection.</summary>
        virtual int count() = 0;

        /// <summary>(ICollection) Copies the elements of the ICollection(T)
        /// to a Array, starting at the specified Array index.</summary>
        virtual void copyTo(Array<T> array, int arrayIndex) = 0;

    protected:
        ICollection() = default;
    };
}

#endif // cl_dotcpp_main_ICollection_hpp

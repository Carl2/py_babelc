/*
 * Copyright (C) 2017 Mattias Sjösvärd (mr@seasword.com)
 *
 * This file is part of babelc but this particular file is 
 * not covered by the GPL2 license, but rather the MIT license as follows:
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a 
 * copy of this software and associated documentation files (the "Software"), 
 * to deal in the Software without restriction, including without limitation 
 * the rights to use, copy, modify, merge, publish, distribute, sublicense, 
 * and/or sell copies of the Software, and to permit persons to whom the 
 * Software is furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR 
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE 
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER 
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN 
 * THE SOFTWARE.
 */
#ifndef ADDRESS_BOOK_H_
#define ADDRESS_BOOK_H_

#include <cstdint>
#include <string>
#include <vector>
#include <memory>

namespace addressbook { namespace v1 {

    enum struct Sex : std::uint8_t {
        Unknown,
        Male,
        Female,
        Neither
    };
        
    using PhoneNumber  = std::uint64_t;
    using PhoneNumbers = std::vector< PhoneNumber >;

    struct Person {
        std::string  itsName;
        Sex          itsSex          = Sex::Unknown;
        PhoneNumbers itsPhoneNumbers;
    };

    struct Server {
        virtual void add( const Person &thePerson ) = 0; 

        virtual ~Server() {}
    };

    using ServerPtr = std::shared_ptr<Server>;

}}

#endif

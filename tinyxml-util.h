/* vim: set ai noet ts=4 sw=4 tw=115: */
//
// Copyright (c) 2014 Nikolay Zapolnov (zapolnov@gmail.com).
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//
#ifndef __d2d772c8d76fcd3cf1aa0fb94ef35729__
#define __d2d772c8d76fcd3cf1aa0fb94ef35729__

#include <yip-imports/tinyxml.h>
#include <string>

TiXmlElement * xmlParse(TiXmlDocument & doc, std::string buffer, const std::string & rootElementName);

bool xmlAttrToFloat(const TiXmlAttribute * attr, float & val);
bool xmlAttrToDouble(const TiXmlAttribute * attr, double & val);
bool xmlAttrToInt(const TiXmlAttribute * attr, int & val);
bool xmlAttrToLong(const TiXmlAttribute * attr, long & val);

std::string xmlError(const TiXmlBase * loc, const std::string & msg);
std::string xmlMissingAttribute(const TiXmlElement * element, const char * attribute);
std::string xmlInvalidAttributeValue(const TiXmlAttribute * attr);

#endif

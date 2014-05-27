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
#include "tinyxml-util.h"

#ifdef BUILDING_YIP
#include "../strtod/strtod.h"
#else
#include <yip-imports/strtod.h>
#endif

#include <cstdlib>
#include <cctype>
#include <sstream>
#include <stdexcept>

TiXmlElement * xmlParse(TiXmlDocument & doc, std::string buffer, const std::string & rootElementName)
{
	if (!doc.LoadBuffer(const_cast<char *>(buffer.data()), buffer.length()))
	{
		std::stringstream ss;
		ss << "error in '" << doc.ValueStr() << "' at row " << doc.ErrorRow() << ", column " << doc.ErrorCol()
			<< ": " << doc.ErrorDesc();
		throw std::runtime_error(ss.str());
	}

	return xmlCheckRootElement(doc, rootElementName);
}

TiXmlElement * xmlCheckRootElement(TiXmlDocument & doc, const std::string & rootElementName)
{
	TiXmlElement * rootElement = doc.RootElement();
	if (rootElement->ValueStr() != rootElementName)
	{
		std::stringstream ss;
		ss << "root element is not '" << rootElementName << "'.";
		throw std::runtime_error(xmlError(rootElement, ss.str()));
	}
	return rootElement;
}

TiXmlElement * xmlCheckRootElement(TiXmlDocument * doc, const std::string & rootElementName)
{
	return xmlCheckRootElement(*doc, rootElementName);
}

TiXmlElement * xmlCheckRootElement(const std::shared_ptr<TiXmlDocument> & doc, const std::string & rootElementName)
{
	return xmlCheckRootElement(*doc.get(), rootElementName);
}

bool xmlAttrToFloat(const TiXmlAttribute * attr, float & val)
{
	return strToFloat(attr->ValueStr(), val);
}

bool xmlAttrToDouble(const TiXmlAttribute * attr, double & val)
{
	return strToDouble(attr->ValueStr(), val);
}

bool xmlAttrToInt(const TiXmlAttribute * attr, int & val)
{
	const char * str = attr->Value();
	char * end = nullptr;
	long value = strtol(str, &end, 0);

	if (!*end)
	{
		val = static_cast<int>(value);
		return true;
	}

	return false;
}

bool xmlAttrToLong(const TiXmlAttribute * attr, long & val)
{
	const char * str = attr->Value();
	char * end = nullptr;
	long value = strtol(str, &end, 0);

	if (!*end)
	{
		val = value;
		return true;
	}

	return false;
}

bool xmlAttrToCommaSeparatedFloatList(const TiXmlAttribute * attr, std::vector<float> & list)
{
	const char * str = attr->Value();
	const char * p;

	do
	{
		p = strchr(str, ',');
		std::string val = (p ? std::string(str, size_t(p - str)) : std::string(str));

		const char * pp = val.c_str();
		char * end = nullptr;
		float value = static_cast<float>(p_strtod(pp, &end));

		while (isspace(*end))
			++end;
		if (*end != 0)
			return false;

		list.push_back(value);
		str = p + 1;
	}
	while (p);

	return true;
}

bool xmlAttrToCommaSeparatedDoubleList(const TiXmlAttribute * attr, std::vector<double> & list)
{
	const char * str = attr->Value();
	const char * p;

	do
	{
		p = strchr(str, ',');
		std::string val = (p ? std::string(str, size_t(p - str)) : std::string(str));

		const char * pp = val.c_str();
		char * end = nullptr;
		double value = p_strtod(pp, &end);

		while (isspace(*end))
			++end;
		if (*end != 0)
			return false;

		list.push_back(value);
		str = p + 1;
	}
	while (p);

	return true;
}

std::string xmlError(const TiXmlBase * loc, const std::string & msg)
{
	if (!loc)
		return msg;

	std::stringstream ss;
	ss << loc->GetDocument()->ValueStr() << '(' << loc->Row() << ',' << loc->Column() << "): " << msg;

	return ss.str();
}

std::string xmlMissingAttribute(const TiXmlElement * element, const char * attribute)
{
	std::stringstream ss;
	ss << "element '" << element->ValueStr() << "' is missing attribute '" << attribute << "'.";
	return xmlError(element, ss.str());
}

std::string xmlInvalidAttributeValue(const TiXmlAttribute * attr)
{
	std::stringstream ss;
	ss << "invalid value for the '" << attr->NameTStr() << "' attribute.";
	return xmlError(attr, ss.str());
}

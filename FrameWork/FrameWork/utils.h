//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2016 Media Design School
//
// File Name	: 
// Description	: 
// Author		: Your Name
// Mail			: your.name@mediadesign.school.nz
//

#if !defined(__UTILS_H__)
#define __UTILS_H__

// Library Includes
#include <strstream>
#include <Windows.h>

// Local Includes

// Types

// Constants

// Prototypes

#define VALIDATE(a) if (!a) return (false)

template<typename T>
std::string ToString(const T& _value)
{
    std::strstream theStream;
    theStream << _value << std::ends;
    return (theStream.str());
}

inline bool InsideRect(const POINT& _krpoi, const RECT& _krrect)
{
	if (_krpoi.x >= _krrect.left &&
		_krpoi.x <= _krrect.right &&
		_krpoi.y >= _krrect.top &&
		_krpoi.y <= _krrect.bottom)
	{
		return true;
	}
	else
	{
		return false;
	}
}

#endif    // __UTILS_H__


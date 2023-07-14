//////////////////////////////////////////////////////////////////////////////
// Copyright (C) 2019 by bitbybit3d, All rights reserved. 
// Author: bitbybit3d@163.com 
// 
// 
// THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
// EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT, 
// MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
//////////////////////////////////////////////////////////////////////////////
#ifndef __JT_TOOLKIT_PROPERTY_H_
#define __JT_TOOLKIT_PROPERTY_H_

#include "DxJtEntity.h"

/**
 * @brief The base class for all attributes.
 */
class JT_TOOLKIT_EXPORT DxJtProperty : public DxJtEntity
{
protected:
    DxJtProperty();

public:
    DXJT_ENTITY_TYPEID_HEADER(DxJtProperty);


    enum SubType
    {
        JtkUNKNOWN,
        JtkSTRING,
        JtkINT,
        JtkFLOAT,
        JtkDATE
    };

    virtual SubType getSubType() const = 0;
    virtual bool getInternal(std::wstring& key, std::wstring& value) const = 0;
    virtual bool getInternal(std::wstring& key, int& value) const = 0;
    virtual bool getInternal(std::wstring& key, float& value) const = 0;
    virtual bool getInternal(std::wstring& key, short& year, short& month,
        short& day, short& hour, short& minutes, short& seconds) const = 0;
};

#endif  // __JT_TOOLKIT_PROPERTY_H_

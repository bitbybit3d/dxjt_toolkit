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

#include <vector>

#include "JtEntity.h"

/**
 * @brief The base class for all attributes.
 */
class JT_TOOLKIT_EXPORT JtProperty : public JtEntity
{
protected:
    JtProperty();

public:

    /**
     * @brief Return the TypeID for class.
     */
    static TypeID classTypeID();
    /**
     * @brief Return the TypeID for instance.
     */
    virtual TypeID typeID() const;
    /**
     * @brief Return true if instance belong to the type id.
     */
    virtual bool isOfSubType(TypeID id) const;

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

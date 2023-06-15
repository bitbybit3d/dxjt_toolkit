//////////////////////////////////////////////////////////////////////////////
// Copyright (C) 2019 by bitbybit3d, All rights reserved. 
// Author: bitbybit3d@163.com 
// 
// 
// THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
// EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT, 
// MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
//////////////////////////////////////////////////////////////////////////////
#ifndef __JT_TOOLKIT_TRISTRIP_SET_H_
#define __JT_TOOLKIT_TRISTRIP_SET_H_

#include "DxJtShape.h"

/**
 * @brief A Tri-Strip Set Shape Element, forming triangles, like
 * OpenGL's triangle strip definition.
 */
class JT_TOOLKIT_EXPORT DxJtTriStripSet : public DxJtShape
{
public:
    DxJtTriStripSet();

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

};

#endif  // __JT_TOOLKIT_TRISTRIP_SET_H_

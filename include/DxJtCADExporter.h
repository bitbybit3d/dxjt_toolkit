//////////////////////////////////////////////////////////////////////////////
// Copyright (C) 2019 by bitbybit3d, All rights reserved. 
// Author: bitbybit3d@163.com 
// 
// 
// THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
// EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT, 
// MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
//////////////////////////////////////////////////////////////////////////////
#ifndef __JT_TOOLKIT_CAD_EXPORTER_H_
#define __JT_TOOLKIT_CAD_EXPORTER_H_

#include "DxJtEntity.h"

class DxJtHierarchy;

/**
 * @brief Save the root node to a JT format file.
 */
class JT_TOOLKIT_EXPORT DxJtCADExporter : public DxJtEntity
{
protected:
    DxJtCADExporter();

public:
    DXJT_ENTITY_TYPEID_HEADER(DxJtCADExporter);


    virtual void setExportPath(const wchar_t* path) = 0;

    virtual bool exportJt(std::shared_ptr<DxJtHierarchy> root) const = 0;
};

#endif  // __JT_TOOLKIT_CAD_EXPORTER_H_

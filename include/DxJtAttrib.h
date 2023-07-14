//////////////////////////////////////////////////////////////////////////////
// Copyright (C) 2019 by bitbybit3d, All rights reserved. 
// Author: bitbybit3d@163.com 
// 
// 
// THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
// EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT, 
// MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
//////////////////////////////////////////////////////////////////////////////
#ifndef __JT_TOOLKIT_ATTRIBUTE_H_
#define __JT_TOOLKIT_ATTRIBUTE_H_

#include "DxJtEntity.h"

/**
 * @brief The base class for all attributes.
 */
class JT_TOOLKIT_EXPORT DxJtAttrib : public DxJtEntity
{
protected:
    DxJtAttrib();

public:
    DXJT_ENTITY_TYPEID_HEADER(DxJtAttrib);


    enum Scope
    {
        JtkINHERITED = 0,
        JtkSHARED = 1,
        JtkINSTANCE = 2
    };
};

/**
 * @brief Attribute class for material.
 */
class JT_TOOLKIT_EXPORT DxJtMaterial : public DxJtAttrib
{
protected:
    DxJtMaterial();

public:
    DXJT_ENTITY_TYPEID_HEADER(DxJtMaterial);

    virtual void setAmbientColor(const std::vector<float>& ambient) = 0;
    virtual void getAmbientColor(std::vector<float>& ambient) const = 0;
    virtual void setDiffuseColor(const std::vector<float>& diffuse) = 0;
    virtual void getDiffuseColor(std::vector<float>& diffuse) const = 0;
    virtual void setSpecularColor(const std::vector<float>& specular) = 0;
    virtual void getSpecularColor(std::vector<float>& specular) const = 0;
    virtual void setEmissionColor(const std::vector<float>& emission) = 0;
    virtual void getEmissionColor(std::vector<float>& emission) const = 0;
    virtual void setShininess(float shininess) = 0;
    virtual float getShininess() const = 0;
};

/**
 * @brief Attribute class for transform.
 */
class JT_TOOLKIT_EXPORT DxJtTransform : public DxJtAttrib
{
protected:
    DxJtTransform();

public:
    DXJT_ENTITY_TYPEID_HEADER(DxJtTransform);


    virtual void setTElements(const std::vector<double>& transf) = 0;
    virtual void getTElements(std::vector<double>& transf) const = 0;
};

#endif  // __JT_TOOLKIT_ATTRIBUTE_H_

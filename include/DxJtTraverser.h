//////////////////////////////////////////////////////////////////////////////
// Copyright (C) 2019 by bitbybit3d, All rights reserved. 
// Author: bitbybit3d@163.com 
// 
// 
// THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
// EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT, 
// MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
//////////////////////////////////////////////////////////////////////////////
#pragma once
#ifndef __JT_TOOLKIT_TRAVERSER_H_
#define __JT_TOOLKIT_TRAVERSER_H_

#include "DxJtHierarchy.h"


class JtTraverserPrivate;

/**
 * @brief A traverser for visit product structure object.
 */
class JT_TOOLKIT_EXPORT DxJtTraverser
{
private:
    DxJtTraverser(const DxJtTraverser&);
    DxJtTraverser& operator=(const DxJtTraverser&);

public:
    DxJtTraverser();
    virtual ~DxJtTraverser();

    /**
     * @brief traverse the descent graph nodes.
     */
    void traverseGraph(std::shared_ptr<DxJtHierarchy> Root);

    /**
     * @brief Setup a pre-action callback for the input node.
     *
     * 默认情况下返回true，使得可以继续递归访问children nodes；而如果
     * 返回false，则将阻止递归任何更下的节点级别。
     *
     * @param CurrNode 当前正在访问的节点
     * @param Level 从遍历开始层级为0开始计算，当前处于哪一级别
     */
    virtual bool preActionCallback(std::shared_ptr<DxJtHierarchy> CurrNode, int Level) {
        return true;
    }

    /**
     * @brief Setup a post-action callback for the input node.
     *
     * 默认情况下返回true，使得可以继续处理直至结束；而如果返回false，则将
     * 阻止任何其他节点。
     *
     * @param CurrNode 当前正在访问的节点
     * @param Level 从遍历开始层级为0开始计算，当前处于哪一级别
     */
    virtual bool postActionCallback(std::shared_ptr<DxJtHierarchy> CurrNode, int Level) {
        return true;
    }

private:
    JtTraverserPrivate* _private;
};

#endif  // __JT_TOOLKIT_TRAVERSER_H_

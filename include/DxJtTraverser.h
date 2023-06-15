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
     * Ĭ������·���true��ʹ�ÿ��Լ����ݹ����children nodes�������
     * ����false������ֹ�ݹ��κθ��µĽڵ㼶��
     *
     * @param CurrNode ��ǰ���ڷ��ʵĽڵ�
     * @param Level �ӱ�����ʼ�㼶Ϊ0��ʼ���㣬��ǰ������һ����
     */
    virtual bool preActionCallback(std::shared_ptr<DxJtHierarchy> CurrNode, int Level) {
        return true;
    }

    /**
     * @brief Setup a post-action callback for the input node.
     *
     * Ĭ������·���true��ʹ�ÿ��Լ�������ֱ�����������������false����
     * ��ֹ�κ������ڵ㡣
     *
     * @param CurrNode ��ǰ���ڷ��ʵĽڵ�
     * @param Level �ӱ�����ʼ�㼶Ϊ0��ʼ���㣬��ǰ������һ����
     */
    virtual bool postActionCallback(std::shared_ptr<DxJtHierarchy> CurrNode, int Level) {
        return true;
    }

private:
    JtTraverserPrivate* _private;
};

#endif  // __JT_TOOLKIT_TRAVERSER_H_

/**
 * Copyright (c) 2008 Christopher Allen Ogden
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#ifndef SYD_FRAMEWORK_VIEWCOMPOSITE_H_
#define SYD_FRAMEWORK_VIEWCOMPOSITE_H_

#include <vector>
#include <algorithm>
#include "ViewObject.h"

namespace sydmvc {

template <class I>
class ViewComposite: public ViewObject<I>
{
    public:
        ViewComposite() {}

        virtual void addChild(ViewObject<I> *view)
        {
            _children.push_back(view);
        }

        virtual void removeChild(ViewObject<I> *view)
        {
            typename ViewChildren::iterator iter = find(_children.begin(), _children.end(), view);
            if (iter != _children.end()) {
                _children.erase(iter);
            }
        }

        virtual void draw(System<I> *sys) const
        {
            for (typename ViewChildren::const_iterator iter = _children.begin();
                    iter != _children.end();
                    iter++) {
                (*iter)->draw(sys);
            }
        }
        
        void setFacade(Facade<I> * facade)
        {
            for (typename ViewChildren::iterator iter = _children.begin();
                    iter != _children.end();
                    iter++) {
                (*iter)->setFacade(facade);
            }
        }

        virtual ~ViewComposite()
        {
            for (typename ViewChildren::iterator iter = _children.begin();
                    iter != _children.end();
                    iter++) {
                delete (*iter);
            }
        }
    private:
        typedef std::vector<ViewObject<I> *> ViewChildren;
        ViewChildren _children;
        DISALLOW_COPY_AND_ASSIGN(ViewComposite);
};

}

#endif

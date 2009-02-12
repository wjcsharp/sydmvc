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

#ifndef SYD_FRAMEWORK_VIEW_H_
#define SYD_FRAMEWORK_VIEW_H_

#include "ViewObject.h"

namespace sydmvc {

/**
 * Views are the output system and can be nested within CompositeViews.
 */
template <class I>
class View: public ViewObject<I>
{
    public:
        /**
         * Set the facade to be used.
         *
         * @param facade    Facade to use.
         */
        void setFacade(Facade<I> * const facade)
        {
            _facade = facade;
        }

        /**
         * Get the facade being used.
         *
         * @return  Facade being used.
         */
        Facade<I> *getFacade() const
        {
            return _facade;
        }

    protected:
        View() {}
        virtual ~View() {}

    private:
        Facade<I> *_facade;
        DISALLOW_COPY_AND_ASSIGN(View);
};

}

#endif

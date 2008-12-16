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

#ifndef SYD_FRAMEWORK_VIEWOBJECT_H_
#define SYD_FRAMEWORK_VIEWOBJECT_H_

namespace sydmvc {

template <class I> class System;
template <class I> class Facade;

/**
 * ViewObjects represent either Views or ViewComposites.
 */
template <class I>
class ViewObject
{
    public:
        /**
         * Set the facade to be used.
         *
         * @param facade    Facade to use.
         */
        virtual void setFacade(Facade<I> * facade) = 0;

        /**
         * Draw itself.
         *
         * @param sys   System to draw with.
         */
        virtual void draw(System<I> *sys) const {};

        /**
         * Add child.
         *
         * @param view  View or ViewComposite object to add as a child.
         */
        virtual void addChild(ViewObject *view) {};

        /**
         * Remove a child.
         *
         * @param view  View or ViewComposite object to remove.
         */
        virtual void removeChild(ViewObject *view) {};

        /**
         * Empty virtual destructor.
         */
        virtual ~ViewObject() { }
    protected:

        /**
         * Empty constructor.
         */
        ViewObject() {}

    private:
        DISALLOW_COPY_AND_ASSIGN(ViewObject);
};

}

#endif

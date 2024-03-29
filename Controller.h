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

#ifndef SYD_FRAMEWORK_CONTROLLER_H_
#define SYD_FRAMEWORK_CONTROLLER_H_

#include "Observer.h"

namespace sydmvc {

template <class I> class Facade;
template <class I> class System;

/**
 * Controllers subscribe to the system to observe and process input before
 * selecting a view to display.
 */
template <class I>
class Controller: public Observer
{
    public:
        /**
         * Set the facade.
         *
         * @param facade    Facade to use.
         */
        virtual void setFacade(Facade<I> * const facade)
        {
            _facade = facade;
        }

        /**
         * Get the facade.
         *
         * @return  Facade being used.
         */
        virtual Facade<I> *getFacade() const
        {
            return _facade;
        }

        /**
         * Attach itself to the system.
         */
        virtual void attach()
        {
            getFacade()->getSystem()->attach(this, getNotificationList());
        }
       
        /**
         * Used by the system to request a list of notification types
         * that should be observed.
         *
         * @return  A list of notification types.
         */
        virtual typename System<I>::NotificationList getNotificationList() const
        {
            return typename System<I>::NotificationList();
        }

        /**
         * Empty destructor.
         */
        virtual ~Controller() {}

    protected:
        Controller() {}

    private:
        Facade<I> *_facade;
        DISALLOW_COPY_AND_ASSIGN(Controller);
};

}

#endif

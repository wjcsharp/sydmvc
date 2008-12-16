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

#ifndef SYD_FRAMEWORK_SUBJECT_H_
#define SYD_FRAMEWORK_SUBJECT_H_

#include <vector>
#include "macros.h"

namespace sydmvc {

/**
 * Subjects are observed by observers.
 */
template <class O>
class Subject
{
    public:
        typedef std::vector<int> NotificationList;

        /**
         * Attach an observer.
         *
         * @param observer  Observer to attach.
         * @param nl        Notification list associated with observer.
         */
        virtual void attach(O *observer, const NotificationList &nl) = 0;

        /**
         * Detach an observer.
         *
         * @param observer  Observer to detach.
         */
        virtual void detach(O *observer) = 0;

    protected:
        Subject() {}
        virtual void notify(int) = 0;

    private:
        DISALLOW_COPY_AND_ASSIGN(Subject);
};

}

#endif

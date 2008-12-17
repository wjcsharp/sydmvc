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

#ifndef SYD_FRAMEWORK_SIMPLE_SUBJECT_H_
#define SYD_FRAMEWORK_SIMPLE_SUBJECT_H_

#include "Subject.h"

namespace sydmvc {

/**
 * A simple subject is a subject that uses a very simple system for the
 * attaching, detaching, and notifying of observers.
 */
template <class S, class O>
class SimpleSubject: public Subject<O>
{
    public:
        /**
         * Attach an observer.
         *
         * @param observer  Observer to attach.
         * @param list      Notification list associated with the observer.
         */
        virtual void attach(O * const observer, const typename Subject<O>::NotificationList &list)
        {
            _observers[observer] = list;
        }

        /**
         * Detach an observer.
         *
         * @param observer  Observer to detach.
         */
        virtual void detach(O * const observer)
        {
            typename ObserverList::iterator iter = _observers.find(observer);
            if (iter != _observers.end()) {
                _observers.erase(iter);
            }
        }

    protected:

        /**
         * Notify all observers who are subscribed for the event.
         *
         * @param event Event type to notify observers of.
         */
        virtual void notify(int event)
        {
            for (typename ObserverList::iterator iter = _observers.begin();
                    iter != _observers.end();
                    iter++) {
                for (typename Subject<O>::NotificationList::iterator innerIter = iter->second.begin();
                        innerIter != iter->second.end();
                        innerIter++) {
                    if ((*innerIter) == event) {
                        iter->first->update(event);
                    }
                }
            }
        }

        SimpleSubject() {}
        virtual ~SimpleSubject() {}

    private:
        typedef std::map<O*, typename Subject<O>::NotificationList> ObserverList;
        ObserverList _observers;
        DISALLOW_COPY_AND_ASSIGN(SimpleSubject);
};

}

#endif

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

#ifndef SYD_FRAMEWORK_FACADE_H_
#define SYD_FRAMEWORK_FACADE_H_

#include <vector>
#include <map>

namespace syd {

template <class I> class ViewObject;

template <class I>
class Facade
{
    public:
        Facade():_quit(false),_system(NULL)
        {
        }

        virtual ~Facade()
        {
            for (typename ControllerList::iterator iter = _controllers.begin();
                    iter != _controllers.end();
                    iter++) {
                if (*iter) delete (*iter);
                (*iter) = NULL;
            }
            if (_system) delete _system;
            _system = NULL;
        }

        virtual void init()
        {
            initSystem();
            attachControllers();
            attachViews();
        }

        virtual void attachController(Controller<I> *controller)
        {
            controller->setFacade(this);
            controller->attach();
            _controllers.push_back(controller);
        }

        virtual void attachView(int key, ViewObject<I> *view)
        {
            _views[key] = view;
        }

        virtual ViewObject<I> *getView(int key) 
        {
            return _views[key];
        }

        virtual void initSystem() = 0;
        virtual void attachControllers() { }
        virtual void attachViews() { }

        virtual void run()
        {
            while (!_quit) {
                if (_system) _system->handleEvents();
                idle();
            }
        }

        virtual void idle(void) {}

        void quit(void)
        {
            _quit = true;
        }

        System<I> *getSystem(void) const
        {
            return _system;
        }

        void setSystem(System<I> *system)
        {
            _system = system;
        }
    private:
        bool _quit;
        System<I> *_system;
        typedef std::vector<Controller<I> *> ControllerList;
        ControllerList _controllers;
        typedef std::map<int, ViewObject<I> *> ViewList;
        ViewList _views;
};

}

#endif

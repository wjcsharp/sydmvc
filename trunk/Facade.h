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

namespace sydmvc {

class Model;

template <class I> class ViewObject;

/**
 * There should be one facade per program.  It is a simplified interface
 * to the rest of the framework.  It should be subclassed.
 */
template <class I>
class Facade
{
    public:
        /**
         * Constructor.
         */
        Facade():_quit(false),_system(NULL)
        {
        }

        /**
         * Destructor.
         */
        virtual ~Facade()
        {
            for (typename ControllerList::iterator iter = _controllers.begin();
                    iter != _controllers.end();
                    iter++) {
                if (*iter) delete (*iter);
                (*iter) = NULL;
            }
            for (typename ViewList::iterator iter = _views.begin();
                    iter != _views.end();
                    iter++) {
                if (iter->second) delete iter->second;
                iter->second = NULL;
            }
            for (typename ModelList::iterator iter = _models.begin();
                    iter != _models.end();
                    iter++) {
                if (iter->second) delete iter->second;
                iter->second = NULL;
            }
            if (_system) delete _system;
            _system = NULL;
        }

        /**
         * Perform initialization.
         */
        virtual void init()
        {
            initSystem();
            attachControllers();
            attachModels();
            attachViews();
        }

        /**
         * Attach a controller to the facade (and System).
         *
         * @param controller    Controller to attach.
         */
        virtual void attachController(Controller<I> *controller)
        {
            controller->setFacade(this);
            controller->attach();
            _controllers.push_back(controller);
        }

        /**
         * Attach a view to the facade.
         *
         * @param key   Key to attach the view with.
         * @param view  View to attach.
         */
        virtual void attachView(int key, ViewObject<I> *view)
        {
            typename ViewList::iterator iter = _views.find(key);
            if (iter != _views.end()) {
                delete (iter->second);
            }
            view->setFacade(this);
            view->attach();
            _views[key] = view;
        }

        /**
         * Get a view that has been attached.
         *
         * @param key   Key of the view to return.
         * @return      View associated with the key.
         */
        virtual ViewObject<I> *getView(int key) 
        {
            return _views[key];
        }

        /**
         * Attach a model to the facade.
         *
         * @param key   Key to attach the model with.
         * @param model Model to attach.
         */
        virtual void attachModel(int key, Model *model)
        {
            ModelList::iterator iter = _models.find(key);
            if (iter != _models.end()) {
                delete (iter->second);
            }
            _models[key] = model;
        }

        /**
         * Get a model that has been attached.
         *
         * @param key   Key of the model to return.
         * @return      Model associated with the key.
         */
        virtual Model *getModel(int key)
        {
            return _models[key];
        }

        /**
         * Initialize the system.
         */
        virtual void initSystem() = 0;

        /**
         * Attach all the controllers.
         */
        virtual void attachControllers() { }

        /**
         * Attach all the views.
         */
        virtual void attachViews() { }

        /**
         * Attach all the models.
         */
        virtual void attachModels() { }

        /**
         * Main loop of the program.
         */
        virtual void run()
        {
            while (!_quit) {
                if (_system) _system->handleEvents();
                idle();
            }
        }

        /**
         * Called once per cycle, if there are no events.
         */
        virtual void idle(void) {}

        /**
         * Cause the main loop to terminate.
         */
        void quit(void)
        {
            _quit = true;
        }

        /**
         * Get the system attached to the facade.
         *
         * @return  System attached.
         */
        System<I> *getSystem(void) const
        {
            return _system;
        }

        /**
         * Associate a system with the facade.
         *
         * @param system    System to associate.
         */
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
        typedef std::map<int, Model *> ModelList;
        ModelList _models;

        DISALLOW_COPY_AND_ASSIGN(Facade);
};

}

#endif

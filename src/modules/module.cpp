#include "modules/module.hpp"
#include "common/util/better_canvas.hpp"

template <typename T>
Module<T>::Module(BetterCanvas* _canvas) 
    : configuration{},
    canvas{_canvas}
    {
    setup();
}

template <typename T>
Module<T>::~Module() { 
    teardown();
}

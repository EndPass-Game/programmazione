#pragma once
#include "vector.hpp"
#include "window.hpp"
#include "resizableWindow.hpp"

namespace graphics{
    class StackLayout:public ResizableWindow{
        public:
            StackLayout(datastruct::Vector<Size> windowsSize,int padding);
            StackLayout(datastruct::Vector<Window*> windowsSize,int padding);
            ~StackLayout();

            void refreshAll();

            void handleScreenSizeChange();

            virtual void handleScreenToSmall(){}
            virtual void handleResizedScreen(){}
            void recenterAllWindows();
            Window* getWindow(int i);
            void repaintAll();
            
        private:
            void calcMinSize_(datastruct::Vector<Size> windowsSize);
            int padding_;
            datastruct::Vector<Window*> windows_;
            Size minSize_;
            Position recenterPosition_(int offest,Size windowsSize);
    };
};
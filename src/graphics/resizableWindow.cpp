#include "resizableWindow.hpp"

namespace graphics 
{
    ResizableWindow::ResizableWindow(){
        currentScreenSize_=new Changeable<Size>({LINES,COLS});
    }
    ResizableWindow::~ResizableWindow(){
        delete currentScreenSize_;
    }
    bool ResizableWindow::updateScreenSize()
    {
        Size newSize={LINES,COLS};
        currentScreenSize_->setCurrent(newSize);
        if(currentScreenSize_->isChanged()) handleScreenSizeChange();
        return currentScreenSize_->isChanged();
    }
} // namespace manager

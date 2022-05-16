#include "stackLayout.hpp"

namespace graphics
{
    StackLayout::StackLayout(datastruct::Vector<Size> windowsSize,int padding):padding_(padding),ResizableWindow(){
        calcMinSize_(windowsSize);
        for(int i=0;i<windowsSize.size();i++){
            windows_.push_back(new Window{{0,0},windowsSize[i]});
        }
        recenterAllWindows();
    }

    StackLayout::StackLayout(datastruct::Vector<Window*> windows,int padding):padding_(padding),windows_(windows), ResizableWindow(){
        datastruct::Vector<Size> windowsSize(windows.size());
        for(int i=0;i<windows.size();i++){
            windowsSize.push_back(windows[i]->getSize());
        }
        calcMinSize_(windowsSize);
        recenterAllWindows();
    }

   void StackLayout::recenterAllWindows(){
        int offestX=padding_;
        for(int i=0;i<windows_.size();i++){
            windows_[i]->moveWindow(recenterPosition_(offestX,windows_[i]->getSize()));
            offestX+=windows_[i]->getSize().x+padding_;
        }
    }

    void StackLayout::calcMinSize_(datastruct::Vector<Size> windowsSize){
        minSize_={padding_,0};
        for(int i=0;i<windowsSize.size();i++){
            if(windowsSize[i].y>minSize_.y){ minSize_.y=windowsSize[i].y; }
            minSize_.x+=windowsSize[i].x+padding_;
        }
    }

    Position StackLayout::recenterPosition_(int offest,Size windowSize){
        int cols=currentScreenSize_->getCurrent().y;
        if(cols<minSize_.y){
            cols=minSize_.y;
        }
        return {offest,(cols-windowSize.y)/2};
    }

    void StackLayout::refreshAll()
    {
        for (int i = 0; i < windows_.size(); i++)
            wrefresh(windows_[i]->getWindow());
    }

    void StackLayout::repaintAll()
    {
        clear();
        refresh();
        recenterAllWindows();
        handleResizedScreen();
        refreshAll();
    }

    void StackLayout::handleScreenSizeChange()
    {
        if (currentScreenSize_->getCurrent() < minSize_)
        {
            handleScreenToSmall();
        }
        else
        {
            repaintAll();
        }
    }

    Window *StackLayout::getWindow(int i)
    {
        return windows_[i];
    }

    StackLayout::~StackLayout()
    {
        for (size_t i = 0; i < windows_.size(); i++)
        {
            delete windows_[i];
        }
    }
};
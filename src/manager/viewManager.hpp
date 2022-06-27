
#include "datastruct/stack.hpp"
#include "views/view.hpp"

namespace manager{

    class ViewManager
    {
    private:
        datastruct::Stack<views::View> stackView;
    public:

        void pushView(views::View *v);

        void popView();

        bool empty();

        views::View* last();
    };

};
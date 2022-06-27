#include "gamestruct/changeable.hpp"
#include "views/view.hpp"
#include "gamestruct/changeable.hpp"
#include "gamestruct/size.hpp"
#include "gamestruct/position.hpp"


namespace views
{
    class ResizableView : public View
    {
    private:
        Changeable<Size> changable;


    public:
        ResizableView(Position pos,Size s);

        virtual void handleScreenToSmall();

        void render(){

        }


    };
}; // namespace views
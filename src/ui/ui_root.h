#ifndef DEMO_UI_CONTROLLER_H
#define DEMO_UI_CONTROLLER_H

class UIRoot
{
public:
    explicit UIRoot(std::shared_ptr<World> world);
    void draw();

private:
    std::shared_ptr<World> world;
};

#endif //DEMO_UI_CONTROLLER_H

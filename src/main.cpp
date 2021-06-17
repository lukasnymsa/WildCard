#include "Application.hpp"

/**
 * Creates new instance of Application and Runs it, then deletes it
 */
int main() {
    auto * app = new Application();
    while(app->Run());
    delete app;
    return 0;
}
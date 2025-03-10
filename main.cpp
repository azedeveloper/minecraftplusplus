#include "core/Application.h"

int main() {
    Application app;
    app.init();
    app.update();
    app.cleanup();
    
    return 0;
}
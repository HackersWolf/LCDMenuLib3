// ##########################################################################################################################
// ########### TASKS SCHEDULER SIMULATION ###################################################################################
// ##########################################################################################################################

void tasksBegin() {
    app.lastRenderMs = 0;
    app.renderIntervalMs = 500;
}

void tasksLoop() {
    if(app.now - app.lastRenderMs >= app.renderIntervalMs) {
        app.lastRenderMs = app.now;
        app.redraw = true;
    }
}

bool tasksShouldRender() {
    if(app.redraw) {
        app.redraw = false;
        return true;
    }
    return false;
}

// ##########################################################################################################################
// ########### REALTIME CLOCK SIMULATION ####################################################################################
// ##########################################################################################################################

void clockLoop() {
    if(app.now - app.lastClockMs >= 1000) {
        app.lastClockMs = app.now;
        app.clockSecond++;

        if(app.clockSecond >= 60) {
            app.clockSecond = 0;
            app.clockMinute++;
        }

        if(app.clockMinute >= 60) {
            app.clockMinute = 0;
            app.clockHour = (app.clockHour + 1) % 24;
        }
    }
}

void clockFormat(char *buffer, size_t size) {
    snprintf(buffer, size, "%02u:%02u:%02u", app.clockHour, app.clockMinute, app.clockSecond);
}

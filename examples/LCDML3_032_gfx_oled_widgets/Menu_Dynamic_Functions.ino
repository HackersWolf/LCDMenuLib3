// ##########################################################################################################################
// ########### MENU DYNAMIC FUNCTIONS #######################################################################################
// ##########################################################################################################################

void menuDynamicHandleInput(char input) {
    if(input == 0) {
        return;
    }

    if(input == 'q') {
        controlConsumeHelp();
        return;
    }

    if(input == 'n') {
        app.page = (app.page + 1) % PAGE_COUNT;
        app.redraw = true;
        return;
    }

    if(input == 'p') {
        app.page = (app.page == 0) ? (PAGE_COUNT - 1) : (app.page - 1);
        app.redraw = true;
        return;
    }

    switch(app.page) {
        case PAGE_TIME:
            if(input == 'u') widgetTime.increment();
            if(input == 'd') widgetTime.decrement();
            if(input == 'r') widgetTime.nextField();
            if(input == 'l') widgetTime.previousField();
            if(input == 'e') widgetTimer.fromSeconds(widgetTimer.toSeconds() + 60);
            break;

        case PAGE_VALUES:
            if(input == 'u') widgetNumeric.increment();
            if(input == 'd') widgetNumeric.decrement();
            if(input == 'r') widgetFloat.increment();
            if(input == 'l') widgetFloat.decrement();
            if(input == 'e') widgetState.next();
            break;

        case PAGE_LISTS:
            if(input == 'u') { widgetRadio.up(); widgetCheck.up(); }
            if(input == 'd') { widgetRadio.down(); widgetCheck.down(); }
            if(input == 'e') { widgetRadio.selectCursor(); widgetCheck.toggleCursor(); }
            break;

        case PAGE_NETWORK:
            if(input == 'u') widgetIp.increment();
            if(input == 'd') widgetIp.decrement();
            if(input == 'r') widgetIp.nextField();
            if(input == 'l') widgetIp.previousField();
            if(input == 'e') widgetWifi.setState(LCDML3_NET_CONNECTED);
            break;

        case PAGE_SYSTEM:
            if(input == 'u') widgetWizard.next();
            if(input == 'd') widgetWizard.previous();
            if(input == 'e') widgetWizard.markComplete(widgetWizard.getStep(), true);
            if(input == 'r') widgetConfirm.toggle();
            break;

        case PAGE_DIAGNOSTIC:
            if(input == 'u') widgetUnits.next();
            if(input == 'd') widgetUnits.previous();
            if(input == 'e') widgetLogs.add(LCDML3_LOG_WARN, "Manual event");
            break;

        case PAGE_STORAGE:
            if(input == 'u') widgetFiles.up();
            if(input == 'd') widgetFiles.down();
            if(input == 'e') widgetActions.trigger(widgetFiles.getCursor());
            break;

        case PAGE_SECURITY:
            if(input == 'u') widgetPin.increment();
            if(input == 'd') widgetPin.decrement();
            if(input == 'r') widgetPin.nextField();
            if(input == 'l') widgetPin.previousField();
            if(input == 'e') widgetConfirm.confirm();
            break;
    }

    app.redraw = true;
}

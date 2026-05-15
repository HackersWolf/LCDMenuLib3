// ##########################################################################################################################
// ########### MENU RENDER 128x64 ASCII #####################################################################################
// ##########################################################################################################################

void renderBegin() {
    Serial.println();
    Serial.println(F("128x64 ASCII renderer initialized."));
}

void renderFrameTop() {
    Serial.println(F("+---------------------+"));
}

void renderLine(const char *text) {
    char line[22];
    uint8_t i = 0;

    for(; i < 21 && text[i] != '\0'; i++) {
        line[i] = text[i];
    }
    for(; i < 21; i++) {
        line[i] = ' ';
    }
    line[21] = '\0';

    Serial.print('|');
    Serial.print(line);
    Serial.println('|');
}

void renderHeader(const char *title) {
    char status[24];
    char line[32];
    widgetStatus.format(status, sizeof(status));
    snprintf(line, sizeof(line), "%-14s %s", title, status);
    renderLine(line);
}

void renderScreen() {
    char line[40];
    char value[24];

    Serial.println();
    renderFrameTop();

    switch(app.page) {
        case PAGE_TIME:
            renderHeader("TIME");
            widgetTime.format(value, sizeof(value));
            snprintf(line, sizeof(line), "Time   %s", value);
            renderLine(line);
            widgetTimer.format(value, sizeof(value));
            snprintf(line, sizeof(line), "Timer  %s", value);
            renderLine(line);
            widgetDate.format(value, sizeof(value));
            snprintf(line, sizeof(line), "Date   %s", value);
            renderLine(line);
            clockFormat(value, sizeof(value));
            snprintf(line, sizeof(line), "RTC    %s", value);
            renderLine(line);
            renderLine("u/d edit l/r field");
            renderLine("n next q help");
            break;

        case PAGE_VALUES:
            renderHeader("VALUES");
            widgetNumeric.format(value, sizeof(value), " %");
            snprintf(line, sizeof(line), "Bright %s", value);
            renderLine(line);
            widgetFloat.format(value, sizeof(value), " Kp");
            snprintf(line, sizeof(line), "PID    %s", value);
            renderLine(line);
            widgetState.label(value, sizeof(value));
            snprintf(line, sizeof(line), "Pump   [%s]", value);
            renderLine(line);
            snprintf(line, sizeof(line), "Encoder step %u", widgetEncoder.getLastStep());
            renderLine(line);
            renderLine("u/d num l/r float");
            renderLine("e state");
            break;

        case PAGE_LISTS:
            renderHeader("LISTS");
            for(uint8_t i = 0; i < 4; i++) {
                uint8_t idx = widgetRadio.getWindowStart() + i;
                snprintf(line, sizeof(line), "%c %s %s", idx == widgetRadio.getCursor() ? '>' : ' ', widgetRadio.isSelected(idx) ? "(o)" : "( )", radioLabels[idx]);
                renderLine(line);
            }
            snprintf(line, sizeof(line), "Mask 0x%04lx", (unsigned long)widgetCheck.getMask());
            renderLine(line);
            renderLine("e select/toggle");
            break;

        case PAGE_NETWORK:
            renderHeader("NETWORK");
            widgetWifi.formatStatus(value, sizeof(value));
            renderLine(value);
            widgetBluetooth.formatStatus(value, sizeof(value));
            renderLine(value);
            widgetIp.format(value, sizeof(value));
            snprintf(line, sizeof(line), "IP %s", value);
            renderLine(line);
            renderLine("SSID Workshop");
            renderLine("BT BLE scan");
            renderLine("e connect");
            break;

        case PAGE_SYSTEM:
            renderHeader("SYSTEM");
            widgetProgress.format(value, sizeof(value), "OTA");
            renderLine(value);
            widgetOta.format(value, sizeof(value));
            renderLine(value);
            snprintf(line, sizeof(line), "Wizard %u/%u", widgetWizard.getStep() + 1, widgetWizard.getStepCount());
            renderLine(line);
            widgetConfirm.format(value, sizeof(value), "Apply?");
            renderLine(value);
            renderLine("u/d step r choice");
            renderLine("e complete");
            break;

        case PAGE_DIAGNOSTIC:
            renderHeader("DIAG");
            widgetDiag.format(value, sizeof(value));
            renderLine(value);
            widgetGraph.format(value, sizeof(value));
            renderLine(value);
            snprintf(line, sizeof(line), "Unit %s", widgetUnits.getLabel());
            renderLine(line);
            snprintf(line, sizeof(line), "Logs visible %u", widgetLogs.countVisible());
            renderLine(line);
            renderLine("u/d unit e log");
            renderLine("Sensor graph live");
            break;

        case PAGE_STORAGE:
            renderHeader("STORAGE");
            snprintf(line, sizeof(line), "File cursor %u", widgetFiles.getCursor());
            renderLine(line);
            snprintf(line, sizeof(line), "Selected %u", widgetFiles.getSelected());
            renderLine(line);
            snprintf(line, sizeof(line), "Last action %u", app.lastAction);
            renderLine(line);
            snprintf(line, sizeof(line), "Cal ready %s", widgetCalibration.isReady() ? "YES" : "NO");
            renderLine(line);
            renderLine("u/d file e action");
            renderLine("Settings adapter");
            break;

        case PAGE_SECURITY:
            renderHeader("SECURITY");
            widgetPin.format(value, sizeof(value), true);
            snprintf(line, sizeof(line), "PIN %s", value);
            renderLine(line);
            widgetConfirm.format(value, sizeof(value), "Unlock?");
            renderLine(value);
            snprintf(line, sizeof(line), "Theme %s", widgetTheme.cursorSymbol());
            renderLine(line);
            renderLine("u/d digit l/r pos");
            renderLine("e confirm");
            renderLine("p previous page");
            break;
    }

    renderFrameTop();
}

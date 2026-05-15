// ##########################################################################################################################
// ########### OBJECTS AND LOGIC ############################################################################################
// ##########################################################################################################################

LCDML3_TimeEditor widgetTime;
LCDML3_TimerEditor widgetTimer;
LCDML3_DateEditor widgetDate;
LCDML3_RadioList widgetRadio;
LCDML3_CheckList widgetCheck;
LCDML3_StateButton widgetState;
LCDML3_NumericEditor widgetNumeric;
LCDML3_FloatEditor widgetFloat;
LCDML3_IPAddressEditor widgetIp;
LCDML3_WiFiMenu widgetWifi;
LCDML3_BluetoothMenu widgetBluetooth;
LCDML3_MenuHeader widgetHeader;
LCDML3_Theme widgetTheme;
LCDML3_StatusBar widgetStatus;
LCDML3_DebugMenu widgetDebug;
LCDML3_ConfirmDialog widgetConfirm;
LCDML3_PinEditor widgetPin;
LCDML3_ProgressScreen widgetProgress;
LCDML3_Wizard widgetWizard;
LCDML3_SettingsAdapter widgetSettings;
LCDML3_RotaryEncoderHelper widgetEncoder;
LCDML3_Sparkline widgetGraph;
LCDML3_LogViewer widgetLogs;
LCDML3_AlarmScheduler widgetAlarms;
LCDML3_UnitSelector widgetUnits;
LCDML3_OTAStatus widgetOta;
LCDML3_CalibrationWizard widgetCalibration;
LCDML3_ActionMenu widgetActions;
LCDML3_SDFileMenu widgetFiles;
LCDML3_DiagnosticMenu widgetDiag;

const char *radioLabels[] = {"Eco", "Normal", "Boost", "Silent", "Manual", "Auto"};
const char *unitLabels[] = {"C", "F", "%", "ppm"};
uint8_t fakeSettings[32];

uint8_t settingsRead(uint16_t address) {
    if(address >= sizeof(fakeSettings)) {
        return 0;
    }
    return fakeSettings[address];
}

void settingsWrite(uint16_t address, uint8_t value) {
    if(address < sizeof(fakeSettings)) {
        fakeSettings[address] = value;
    }
}

void actionCallback(uint8_t id) {
    app.lastAction = id;
    widgetLogs.add(LCDML3_LOG_INFO, "Action executed");
}

void logicBegin() {
    widgetTime.begin(14, 32, 5, true);
    widgetTimer.begin(0, 15, 0);
    widgetDate.begin(2026, 5, 15);
    widgetRadio.begin(6, 4, 1);
    widgetCheck.begin(6, 4, 0x05);
    widgetState.begin(3, LCDML3_STATE_AUTO);
    widgetNumeric.begin(75, 0, 100, 5, false);
    widgetFloat.begin(1.250f, 0.0f, 20.0f, 0.050f, 3, false);
    widgetIp.begin(192, 168, 1, 42);
    widgetWifi.begin();
    widgetWifi.setCredentials("Workshop", "secret");
    widgetWifi.setState(LCDML3_NET_IDLE);
    widgetBluetooth.begin();
    widgetBluetooth.setBleMode(true);
    widgetBluetooth.setState(LCDML3_BT_BLE_SCAN);
    widgetHeader.begin(EXAMPLE_TITLE, EXAMPLE_BOARD, 1);
    LCDML3_applyThemePreset(widgetTheme, LCDML3_THEME_HIGH_CONTRAST);
    widgetStatus.setIcon(LCDML3_ICON_WIFI, true);
    widgetStatus.setIcon(LCDML3_ICON_SD, true);
    widgetDebug.begin(13);
    widgetConfirm.begin(false);
    widgetPin.begin(4);
    widgetProgress.begin(100);
    widgetWizard.begin(5);
    widgetSettings.begin(settingsRead, settingsWrite);
    widgetEncoder.begin(1, 10, 90);
    widgetGraph.begin(0, 1023);
    widgetLogs.clear();
    widgetLogs.add(LCDML3_LOG_INFO, "Boot");
    widgetLogs.add(LCDML3_LOG_WARN, "Demo mode");
    widgetAlarms.begin();
    widgetAlarms.set(0, 7, 30, 0x1F, true);
    widgetUnits.begin(unitLabels, 4, 0);
    widgetOta.begin();
    widgetOta.setState(LCDML3_OTA_CHECKING);
    widgetCalibration.begin(2);
    widgetCalibration.captureRaw(0, 100, 0);
    widgetCalibration.captureRaw(1, 900, 1000);
    widgetActions.begin(actionCallback);
    widgetFiles.begin(4);
    widgetFiles.setItemCount(18);
    widgetDiag.begin();
    widgetDiag.setI2CFound(3);
    widgetDiag.setWiFiFound(7);
    widgetDiag.setHeap(42120);
    app.redraw = true;
}

void logicLoop() {
    app.now = millis();

    if(app.now - app.lastSensorMs >= 1000) {
        app.lastSensorMs = app.now;
        app.sensorValue = (app.sensorValue + 73) % 1024;
        widgetGraph.add(app.sensorValue);
        widgetDiag.setUptime(app.now);
        widgetProgress.add(5);
        if(widgetProgress.isDone()) {
            widgetProgress.set(0);
        }
        widgetOta.setProgress(widgetProgress.percent());
        app.redraw = true;
    }

    menuDynamicHandleInput(app.lastInput);
}

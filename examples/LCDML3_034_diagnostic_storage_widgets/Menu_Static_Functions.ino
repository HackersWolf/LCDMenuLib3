// ##########################################################################################################################
// ########### MENU STATIC FUNCTIONS ########################################################################################
// ##########################################################################################################################

void menuStaticBegin() {
    Serial.println(F("Static pages ready: ABOUT, HELP, DEFAULTS, MONITOR."));
}

void menuStaticAbout() {
    Serial.println(F("LCDMenuLib3 Cannaduino-style example."));
    Serial.println(F("The layout mirrors a 128x64 GLCD project while staying Serial portable."));
}

void menuStaticDefaults() {
    widgetSettings.writeInt32(0, widgetNumeric.getValue());
    widgetSettings.writeFloat(4, widgetFloat.getValue());
    widgetSettings.commit();
    widgetLogs.add(LCDML3_LOG_INFO, "Defaults saved");
}

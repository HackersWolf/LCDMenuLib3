// ##########################################################################################################################
// ########### CONTROL ######################################################################################################
// ##########################################################################################################################

void controlBegin() {
    Serial.println(F("Controls: n=next page, p=previous page, u/d/l/r=edit, e=enter, q=back/help"));
}

void controlLoop() {
    app.lastInput = 0;

    if(Serial.available() > 0) {
        app.lastInput = (char)Serial.read();
        app.redraw = true;
    }
}

void controlConsumeHelp() {
    Serial.println(F("----------------------------------------------------------------"));
    Serial.println(F("n/p page  u/d value or cursor  l/r field/state  e select/toggle"));
    Serial.println(F("q prints this help. The sketch renders a 128x64 style ASCII screen."));
    Serial.println(F("----------------------------------------------------------------"));
}

#include "SparkFunBME280.h"
//Library allows either I2C or SPI, so include both.
#include "Wire.h"
BME280 mySensor;
void setup() {
    	mySensor.settings.commInterface = I2C_MODE;
	mySensor.settings.I2CAddress = 0x77;
	mySensor.settings.runMode = 3; //Normal mode
	mySensor.settings.tStandby = 0;
	mySensor.settings.filter = 0;
	mySensor.settings.tempOverSample = 1;
	
	Serial.begin(57600);
	
	//Calling .begin() causes the settings to be loaded
	delay(10);  //Make sure sensor had enough time to turn on. BME280 requires 2ms to start up.
	mySensor.begin();

    //WiFiManager
    //Local intialization. Once its business is done, there is no need to keep it around
    //reset saved settings
    //wifiManager.resetSettings();
    
    //set custom ip for portal
    //wifiManager.setAPStaticIPConfig(IPAddress(10,0,1,1), IPAddress(10,0,1,1), IPAddress(255,255,255,0));
	if(mySensor.readTempF() >= 30)
	{
    		reportThaw();
	}
	else
	{
		ESP.deepSleep(300e6); //Send ESP into deep sleep for 5 minutes.
	}
}

void loop() {
    // put your main code here, to run repeatedly:
    
}

void reportThaw(){
    Serial.println("Printer is being thawed!");
    WiFiManager wifiManager;
    wifiManager.autoConnect("FridgeMonitor");
    HTTPClient http;
    http.begin("http://launchify-fridge.azurewebsites.net/freezerthaw/?phone=6095800390");
    int httpCode = http.GET();
    delay(10000);
    
}

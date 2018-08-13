/*
*This Firmware is to connect to a WPA2 Enterprise network with a ESP8266.
*Tested on NodeMCU.
***Arduino IDE Settings**
*Board: "NodeMCU 1.0 (ESP12E Module)"
*Flash Size: "4M (1M SPIFFS)"
*Debug Port: "Disabled"
*Debug Level: "None"
*lwIP Variant: "v2 Higher Bandwidth"
*CPU Frequency: "160 MHz"
*Upload Speed: "921600"
*Erase Flash: "All Flash Contents"
*Programmer: "AVR ISP"
*/

/* Lynton Brown 08/06/2018*/

#include <ESP8266WiFi.h> //Include ESP8266WiFi Library

extern "C" { //Create C Linkage
    #include "user_interface.h" //Include user_interface Library
    #include "wpa2_enterprise.h" //Include wpa2_enterprise Library
    }

static const char* ssid = "NETWORKSSID"; //SSID(Network) Name
static const char* username = "USERNAME"; //Login Name
static const char* password = "PASSWORD"; //Password
int connectionFlag=0; //set state of flag

void ConnectToWPA2Enterprise(){ //Funtion to connect to WPA2 Enterprise
    Serial.print("\r\nDisconnecting from last APs");
    ESP.eraseConfig();  //Erase Network Information already loaded
    delay(1000); //Stop for 1 second
    WiFi.mode(WIFI_STA); //Set WiFi Station Mode
    WiFi.disconnect(); //Disconnect from any station
    delay(1000); //Stop for 1 second
    Serial.print("\r\nPreparing Network Connection...");

    struct station_config wifi_config; //Create Structure
    memset(&wifi_config, 0, sizeof(wifi_config)); //Fill block in memory with 0
    strcpy((char*)wifi_config.ssid, ssid); //Copy ssid to structure with null at end

    wifi_set_opmode(0x01); //Set Wi-Fi working mode and save it in flash(**Use Either HEX or NAME** 0x00: NULL_MODE 0x01: STATION_MODE  0x02: SOFTAP_MODE  0x03: SATATIONAP_MODE)
    wifi_station_set_config(&wifi_config); //Set Wi-Fi Station configuration, and save it to flash. Sets up to send ssid
    wifi_station_clear_enterprise_cert_key(); //Release user certificate and private key resources and clear related status after being connected to the WPA2_Enterprise AP.
    wifi_station_set_wpa2_enterprise_auth(1);//Set authentication of WPA2_Enterprise. (0: disable authentication of WPA2_Enterprise, clear the status 1: enable authentication of WPA2_Enterprise)
    wifi_station_set_enterprise_identity((uint8*)username, strlen(username)); //
    wifi_station_set_enterprise_username((uint8*)username, strlen(username)); //Set ESP8266 Station’s user name for connecting to WPA2_Enterprise AP.
    wifi_station_set_enterprise_password((uint8*)password, strlen(password)); //Set the password for connecting to WPA2_Enterprise AP. It is used for EAPTTLS / EAP-PEAP authentication.
    wifi_station_connect(); //Connect Wi-Fi Station to AP.

    Serial.print("\r\nConnection in Progress..."); //Send Header to Serial Port
    unsigned long startMillis = 0; //Create variable and set to 0
    while (WiFi.status()!=WL_CONNECTED){ //While not connected to the SSID
        unsigned long endMills = millis(); //create varabile and set to current millis (time since power on)
        delay(2000);
        Serial.print("."); //Send "." to Serial Port as Place Holder of where the code is at
        }
    Serial.println(); //Send Return Carrage to Serial Port
    Serial.println("WiFi connected to "+String(ssid)); //Send Header to Serial Port
    Serial.println("IP address: "); //Send Header to Serial Port
    Serial.println(WiFi.localIP()); //Send IP Address to Serial Port
    connectionFlag=1;
    return;
    }
    
void setup(){ //Function to run on startup
    Serial.begin(115200); //Open Serial Port with baudrate 9600
    }

void loop(){
    if(connectionFlag==0;){ //Check state of flag
        ConnectToWPA2Enterprise(); //Call function to connect to WPA2 Enterprise network
        }
    }

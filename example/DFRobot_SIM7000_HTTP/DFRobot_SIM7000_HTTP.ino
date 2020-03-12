 /*
  * File  : DFRobot_SIM7000_HTTP.ino
  * Power : SIM7000 needs 7-12V DC power supply
  * Brief : This example verify HTTP connection over a HTTP request
  *         With initialization completed, we connect to server POST data and GET data
  *         Thus we finished the HTTP POST and GET verification
  * Note  : If you use NB-IOT please confirm that the IOT is in the whitelist of your NB card
  *         If you use Mega please connect PIN8 PIN10 and set PIN_RX = 10
  */

  #include PIN_TX 7
  #include PIN_RX 8

  //login website http://www.thingspeak.com
  #define deviceNo "DEVICE ID"
  #define sensorId "SENSOR ID"
  #define value "VALUE"

  //this url is use for post data to thingspeak
  #define POSTURL " "
  //this url is use for get data from thingspeak
  #define GETURL " "

  softwareSerial mySerial(PIN_RX, PIN_TX);
  DFRobot_SIM7000 sim7000;
  

void setup() {
  //variable
  int signalStrength, dataNum;
  Serial.begin(115200);                       //communication baut rate 
  while(!Serial);
  sim7000.begin(mySerial);
  Serial.println("Hidupkan SIM7000");
  if(sim7000.turnON()){                       // Turn on sim7000    
    Serial.println("Hidup !!");
  }

  Serial.println("Set baud rate");
  while(1){
    if(sim7000.setBaudRate(19200){
      //Set SIM7000 baud rate from 115200 to 19200 reduce the baud rate to avoid distortion
      Serial.println("Set baud rate:19200");    
      break;
    }else{
      Serial.println("gagal untuk set baud rate");
      delay(1000);
    }
  }

  Serial.println("Cek Sim Card");
  if(sim7000.checkSIMStatus()){             //check sim card
    Serial.println("SIM card Siap");
  }else{
    Serial.println("Sim card error, cek jika kamu belum memasukkan sim card dan restart SIM7000");
    while(1);
  }

 Serial.println("Set net mode.....");
 while(1){
  if(sim7000.setNetMode(GPRS)){             //set net mode GPRS
    Serial.println("Set GPRS mode");
    break;
  }else{
    Serial.println("Gagal untuk set mode");
    delay(1000);
  }
 }

 Serial.println("Dapatkan kualitas sinyal");
 signalStength=sim7000.checkSignalQuality();        //Check signal quality from (0-30)
 Serial.print("signalStrength= ");
 Serial.println(signalStrength);
 delay(500);    //delay 1/2 second 

 Serial.println("Attaching service....");
 while(1){
  if(sim7000.attacthService()){                   //open the connection
    Serial.println("Attach Service");
    break;
  }else{
    Serial.println("Fail to attach service");
    delay(1000);
  }
 }

 Serial.println("Init http...");
 while(1){
  if(sim7000.httpInit(GPRS)){                 //init http service
    Serial.println("HTTP init");
    break;
  }else{
    Serial.println("Fail to init http");
  }
 }

  Serial.print("POST ke");
  Serial.printl(POSTURL);
  String httpbuff;
  httpbuff += "{\"deviceNo\":\"";                          //{
  httpbuff += deviceNo;                                    //   "deviceNo" : "DEVICE NO",
  httpbuff += "\",\"sensorDatas\":[{\"sensorsId\":";       //      "sensorDatas":[{
  httpbuff += sensorsId;                                   //          "sensorsId" :  SENSOR ID,
  httpbuff += ",\"value\":\"";                             //          "value"     : "  VALUE  "
  httpbuff += value;                                       //       }]
  httpbuff += "\"}]}";                                     //}


  while(1){
    if(sim7000.httpPost(POSTURL,httpbuff)){
      Serial.println("Post sukses");
      break;
    }else{
      Serial.println("Gagal untuk post");
    }
  }

  Serial.print("GET from");
  Serial.println(GETURL);
  sim7000.httpGet(GETURL);                      //http get

  Serial.println("Disconnect");
  sim7000.httpDisconnect();                     //disconnect
  Serial.println("Tutup jaringan");
  sim7000.closeNetwork();                       //close network
  Serial.println("Matikan sim7000");
  sim7000.turnOFF();                            //turn off sim7000
 
}

void loop() {
  delay(1000);
}

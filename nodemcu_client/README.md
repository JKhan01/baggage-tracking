## The ESP8266 NodeMCU Client

### You need to setup the RFID and NodeMCU libraries before getting started.

- To setup the NodeMCU dependancies, go to the link below:
>> [Click Here](https://create.arduino.cc/projecthub/electropeak/getting-started-w-nodemcu-esp8266-on-arduino-ide-28184f) to go to the link.
>>> Follow the first two steps in the blog and verify the setup from step 3.

- To setup the use of RFID Reader-Tags, go to the link below:
>> [Click Here](https://www.instructables.com/MFRC522-RFID-Reader-Interfaced-With-NodeMCU/) for the blog post.
>>> **Just Follow the Step Number 4 for library download.**

***For RFID Reader to NodeMCU wiring connection, follow step 3 in the [link](https://www.instructables.com/MFRC522-RFID-Reader-Interfaced-With-NodeMCU/)***

### Once the above setup is done, you are all set to upload the final code.
> The final integrated code is in [esp_api_rfid](./esp_api_rfid/).

> The code to test rfid and nodemcu connection is in [rfid_reader_nodemcu](./rfid_reader_nodemcu/)

> The code to test flask server and nodemcu connection is in [esp_api_test](./esp_api_test/)
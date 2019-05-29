# DUSTBOX PM2.5 Detector

Prerequisites:
- Arduino IDE
- ThingSpeak

Components Used:
- TFT 2.2" LCD Color module 176x220 ILI9225
- PMS 3003 PM2.5 Plantower Technology
- NodeMCU (Version 3)
- Pin Adapter SG00343

ThingSpeak:

- [ThingSpeak](http://www.thingspeak.com) is an open “Internet of Things” application and API to store and retrieve data from things using HTTP over the Internet or via a Local Area Network. With ThingSpeak, you can create sensor logging applications, location tracking applications, and a social network of things with status updates.

- ThingSpeak is available on the [ThingSpeak Community](http://community.thingspeak.com/) site which features a [Blog](http://community.thingspeak.com/),[Forum](http://community.thingspeak.com/forum/),[Documentation](https://thingspeak.com/docs) and [Tutorials](https://thingspeak.com/docs/tutorials)

---
 Circuit Diagram:

 ![Schema](doc/images/circuit_diagram.jpg?raw=true=20x)
 
 Connect to ThingSpeak:
 
 ![Prototype](doc/images/thingspeak_exam.JPG?raw=true=60x)
 
 ---
Connect to Thingspeak via "dustBox.ino" [Example](https://www.mathworks.com/help/thingspeak/read-and-post-temperature-data.html)

	String urlTP = "thingspeak api" + String(data.PM_AE_UG_1_0) + "&field2=" + String(data.PM_AE_UG_2_5) + "&field3=" + String(data.PM_AE_UG_10_0);
 
 
 That's it.
 ---
 ![final](doc/images/final.jpg?raw=true=60x)

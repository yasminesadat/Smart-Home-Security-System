# Smart Home Security System

## Abstract
The **Smart Home Security System** is an advanced security solution designed to enhance home safety by integrating modern sensor technologies and providing real-time alerts through a web interface. The system leverages **motion detection sensors**, **infrared sensors**, and **ultrasonic sensors** to monitor entry points and critical areas of the house. Through **Server Side Includes (SSI)** and **CGI (Common Gateway Interface)**, the web app allows homeowners to interact with the system using HTTP requests, providing intuitive control and automated responses. This system can be accessed via a **web browser on mobile devices** when connected to the same local network as the Raspberry Pi Pico W microcontroller.

## Features
- **Motion Detection at Entry Points**: Detects movement near the door using ultrasonic and infrared sensors.
- **Real-time Alerts**: Sends notifications to the web app, informing homeowners of detected intrusions.
- **Automated Responses**: Triggers alarms, controls lights, and manages the door lock mechanism in response to detected intrusions.
- **Web-Based Control**: Homeowners can manually control the system, including deactivating the alarm, controlling the servo motor, or resetting the system via a mobile web app.

## Methods
<details>
<summary>Components and Workflow</summary>

### Hardware Components
- **Infrared Sensor**: Detects human presence inside the house, specifically in sensitive areas.
- **Ultrasonic Sensor**: Measures distance to detect approaching intruders near the door.
- **Buzzer**: Emits an audible alarm to alert neighbors and deter intruders.
- **Servo Motor**: Controls the door, allowing it to open or close based on system responses.

### Motion Detection Workflow
1. **Ultrasonic Sensor**: Continuously measures the distance to detect when an object is near the door. If an object is detected within 20 cm, the system triggers an alert.
2. **Infrared Sensor**: Monitors for movement in high-priority areas, such as rooms with valuable assets. If motion is detected, it confirms an intrusion.
3. **Automated Actions**:
   - **Entry Point Detection**: If motion is detected at the door, the buzzer sounds, and real-time notifications are sent to the web app.
   - **Critical Area Detection**: When movement is detected in a sensitive area, the system activates a buzzer and turns on the lights.

### Web App & Communication

The system uses a **web-based app** that can be accessed from a mobile browser when connected to the same Wi-Fi network as the **Raspberry Pi Pico W microcontroller**. The web app is built using **SSI (Server Side Includes)**, **CGI (Common Gateway Interface)**, and **HTTP requests** to facilitate real-time communication and control between the server (Pico W) and the client (mobile web app).

- **SSI**: Enables dynamic content inclusion in HTML pages. The web app uses SSI to update sensor data and system status in real-time.
- **CGI**: Allows the web app to communicate with the Pico W and perform server-side actions, such as activating/deactivating alarms, controlling the door servo motor, or sending notifications.
- **HTTP Requests**: The web app sends HTTP requests to the Pico W to trigger actions (e.g., turn on the alarm, open the door) based on sensor data and user interactions.

### Flow of Operation:
1. **Intrusion Detection**: When motion is detected by the sensors, the Pico W microcontroller sends data to the web app via HTTP requests.
2. **Web App Response**: The user receives real-time alerts on their mobile browser and can take immediate actions, such as deactivating the alarm, opening the door, or resetting the system.
3. **Manual Controls**: Homeowners can deactivate or reset the light system through the mobile web app. A sound system feature is under development.

</details>

## Images

### Home Model 
![Home](https://github.com/user-attachments/assets/7cf49dba-d99c-4ccf-9d59-021c6947ba0b)

### App Screenshots
<p float="left">
  <img src="https://github.com/user-attachments/assets/24992bb8-15e0-4f03-b0e5-8901531772da" width="200" />
  <img src="https://github.com/user-attachments/assets/34291f95-a148-4a26-94c0-4733bb07f31e" width="200" />
  <img src="https://github.com/user-attachments/assets/e0157c2f-2202-495c-aa47-c12fa7d04d0c" width="200" />
  <img src="https://github.com/user-attachments/assets/c1854913-0db9-4c9c-96e7-c2302b763fed" width="200" />
  <img src="https://github.com/user-attachments/assets/0954cb8b-3bae-4573-9853-e59d50eeada6" width="200" />
</p>

## Setup

### Hardware Setup
1. **Connect the Ultrasonic Sensor** to the designated GPIO pins on the Raspberry Pi Pico W.
2. **Connect the Infrared Sensor** to the appropriate input pins.
3. **Attach the Buzzer** to the output pin for audio alerts.
4. **Integrate the Servo Motor** to control the door’s movement.
5. **Add LEDs** to have an additional light system with its controls.

### Web App Access
- Open the web app on any browser, using the **IP address** of the Raspberry Pi Pico W, ensuring that your device is on the same local network.
- The network configurations, including the Wi-Fi credentials and other settings, are found in the **main.c** file.
- Once the code is uploaded to the microcontroller, open the **serial monitor** to see the IP address where the web app has been deployed.

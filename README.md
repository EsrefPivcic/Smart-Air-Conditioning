# Smart-Air-Conditioning

## Project Description:

The Smart-Air-Conditioning project is designed to simplify the management of various air conditioning devices. The goal of the project is to provide a web application for controlling air conditioning devices via internet communication.

The project consists of three main components:

1. **Control Panel:** This is a web application (HTML and JS) accessible from a browser. It allows users to control the climate settings remotely.

2. **Execution Side:** This is implemented using a NodeMCU ESP-12f with a DHT-22 temperature and humidity sensor, as well as an LED indicator light. The LED light is used for demonstration purposes to represent the operation of the air conditioning unit.

3. **Real-time Database:** A real-time database is created using Google's Firebase service. It enables communication between the control panel and the execution side.

## Functionality:

### Automatic Climate Control:

- When using automatic climate control, the user can simply select their desired temperature using a slider on the web application. In this case, the web application sends the desired temperature to the real-time database.

- The execution side checks this temperature value every 1000 milliseconds. If the desired temperature is higher or lower than the current temperature, the heating or cooling will automatically activate until the desired temperature is reached.

- After reaching the desired temperature, the climate control system will turn off. It will re-activate if there is a change in temperature (+/-1 degree tolerance) or if the user adjusts the desired temperature again.

- The heating and cooling are demonstrated using a LED light, which will glow red for heating and blue for cooling, with varying intensity.

### Manual Climate Control:

- Users also have the option for manual control. The web application provides buttons to enable or disable automatic control.

- If the user disables automatic control, the slider for setting the desired temperature in automatic mode will be disabled. Instead, two sliders for manual control of heating and cooling will be enabled.

- For example, by selecting a value on the heating slider, the user can activate heating at a certain intensity. Changing the value on the slider will adjust the heating intensity or turn it off.

- If the user decides to manually activate cooling while heating is already active, the cooling will start at the desired intensity, and the heating will automatically turn off.

### Reading Current Temperature and Humidity:

- The web application displays the current temperature and humidity values in the room where the air conditioning unit is located. These values refresh every 30 seconds.

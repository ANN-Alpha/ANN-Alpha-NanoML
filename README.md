# Pronet ANN Alpha 2.1.1
This is the Pronet ANN, an easy to use, lightweight machine learning algoritim for microcontrollers. Traditionaly, you would install a heavy machine learning module that is around 0.5 GB ( Tensorflow ), and they only run on a CPU. But now you can take a module that is only a few Kilobytes, and run it on microcontrollers as well!

Here is our release log for the Pronet ANN: [Release log](https://github.com/PronetAI/Artifical-nueral-network/blob/main/Release-logs.md).

## Installation
To install the module, enter the following on your terminal inside an project folder.
```
$ git clone https://github.com/Pronet/Artifical-nueral-network.git
```
The code of this moudle is inside the `main.ino` file. You will run the code there per your requirments and settings. 

## Hardware
For this application we recomend for the best performence, an Arduino Nano 33 BLE Sense. This is because due to the very powerful processor and enchanced AI Capabilites, it is perfect to run this application. In general, any microcontroller will work for this project BUT some of them are very slow and it will take a long time to run this application. Below we have a list of the microcontrollers fit for the job, and microcontrollers that are not good for this application.

### Good Speed microcontrollers
* Arduino Nano 33 BLE(Sense)
* Arduino Mega 2560 R3
* ESP32 / ESP32 Wifi
* Arduino Maker Vidor 4000
* RP2040
* MKR WAN 1300
### Low Speed microcontrollers
* RPI Pico
* Arduino Uno / Wifi Rev3
* Arduino Nano, Micro, Lenardo, Every
## Functions
### Number of nodes
This part of the code determines how many nodes there are throughout the whole nueral network.
```
const int PatternCount = 10; const int Input_Nodes = 7;const int Hidden_Nodes = 8; const int Output_Nodes = 4;
```
You can alter it by simply changing the number inside the variable

### Initial Parameters
Here we are determining how fast the network learns, the success margin, as well as the maximum values for the random weights
```
const float LearningRate = 0.85; const float Momentum = 0.9; const float InitialWeightMax = 0.5; const float Success = 0.0004;
```
You can alter it by simply changing the number inside the variables

### Input node array
In this array we are storing the different set's of inputs we are going to give the network
```
const byte Input[PatternCount][Input_Nodes] = 
 {{ 1, 1, 1, 1, 1, 1, 0 }, { 0, 1, 1, 0, 0, 0, 0 },
  { 1, 1, 0, 1, 1, 0, 1 }, { 1, 1, 1, 1, 0, 0, 1 },
  { 0, 1, 1, 0, 0, 1, 1 }, { 1, 0, 1, 1, 0, 1, 1 }, 
  { 0, 0, 1, 1, 1, 1, 1 }, { 1, 1, 1, 0, 0, 0, 0 },  
  { 1, 1, 1, 1, 1, 1, 1 }, { 1, 1, 1, 0, 0, 1, 1 }}; 
```
We can add or remove values by simply editing the array.

**NOTE: THE NUMBER OF SINGLE BINARY DIGITS IN EACH ELEMENT OF THE ARRAY MUST MATCH THE NUMBER OF INPUT NODES**

### Input node array
In this array we are storing the different set's of target outputs we want the metwork to output.
```
const byte Target[PatternCount][Output_Nodes] = 
 {{ 0, 0, 0, 0 }, { 0, 0, 0, 1 }, 
  { 0, 0, 1, 0 }, { 0, 0, 1, 1 }, 
  { 0, 1, 0, 0 }, { 0, 1, 0, 1 }, 
  { 0, 1, 1, 0 }, { 0, 1, 1, 1 }, 
  { 1, 0, 0, 0 }, { 1, 0, 0, 1 }};
```
We can also change this by altering the arrays elements.

**NOTE: THE NUMBER OF SINGLE BINARY DIGITS IN EACH ELEMENT OF THE ARRAY MUST MATCH THE NUMBER OF OUTPUT NODES**

### Setup loop
In here, you can define some "finer" details about the program, just how you want the information to be outputed
```
void setup(){ Serial.begin(9600); Print_Time = 1;}  
```
Here we can change at how many bytes per second the serial monitor will output the information, and how much time it takes to output one piece of information

*We are not responible if any of your hardware is damaged during the activity of this program. We are put the suggested hardware in order to run this application. Speeds of processing varies from device to device.*

*We do not have any affiliation with the Arduino company nor is this sponsored by them.*

*COPYRGIHT PRONETAI 2022*

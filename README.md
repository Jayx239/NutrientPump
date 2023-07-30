# Nutrient Pump

This is the mono repo for the nutrient pump system. The repo includes the Arduino device code and web api for invoking the nutrient pumps.

## Tutorial:

This implementation was based off of the following tutorial: https://arduinogetstarted.com/tutorials/arduino-relay

The link has details on the required arduino components and their setup.

## Parts list

TODO: add parts list

## test_script

This is the arduino code. It takes in a json string terminated with newline as the input. As of initial commit the command format is:

```json
{ "pid": 0, "dms": 500 }
```

## web/pumpControlApi

Nodejs webapp that provides api for running pump on arduino.

POST /execute

Request:

```json
{
  "pumpId": 0,
  "durationMs": 500
}
```

Arguments:
PumpId is the index of the pump in the arduino code. 0 based index

durationMs is the duration the pump will run for in MS.

There is also a web ui for this flow at /executer.html.

## Helpful serial documentation

https://serialport.io/

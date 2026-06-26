# penguin

><b>P</b>erception-<b>E</b>nabled <b>N</b>avigation and <b>G</b>eneral-<b>U</b>tility <b>IN</b>telligence

Hybrid differential legged-wheeled biped rover for embodied AI, computer vision, and autonomous navigation.

 ### Status
>- Controller manufactured and partially assembled.
>- Soldering and hardware validation in progress.
>- Mechanical components currently being printed.

<details>
<summary><strong>Table of Contents</strong></summary>

- [penguin](#penguin)
    - [Status](#status)
  - [Overview](#overview)
  - [Features](#features)
    - [Controller](#controller)
    - [Mechanical](#mechanical)
  - [Architecture](#architecture)
    - [Systems](#systems)
  - [Electrical](#electrical)
    - [Power System](#power-system)
    - [Microcontroller](#microcontroller)
    - [Motor Drivers](#motor-drivers)
    - [Sensor Interfaces](#sensor-interfaces)
    - [Vision Interface](#vision-interface)
  - [Mechanical](#mechanical-1)
    - [Chassis](#chassis)
    - [Leg Assembly](#leg-assembly)
  - [Firmware](#firmware)
  - [Repository Structure](#repository-structure)
  - [Gallery](#gallery)

</details>

I built penguin cause I wanted to create an intelligent robot from the ground up. 

<table>
  <tr>
    <td width="50%">
      <img src="/media/images/penguin_controller_front_3D.png">
    </td>
    <td width="50%">
      <img src="/media/images/penguin_controller_back_3D.png">
    </td>
  </tr>
  <tr>
    <td width="50%">
      <img src="/media/images/penguin_body_front_3D.png">
    </td>
    <td width="50%">
      <img src="media/images/penguin_body_side_3D.png">
    </td>
  </tr>
</table>

## Overview
Put simply, Penguin is a platform for experimentation with intelligent robotics. 

The project began as a simpler, maze-solving rover for a course project (MREN 178 - DSA). My team couldn't deliver the rover in time
so we scaled down. I had already started with hardware, which pushed me to adopt the project into my own, with the intent to expand it past maze-solving.  

After that term (Winter '26), I designed a controller PCB and the necessary compoments for the chassis. 

Now its June, and I'm documenting everything and writing
firmware.

## Features 
### Controller
The controller is powered by a 7.4V LiPo Battery and driven by an ESP32-S3 (N16 1U).

Below is a list of features from power circuits to various peripherals. 
- Power-entry circuitry with OC/OV protetction, RPP, PI-filter, and dual-mosfet BMS.
- Regulation circuit featuring buck converter, 5V ORing, and LDO for logic power (3V3) 
- ESP32-S3 breakout circuitry with USB differential routing, S3 boot mode selection and reset toggle. 
- Controlled power delivery via CMOS circuits for main motor power. 
- N20 motors with encoders for wheels driven by a DRV8833 chip. 
- DS3218 20kg Servo motors for hip joints, driven by PWM signals from S3. 
- OV2640 camera with FPC connector and three-level voltage regulation. 
- I2C bus with three ToF sensors, OLED screen, and GPIO expander.
- Audible and visual indicators. 
- cool silkscreen penguin. 

### Mechanical 
- Three-layer internal stackup for housing motors, controller board, and routing cables.
- Integrated vents and ports for sensors and devices, air flow, and weight reduction.
- Hybrid locomotion system with wheels and legs.
- Multi-bar leg assembly - pivot arm, mounting arm (hip), leg. 

## Architecture 
### Systems 

## Electrical 
This section provides low-level explanations of the significant circuits of each "module" of the controller.

I encourage you to clone the repo or you use [KiCanvas](https://kicanvas.org/) to look at the schematic and board files. 

### Power System

**Power Entry**
<p align="center">
  <img src="/media/images/circuits/pwr/power_entry.png" width="700">
</p>

**Battery-Management-System (BMS)**
<p align="center">
  <img src="/media/images/circuits/pwr/bms.png" width="700">
</p>

**Voltage Regulation (I)**
<p align="center">
  <img src="/media/images/circuits/pwr/buck.png" width="700">
</p>

**5V ORing**
<p align="center">
  <img src="/media/images/circuits/pwr/oring.png" width="700">
</p>


**Voltage Regulation (II)**
<p align="center">
  <img src="/media/images/circuits/pwr/ldo.png" width="700">
</p>

**Controlled Motor Power Delivery**
<p align="center">
  <img src="/media/images/circuits/pwr/cmos.png" width="700">
</p>

**Voltage Sensing**




### Microcontroller

### Motor Drivers

### Sensor Interfaces

### Vision Interface

## Mechanical 
### Chassis 
### Leg Assembly

## Firmware

## Repository Structure 

## Gallery 

---
Jeevan Sanchez, 2026

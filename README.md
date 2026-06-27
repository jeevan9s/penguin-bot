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
  <img src="/media/images/circuits/pwr/power_entry.png" width="500">
</p>

The 7.4V battery power enters through a Molex Micro-Fit (3mm Pitch) header, where it is then met with a 12V 7A fuse for over-current protection. A PTC resettable fuse was selected for durability. 

The positive battery line is then protected from voltage spikes with a Transient Voltage Supression (TVS) diode placed in paralell for clamping. 
- The diode's standoff @ `9V`
- Breakdown @ `10V`
- Clamps @ `15.4V`

The positive line then goes through a Reverse Polarity Protection (RPP) circuit, using a P-Channel MOSFET for lossless efficiency (lower V drop than standard diodes). 

A Zener diode and resistor is placed between the MOSFET's gate and source for gate over-voltage protection. 

A bulk electrolytic (100μF) capacitor, ferrite bead, and high-frequency (0.1μF) capacitor are then placed to create a third-order low pass filter (π-filter). 
- This is used to smooth voltage spikes and reduce EMI.

The ferrite bead was primariy selected for its saturation current and DCR. 

The approximate current draw with safety margin $I_{net}$ is 5A.

$I_{\mathrm{sat}} = 1.5 \times I_{\mathrm{net}} \approx 10 A$

Minimize heat dissipation. 

$DCR$ is 10Ω

$P_{heat} = DCR \times I_{\mathrm{sat}} \approx 0.25 W$

**Battery-Management-System (BMS)**
<p align="center">
  <img src="/media/images/circuits/pwr/bms.png" width="500">
</p>

The BMS system uses the negative terminal of the battery and features a `HY2120` protection IC with a dual-mosfet to form the system's **GND**. 

The IC uses the balance tap of the battery (VC ~ 3.7V nominal) to monitor the level of Cell 1, while using the main positive terminal (VDD ~ 7.4V nominal) to monitor Cell 2.

This allows the IC to indepdently track each cell's voltage and trigger the dual-MOSFET to cut off power if either cell suffers from overcharge or overdischarge. 

**Voltage Regulation (I)**
<p align="center">
  <img src="/media/images/circuits/pwr/buck.png" width="500">
</p>

The controller uses a cascade regulation system, starting with the `TPS5405DR` buck converter. 

The input voltage is `VBATT` (7.4V), after the protection and filtering circuitry, and the output is 5V. 

The $R_{osc}$ value will determine the switching frequency of the converter. 

Switching frequency is governed by the relationship. 
$$R_{\text{OSC}} (\text{k}\Omega) = 21.82 \cdot f_{\text{SW}}^{-1.167}$$

I chose a value of `100kΩ` for a $f_{SW}$ of approximately `271 kHz`

For the soft-start capacitor $C_{ss}$ , I chose a value of `10nF` for a soft-start time of `5ms`

The values below were taken from the [TPS5405DR Datasheet](https://www.ti.com/lit/gpn/tps5405)

$$
C_{SS} = \frac{t_{SS} \cdot I_{SS}}{V_{REF}}
$$

$$
C_{SS} = \frac{(5\,\mathrm{ms})(2\,\mathrm{\mu A})}{0.8\,\mathrm{V}}
= 12.5\,\mathrm{nF}
\approx 10\,\mathrm{nF}
$$

The inductor values were chosen using the equation below. 

$$
L=\frac{V_{out}\left(V_{in}-V_{out}\right)}
{V_{in}f_{sw}\Delta I_L}
$$

Using our calculated $f_{sw}$ from above and our voltage requirements (8.4V in, 5V out):
$$
L=
\frac{(5\,\mathrm{V})(8.4\,\mathrm{V}-5\,\mathrm{V})}
{(8.4\,\mathrm{V})(525\,\mathrm{kHz})(0.3\,\mathrm{A})}

\approx
10\,\mathrm{\mu H}
$$

The Schottky diode is rated for the `2A` output current and `8.4V`

**5V ORing**
<p align="center">
  <img src="/media/images/circuits/pwr/oring.png" width="500">
</p>

The `5V` rails from both USB and the buck converter are combined using an OR-ing circuit (Dual Ideal Diodes) to prevent backfeeding before feeding the second stage of regulation.

In this configuration, the outputs of both `LM66100` ideal diode controllers are tied together to form the shared `5V` rail. The `CE` pins of each device are also tied to the output rail, ensuring both controllers are only enabled once the rail is present 

**Voltage Regulation (II)**
<p align="center">
  <img src="/media/images/circuits/pwr/ldo.png" width="500">
</p>

The second stage of voltage regulation involes a Low-Dropout Regulator (LDO), the `AMS1117`

It is fed the combined `5V` rail from the OR-ing circuit to produce the controller's logic-level voltage: `3V3`

**Controlled Motor Power Delivery**
<p align="center">
  <img src="/media/images/circuits/pwr/cmos.png" width="500">
</p>

The power for the N20 and Servo motors is controlled using a complementary-MOSFET (CMOS) setup, driven by a digital `HIGH` from the S3.

- When the control signal is low or floating, the N-channel MOSFET remains off and a pull-up resistor holds the gate of the P-channel MOSFET at the supply voltage, keeping it disabled and disconnecting the load rail.

- When the control signal is driven high, the N-channel MOSFET turns on and pulls the P-channel gate low, creating sufficient gate-source voltage to enable conduction and connect the supply to the load.

This controlled power line, `VMOT = 7.4V` powers the supply voltage of the `DRV8833` chip, and is converted via local buck converter to produce `VSERVO = 5V`


**Voltage Sensing**

A resistor divider circuit is used to produce a signal to be read by the S3's internal ADC.

- $R_1 = 100\,\mathrm{k\Omega}$
- $V_{batt} = 7.4\,\mathrm{V}$
- $V_{out} = 2.8\,\mathrm{V}$

$$
R_2 = \frac{R_1 \cdot V_{out}}{V_{batt} - V_{out}}
$$

$$
R_2 = \frac{100\,000 \cdot 2.8}{7.4 - 2.8}
= 50\,\mathrm{k\Omega}
\approx 47\,\mathrm{k\Omega}
$$

### Microcontroller
The controller is driven by an ESP32-S3-WROOM-1U-N16 microcontroller.

The `U` and `N16` model was selected for layout flexibility and memory capacity (16MB).

A `MCP23017` GPIO expander was used to accomodate space for all digital inputs/outputs. 

**Digital IO**
<p align="center">
  <img src="/media/images/circuits/mcu/s3.png" width="500">
</p>

**Mode Select and Reset Toggle**
<p align="center">
  <img src="/media/images/circuits/mcu/s3_toggles.png" width="300">
</p>

The S3 can be put into **BOOT** mode and **RESET** with onboard buttons.

**BOOT** mode determines whether the chip runs existing code from flash memory or waits to download new firmware.
- The ESP32 samples the **BOOT** pin (`GPIO0`) during reset to determine the boot mode.
- It is **active-low**: when pulled to **GND** during reset, the chip enters UART bootloader mode for flashing firmware.
- The circuit uses a momentary push-button to **GND** and a `10kΩ` pull-up resistor to ensure a defined high state during normal operation.

| BOOT0 Level | Boot Mode |
|-------------|-----------|
| HIGH | Programming Mode |
| LOW | Memory Mode |

**RESET** controls the Enable (EN) pin which is the ON/OFF (reset) switch for the ESP32.
- It is **active-low**: when pulled to **GND** it turns off the chip, and when released, it restarts.
- The circuit consists of a momentary push-button, a pull-up resistor to ensure the chip is enabled by default, and a `1µF` capacitor to filter out button noise.

### Motor Drivers
The `N20` wheel hub motors are driven by a `DRV8833` chip, and their encoder signals are routed to digital pins on the `S3`. 

They are connected via 6-Pin Molex Nano-Fit (2.50mm Pitch) headers, and feature decoupling across the motor terminals and on the encoder power supply. 
<p align="center">
  <img src="/media/images/circuits/motors/mtr_in.png" width="300">
</p>

The **Servo** hip motors are driven by PWM signals from the `S3`, and are connected by a single 4-Pin Molex Nano-Fit header. 

The connector has decoupling on the power supply, and series resistors on the signal lines to improve signal integrity and reduce noise. 
<p align="center">
  <img src="/media/images/circuits/motors/servo_in.png" width="300">
</p>

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

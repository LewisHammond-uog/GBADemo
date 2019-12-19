**WK1 TUTORIAL**

This week's tutorial will be assessed as part of your assessment for this module. This work will need to be submitted with your assignment on the assignment deadline. For further information please see the Assessment criteria available on this Moodle page.

Ensure that the sample project Hello_GBA is able to be set up and be deployed to the mGBA emulator from within Visual Studio Code and that everything is displayed correctly. Add a breakpoint to ensure that debugging information is available!

The current state of the Hello_GBA project simply draws four pixels to screen buffer memory and displays these each frame. Your task for this tutorial is to expand upon this sample program and create some functionality to allow  greater control of drawing to the screen. Allowing Boxes, filled and outline to be drawn, lines to be drawn and the colour of each line and box to be set.

You should set about configuring some #defines to map out GBA memory addresses for VRAM and Display Modes . All hardware defines you need are outlined in the GBATEK documentation.

Create type defines for the basic integer input types that will be used throughout this module where there bitsize is denoted in their define E.G. uint8, uint16, uint32 (or simply u8, u16, u32 and s8, s16, and s32 for their signed counterparts).

Once this has been done create a simple scene that demonstrates coloured boxes moving around the screen. Create some paddle style boxes and a square ball and demonstrate a quick game of pong without any user input. If you want to push your skills you should implement a circle drawing routine using Bresenham's Algorithm
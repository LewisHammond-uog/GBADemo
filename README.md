# GBA Programming Tutorial Series

This repo is the starting point for the assessment tasks for CT5036 Programming Low Level Architecture.  

Visual Studio Code is being usd as the IDE for this series, with the intent being that the root folder of this repository is the folder that will be opened with VS Code with each specific project functioning as a sub folder from that root folder.  

There is some small amount of set up involved in this where the **${env:proj_working_dir}** and **{env:proj_name}** variable within **task.json** will need to be modified to set the current working project/tutorial. You will need to modify **task.json** to ensure that the *gdb-debug* and *run* tasks have the correct path to the mGBA executable.

Some modification to **c_cpp_properties.json** will need to be made to make sure the the correct include directories are specified. This is quite straight forward as all you will need to modify is the environment variable **{env:proj_name}** on line 3 of **c_cpp_properties.json** to indicate which sub folder you want to set as your current project to build.  

There will be some modification to the **launch.json** file to accommodate for the project/tutorial that is to be run and the correct GBA/ELF files to be launched buy the debugger. You need to make sure that **miDebuggerPath** has the right settings for where devkitARM has been installed on your computer.

These tutorials will be tested on both PC and Mac, if any problems occur with building then hit me up in class, via email, on discord or on the associated youtube videos that will accompany each tutorial or use GitHub to raise an issue.  
  
Additionally **each sub folder** contains their own readme.MD, you should use this format on your own assessment tasks to include any information or instructions that may be required to run your GBA projects and tutorials.

Happy Coding and have fun.

.kthanxby.

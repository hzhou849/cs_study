## How to debug with VsCode

1) use the vscode folder reference files to setup for c++ projects
   NOTE: there is alot of compatibility issues. You may need to restart VSC periodically

2) compile your project with g++ -std=c++11 -g <project.cpp> -o <project name>

3) click on the debug button on the side, a new panel to debug will appear
   click on create json files, if a new tab pops up select 'default configuration'
   fix the path to the gdb file you just created

4) a new launch.json file will be generated. If you have problems, 
   ammend the following fields: or delete the json files and start all over again.

### launch.json
{
	// Use IntelliSense to learn about possible attributes.
	// Hover to view descriptions of existing attributes.
	// For more information, visit: https://go.microsoft.com/fwlink/?linkid=830387
	"version": "0.2.0",
	"configurations": [
		{
			"name": "(gdb) Launch",
			"type": "cppdbg",
			"request": "launch",
			"program": "${workspaceFolder}/a.out", --> modify to path
			"args": [-std=c++11], ---> maybe required
			"stopAtEntry": false,
			"cwd": "${workspaceFolder}",
			"environment": [],
			"externalConsole": false,
			"MIMode": "gdb",
			"setupCommands": [
				{
					"description": "Enable pretty-printing for gdb",
					"text": "-enable-pretty-printing",
					"ignoreFailures": true
				}
			]
		}
	]
}

###CPP config file
	 "configurations": [
        {
            "name": "Linux",
            "includePath": [
                "${workspaceFolder}/**"      --> required to update to this format
            ],
            "defines": [],
            "compilerPath": "/usr/bin/g++",  --> required to change to 'g++' to work
            "cStandard": "gnu11",
            "cppStandard": "c++11",          --> required to change to 'c++11'
            "intelliSenseMode": "linux-gcc-x64"
        }

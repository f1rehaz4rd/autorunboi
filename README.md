# autorunboi
A Red Team tool used to flood important registers in the Windows registry in attempt to hide other red team activity and
give blue team some IR to report.

NOTE: The code is in flood.cpp

## Deployment
Compile the .cpp file into an executable to run on the target system.

NOTE: If you do not run it as an administrative user it will not flood HKLM registry.
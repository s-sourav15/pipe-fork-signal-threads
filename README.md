# using-pipe-signal-and-thread-functionalities-of-linux-os
The project makes use of fork, pipe, signal and multi-threading capabilities of the linux os to create a communication protocol between an admin and computer wit inputs being taken from the user

USAGE
  For comipling just run the makefile
  Make sure to give the arguments as follows when running the files:
    Admin.exe: ./Admin.exe Portno timeout-time
    Client.exe: ./Client.exe client-id IP-address Portno
    
  Make sure the Portno is same in both the files

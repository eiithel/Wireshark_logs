# Wireshark_logs

The aim of the project is to analyze TCP streams exchanged from a videoconferencing equipment.

This application is a csv parser for wireshark logs.
The aim of the software is to compute Jitter from packets time of arrival.

![](https://github.com/eiithel/Wireshark_logs/blob/master/doc/images/wireshark_app.png)

The application analyzes the file originated from wireshark and generate two outfiles that summarize the progress of the session.

* **report2.csv**  
This file records all the TCP segments delays and the associated time since epoch. 

* **reportGlobal.csv**  
This file is a general overview of the progress of the session with average jitter and average latency.

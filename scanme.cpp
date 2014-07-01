#include <iostream>
#include <fstream>
#include <windows.h>
#include <string>
#include <time.h>
#include <limits>

using namespace std;

const string programName = "SystemLogv0.4 | Basic SysInfo Logger\n";
const string programError = "[ERROR] : ";

HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE); // handle standard output device. Initially, this is the active console screen buffer.

//***************************************************************************************
// Preparatory functions
//***************************************************************************************

void callTemplog();
void br();
void clear();
void eicarTest();
float colorSys(string, int);
float createTemp();
float getInternet();
float getProcess();
float getStartup();
float getSysinfo();

//***************************************************************************************
// Call temp log using notepad
//***************************************************************************************
void callTemplog()
{
	system("start notepad temp.log");
}

//***************************************************************************************
// br, breakline.
//***************************************************************************************
void br()
{
	cout << endl;
}

//***************************************************************************************
// Clear: Self explanatory
//***************************************************************************************
void clear()
{
	system("cls");
}

//***************************************************************************************
// Font coloring: Green(OK), Red(Not Ok), Blue(Reading)
//***************************************************************************************
float colorSys(string input, int num)
{
	int txtLength = input.length(), count;
	
	switch(num)
	{
		case 1:
			//green
			for (count = 0; count < txtLength;count++)
			SetConsoleTextAttribute(console, 2);
			cout << input;
			SetConsoleTextAttribute(console, 07);
			break;
			
		case 2:
			//red
			for (count = 0; count < txtLength;count++)
			SetConsoleTextAttribute(console, 4);
			cout << input;
			SetConsoleTextAttribute(console, 07);
			break;
			
		case 3:
			//blue
			for (count = 0; count < txtLength;count++)
			SetConsoleTextAttribute(console, 1);
			cout << input;
			SetConsoleTextAttribute(console, 07);
			break;
			
		case 4:
			//purple
			for (count = 0; count < txtLength;count++)
			SetConsoleTextAttribute(console, 5);
			cout << input;
			SetConsoleTextAttribute(console, 07);
			break;
			
		default:
			//white
			for (count = 0; count < txtLength;count++)
			SetConsoleTextAttribute(console, 07);
			cout << input;
			SetConsoleTextAttribute(console, 07);
			break;
	}
	
}

//***************************************************************************************
// EICAR TEST FILE : http://www.eicar.org/86-0-Intended-use.html
//***************************************************************************************
void eicarTest()
{
	string result,final;
	system("title SystemLogv0.4 - Xtra - Test if AV is working");
	ofstream eicar;
 	eicar.open ("eicar.com");
  	eicar << "X5O!P%@AP[4\\PZX54(P^)7CC)7}$EICAR-STANDARD-ANTIVIRUS-TEST-FILE!$H+H*";
 	eicar.close();
	system("start eicar.com");
	ifstream testfile("eicar.com");
	if(testfile.is_open())
	{
		while(testfile.good())
		{
			getline(testfile,result);
			final += result;
		}
		
		colorSys("NOT OK!\n", 2);
		system ("echo [TESTAV]: NOT OK! >> temp.log");
		system("echo. >> temp.log");
	}
	else
	{
	colorSys("OK! \n", 1);
	system ("echo [TESTAV]: OK! >> temp.log");
	system("echo. >> temp.log");
	}	
	
}

//***************************************************************************************
//Create the temporary logfile.
//***************************************************************************************
float createTemp()
{
	system("del /f /a /q temp.log");
	
	time_t rawtime; //creates and object of the built in time function
  	struct tm * timeinfo; //no idea what this do

  	time ( &rawtime ); //gets the time from the computer
  	timeinfo = localtime ( &rawtime ); //store that time here
	
	ofstream templog;
  	templog.open ("temp.log");
  	templog << "=============================================================================\n";
  	templog << programName;
  	templog << "Plese pass this log to someone can analyze windows system logs.\n";
  	templog << "Time created: " << asctime(timeinfo); 
  	templog << "=============================================================================\n\n";
  	templog.close();
	
	system("echo. >> pingLog.x");
	system("echo. >> runLog.x");
	system("echo. >> sysLog.x");
	system("echo. >> startLog.x");
	
}

//***************************************************************************************
//Get Running process
//***************************************************************************************
float getProcess()
{	
	system("del /f /a /q runLog.x");
				
	string result, final;
	colorSys("[Status] Get Running Process: ", 3);
	system("TASKLIST /v /fi \"STATUS eq running\" >> runLog.x");
	
	ifstream logfile("runLog.x");
	if(logfile.is_open())
	{
		while(logfile.good())
		{
			getline(logfile,result);
			final += result;
		}
		
		colorSys("OK!\n", 1);
		system ("echo [GETPROCESS]: OK! >> temp.log");
		system("type runLog.x >> temp.log");
		system("echo. >> temp.log");
	}
	else
	{
	system ("echo [GETPROCESS]: ERROR LOGFILE ERROR! >> temp.log");
	colorSys(programError+"Error! logifle can't be read or didn't exist!", 2);
	return 0;
	}	
}

//***************************************************************************************
//Get Startup Process
//***************************************************************************************
float getStartup()
{	
	system("del /f /a /q startLog.x");
				
	string result, final;
	colorSys("[Status] Get Startup: ", 3);
	system("wmic startup get caption,command >> startLog.x");
	
	ifstream logfile("startLog.x");
	if(logfile.is_open())
	{
		while(logfile.good())
		{
			getline(logfile,result);
			final += result;
		}
		
		colorSys("OK!\n", 1);
		system ("echo [GETSTARTUP]: OK! >> temp.log");
		system("type startLog.x >> temp.log");
		system("echo. >> temp.log");
	}
	else
	{
	system ("echo [GETSTARTUP]: ERROR LOGFILE ERROR! >> temp.log");
	colorSys(programError+"Error! logifle can't be read or didn't exist!", 2);
	return 0;
	}	
}

//***************************************************************************************
//Get SystemInfo
//***************************************************************************************
float getSysinfo()
{	
	system("del /f /a /q sysLog.x");
		
	string result, final;
	system("systeminfo >> sysLog.x");
	colorSys("[Status] Get SysInfo: ", 3);
	
	ifstream logfile("sysLog.x");
	if(logfile.is_open())
	{
		while(logfile.good())
		{
			getline(logfile,result);
			final += result;
		}
		
		colorSys("OK!\n", 1);
		system ("echo [GETSYSINFO]: OK! >> temp.log");
		system("type sysLog.x >> temp.log");
		system("echo. >> temp.log");
		
	}
	else
	{
	system ("echo [GETSYSINFO]: ERROR LOGFILE ERROR! >> temp.log");
	colorSys(programError+"Error! logifle can't be read or didn't exist!", 2);
	return 0;
	}	
}

//***************************************************************************************
//Pinging google.com for checking the internet connection
//***************************************************************************************
float getInternet()
{	
	system("del /f /a /q pingLog.x");
			
	string result,final;
	colorSys("[Status] Pinging sophos.com: ", 3);
	system("ping sophos.com >>pingLog.x");
	
	ifstream logfile("pingLog.x");
	if (logfile.is_open())
	{
		while(logfile.good())
		{
			getline(logfile,result);
			final += result;
		}
		
		if(final.find("Reply from") != string::npos)
		{
		colorSys("OK!\n", 1);
		system("echo [PING]:OK! >> temp.log");
		system("type pingLog.x >> temp.log");
		system("echo. >> temp.log");
		}
		else
		{
		colorSys("NOT OK!\n", 2);
		system("echo [PING]:NOT OK! >> temp.log");
		system("type pingLog.x >> temp.log");
		system("echo. >> temp.log");
		}
		
		logfile.close();
	}
	else
	{
	system("echo [PING]:ERROR LOGFILE ERROR! >> temp.log");
	colorSys(programError+"Error! logifle can't be read or didn't exist!", 2);
	return 0;
	}
}

//***************************************************************************************
//Main Progam
//***************************************************************************************
int main() 
{
	#ifdef _WIN32 || _WIN64
	//do nothing
	#else
	cout << "This will not run in your system";
	return 0;
	#endif
	clean:
	int choice = 0;
	
	system("title Creating temp.log");
	colorSys("Creating temp.log, please wait..", 1);
	createTemp();	
	clear();
	
	start:
	clear();
	system("title SystemLogv0.4 - Basic Sysinfo Scanner");
	colorSys("======================================================================\n",4);
	colorSys(programName,4);
	colorSys("Just another system information scanner, nothing special.\n",4);
	colorSys("THIS APPLICATION MUST BE IN ROOT ACCOUNT!\n",4);
	colorSys("======================================================================\n",4);
	colorSys(" Scan: \n", 4);
	colorSys("\t [1] System Information\n", 4);
	colorSys("\t [2] Running Process\n", 4);
	colorSys("\t [3] Startup Process\n", 4);
	colorSys("\t [4] Check Internet Connection (PING)\n", 4);
	colorSys("\t [5] Log ALL\n", 4);
	colorSys("\t [6] Xtra: Check your antivirus if working\n", 4);
	colorSys("\t [7] Refresh\n", 4);
	colorSys("\t [8] Open User Manual\n", 4);
	colorSys("\t [9] About\n", 4);
	colorSys("\t [CTRL+C] Exit\n", 4);
	br();
	colorSys("\tInput: ", 4);
	
	while (!(cin >> choice))
    {
        cin.clear();
        cin.ignore(numeric_limits<int>::max(), '\n');
        colorSys("\tPlease enter a proper input: ", 4);
    }
    
    br();br();
	
	switch(choice)
	{
		case 1:
			system("title SystemLogv0.4 - Get System Information");
			getSysinfo();
			callTemplog();
			goto start;
			break;
			
		case 2:
			system("title SystemLogv0.4 - Get Running Process");
			getProcess();
			callTemplog();
			goto start;
			break;
			
		case 3:
			system("title SystemLogv0.4 - Get Startup Process");
			getStartup();
			callTemplog();
			goto start;
			break;
			
		case 4:
			system("title SystemLogv0.4 - Pinging sophos.com");
			getInternet();
			callTemplog();
			goto start;
			break;
			
		case 5:
			system("title SystemLogv0.4 - Log all");	
			getSysinfo();
			getProcess();
			getStartup();
			getInternet();
			callTemplog();
			goto start;
			break;
			
		case 6:
			eicarTest();
			callTemplog();
			goto start;
			break;
			
		case 7:
			goto clean;
			break;
			
		case 8:
			system("start usermanual.pdf");
			main();
			break;
			
		case 9:
			clear();
			system("title SystemLogv0.4 - About");
			colorSys("======================================================================\n",1);
			colorSys(programName,5);
			br();
			colorSys("SystemLog is a basic system information logger that gets specific logs in any\n",5);
			colorSys("Windows operating system later than Windows XP. This application uses some\n",5);
			colorSys("Windows utilities to get specific logs depending on the needs of the user.\n",5);
			br();
			colorSys("======================================================================\n",1);
			br();
			colorSys("Programming is art, I suck at art.\n",2);
			colorSys("(Press any key to go back.)",2);
			system("pause>nul");
			goto start;
			break;
		
		case 0:
		while(true)
		{
			return 0;
		}
		break;
		
		default:
			main();
			break;
			
	}
	
return 0;
}

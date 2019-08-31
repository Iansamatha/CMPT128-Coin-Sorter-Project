//This is a C++ program that will sort coins based on information from a text file
//The lines in the code will contain, in order,
//weight, diameter, if the coin is bent, and if the faces match.
//Because the weight and diameter are sensor readings and do not represent their appropriate units,
//The weight and diameter sensor readings will be converted into grams and diameter
//Based on the coins' properties if they are canadain coins, they will be
//put into proper rolls and replaced when the rolls are full.
//If the coin is bent it will be placed in a bent coin container.
//The container will be replaced once it reaches the maximum.
//Coins that are not bent and do not folow the same properties
//will be put in the "other" coin container
//and will be replaced when it reaches the maximum weight.
//Errors will show up on the console but not the output file.

//There will be a final summary on the amount of rolls, coins in a partial roll,
//grams of bent coins, number of total other coins, completely filled other coin containers,
//and number of coins in the partially fully other coin container. 

//Author: Favian (Ian) Samatha
//Date: November 12, 2017
//Student ID: 301328390


//Included libraries
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>

using namespace std;

int main()
{
	//Declared and intialized constants involving the coin's properties
	const double NICKELMINWEIGHT = 3.60; 
	const double NICKELMAXWEIGHT = 4.30;
	const double NICKELMINDIAMETER = 20.20;
	const double NICKELMAXDIAMETER = 21.80;
	const double DIMEMINWEIGHT = 1.30;
	const double DIMEMAXWEIGHT = 2.20;
	const double DIMEMINDIAMETER = 17.30;
	const double DIMEMAXDIAMETER = 18.70;
	const double QUARTERMAXWEIGHT = 4.80;
	const double QUARTERMINWEIGHT = 4.00;
	const double QUARTERMINDIAMETER = 22.80;;
	const double QUARTERMAXDIAMETER = 24.60;
	const double LOONIEMINWEIGHT = 6.50;
	const double LOONIEMAXWEIGHT = 7.50;
	const double LOONIEMINDIAMETER = 25.0;
	const double LOONIEMAXDIAMETER = 27.0;
	const double TOONIEMINWEIGHT = 6.75;
	const double TOONIEMAXWEIGHT = 7.85;
	const double TOONIEMINDIAMETER = 26.90;
	const double TOONIEMAXDIAMETER = 29.10;
	const int MAXNICKELROLL = 40;
	const int MAXDIMEROLL = 50;
	const int MAXQUARTERROLL = 40;
	const int MAXLOONIEROLL = 25;
	const int MAXTOONIEROLL = 25;



	//Initialized and declared constants for the program

	const string usable = "usable";
	const string bent = "bent";
	const string OneMatch = "OneMatch";
	const string NoMatch = "NoMatch";
	const string BothMatch = "BothMatch";
	const int arraysize1 = 1025;
	const int MINLINES = 1;
	const int MAXLINES = 5000;
	const int MAXSENSOR = 255;
	const int MINSENSOR = 0;
	const double BENTCOINCONTAINERMAXGRAMS = 100;
	const double OTHERCOINCONTAINERMAXGRAMS = 200;
	const double  INCREASELENGTHMAX = 5.0;
	const double  INCREASELENGTHMIN = 0.0;
	const double MAXWEIGHT = 10.00;
	const double MINWEIGHT = 0.00;
	const double MAXDIAMETER = 40.00;
	const double MINDIAMETER = 10.00;

	//Declared and intialized all integer variables related to the program.
	int nlines = 0;
	int linesintext = 0;
	int data = 0;
	int tries = 0;
	int maxtries = 3;
	int weight = 0;
	int diameter = 0;
	int partialnickelroll = 0;
	int partialdimeroll = 0;
	int partialquarterroll = 0;
	int partialloonieroll = 0;
	int partialtoonieroll = 0;
	int nickelsinroll = 0;
	int fullnickelrolls = 0;
	int dimesinroll = 0;
	int fulldimerolls = 0;
	int quartersinroll = 0;
	int fullquarterrolls = 0;
	int looniesinroll = 0;
	int fullloonierolls = 0;
	int tooniesinroll = 0;
	int fulltoonierolls = 0;
	int bentcoincontainers = 0;
	int othercoincontainers = 0;
	int othercoins = 0;
	int othertotalcoins = 0;
	int benttotalcoins = 0;
	int bentcoins = 0;

	//Declared and initalized all doubles for the program
	double grams = 0;
	double weightofbentcontainer = 0;
	double weightoftotalbentcoins = 0;
	double weightofothercontainer = 0;
	double weightoftotalothercoins = 0;
	double wirelengthconversion = 0;
	double diameterconversion = 0;

	//Declared and intialized all characters for the program
	char simulationame[arraysize1] = {'\0'};
	char sensorname[arraysize1] = {'\0'};
	char space = '0';
	char trash = '0';

	//Declared strings, input, and output stream
	string usableorbent = "0";
	string match = "0";
	ifstream sensorfile;
	ofstream simulationresults;
	
	//This will ask the user to input an existing file name with three tries.
	//If the file fails to open, a try will be used. 
	//If tries are exceeded the program will terminate.
	do 
	{
		//This message will appear and terminate the program if the user exceeded the amount of tries and still failed. 
		tries ++;
		if (tries > 3)
		{
			cerr <<"ERROR: You exceeded maximum number of tries allowed" << endl;
			cerr <<"while entering the input file name";	
			return 1;
		}
		//Asks the user for the name of the input file
		cout <<"Type the name of the input file containing sensor readings: " << endl;
		cin >> sensorname;
		sensorfile.open(sensorname);

		//Displays error message when file cannot be openned
		if (sensorfile.fail ())
		{
			cerr<<"ERROR: File "<< sensorname << " could not be opened for input" << endl;
		}
	} while ( sensorfile.fail());
	//re-initializing tries to 0 for the next step
	tries = 0;



	//This will ask the user to input an existing file name for the output file with three tries
	//If tries are exceeded, the program will terminate.
	do 
	{
		//If the file cannot open, this message will appear.
		if (simulationresults.fail ())
		{
			cerr << "ERROR: File " << simulationame << " could not be opened for output" << endl;
			
		}
		//Asks the user for the outputfile name.
		cout <<"Type the name of the output file which will hold the simulation results: " << endl;
		cin >> simulationame;
		simulationresults.open(simulationame);

			tries ++;

		//If the file cannot open after three tries, this will appear and terminate the program. 
		if (tries >= 3 && simulationresults.fail())
		{
			cerr<<"ERROR: File "<< simulationame << " could not be opened for output" << endl;
			cerr <<"ERROR: You exceeded maximum number of tries allowed" << endl;
			cerr <<"while entering the output file name";		
			return 2;
		}
	} while ( simulationresults.fail());



	//This will read line 0 (or the first line of the text file) which contains the number of lines in the program.
	if ( !(sensorfile >> linesintext))
	{
		//If it cannot read the data and it is at the end of the line, the program will display an error message and end the program.
		if (sensorfile.eof())
		{
			cerr<<"ERROR: Input data file is empty";
			return 3;
		}
		//If the first data is not an integer, the program will display an error message and end the program.
		else 
		{
			cerr<<"ERROR: First piece of data in the file is not an integer";
			return 4;
		}
	}
	//If the first data is smaller than the minimum number of lines or larger than the maximum number of lines
	//The program will determine an error message and terminate the program.
	if (linesintext < MINLINES || linesintext > MAXLINES)
	{
		cerr <<"ERROR: The number of sensor readings is out of range";
		return 5;
	}



	//This while loop will begin reading the lines in the inputfile.
	//It will display messages according to the information inside.
	//All error messages will be displayed on the console
	//All other outputs will be displayed on both the console and the output file.
	while ( nlines <= linesintext)
	{
		//This is the current line number of the text file
		nlines ++;
		//This will read the weight which is the first integer of the line.
		if(!(sensorfile >> weight))
		{
			//If the weight cannot be read and it is not the end of the file, then it is not an integer.
			//As a result, the program will stop reading the file and the summary will be displayed.
			if( !(sensorfile.eof()))
			{
				cerr <<"ERROR: Weight sensor value read on line "<< nlines << " is not an integer\n";
				cerr <<"Simulation terminated early: Please correct your data file";
				break;
			}
			//If the weight cannot be read and it is at the end of the file
			//The program will stop reading the file and the summary will be displayed.
			else if (sensorfile.eof())
			{
				cerr <<"ERROR: No more data\n";
				cerr <<"Simulation completed early before line "<< nlines <<" of input";

				break; 
			}
		}
		//This command will read the space after the weight value.
		sensorfile.get();
		
		//If the line ends wiith only the weight value,
		//an error message wil appear and ignore the line.
		if (sensorfile.peek() == '\n')
		{
			
			cerr << "ERROR: Weight sensor measurement only\n";
			cerr << "Ignoring line "<< nlines <<" of the input file\n";
			continue;
		}

		//This will read the diameter value which is the second integer of the line.
		if (!(sensorfile >> diameter))
		{
			//If the diameter is not an integer, the simulation will end.
			cerr<<"ERROR: Diameter sensor value read on line "<< nlines << " is not an integer\n";
			cerr <<"Simulation terminated early: Please correct your data file";
			break;
		}
		
		//This will read the blank space after the diameter value
		sensorfile.get();
		//If the line ends with only the weight sensor and diameter value
		//an error message will appear and it will ignore this line and move on to the next line.
		if (sensorfile.peek() == '\n')
		{
			cerr << "ERROR: Weight and diameter sensor measurements only\n";
			cerr << "Ignoring line "<< nlines <<" of the input file\n";
			continue;
		}

		//This will read the first string that will determine if the coin is bent or unbent
		sensorfile >> usableorbent;
		//If the string is neither "usable" or "bent"
		//the program will display an error message and ignore the line.
		if (usableorbent != usable && usableorbent != bent)
		{
			cerr <<"ERROR: Result of test to determine if coin is bent at line " << nlines << " is invalid" << endl;
			cerr <<"Ignoring this line of data\n";
			//This will skip all the extra data on the current line until it moves to the next line
			while(sensorfile.peek() != '\n')
				{
					sensorfile.get();
				}
			continue;
		}
		//This will read the blank space after the first string value.
		sensorfile.get();

		//If the line ends with only the weight, diameter, and 1st string reading
		//an error message will display and it will skip the current line
		if (sensorfile.peek() == '\n')
		{
			cerr << "ERROR: Weight and diameter sensor measurements and bent string only\n";
			cerr << "Ignoring line "<< nlines <<" of the input file\n";
			continue;
		}

		//This will read the 2nd string which will determine
		//if the coin is a canadian coin.
		sensorfile >> match;


		//If the string does not read "BothMatch", "OneMatch", or "NoMatch",
		//there will be an error message and it will skip the line.
		if (match != BothMatch && match != OneMatch && match != NoMatch)
		{
			cerr << "ERROR: image processing result at line " << nlines << " is invalid \n";
			cerr <<"Ignoring this line of data\n";
			//This loop will grab any extra data from the line and ignore it until a new line is reached.
			while(sensorfile.peek() != '\n')
				{
					sensorfile.get();
				}
			continue;
		}
		
		//If there are extra spaces after the 2nd string, this loop will read the extra spaces
		//until there is a new line or another word.
		while (sensorfile.peek() == ' ' && sensorfile.peek() != '\n')
		{ 
			sensorfile.get();
			//If the programs reads something other than a new line or a space, it means there is extra data in the line.
			//If there is extra data, the program will ignore the extra data and display an error message.
			if (sensorfile.peek() != ' ' && sensorfile.peek() != '\n')
			{	
				while(sensorfile.peek() != '\n')
				{
					sensorfile.get();
				}
				cerr << "ERROR: Extra data at line " << nlines << ".  Ignoring extra data\n";
				//If data is also out of range, then it will ignore the line
				if ( weight < MINSENSOR || weight > MAXSENSOR || data < MINSENSOR || data > MAXSENSOR)
				{
					continue;
				}
				
			}
		}

		//If the weight sensor is out of range, an error message appears and ignores the line.
		if ( weight < MINSENSOR || weight > MAXSENSOR )
		{
			cerr << "ERROR: Sensor reading out of range, ignoring line " << nlines << " in the input file \n";
			while(sensorfile.peek() != '\n')
				{
					sensorfile.get();
				}
			continue;
		}
		//If the weight sensor is out of range, an error message appears and ignores the line.
		if ( diameter < MINSENSOR || diameter > MAXSENSOR )
		{
			cerr << "ERROR: Sensor reading out of range, ignoring line " << nlines << " in the input file \n";
			while(sensorfile.peek() != '\n')
				{
					sensorfile.get();
				}
			continue;
		}

		
		//These are the conversions for the sensor measurements to weight and diameter.
		//The ratio of the conversion is (max1 - min1) / (max2 - min2) where max and min 2 are the sensor readings
		//and max and min 1 are the units we want them to be. 
		//Then we would multiply the sensor reading to that ratio.
		wirelengthconversion = weight * (( INCREASELENGTHMAX - INCREASELENGTHMIN) / (MAXSENSOR - MINSENSOR));
		diameterconversion = 10 + ( diameter * (( MAXDIAMETER - MINDIAMETER) / ( MAXSENSOR - MINSENSOR)) );
		
		//finding the grams form hook's law.
		grams = 2 * wirelengthconversion;
	
		//If the coin is bent, this will add weight to the total amount of bent coins.
		if ( usableorbent == bent)
		{
			benttotalcoins++;
			bentcoins++;
			weightoftotalbentcoins += grams;
			weightofbentcontainer += grams;

			if (weightofbentcontainer <= BENTCOINCONTAINERMAXGRAMS)
			{
				cout << "The Coin Sorter has sent this coin to the bent coin container" << endl;
				cout << "The coins in the bent coin container now weigh "<< fixed << setprecision(2) << setw(6) << weightofbentcontainer << " grams" << endl;
				simulationresults << "The Coin Sorter has sent this coin to the bent coin container" << endl;
				simulationresults << "The coins in the bent coin container now weigh "<< fixed << setprecision(2) << setw(6) << weightofbentcontainer << " grams" << endl;
			}
			//If the bent coin container is full, it will be replaced.
			else if (weightofbentcontainer >= BENTCOINCONTAINERMAXGRAMS)
			{
				bentcoins = 0;
				cout << "The Coin Sorter has sent this coin to the bent coin container" << endl;
				cout << "This coin does not fit in the bent coin container" << endl;
				cout << "The bent coin container has been replaced" << endl;
				simulationresults << "The Coin Sorter has sent this coin to the bent coin container" << endl;
				simulationresults << "This coin does not fit in the bent coin container" << endl;
				simulationresults << "The bent coin container has been replaced" << endl;
				weightofbentcontainer = 0;
				bentcoincontainers ++;
				weightofbentcontainer +=  grams;
				cout << "The coin in the bent coin container now weighs " << fixed << setprecision(2) << setw(5) << weightofbentcontainer << " grams" << endl;
				simulationresults << "The coin in the bent coin container now weighs " << fixed << setprecision(2) << setw(5) << weightofbentcontainer << " grams" << endl;
			}
		}

		//If the properties of the coin fit the nickel and the both sides of the coin matches
		//a nickel will be added to the roll.
		else if (  grams >= NICKELMINWEIGHT && grams <= NICKELMAXWEIGHT &&  diameterconversion >= NICKELMINDIAMETER && diameterconversion <= NICKELMAXDIAMETER && match == BothMatch)
		{
			nickelsinroll ++;
			//These messages will be displayed if the roll is not yet full.
			if (nickelsinroll < MAXNICKELROLL)
			{
				cout << "The Coin Sorter has sent one coin to the nickels wrapper" << endl;
				cout << "There are now " << nickelsinroll << " coins in the nickels wrapper" << endl;
				simulationresults << "The Coin Sorter has sent one coin to the nickels wrapper" << endl;
				simulationresults << "There are now " << nickelsinroll << " coins in the nickels wrapper" << endl;
			}
			//These messages will display if the roll is full.
			//The amount of nickels in a partial roll will reset
			//and the number of full nickel rolls will increase by 1
			else if (nickelsinroll = MAXNICKELROLL)
			{
				cout << "The Coin Sorter has sent one coin to the nickels wrapper" << endl;
				cout << "The nickel wrapper is now full" << endl;
				cout << "The nickel wrapper has now been replaced" << endl;
				simulationresults << "The Coin Sorter has sent one coin to the nickels wrapper" << endl;
				simulationresults << "The nickel wrapper is now full" << endl;
				simulationresults << "The nickel wrapper has now been replaced" << endl;
				nickelsinroll = 0;
				fullnickelrolls++;
			}
		}
		//If the properties of the coin fit the dime and the both sides of the coin matches
		//a dime will be added to the roll.
		else if ( ( grams >= DIMEMINWEIGHT && grams <= DIMEMAXWEIGHT) && ( diameterconversion >= DIMEMINDIAMETER && diameterconversion <= DIMEMAXDIAMETER) && (match == BothMatch)) 
		{
			dimesinroll ++;
			//These messages will be displayed if the roll is not yet full.
			if (dimesinroll < MAXDIMEROLL)
			{
				
				cout << "The Coin Sorter has sent one coin to the dimes wrapper" << endl;
				cout << "There are now " << dimesinroll << " coins in the dimes wrapper" << endl;
				simulationresults << "The Coin Sorter has sent one coin to the dimes wrapper" << endl;
				simulationresults << "There are now " << dimesinroll << " coins in the dimes wrapper" << endl;
				
			}
			//These messages will display if the roll is full.
			//The amount of dimes in a partial roll will reset
			//and the number of full dime rolls will increase by 1
			else if (dimesinroll = MAXDIMEROLL)
			{

				cout << "The Coin Sorter has sent one coin to the dimes wrapper" << endl;
				cout << "The dime wrapper is now full" << endl;
				cout << "The dime wrapper has now been replaced" << endl;
				simulationresults << "The Coin Sorter has sent one coin to the dimes wrapper" << endl;
				simulationresults << "The dime wrapper is now full" << endl;
				simulationresults << "The dime wrapper has now been replaced" << endl;
				dimesinroll = 0;
				fulldimerolls++;

			}
		}
		//If the properties of the coin fit the quarter and the both sides of the coin matches
		//a quarter will be added to the roll.
		else if ( ( grams >= QUARTERMINWEIGHT && grams <= QUARTERMAXWEIGHT) && ( diameterconversion >= QUARTERMINDIAMETER && diameterconversion <= QUARTERMAXDIAMETER) && (match == BothMatch)) 
		{
			quartersinroll ++;
			//These messages will be displayed if the roll is not yet full.
			if (quartersinroll < MAXQUARTERROLL)
			{
				cout << "The Coin Sorter has sent one coin to the quarters wrapper" << endl;
				cout << "There are now " << quartersinroll << " coins in the quarters wrapper" << endl;
				simulationresults << "The Coin Sorter has sent one coin to the quarters wrapper" << endl;
				simulationresults << "There are now " << quartersinroll << " coins in the quarters wrapper" << endl;
			}
			//These messages will display if the roll is full.
			//The amount of quarters in a partial roll will reset
			//and the number of full quarter rolls will increase by 1
			else if (quartersinroll = MAXQUARTERROLL)
			{
				cout << "The Coin Sorter has sent one coin to the quarters wrapper" << endl;
				cout << "The quarter wrapper is now full" << endl;
				cout << "The quarter wrapper has now been replaced" << endl;
				simulationresults << "The Coin Sorter has sent one coin to the quarters wrapper" << endl;
				simulationresults << "The quarter wrapper is now full" << endl;
				simulationresults << "The quarter wrapper has now been replaced" << endl;
				quartersinroll = 0;
				fullquarterrolls++;
			}
		}

		//If the properties of the coin fit the loonie and the both sides of the coin matches
		//a loonie will be added to the roll.
		else if ( ( grams >= LOONIEMINWEIGHT && grams <= LOONIEMAXWEIGHT) && ( diameterconversion >= LOONIEMINDIAMETER && diameterconversion <= LOONIEMAXDIAMETER) && (match == BothMatch)) 
		{
			looniesinroll ++;
			//These messages will be displayed if the roll is not yet full.
			if (looniesinroll < MAXLOONIEROLL)
			{
				cout << "The Coin Sorter has sent one coin to the loonies wrapper" << endl;
				cout << "There are now " << looniesinroll << " coins in the loonies wrapper" << endl;
				simulationresults << "The Coin Sorter has sent one coin to the loonies wrapper" << endl;
				simulationresults << "There are now " << looniesinroll << " coins in the loonies wrapper" << endl;
				
			}
			//These messages will display if the roll is full.
			//The amount of loonies in a partial roll will reset
			//and the number of full loonie rolls will increase by 1
			else if (looniesinroll = MAXLOONIEROLL)
			{
				cout << "The Coin Sorter has sent one coin to the loonies wrapper" << endl;
				cout << "The loonie wrapper is now full" << endl;
				cout << "The loonie wrapper has now been replaced" << endl;
				simulationresults << "The Coin Sorter has sent one coin to the loonies wrapper" << endl;
				simulationresults << "The loonie wrapper is now full" << endl;
				simulationresults << "The loonie wrapper has now been replaced" << endl;
				looniesinroll = 0;
				
				fullloonierolls++;
			}
		}
		//If the properties of the coin fit the toonie and the both sides of the coin matches
		//a toonie will be added to the roll.
		else if ( ( grams >= TOONIEMINWEIGHT && grams <= TOONIEMAXWEIGHT) && ( diameterconversion >= TOONIEMINDIAMETER && diameterconversion <= TOONIEMAXDIAMETER) && (match == BothMatch)) 
		{
			tooniesinroll ++;
			//These messages will be displayed if the roll is not yet full.
				if (tooniesinroll < MAXTOONIEROLL)
			{
		
				cout << "The Coin Sorter has sent one coin to the toonies wrapper" << endl;
				cout << "There are now " << tooniesinroll << " coins in the toonies wrapper" << endl;
				simulationresults << "The Coin Sorter has sent one coin to the toonies wrapper" << endl;
				simulationresults << "There are now " << tooniesinroll << " coins in the toonies wrapper" << endl;
				
			}
			//These messages will display if the roll is full.
			//The amount of toonies in a partial roll will reset
			//and the number of full toonie rolls will increase by 1
			else if (tooniesinroll = MAXTOONIEROLL)
			{
				cout << "The Coin Sorter has sent one coin to the toonies wrapper" << endl;
				cout << "The toonie wrapper is now full" << endl;
				cout << "The toonie wrapper has now been replaced" << endl;
				simulationresults << "The Coin Sorter has sent one coin to the toonies wrapper" << endl;
				simulationresults << "The toonie wrapper is now full" << endl;
				simulationresults << "The toonie wrapper has now been replaced" << endl;
				tooniesinroll = 0;
				fulltoonierolls++;
			}
		}
		//If the properties do not match any of the coins
		//or if only one side or none of the sides of the coin matches,
		//then the coin will go in the other coin container.
		//1 will be added to the number of coins in the partially full container and total other coins.
		//and the grams will be added to the total weight of other coins and partially full container
		else
		{
			othertotalcoins ++;
			weightoftotalothercoins += grams;
			weightofothercontainer += grams;

			//If the other container is not at its max, it will display these messages.
			if (weightofothercontainer <= OTHERCOINCONTAINERMAXGRAMS)
			{
				cout << "The Coin Sorter has sent this coin to the other coin container" << endl;
				cout << "The coins in the other coin container now weigh "<< fixed << setprecision(2) << setw(6) << weightofothercontainer << " grams" << endl;
				simulationresults << "The Coin Sorter has sent this coin to the other coin container" << endl;
				simulationresults << "The coins in the other coin container now weigh "<< fixed << setprecision(2) << setw(6) << weightofothercontainer << " grams" << endl;
			}
			//If the other container is full, it will display these messages.
			//The number of other coins in a partially full container wil reset to 0
			//number of full other coin containers will increase
			else if (weightofothercontainer > OTHERCOINCONTAINERMAXGRAMS)
			{
				othercoins = 0;
				cout << "The Coin Sorter has sent this coin to the other coin container" << endl;
				simulationresults << "The Coin Sorter has sent this coin to the other coin container" << endl;
				weightofothercontainer = 0;
				othercoincontainers ++;
				weightofothercontainer += grams;
				cout << "The coins in the other coin container now weigh "<< fixed << setprecision(2) << setw(6) << weightofothercontainer << " grams" << endl;
				simulationresults << "The coins in the other coin container now weigh "<< fixed << setprecision(2) << setw(6) << weightofothercontainer << " grams" << endl;
			}
			othercoins ++;

		}		

	}
	
	//This will print a summary without the error messsages on to the console and the output file.
	cout << endl << endl << endl << endl;
	cout << "SUMMARY" << endl;
	cout << "The Coin Sorter made " << setw(3) << fullnickelrolls << " rolls of nickels." << endl;
	cout << "    There are " << setw(2) << nickelsinroll << " nickels in the partially full roll." << endl;
	cout << "The Coin Sorter made " << setw(3) << fulldimerolls << " rolls of dimes." << endl;
	cout << "    There are " << setw(2) << dimesinroll << " dimes in the partially full roll." << endl;
	cout << "The Coin Sorter made " << setw(3) << fullquarterrolls << " rolls of quarters." << endl;
	cout << "    There are " << setw(2) << quartersinroll << " quarters in the partially full roll." << endl;
	cout << "The Coin Sorter made " << setw(3) << fullloonierolls << " rolls of loonies." << endl;
	cout << "    There are " << setw(2) << looniesinroll << " loonies in the partially full roll." << endl;
	cout << "The Coin Sorter made " << setw(3) << fulltoonierolls << " rolls of toonies." << endl;
	cout << "    There are " << setw(2) << tooniesinroll << " toonies in the partially full roll." << endl;
	cout << "The Coin Sorter processed " << setw(5) << othertotalcoins << " other coins." << endl;
	cout << "    The other coins completely filled " << setw(3) << othercoincontainers << " containers" << endl;
	cout << "    There were " << setw(2) << othercoins << " other coins in the partially full container" << endl;
	cout << "    The total weight of the other coins was " << fixed << setprecision(3) << setw(9) << weightoftotalothercoins << " grams" << endl;
	cout << "The Coin Sorter processed " << setw(11) << fixed << setprecision(4) << weightoftotalbentcoins << " g of bent coins";
	simulationresults << endl << endl << endl;
	simulationresults << "SUMMARY" << endl;
	simulationresults << "The Coin Sorter made " << setw(3) << fullnickelrolls << " rolls of nickels." << endl;
	simulationresults << "    There are " << setw(2) << nickelsinroll << " nickels in the partially full roll." << endl;
	simulationresults << "The Coin Sorter made " << setw(3) << fulldimerolls << " rolls of dimes." << endl;
	simulationresults << "    There are " << setw(2) << dimesinroll << " dimes in the partially full roll." << endl;
	simulationresults << "The Coin Sorter made " << setw(3) << fullquarterrolls << " rolls of quarters." << endl;
	simulationresults << "    There are " << setw(2) << quartersinroll << " quarters in the partially full roll." << endl;
	simulationresults << "The Coin Sorter made " << setw(3) << fullloonierolls << " rolls of loonies." << endl;
	simulationresults << "    There are " << setw(2) << looniesinroll << " loonies in the partially full roll." << endl;
	simulationresults << "The Coin Sorter made " << setw(3) << fulltoonierolls << " rolls of toonies." << endl;
	simulationresults << "    There are " << setw(2) << tooniesinroll << " toonies in the partially full roll." << endl;
	simulationresults << "The Coin Sorter processed " << setw(5) << othertotalcoins << " other coins." << endl;
	simulationresults << "    The other coins completely filled " << setw(3) << othercoincontainers << " containers" << endl;
	simulationresults << "    There were " << setw(2) << othercoins << " other coins in the partially full container" << endl;
	simulationresults << "    The total weight of the other coins was " << fixed << setprecision(3) << setw(9) << weightoftotalothercoins << " grams" << endl;
	simulationresults << "The Coin Sorter processed " << setw(11) << fixed << setprecision(4) << weightoftotalbentcoins << " g of bent coins";
	

	
	


	//This will close both of the files. 
	simulationresults.close();
	sensorfile.close();
	return 0;

	
}

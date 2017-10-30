#include <iostream>
#include <string>
#include <fstream>

using namespace std;

void prompt () {

	string cmd_line, cmd;
	ofstream in_file, out_file;
	int free_sp, page_sub, time;
	
	while (true) {
		
		cout << "[ep3]:" << endl;
		getline (cin, cmd_line);
		cmd = cmd_line.substr (0, 2);
		
		switch (cmd) {
			case "car":
				in_file.open (cmd_line (8));
			break;

			case "esp":
				free_sp = stoi (cmd_line.substr (7), NULL, 10);
			break;

			case "sub":
				page_sub = stoi (cmd_line.substr (10), NULL, 10);
			break;

			case "exe":
				time = stoi (cmd_line.substr (8), NULL, 10);
			break;

			case "sai":
				exit(0);
		}
	}
}
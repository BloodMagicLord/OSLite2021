#include <iostream>
#include <fstream>
#include <string>
#include <signal.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>

using std::cin;
using std::cout;
using std::string;
using std::ifstream;

int main() {
	string line;
	int pid;

	ifstream file;
	file.open(".pid");
	file >> pid;
	file.close();

	while (true) {
		cin >> line;
		if (line == "+") {
			kill (pid, SIGUSR1);
			cout << "Changed to +.\n";
		} else if (line == "*") {
			kill (pid, SIGUSR2);
			cout << "Changed to *.\n";
		} else if (line == "TERM") {
			int result = kill (pid, SIGTERM);
			cout << "Bye, bye!\n";
			return 0;
		}
	}
	return 0;
}

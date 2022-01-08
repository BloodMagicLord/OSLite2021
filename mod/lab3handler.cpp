\#include <iostream>
#include <fstream>
#include <string>
#include <unistd.h>
#include <signal.h>

using std::cout;
using std::string;
using std::ofstream;

string mode="+";

void usr1(int signal) {
	mode = "+";
}

void usr2(int signal) {
	mode = "*";
}

void term(int signal) {
	mode = "sigterm";
}

int main() {
	ofstream file;
	file.open(".pid");
	file << getpid();
	file.close();

	int answer = 1, value = 2;

	signal(SIGUSR1, usr1);
	signal(SIGUSR2, usr2);
	signal(SIGTERM, term);

	while (true) {
		if (mode == "+") {
			answer += value;
			//raise(SIGUSR2);
		} else if (mode == "*") {
			answer *= value;
			//raise(SIGUSR1);
		} else if (mode == "sigterm") {
			cout << "Exit\n";
			return 0;
		}
		cout << answer << "\n";
		int sys = system("sleep 1s");
	}
	return 0;
}

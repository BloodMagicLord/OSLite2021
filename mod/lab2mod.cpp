
#include <iostream>
#include <fstream>
#include <streambuf>
#include <vector>
#include <string>
#include <dirent.h>

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::vector;

void fastscan (int & num, string str) {
	char c = str[0];
	int index = 0;
	for (; (c < '0' || c > '9') && c != '-'; c = str[++index]);
	num = 0;
	for (; (c >= '0' && c <= '9'); c = str[++index]) {
		num = num * 10 + c - '0';
	}
}

int main() {
	DIR *dir;
	struct dirent *diread;
	vector < string > files;

	if ((dir = opendir("/proc/")) != nullptr) {
		while ((diread = readdir(dir)) != nullptr) {
			string name = diread->d_name;
			if (name[0] >= '0' && name[0] <= '9') {
				files.push_back(name);
			}
		}
		closedir(dir);
	} else {
		perror ("opendir");
		return EXIT_FAILURE;
	}

	int count = 0;
	int maxVm = 0;
	string maxVmPid="";
	for (auto file : files) {
		string path = "/proc/" + file + "/status";
		std::ifstream status(path);
		string str((std::istreambuf_iterator < char > (status)),
				std::istreambuf_iterator < char > ());
		int index = str.find("VmSize");
		int answer = 0;
		if (index > 0) {
			string sub = str.substr(index);
			fastscan(answer, sub);
			if (maxVm < answer) {
				maxVm = answer;
				maxVmPid = file;
			}
		}
		cout << file << " : " << answer << "\n";
	}

	cout << maxVmPid << "\n";
	return EXIT_SUCCESS;
}

#include"header.h"


void duplicateOriginalData(const string original_data_path, const string use_data) {
	if (_mkdir(use_data.c_str()) == 0) {
		filesystem::remove_all(use_data);
	}
	filesystem::create_directory(use_data);
	ifstream infile(original_data_path + "//datasetsnames.txt");
	if (infile.fail()) {
		cout << "Cannot open file datasetsnames.txt at " + original_data_path + "//";
		exit(1);
	}
	string line;
	while (getline(infile, line)) {
		if (line == "\n") break;
		filesystem::create_directory(use_data + "//" + line);
		filesystem::copy(original_data_path + "/" + line + "/", use_data + "/" + line + "/");
	}
}

bool deallocateDuplicatedData(const string use_data) {
	if (filesystem::remove_all(use_data)) return true;
	return false;
}
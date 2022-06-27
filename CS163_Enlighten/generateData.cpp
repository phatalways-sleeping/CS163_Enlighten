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

bool removeDatasets(string path, string name) {
	ifstream infile(path + "//datasetsnames.txt");
	if (infile.fail()) {
		cout << "Error at opening datasets names.";
		exit(1);
	}
	vector<string> names;
	bool allow_to_modify = false;
	int index = -1, i = -1;
	string line;
	while (getline(infile, line)) {
		names.push_back(line);
		i++;
		if (line == name) {
			allow_to_modify = true;
			index = i;
		}
	}
	infile.close();
	if (allow_to_modify) {
		names.erase(names.begin() + index);
		ofstream outfile(path + "//datasetsnames.txt", ios::out);
		if (outfile.is_open()) {
			for (int i = 0; i < names.size(); i++) outfile << names[i] << '\n';
		}
		outfile.close();
		filesystem::remove_all(path + "//" + name);
	}
	return allow_to_modify;
}

bool resetCurrentDataset(string path, string name, string original_path) {
	ifstream infile(path + "//datasetsnames.txt");
	if (infile.fail()) {
		cout << "Error at opening datasets names.";
		exit(1);
	}
	bool allow_to_modify = false;
	string line;
	while (getline(infile, line)) {
		if (line == name) {
			allow_to_modify = true;
			break;
		}
	}
	infile.close();
	if (!allow_to_modify) return false;
	allow_to_modify = false;
	infile.open(original_path + "//datasetsnames.txt");
	if (infile.fail()) {
		cout << "Error at opening datasets names.";
		exit(1);
	}
	while (getline(infile, line)) {
		if (line == name) {
			allow_to_modify = true;
			break;
		}
	}
	if (allow_to_modify) {
		filesystem::remove_all(path + "//" + name);
		filesystem::create_directory(path + "//" + name);
		filesystem::copy(original_path + "/" + name + "/", path + "/" + name + "/");
	}

	return allow_to_modify;
}
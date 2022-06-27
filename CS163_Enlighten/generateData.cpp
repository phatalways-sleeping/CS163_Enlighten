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

bool removeDatasets(string source) {
	int index_of_split = source.find_last_of("\//");
	string path = source.substr(0, index_of_split), name = source.substr(index_of_split + 1);
	string folder_name = upper(name.substr(0, name.find_last_of(".")));
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
		if (line == folder_name) {
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
		filesystem::remove_all(path + "//" + folder_name);
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

string upper(string s) {
	string ns = "";
	for (int i = 0; i < s.size(); i++) {
		if ('a' <= s[i] && s[i] <= 'z') {
			ns += s[i] - 'a' + 'A';
		}
		else {
			ns += s[i];
		}
	}
	return ns;
}

bool addNewDataSets(string path, string destination) {
	int index_of_split = path.find_last_of("\//");
	string source = path.substr(0, index_of_split);
	string dataset_name = path.substr(index_of_split + 1);
	string dataset_folder = upper(dataset_name.substr(0, dataset_name.find_last_of(".")));
	// Checking if there is any error in arguments
	if (source.empty() || destination.empty() || dataset_folder.empty() || dataset_name.empty()) return false;

	// Checking whether the current location already contains the dataset_folder
	ifstream infile(destination + "//datasetsnames.txt");
	if (infile.fail())
	{
		cout << "Error at opening datasets names.";
		exit(1);
	}
	bool already_contain = false;
	string line;
	while (getline(infile, line)) {
		if (line == dataset_folder)
		{
			already_contain = true;
			break;
		}
	}
	infile.close();

	// If contains, remove and create the new one
	if (already_contain) filesystem::remove_all(destination + "//" + dataset_folder);
	filesystem::create_directory(destination + "//" + dataset_folder);

	// Update the name to the datasetsnames.txt of the location folder
	if (!already_contain) {
		ofstream outfile(destination + "//datasetsnames.txt", ios::app);
		if (outfile.is_open()) {
			outfile << dataset_folder << "\n";
		}
		outfile.close();
	}

	// Create the datasetsnames.txt in the newly created folder
	ofstream outfile(destination + "//" + dataset_folder + "//datasetsnames.txt", ios::out);
	if (outfile.is_open()) {
		outfile << dataset_name << "\n";
	}
	outfile.close();

	// Copying the new dataset into the newly created folder
	filesystem::copy_file(source + "/" + dataset_name, destination + "/" + dataset_folder + "/" + dataset_name);

	return addToUseData(destination + "/" + dataset_folder + "/" + dataset_name, use_data);
}

bool addToUseData(string path, string destination) {
	int index_of_split = path.find_last_of("\//");
	string dataset_name = path.substr(index_of_split + 1);
	string dataset_folder = upper(dataset_name.substr(0, dataset_name.find_last_of(".")));
	if (path.empty() || destination.empty() || dataset_folder.empty() || dataset_name.empty()) return false;
	ifstream infile(destination + "//datasetsnames.txt");
	if (infile.fail())
	{
		cout << "Error at opening datasets names.";
		exit(1);
	}
	bool already_contain = false;
	string line;
	while (getline(infile, line)) {
		if (line == dataset_folder)
		{
			already_contain = true;
			break;
		}
	}
	infile.close();

	if (already_contain) filesystem::remove_all(destination + "//" + dataset_folder);
	filesystem::create_directory(destination + "//" + dataset_folder);

	if (!already_contain) {
		ofstream outfile(destination + "//datasetsnames.txt", ios::app);
		if (outfile.is_open()) {
			outfile << dataset_folder << "\n";
		}
		outfile.close();
	}

	ofstream outfile(destination + "//" + dataset_folder + "//datasetsnames.txt", ios::out);
	if (outfile.is_open()) {
		outfile << dataset_name << "\n";
	}
	outfile.close();

	// Copying the new dataset into the newly created folder
	filesystem::copy_file(path, destination + "/" + dataset_folder + "/" + dataset_name);
	return true;
}
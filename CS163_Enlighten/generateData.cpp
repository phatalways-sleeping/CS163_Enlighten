#include"header.h"
#include "test_function.h"


void addNewDataset(Enlighten& dataset, string original_data_path) {

}

void changeCurrentDataset(Enlighten& dataset, string new_data_path, string original_data_path) {

}

void duplicateOriginalData(const string original_data_path, const string use_data) {
	filesystem::remove_all(use_data);
	filesystem::create_directory(use_data);
	ifstream infile(original_data_path + "//datasetsnames.txt");
	if (infile.fail()) {
		cout << "Cannot open file datasetsnames.txt at " + original_data_path + "//";
		exit(1);
	}
	string line;
	while (getline(infile, line)) {
		if (line == "\n") break;
		cout << line << endl;
		filesystem::create_directory(use_data + "//" + line);
		filesystem::copy(original_data_path + "/" + line + "/", use_data + "/" + line + "/");
	}
	infile.close();
}

bool deallocateDuplicatedData(const string use_data) {
	if (filesystem::remove_all(use_data)) return true;
	return false;
}

bool removeDatasets(string source) {
	int index_of_split = source.find_last_of("\\//");
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
	int index_of_split = path.find_last_of("\\//");
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
	int index_of_split = path.find_last_of("\\//");
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

string findFolder(string name, string dictionary_link) {
	ifstream infile(dictionary_link);
	if (infile.fail()) return "";
	name = upper(name);
	int number;
	string folder;
	infile >> number;
	string line;
	while (getline(infile, line)) {
		int sep = line.find_first_of(" ");
		if (line.substr(0, sep) != name) continue;
		line = line.substr(sep + 1);
		int index = line.find_last_of("\\//");
		string folderlink = line.substr(0, index);
		int i = folderlink.find_last_of("\\//");
		folder = upper(folderlink.substr(i + 1));
	}
	infile.close();
	return folder;
}

bool changeDataset(string folderpath, string destination) {
	vector<string> names;
	for (const auto& file : filesystem::directory_iterator(folderpath)) {
		int i = file.path().string().find_last_of("\\//");
		names.push_back(file.path().string().substr(i + 1));
	}

	filesystem::remove_all(destination + "//");
	filesystem::copy(folderpath + "/", destination + "/");

	ofstream file(destination + "//datasetsnames.txt", ios::out);
	for (auto i : names) file << i << '\n';
	file.close();
	return true;
}
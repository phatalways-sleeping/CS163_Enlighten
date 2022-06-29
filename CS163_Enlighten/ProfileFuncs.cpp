#include"struct_and_dependencies.h"

bool readUserProfile(string path, string username, Profile& profile) {
    fstream file(path, ios::in);
    if (file.fail()) {
        file.close();
        return false;
    }
    vector<vector<string>> v;
    vector<string> k;
    string line, word;
    if (file.is_open())
    {
        while (getline(file, line))
        {
            k.clear();
            stringstream s(line);
            while (getline(s, word, ','))
                k.push_back(word);
            v.push_back(k);
        }
    }
    file.close();
    bool has_username = false;
    for (int i = 0; i < v.size(); i++) {
        if (v[i][0] == username) {
            has_username = true;
            for (int j = 0; j < v[i].size(); j++) {
                if (j == 0) {
                    profile.username = v[i][j];
                }
                if (v[i][j] == "rank") profile.level = stoi(v[i][j + 1]);
                if (v[i][j] == "score") profile.scores = stod(v[i][j + 1]);
                if (v[i][j] == "dates") {
                    for (int z = j + 1; z < v[i].size(); z++) profile.dates_login.push_back(v[i][z]);
                }
            }
            break;
        }
    }
    return has_username;
}

bool readAllUserProfile(string path, vector<Profile>& profiles) {
    fstream file(path, ios::in);
    if (file.fail()) {
        file.close();
        return false;
    }
    vector<vector<string>> v;
    vector<string> k;
    string line, word;
    if (file.is_open())
    {
        while (getline(file, line))
        {
            k.clear();
            stringstream s(line);
            while (getline(s, word, ','))
                k.push_back(word);
            v.push_back(k);
        }
    }
    file.close();
    for (int i = 0; i < v.size(); i++) {
        Profile current_profile;
        for (int j = 0; j < v[i].size(); j++) {
            if (j == 0) current_profile.username = v[i][j];
            if (v[i][j] == "rank") current_profile.level = stoi(v[i][j + 1]);
            if (v[i][j] == "score") current_profile.scores = stod(v[i][j + 1]);
            if (v[i][j] == "dates") {
                for (int z = j + 1; z < v[i].size(); z++) current_profile.dates_login.push_back(v[i][z]);
            }
        }
        profiles.push_back(current_profile);
    }
    return profiles.size() > 0;
}


bool writeUserProfile(string path, string username, const Profile& profile) {
    vector<Profile> profiles;
    if (readAllUserProfile(path, profiles)) {
        bool has_username = false;
        for (int i = 0; i < profiles.size(); i++) {
            if (profiles[i].username == profile.username) {
                profiles[i] = profile;
                has_username = true;
                break;
            }
        }
        if (!has_username) profiles.push_back(profile);
        ofstream file(path, ios::out);
        if (file.is_open()) {
            for (int i = 0; i < profiles.size(); i++) {
                file << profiles[i].username << ",rank," << to_string(profiles[i].level) << ",score," << to_string(profiles[i].scores) << ",dates,";
                for (int j = 0; j < profiles[i].dates_login.size(); j++) file << profiles[i].dates_login[j] << ",";
                file << '\n';
            }
        }
        file.close();
    }

    return true;
}
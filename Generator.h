#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <chrono>
#include <thread>

class Group {
public:
	int id;
	std::string name;
	Group(int id, std::string name) {
		this->id = id;
		this->name = name;
	}
	bool operator==(Group group) {
		return this->id == group.id;
	}
};

class Generator
{
private:
	std::vector<std::string> activities;
	std::vector<Group> groups;
	int activitiesPerDay = 0;
	int numberOfDays = 0;
	std::fstream file;
public:
	void addActivity(std::string name) {
		this->activities.push_back(name);
	}

	void addGroup(std::string& name) {
		this->groups.push_back(Group(groups.size() ? groups[groups.size() - 1].id + 1 : 1, name));
	}

	void ScheduleActivities() {
		if (!activities.size() || !groups.size()) {
			std::cout << "No activities or groups entered!" << std::endl;
			std::this_thread::sleep_for(std::chrono::milliseconds(1000));
			return;
		}
		std::cout << "Enter the number of days: "; std::cin >> numberOfDays;
		std::string fileName; std::cout << "Enter the name of save file (example: spreadsheet.csv): "; std::cin >> fileName;
		file.open(fileName, std::ios::out | std::ios::app);
		file.clear();
		//cast to float otherwise integer arithmetics are used
		activitiesPerDay = ceil(activities.size() / (float)numberOfDays);
		std::vector<std::string> timeArr;
		for (int i = 0; i < activitiesPerDay; i++) {
			std::string time;
			switch (i) {
			case 0:
				time = "1st";
				break;
			case 1:
				time = "2nd";
				break;
			case 2:
				time = "3rd";
				break;
			default:
				time = std::to_string(i + 1).append("th");
			}

			std::string temp; std::cout << "Enter the " << time << " activity time: "; std::cin.ignore(); std::getline(std::cin, temp);
			timeArr.push_back(temp);
		}
		//set up rows in csv
		file << "Groups:;";
		for (Group group : groups) {
			file << group.name << ";";
		}
		file << "\n";
		while (activities.size() < groups.size())
			activities.push_back("Free Time");
		//doesn't work if two activities have the same name
		std::string startingActivity = activities[0];
		for (int i = 0; i < numberOfDays; i++) {
			for (int j = 0; j < activitiesPerDay; j++) {
				file << "Day " << i + 1 << " " << timeArr[j] << ";";
				for (int k = 0; k < groups.size(); k++) {
					file << activities[k] << ";";
				}
				file << "\n";
				//rotate activities
				activities.insert(activities.begin(), activities[activities.size() - 1]);
				activities.pop_back();
				//check if rotation completed
				if (activities[0] == startingActivity && i == numberOfDays - 1)
					return;
			}
		}
		std::cout << "Finished generating the timetable!" << std::endl;
		std::this_thread::sleep_for(std::chrono::milliseconds(5000));
		return;
	}
};


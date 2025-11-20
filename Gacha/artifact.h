#pragma once

#include <iostream>
#include <vector>
#include <random>
#include <conio.h>
#include <algorithm>
#include <iomanip>

class artifactSystem {
private:
	const std::vector<std::string> artifactType = { "Flower of Life" , "Plume of Death", "Sands of Eon", "Goblet of Eonothem", "Circlet of Logos" };
	const std::vector<std::pair<std::string, double>> artifactStats = {
		{"HP", 0.2333}, {"ATK", 0.2333}, {"DEF", 0.2333}, {"CRIT Rate", 0.1}, {"CRIT DMG", 0.1},
		{"Energy Recharge", 0.05}, {"Elemental Mastery", 0.05} };

	struct artifact {
		std::string type;
		std::string mainStat;
		double mainStat_val = 0.0;
		std::vector<std::pair<std::string, double>> addStat;
	};

	struct basisParameters {
		static constexpr double baseChanceForFourStat = 0.25;
	};

	void distStat(std::vector<std::pair<std::string, double>> acceptableStats) {
		double chance = dist(gen);
		bool isFourStat = false;

		if (chance < basisParameters::baseChanceForFourStat) { isFourStat = true; }
		// выборка по распределению
	}

protected:
	std::random_device rd;
	std::mt19937 gen;
	std::uniform_real_distribution<double> dist;
public:
	artifactSystem() : gen(rd()), dist(0.0, 1.0) {}

	void getArtifact() {
		artifact currentArtifact;

		std::uniform_int_distribution<size_t> artTypeDist(0, artifactType.size() - 1);
		size_t artTypeIndex = artTypeDist(gen);
		std::string artType = artifactType[artTypeIndex];
		currentArtifact.type = artType;

		switch (artTypeIndex) {
			case(0):
				currentArtifact.mainStat = "HP";
				break;
			case(1):
				currentArtifact.mainStat = "ATK";
				break;
			case(2): {
				const std::vector<std::pair<std::string, double>> acceptableStats = { {"ATK", 0.2667}, {"HP", 0.2667}, {"DEF", 0.2667}, {"Energy Recharge", 0.1}, {"Elemental Mastery", 0.1} };
				distStat(acceptableStats);
			}
				   break;
			case(3): {
				const std::vector<std::pair<std::string, double>> acceptableStats = {
					{"ATK", 0.1975}, {"HP", 0.1975}, {"DEF", 0.1975}, {"Elemental Mastery", 0.05}, {"Physical DMG Bonus", 0.05}, {"Pyro DMG Bonus", 0.05},
					{"Hydro DMG Bonus", 0.05}, {"Dendro DMG Bonus", 0.05}, {"Electro DMG Bonus", 0.05},
					{"Anemo DMG Bonus", 0.05}, {"Cryo DMG Bonus", 0.05}, {"Geo DMG Bonus", 0.05} };
				distStat(acceptableStats);
			}
				   break;
			case(4): {
				const std::vector<std::pair<std::string, double>> acceptableStats = {
					{"ATK", 0.22}, {"HP", 0.22}, {"DEF", 0.22}, {"Elemental Mastery", 0.04},
					{"CRIT Rate", 0.1}, {"CRIT DMG", 0.1}, {"Healing Bonus", 0.1} };
				distStat(acceptableStats);
				break;
			}
		}
	}
};

int startGacha_Artifact() {
	std::cout << "ARTIFACT SIMULATOR" << std::endl;
	std::cout << std::endl;
	return 0;
}
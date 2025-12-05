#pragma once
#include <iostream>
#include <random>
#include <vector>
#include <conio.h>
#include <iomanip>
#include <algorithm>
#include <string>

class Gacha {
protected:
    std::random_device rd;
    std::mt19937 gen;
    std::uniform_real_distribution<> charDist;

    const std::vector<std::string> threeStarItem = { "Trash" };

    const std::vector<std::string> fourStarItem = {
        "Ceremonial Sword", "Favonius Sword", "Ceremonial Greatsword", "Favonius Greatsword",
        "Dragon's Thunder", "Ceremonial Memoirs", "Favonius Codex", "Ceremonial Bow", "Favonius Warbow", "Dragon's Roar",
        "Sword-Flute", "Raincutter", "Sword-Bell", "Favonius Lance", "Eye of Perception", "Wanderer's Song", "Rusty Bow", "Stringless" };

    const std::vector<std::string> fourStarCharacter = {
        "Aino", "Ifa", "Lan Yan", "Kachina", "Ka Min", "Charlotte", "Lynette", "Mika", "Faruzan", "Candace", "Collei", "Yun Jin",
        "Shikanoin Heizou", "Gorou", "Thoma", "Rosaria", "Sucrose", "Chongyun", "Bennett", "Ningguang", "Beidou", "Amber", "Kaeya", "Lisa",
        "Dahlia", "Yanxiao", "Ororon", "Sethos", "Chevreuse", "Freminet", "Kaveh", "Yaoyao", "Layla", "Dori", "Kuki Shinobu", "Kirara",
        "Kujou Sara", "Sayu", "Yanfei", "Xinyan", "Diona", "Noelle", "Fischl", "Xingqiu", "Xiangling", "Razor", "Barbara" };

    const std::vector<std::string> fiveStarCharacter = { "Mizuki", "Tighnari", "Mona", "Diluc", "Dehya", "Keqing", "Qiqi", "Jean" };

    const std::vector<std::string> fiveStarItem = {
        "Skyward Sword", "Wolf's Gravestone", "Jade Cutter", "Prayer to the Sacred Winds", "Amos' Bow",
        "Falcon Sword", "Skyward Pride", "Skyward Spine", "Skyward Atlas", "Skyward Wing" };

    struct dynamicParameters {
        struct dropLists {
            std::vector <std::pair<std::string, int>> fiveStarDrop;
            std::vector<std::pair<std::string, int>> charDrop;
            std::vector<std::string> inventory;
        };
        struct numericValues {
            int countForFourStar = 0;
            int countForFiveStar = 0;
            int rate = 0;
            long starBless = 0;
            long stardust = 0;
            int totalPullCounter = 0;
        };
    };

    dynamicParameters::dropLists drop_lists;
    dynamicParameters::numericValues numeric_space;

    struct basisParameters {
        struct baseChances {
            static constexpr double baseFiveStarChance = 0.007;
            static constexpr double baseFourStarChance = 0.051;
            static constexpr double baseEqualChance = 0.5;
            static constexpr std::pair<double, double> factor = { 0.04, 2.85 };
        };
        struct pullValues {
            static constexpr int startPityValue = 73;
            static constexpr int fiveStarLimit = 90;
            static constexpr int fourStarLimit = 10;
            static constexpr int constLimit = 6;
        };
        struct starCurrencyVal{
            static constexpr int baseBlessForFiveStar = 10;
            static constexpr int baseBlessForFourStar = 2;
            static constexpr int limitBlessForFiveStar = 25;
            static constexpr int limitBlessForFourStar = 5;
            static constexpr int starDustValue = 18;
        };
    };

    bool checkDuplicate(std::string drop) {
        bool duplicate = false;
        bool isLastConst = false;
        size_t index;

        for (size_t i = 0; i < drop_lists.charDrop.size(); i++) {
            if (drop == drop_lists.charDrop[i].first) {
                duplicate = true;
                index = i;
                break;
            }
        }
        if (!duplicate) {
            drop_lists.charDrop.push_back({ drop, 0 });
        }
        else {
            if (drop_lists.charDrop[index].second < basisParameters::pullValues::constLimit) { drop_lists.charDrop[index].second++; }
            else isLastConst = true;
        }
        return isLastConst;
    }

public:

    Gacha() : gen(rd()), charDist(0.0, 1.0) {}

    int getPulls() {
        return numeric_space.totalPullCounter;
    }

    void getCurrency() {
        std::cout << "Star Bless: " << numeric_space.starBless << " (" << numeric_space.starBless / 5.0 << ")" << std::endl;
        std::cout << "Stardust: " << numeric_space.stardust << std::endl;
    }

    void getInventory() {
        if (!drop_lists.inventory.empty()) {
            for (size_t i = 1; i < drop_lists.inventory.size() + 1; i++) {
                std::cout << std::setw(30) << drop_lists.inventory[i - 1];
                if (i % 3 == 0) std::cout << std::endl;
            }
        }
        else {
            std::cout << "You haven't obtained any items" << std::endl;
        }
        std::cout << std::endl;
    }

    void constellationList() {
        if (!drop_lists.charDrop.empty()) {
            std::sort(drop_lists.charDrop.begin(), drop_lists.charDrop.end(), [](const std::pair<std::string, int>& a, const std::pair<std::string, int>& b) {
                return a.second > b.second; });

            for (size_t i = 1; i < drop_lists.charDrop.size() + 1; i++) {
                std::cout << std::setw(30) << drop_lists.charDrop[i - 1].first << " " << drop_lists.charDrop[i - 1].second;
                if (i != 0 && i % 3 == 0) std::cout << std::endl;
            }
        }
        else {
            std::cout << "You don't have any characters yet" << std::endl;
        }
    }

    void getStatistic(bool debug = false) {

        double avr = 0;
        std::vector<int> dist(basisParameters::pullValues::fiveStarLimit, 0);

        if (!drop_lists.fiveStarDrop.empty()) {
            for (size_t i = 1; i < drop_lists.fiveStarDrop.size() + 1; i++) {
                if (!debug) {
                    std::cout << std::setw(30) << drop_lists.fiveStarDrop[i - 1].first << " - " << drop_lists.fiveStarDrop[i - 1].second;
                    if (i != 0 && i % 3 == 0) std::cout << std::endl;
                }
                avr += drop_lists.fiveStarDrop[i - 1].second;
            }
            avr /= (double)drop_lists.fiveStarDrop.size();
            std::cout << std::endl;

            for (size_t i = 0; i < drop_lists.fiveStarDrop.size(); i++) {
                dist[drop_lists.fiveStarDrop[i].second - 1]++;
            }
        }
        else {
            std::cout << "You haven't obtained any 5-star drops yet" << std::endl;
        }

        std::cout << std::endl;
        std::cout << std::setw(15) << "Average: " << avr << std::endl;

        if (debug) {
            std::cout << std::setw(18) << "Distribution: " << std::endl;
            std::cout << std::endl;

            for (size_t i = 1; i < dist.size() + 1; i++) {
                long sum = 0;
                for (size_t j = 0; j < dist.size(); j++) { sum += dist[j]; }

                std::cout << std::setw(15) << i << "-th: " << std::setw(7) << dist[i - 1] << " (" << std::fixed << std::setprecision(3) << dist[i - 1] * 100.0 / sum << "%)";
                if (i != 0 && i % 3 == 0) std::cout << std::endl;
            }
        }
    }
};

class GachaAlgorithm : public Gacha {
private:
    double calcProbability(int currentPull) {
        return basisParameters::baseChances::factor.first * currentPull - basisParameters::baseChances::factor.second;
    }

    double rateForFiveStar(int currentPull) {
        if (currentPull == basisParameters::pullValues::fiveStarLimit) { return 1.0; }
        if (currentPull >= basisParameters::pullValues::startPityValue) { return calcProbability(currentPull); }
        else { return basisParameters::baseChances::baseFiveStarChance; }
    }

    double rateForFourStar(int currentPull) {
        if (currentPull == basisParameters::pullValues::fourStarLimit) { return 1.0; }
        else { return basisParameters::baseChances::baseFourStarChance; }
    }
public:
    void singleWish(bool debug = false) {

        numeric_space.totalPullCounter++;
        numeric_space.countForFiveStar++;
        numeric_space.countForFourStar++;
        numeric_space.rate++;

        double chance = charDist(gen);

        if (chance < rateForFiveStar(numeric_space.countForFiveStar)) {
            // Character or Item
            if (charDist(gen) < basisParameters::baseChances::baseEqualChance) {
                std::uniform_int_distribution<size_t> dis(0, fiveStarCharacter.size() - 1);
                std::string drop = fiveStarCharacter[dis(gen)];
                if (!debug) { std::cout << "5-Star " << drop; }


                if (checkDuplicate(drop)) numeric_space.starBless += basisParameters::starCurrencyVal::limitBlessForFiveStar;
                else numeric_space.starBless += basisParameters::starCurrencyVal::baseBlessForFiveStar;

                drop_lists.fiveStarDrop.push_back({ drop, numeric_space.rate });

                numeric_space.countForFiveStar = 0;
                numeric_space.rate = 0;
            }
            else {
                std::uniform_int_distribution<size_t> dis(0, fiveStarItem.size() - 1);
                std::string drop = fiveStarItem[dis(gen)];
                if (!debug) { std::cout << "5-Star " << drop; }

                numeric_space.starBless += basisParameters::starCurrencyVal::baseBlessForFiveStar;
                drop_lists.fiveStarDrop.push_back({ drop, numeric_space.rate });
                drop_lists.inventory.push_back(drop);
                numeric_space.countForFiveStar = 0;
                numeric_space.rate = 0;
            }

        }
        else if (chance < rateForFourStar(numeric_space.countForFourStar)) {
            // Character or Item
            if (charDist(gen) < basisParameters::baseChances::baseEqualChance) {
                std::uniform_int_distribution<size_t> dis(0, fourStarCharacter.size() - 1);
                std::string drop = fourStarCharacter[dis(gen)];
                if (!debug) { std::cout << "4-Star " << drop; }

                if (checkDuplicate(drop)) numeric_space.starBless += basisParameters::starCurrencyVal::limitBlessForFourStar;
                else numeric_space.starBless += basisParameters::starCurrencyVal::baseBlessForFourStar;
            }
            else {
                std::uniform_int_distribution<size_t> dis(0, fourStarItem.size() - 1);
                std::string drop = fourStarItem[dis(gen)];
                if (!debug) { std::cout << "4-Star " << drop; }

                numeric_space.starBless += basisParameters::starCurrencyVal::baseBlessForFourStar;
                drop_lists.inventory.push_back(drop);
            }

            numeric_space.countForFourStar = 0;
        }
        else {
            if (!debug) { std::cout << threeStarItem[0]; }
            numeric_space.stardust += basisParameters::starCurrencyVal::starDustValue;
        }
    }

    void multiWish(long n, bool debug = false) {
        for (long i = 0; i < n; i++) {
            singleWish(debug);
            if (!debug) { std::cout << std::endl; }
        }
    }
};

class EventBanner : public GachaAlgorithm {
private:
    const std::string eventCharacter = "Escoffie";
    bool gotEventCharacter = false;
public:
    
};

class DebugSys : public GachaAlgorithm {
private:
    void clearData(bool exit = false) {
        drop_lists.charDrop.clear();
        drop_lists.fiveStarDrop.clear();
        drop_lists.inventory.clear();
        drop_lists.charDrop.shrink_to_fit();
        drop_lists.fiveStarDrop.shrink_to_fit();
        drop_lists.inventory.shrink_to_fit();
        numeric_space.starBless = 0;
        numeric_space.stardust = 0;
        numeric_space.totalPullCounter = 0;
        numeric_space.rate = 0;
        numeric_space.countForFiveStar = 0;
        numeric_space.countForFourStar = 0;

        if (!exit) {
            std::cout << "local data has been cleared" << std::endl;
            std::cout << std::endl;
        }
    }

    void distTest() {
        long n;
        std::cout << "> "; std::cin >> n;
        multiWish(n, true);
        getStatistic(true);
    }
public:
    void start() {
        std::string command;
        while (true) {
            std::cout << ">> "; std::getline(std::cin, command);
            std::cout << std::endl;

            if (command == "exit") { break; }
            else if (command == "clear") { clearData(); }
            else if (command == "mw") { distTest(); }
            else { std::cout << "command not found\n" << std::endl; }
        }
        command.clear();
        clearData(true);
    }
};

int startGacha_Banner() {
    std::cout << "BANNER SIMULATOR" << std::endl;
    std::cout << std::endl;
    GachaAlgorithm gachaSystem;
    static constexpr int ESC_KEY = 27;

    std::cout << "(1) to Wish once\n(2) to Wish 10 times\n(3) to view inventory\n(4) to view statistics" << std::endl;

    while (true) {

        std::cout << std::endl;
        std::cout << "Total pulls: " << gachaSystem.getPulls() << " (" << gachaSystem.getPulls() * 160 << " Primogems)" << std::endl;
        gachaSystem.getCurrency();

        std::cout << "____________________" << std::endl;

        int type = _getch();
        std::cout << std::endl;

        if (type == '1') {
            gachaSystem.singleWish();
            std::cout << std::endl;
        }
        else if (type == '2') {
            gachaSystem.multiWish(10);
            std::cout << std::endl;
        }
        else if (type == '3') {
            gachaSystem.getInventory();
        }
        else if (type == '4') {
            std::cout << "Constellations: " << std::endl;
            gachaSystem.constellationList();

            std::cout << std::endl;

            std::cout << "Statistics: " << std::endl;
            gachaSystem.getStatistic();
            std::cout << std::endl;
        }
        else if (type == ESC_KEY) { return 0; } // выход на esc
        // debug
        else {
            if (type == '0') {
                int doubleCheck = _getch();
                if (doubleCheck == '0') {
                    std::cout << "// debug //" << std::endl;
                    std::cout << std::endl;
                    DebugSys init;
                    init.start();
                }
            }
        }
    }
}
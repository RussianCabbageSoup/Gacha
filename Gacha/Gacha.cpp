#include <iostream>
#include <random>
#include <vector>
#include <conio.h>
#include <limits>
#include <iomanip>
#include <cmath>
#include <algorithm>

class GachaSystem {
private:

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

    struct dinamicParameters {
        struct massive {
            std::vector <std::pair<std::string, int>> fiveStarDrop;
            std::vector<std::pair<std::string, int>> charDrop;
            std::vector<std::string> inventory;
        };
        struct number {
            int countForFourStar = 0;
            int countForFiveStar = 0;
            int rate = 0;
            long starBless = 0;
            long stardust = 0;
            int totalPullCounter = 0;
        };
    };

    dinamicParameters::massive listVal;
    dinamicParameters::number numberVal;

    struct basisParameters {
        static constexpr double baseFiveStarChance = 0.007;
        static constexpr double baseFourStarChance = 0.051;
        static constexpr int startPityValue = 73;
        static constexpr int fiveStarLimit = 90;
        static constexpr int fourStarLimit = 10;
        static constexpr std::pair<double, double> factor = {0.04, 2.85};
        static constexpr int constLimit = 6;
    };

    double calcProbability(int currentPull) {
        return basisParameters::factor.first * currentPull - basisParameters::factor.second;
    }

    double rateForFiveStar(int currentPull) {
        if (currentPull == basisParameters::fiveStarLimit) { return 1.0; }
        if (currentPull >= basisParameters::startPityValue) { return calcProbability(currentPull); }
        else { return basisParameters::baseFiveStarChance; }
    }

    double rateForFourStar(int currentPull) {
        if (currentPull == basisParameters::fourStarLimit) { return 1.0; }
        else { return basisParameters::baseFourStarChance; }
    }

    bool checkDuplicate(std::string drop) {
        bool duplicate = false;
        bool isLastConst = false;
        size_t index;

        for (size_t i = 0; i < listVal.charDrop.size(); i++) {
            if (drop == listVal.charDrop[i].first) {
                duplicate = true;
                index = i;
            }
        }
        if (!duplicate) {
            listVal.charDrop.push_back({ drop, 0 });
        }
        else {
            if (listVal.charDrop[index].second < basisParameters::constLimit) { listVal.charDrop[index].second++; }
            else isLastConst = true;
        }
        return isLastConst;
    }

public:

    GachaSystem() : gen(rd()), charDist(0.0, 1.0) {}

    int getPulls() {
        return numberVal.totalPullCounter; 
    }

    void getCurrency() {
        std::cout << "Star Bless: " << numberVal.starBless << " (" << numberVal.starBless / 5.0 << ")" << std::endl;
        std::cout << "Stardust: " << numberVal.stardust << std::endl;
    }

    void getInventory() {
        if (!listVal.inventory.empty()) {
            for (size_t i = 1; i < listVal.inventory.size() + 1; i++) {
                std::cout << std::setw(30) << listVal.inventory[i - 1];
                if (i % 3 == 0) std::cout << std::endl;
            }
        }
        else {
            std::cout << "You haven't obtained any items" << std::endl;
        }
        std::cout << std::endl;
    }

    void constellationList() {
        if (!listVal.charDrop.empty()) {
            std::sort(listVal.charDrop.begin(), listVal.charDrop.end(), [](const std::pair<std::string, int>& a, const std::pair<std::string, int>& b) {
                return a.second > b.second; });

            for (size_t i = 1; i < listVal.charDrop.size() + 1; i++) {
                std::cout << std::setw(30) << listVal.charDrop[i - 1].first << " " << listVal.charDrop[i - 1].second;
                if (i != 0 && i % 3 == 0) std::cout << std::endl;
            }
        }
        else {
            std::cout << "You don't have any characters yet" << std::endl;
        }
    }

    void getStatistic() {

        double avr = 0;
        std::vector<int> dist(90, 0);

        if (!listVal.fiveStarDrop.empty()) {

            for (size_t i = 1; i < listVal.fiveStarDrop.size() + 1; i++) {
                std::cout << std::setw(30) << listVal.fiveStarDrop[i - 1].first << " - " << listVal.fiveStarDrop[i - 1].second;
                if (i != 0 && i % 3 == 0) std::cout << std::endl;

                avr += listVal.fiveStarDrop[i - 1].second;
            }
            avr /= (double)listVal.fiveStarDrop.size();
            std::cout << std::endl;

            for (size_t i = 0; i < listVal.fiveStarDrop.size(); i++) {
                dist[listVal.fiveStarDrop[i].second - 1]++;
            }
        }
        else {
            std::cout << "You haven't obtained any 5-star drops yet" << std::endl;
        }

        std::cout << std::endl;
        std::cout << std::setw(15) << "Average: " << avr << std::endl;
        std::cout << std::setw(15) << "Distribution: " << std::endl;
        std::cout << std::endl;
        for (size_t i = 1; i < dist.size() + 1; i++) {
            std::cout << std::setw(8) << i << "-th: " << std::setw(5) << dist[i - 1];
            if (i != 0 && i % 6 == 0) std::cout << std::endl;
        }
    }

    void singleWish() {

        numberVal.totalPullCounter++;
        numberVal.countForFiveStar++;
        numberVal.countForFourStar++;
        numberVal.rate++;

        double chance = charDist(gen);

        if (chance < rateForFiveStar(numberVal.countForFiveStar)) {
            // Character or Item
            if (charDist(gen) < 0.5) {  
                std::uniform_int_distribution<size_t> dis(0, fiveStarCharacter.size() - 1);
                std::string drop = fiveStarCharacter[dis(gen)];
                std::cout << "5-Star " << drop;

                if (checkDuplicate(drop)) numberVal.starBless += 25;
                else numberVal.starBless += 10;

                listVal.fiveStarDrop.push_back({ drop, numberVal.rate });

                numberVal.countForFiveStar = 0;
                numberVal.rate = 0;
            }
            else {
                std::uniform_int_distribution<size_t> dis(0, fiveStarItem.size() - 1);
                std::string drop = fiveStarItem[dis(gen)];
                std::cout << "5-Star " << drop;

                numberVal.starBless += 10;
                listVal.fiveStarDrop.push_back({ drop, numberVal.rate });
                listVal.inventory.push_back(drop);
                numberVal.countForFiveStar = 0;
                numberVal.rate = 0;
            }

        }
        else if (chance < rateForFourStar(numberVal.countForFourStar)) {
            // Character or Item
            if (charDist(gen) < 0.5) {    
                std::uniform_int_distribution<size_t> dis(0, fourStarCharacter.size() - 1);
                std::string drop = fourStarCharacter[dis(gen)];
                std::cout << "4-Star " << drop;

                if (checkDuplicate(drop)) numberVal.starBless += 5;
                else numberVal.starBless += 2;
            }
            else {
                std::uniform_int_distribution<size_t> dis(0, fourStarItem.size() - 1);
                std::string drop = fourStarItem[dis(gen)];
                std::cout << "4-Star " << drop;

                numberVal.starBless += 2;
                listVal.inventory.push_back(drop);
            }

            numberVal.countForFourStar = 0;
        }
        else {
            std::cout << threeStarItem[0];
            numberVal.stardust += 18;
        }
    }

    void multiWish(long n) {
        for (int i = 0; i < n; i++) {
            singleWish();
            std::cout << std::endl;
        }
    }
};

int main() {
    std::cout << "SIMULATOR" << std::endl;
    std::cout << std::endl;
    GachaSystem gachaSystem;

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
        // debug
        else {
            gachaSystem.multiWish(1500000);
        }
    }
    return 0;
}
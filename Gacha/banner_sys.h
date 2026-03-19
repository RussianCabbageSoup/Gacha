#pragma once

#include <iostream>
#include <random>
#include <vector>
#include <conio.h>
#include <iomanip>
#include <algorithm>
#include <string>
#include <unordered_map>

class Banner_System {
protected:
    std::random_device rd;
    std::mt19937 gen;
    std::uniform_real_distribution<> distribution;

    const std::vector<std::string> three_star_item = { "Trash" };

    const std::vector<std::string> four_star_item = {
        "Ceremonial Sword", "Favonius Sword", "Ceremonial Greatsword", "Favonius Greatsword",
        "Dragon's Thunder", "Ceremonial Memoirs", "Favonius Codex", "Ceremonial Bow", "Favonius Warbow", "Dragon's Roar",
        "Sword-Flute", "Raincutter", "Sword-Bell", "Favonius Lance", "Eye of Perception", "Wanderer's Song", "Rusty Bow", "Stringless" };

    const std::vector<std::string> four_star_character = {
        "Aino", "Ifa", "Lan Yan", "Kachina", "Ka Min", "Charlotte", "Lynette", "Mika", "Faruzan", "Candace", "Collei", "Yun Jin",
        "Shikanoin Heizou", "Gorou", "Thoma", "Rosaria", "Sucrose", "Chongyun", "Bennett", "Ningguang", "Beidou", "Amber", "Kaeya", "Lisa",
        "Dahlia", "Yanxiao", "Ororon", "Sethos", "Chevreuse", "Freminet", "Kaveh", "Yaoyao", "Layla", "Dori", "Kuki Shinobu", "Kirara",
        "Kujou Sara", "Sayu", "Yanfei", "Xinyan", "Diona", "Noelle", "Fischl", "Xingqiu", "Xiangling", "Razor", "Barbara" };

    const std::vector<std::string> five_star_character = { "Mizuki", "Tighnari", "Mona", "Diluc", "Dehya", "Keqing", "Qiqi", "Jean" };

    const std::vector<std::string> five_star_item = {
        "Skyward Sword", "Wolf's Gravestone", "Jade Cutter", "Prayer to the Sacred Winds", "Amos' Bow",
        "Falcon Sword", "Skyward Pride", "Skyward Spine", "Skyward Atlas", "Skyward Wing" };

    struct dynamic {
        struct lists {
            std::vector <std::pair<std::string, int>> five_star_drop;
            std::vector <std::pair<std::string, long>> four_star_drop;
            std::unordered_map<std::string, int> character_drop;
            std::vector<std::string> inventory;
        };
        struct counters {
            int pity_five_star = 0;
            int pity_four_star = 0;
            long currency_1 = 0;
            long currency_2 = 0;
            int total_pulls = 0;
        };
    };

    dynamic::lists drop_list;
    dynamic::counters counter;

    struct basis_params {
        struct probability {
            static constexpr double five_star_chance = 0.0063;
            static constexpr double four_star_chance = 0.051;
            static constexpr double equal = 0.5;
            static constexpr double increase_event_character = 0.585;
            static constexpr std::pair<double, double> factor_pity = { 0.057, 4.15 };
            static constexpr double factor_default = 0.000015;
        };
        struct limits {
            static constexpr int start_ptiy_val = 74;
            static constexpr int five_star_pity_limit = 90;
            static constexpr int four_star_pity_limit = 10;
            static constexpr int const_limit = 6;
        };
        struct currency{
            static constexpr int ccy_base_five_star = 10;
            static constexpr int ccy_base_four_star = 2;
            static constexpr int ccy_limit_five_star = 25;
            static constexpr int ccy_limit_four_star = 5;
            static constexpr int star_dust_val = 15;
        };
    };

    bool is_last_const(std::string drop) {
        auto it = drop_list.character_drop.find(drop);
        if (it == drop_list.character_drop.end()) {
            drop_list.character_drop[drop] = 0;
            return false;
        }

        if (it->second == basis_params::limits::const_limit) {
            return true;
        }
        else {
            it->second++;
            return false;
        }
    }


public:

    Banner_System() : gen(rd()), distribution(0.0, 1.0) {}

    std::pair<int, int> get_current_pity() {
        return { counter.pity_four_star, counter.pity_five_star };
    }

    int get_pulls() { return counter.total_pulls; }

    void get_ccy() {
        std::cout << "Star Bless: " << counter.currency_1 << " (" << counter.currency_1 / 5.0 << ")" << std::endl;
        std::cout << "Stardust: " << counter.currency_2 << std::endl;
    }

    void get_inventory() {
        if (!drop_list.inventory.empty()) {
            for (size_t i = 1; i < drop_list.inventory.size() + 1; i++) {
                std::cout << std::setw(30) << drop_list.inventory[i - 1];
                if (i % 3 == 0) std::cout << std::endl;
            }
        }
        else {
            std::cout << "You haven't obtained any items" << std::endl;
        }
        std::cout << std::endl;
    }

    void constellation() {
        if (!drop_list.character_drop.empty()) {
            std::vector<std::pair<std::string, int>> temp_vec(drop_list.character_drop.begin(),
                drop_list.character_drop.end());
            std::sort(temp_vec.begin(), temp_vec.end(),
                [](const auto& a, const auto& b) {
                    return a.second > b.second;
                });
            
            int i = 1;
            for (const auto p: temp_vec) {
                std::cout << std::setw(30) << p.first << " " << p.second;
                if (i != 0 && i % 3 == 0) std::cout << std::endl;
                i++;
            }
        }
        else {
            std::cout << "You don't have any characters yet" << std::endl;
        }
    }

    void get_statistic(bool debug = false, bool is_lite = false) {

        double avg_pity = 0;
        std::vector<int> dist_five_star(basis_params::limits::five_star_pity_limit, 0);

        if (!drop_list.five_star_drop.empty()) {
            for (size_t i = 1; i < drop_list.five_star_drop.size() + 1; i++) {
                if (!debug) {
                    std::cout << std::setw(30) << drop_list.five_star_drop[i - 1].first << " - " << std::setw(2) << drop_list.five_star_drop[i - 1].second;
                    if (i != 0 && i % 3 == 0) std::cout << std::endl;
                }
                avg_pity += drop_list.five_star_drop[i - 1].second;
            }
            avg_pity /= (double)drop_list.five_star_drop.size();
            std::cout << std::endl;

            for (size_t i = 0; i < drop_list.five_star_drop.size(); i++) {
                dist_five_star[drop_list.five_star_drop[i].second - 1]++;
            }
        }
        else {
            std::cout << "You haven't obtained any 5-star drops yet" << std::endl;
        }

        std::cout << std::endl;
        std::cout << std::setw(15) << "Average for five star: " << avg_pity << std::endl;

        std::vector<int> dist_four_star(basis_params::limits::four_star_pity_limit, 0);

        if (!is_lite) {
            double avg_four_star = 0;
            
            if (!drop_list.four_star_drop.empty()) {
                for (size_t i = 1; i < drop_list.four_star_drop.size() + 1; i++) {
                    avg_four_star += drop_list.four_star_drop[i - 1].second;
                }
                avg_four_star /= (double)drop_list.four_star_drop.size();
                for (size_t i = 0; i < drop_list.four_star_drop.size(); i++) {
                    if (!(drop_list.four_star_drop[i].second > basis_params::limits::four_star_pity_limit)) {
                        dist_four_star[drop_list.four_star_drop[i].second - 1]++;
                    }
                }
            }
            std::cout << std::setw(15) << "Average for four star: " << avg_four_star << std::endl;
        }

        if (debug) {
            std::cout << std::endl;
            std::cout << std::setw(18) << "Distribution for five star:" << std::endl;
            std::cout << std::endl;

            for (size_t i = 1; i < dist_five_star.size() + 1; i++) {
                long sum = 0;
                for (size_t j = 0; j < dist_five_star.size(); j++) { sum += dist_five_star[j]; }

                std::cout << std::setw(12) << i << ": " << std::setw(7) << dist_five_star[i - 1];
                if (i != 0 && i % 5 == 0) std::cout << std::endl;
            }


            if (!is_lite) {
                std::cout << std::endl;
                std::cout << std::setw(18) << "Distribution for four star:" << std::endl;
                std::cout << std::endl;

                for (size_t i = 1; i < dist_four_star.size() + 1; i++) {
                    long sum = 0;
                    for (size_t j = 0; j < dist_four_star.size(); j++) { sum += dist_four_star[j]; }

                    std::cout << std::setw(15) << i << ": " << std::setw(8) << dist_four_star[i - 1];
                    if (i != 0 && i % 2 == 0) std::cout << std::endl;
                }
            }
        }

        if (!debug) {
            std::cout << std::endl;
            std::cout << "Total pulls: " << get_pulls() << " (" << get_pulls() * 160 << " Primogems)" << std::endl;
            get_ccy();
        }
    }
};

class Default_Banner : public Banner_System {
private:
    double calc_probability(int current_pity) {
        return basis_params::probability::factor_pity.first * current_pity - basis_params::probability::factor_pity.second;
    }

    double five_star_rate(int current_pity) {
        if (current_pity >= basis_params::limits::five_star_pity_limit) return 1.0;
        if (current_pity >= basis_params::limits::start_ptiy_val) return calc_probability(current_pity); 
        else return basis_params::probability::five_star_chance + (basis_params::probability::factor_default * current_pity);
    }

    double four_star_rate(int current_pity) {
        if (current_pity >= basis_params::limits::four_star_pity_limit) return 1.0;
        else return basis_params::probability::four_star_chance;
    }
public:
    void single_wish(bool debug = false, bool is_lite = false) {

        counter.total_pulls++;
        counter.pity_four_star++;
        counter.pity_five_star++;

        double chance = distribution(gen);

        if (chance < five_star_rate(counter.pity_four_star)) {
            if (distribution(gen) < basis_params::probability::equal) {
                std::uniform_int_distribution<size_t> dis(0, five_star_character.size() - 1);
                std::string drop = five_star_character[dis(gen)];
                if (!debug) { std::cout << "\033[33m5-STAR " << drop << "\033[0m"; }

                if (!debug) {
                    if (is_last_const(drop)) counter.currency_1 += basis_params::currency::ccy_limit_five_star;
                    else counter.currency_1 += basis_params::currency::ccy_base_five_star;
                }

                drop_list.five_star_drop.push_back({ drop, counter.pity_four_star });

                counter.pity_four_star = 0;
            }
            else {
                std::uniform_int_distribution<size_t> dis(0, five_star_item.size() - 1);
                std::string drop = five_star_item[dis(gen)];
                if (!debug) { std::cout << "\033[33m5-STAR " << drop << "\033[0m"; }

                counter.currency_1 += basis_params::currency::ccy_base_five_star;
                drop_list.five_star_drop.push_back({ drop, counter.pity_four_star });
                drop_list.inventory.push_back(drop);
                counter.pity_four_star = 0;
            }

        }
        else if (chance < four_star_rate(counter.pity_five_star) && !is_lite) {
            // Character or Item
            if (distribution(gen) < basis_params::probability::equal) {
                std::uniform_int_distribution<size_t> dis(0, four_star_character.size() - 1);
                std::string drop = four_star_character[dis(gen)];
                if (!debug) { std::cout << "\033[35m4-Star " << drop << "\033[0m"; }

                if (!debug) {
                    if (is_last_const(drop)) counter.currency_1 += basis_params::currency::ccy_limit_four_star;
                    else counter.currency_1 += basis_params::currency::ccy_base_four_star;
                }
                drop_list.four_star_drop.push_back({ drop, counter.pity_five_star });
            }
            else {
                std::uniform_int_distribution<size_t> dis(0, four_star_item.size() - 1);
                std::string drop = four_star_item[dis(gen)];
                if (!debug) { std::cout << "\033[35m4-Star " << drop << "\033[0m"; }

                counter.currency_1 += basis_params::currency::ccy_base_four_star;
                drop_list.inventory.push_back(drop);
                drop_list.four_star_drop.push_back({ drop, counter.pity_five_star });
            }

            counter.pity_five_star = 0;
        }
        else {
            if (!debug) {
                std::cout << "\033[36m" << three_star_item[0] << "\033[0m";
                counter.currency_2 += basis_params::currency::star_dust_val;
            }
        }
    }

    void multiwish(long n, bool debug = false, bool is_lite = false) {
        for (long i = 0; i < n; i++) {
            single_wish(debug, is_lite);
            if (!debug) { std::cout << std::endl; }
        }
    }
};

class Event_CharacterBanner : public Banner_System {
private:
    const std::string event_character = "EVENT";
    const std::vector<std::string> event_epics = { "event1", "event2", "event3" };

    bool lost_lega = false;
    bool lost_epic = false;

    double calc_probability(int current_pity) {
        return basis_params::probability::factor_pity.first * current_pity - basis_params::probability::factor_pity.second;
    }

    double five_star_rate(int current_pity) {
        if (current_pity >= basis_params::limits::five_star_pity_limit) return 1.0;
        if (current_pity >= basis_params::limits::start_ptiy_val) return calc_probability(current_pity);
        else return basis_params::probability::five_star_chance + (basis_params::probability::factor_default * current_pity);
    }

    double four_star_rate(int current_pity) {
        if (current_pity >= basis_params::limits::four_star_pity_limit) return 1.0;
        else return basis_params::probability::four_star_chance;
    }

public:

    void single_wish(bool debug = false, bool is_lite = false) {

        counter.total_pulls++;
        counter.pity_four_star++;
        counter.pity_five_star++;

        double chance = distribution(gen);
        //std::cout << rateForFiveStar(numeric_space.countForFiveStar) << " ";
        if (chance < five_star_rate(counter.pity_four_star)) {
            if (distribution(gen) < basis_params::probability::increase_event_character || lost_lega) {

                if (!debug) { std::cout << "\033[33m5-STAR " << event_character << "\033[0m"; }

                if (!debug) {
                    if (is_last_const(event_character)) counter.currency_1 += basis_params::currency::ccy_limit_five_star;
                    else counter.currency_1 += basis_params::currency::ccy_base_five_star;
                }

                drop_list.five_star_drop.push_back({ event_character, counter.pity_four_star });

                counter.pity_four_star = 0;
                lost_lega = false;
            }
            else {
                std::uniform_int_distribution<size_t> dis(0, five_star_character.size() - 1);
                std::string drop = five_star_character[dis(gen)];
                if (!debug) { std::cout << "\033[33m5-STAR " << drop << "\033[0m"; }

                if (!debug) {
                    if (is_last_const(drop)) counter.currency_1 += basis_params::currency::ccy_limit_five_star;
                    else counter.currency_1 += basis_params::currency::ccy_base_five_star;
                }

                drop_list.five_star_drop.push_back({ drop, counter.pity_four_star });

                counter.pity_four_star = 0;
                lost_lega = true;
            }

        }
        else if (chance < four_star_rate(counter.pity_five_star) && !is_lite) {
            if (distribution(gen) < basis_params::probability::equal || lost_epic) {
                std::uniform_int_distribution<size_t> dis(0, event_epics.size() - 1);
                std::string drop = event_epics[dis(gen)];

                if (!debug) { std::cout << "\033[35m4-Star " << drop << "\033[0m"; }

                if (!debug) {
                    if (is_last_const(drop)) counter.currency_1 += basis_params::currency::ccy_limit_four_star;
                    else counter.currency_1 += basis_params::currency::ccy_base_four_star;
                }

                drop_list.four_star_drop.push_back({ drop, counter.pity_five_star });
                lost_epic = false;
            }
            else {
                if (distribution(gen) < basis_params::probability::equal) {
                    std::uniform_int_distribution<size_t> dis(0, four_star_character.size() - 1);
                    std::string drop = four_star_character[dis(gen)];
                    if (!debug) { std::cout << "\033[35m4-Star " << drop << "\033[0m"; }

                    if (!debug) {
                        if (is_last_const(drop)) counter.currency_1 += basis_params::currency::ccy_limit_four_star;
                        else counter.currency_1 += basis_params::currency::ccy_base_four_star;
                    }
                    drop_list.four_star_drop.push_back({ drop, counter.pity_five_star });
                }
                else {
                    std::uniform_int_distribution<size_t> dis(0, four_star_item.size() - 1);
                    std::string drop = four_star_item[dis(gen)];
                    if (!debug) { std::cout << "\033[35m4-Star " << drop << "\033[0m"; }

                    counter.currency_1 += basis_params::currency::ccy_base_four_star;
                    drop_list.inventory.push_back(drop);
                    drop_list.four_star_drop.push_back({ drop, counter.pity_five_star });
                }

                lost_epic = true;
            }
            counter.pity_five_star = 0;
        }
        else {
            if (!debug) {
                std::cout << "\033[36m" << three_star_item[0] << "\033[0m";
                counter.currency_2 += basis_params::currency::star_dust_val;
            }
        }
    }

    void multiwish(long n, bool debug = false, bool is_lite = false) {
        for (long i = 0; i < n; i++) {
            single_wish(debug, is_lite);
            if (!debug) std::cout << std::endl;
        }
    }
};

class Debug_System {
private:

    Default_Banner object_1;
    Event_CharacterBanner object_2;

    bool is_default_banner;

    void distribution_test(bool is_lite = false) {
        long n;
        std::cout << "> "; std::cin >> n;

        if (is_default_banner) {
            if (is_lite) {
                object_1.multiwish(n, true, true);
                object_1.get_statistic(true, true);
            }
            else {
                object_1.multiwish(n, true);
                object_1.get_statistic(true);
            }
        }
        else {
            if (is_lite) {
                object_2.multiwish(n, true, true);
                object_2.get_statistic(true, true);
            }
            else {
                object_2.multiwish(n, true);
                object_2.get_statistic(true);
            }
        }
    }
public:

    Debug_System(bool v) : is_default_banner(v) {}

    void start() {
        std::string command;
        while (true) {
            std::cout << ">> "; std::getline(std::cin, command);
            std::cout << std::endl;

            if (command == "exit") { break; }
            else if (command == "mw") { distribution_test(); }
            else if (command == "mwl") { distribution_test(true); }
            else { std::cout << "command not found\n" << std::endl; }
        }
        command.clear();
    }
};

static constexpr int ESC_KEY = 27;
int start_banner();

int start_EventBanner() {

    Event_CharacterBanner event_banner;

    std::cout << "\n|| EVENT BANNER ||\n\n";
    std::cout << "(1) Wish once\n(2) Wish 10 times\n(3) View inventory\n(4) View statistics" << std::endl;

    while (true) {
        std::cout << std::endl;
        std::pair<int, int> current_pity = event_banner.get_current_pity();
        std::cout << "Pity 5-Star: " << current_pity.first << std::endl;
        std::cout << "Pity 4-Star: " << current_pity.second << std::endl;

        std::cout << "____________________\n" << std::endl;

        bool correct_key = false;

        while (!correct_key) {
            int click = _getch();

            switch (click) {
            case('1'):
                event_banner.single_wish();
                std::cout << std::endl;
                correct_key = true;
                break;

            case('2'):
                event_banner.multiwish(10);
                correct_key = true;
                break;
            
            case('3'):
                event_banner.get_inventory();
                correct_key = true;
                break;
            
            case('4'):
                std::cout << "Constellations: " << std::endl;
                event_banner.constellation();

                std::cout << std::endl;

                std::cout << "Statistics: " << std::endl;
                event_banner.get_statistic();
                correct_key = true;
                break;
            
            case(ESC_KEY): return 0;
            // debug
            case('0'):
                if (click == '0') {
                    int doubleCheck = _getch();
                    if (doubleCheck == '0') {
                        std::cout << "// debug //" << std::endl;
                        std::cout << std::endl;
                        Debug_System init(false);
                        init.start();
                    }
                }
                correct_key = true;
                break;
            }
        }
    }
    return 0;
}

int start_DefaultBanner() {

    Default_Banner default_banner;

    std::cout << "\n|| DEFAULT BANNER ||\n\n";
    std::cout << "(1) Wish once\n(2) Wish 10 times\n(3) View inventory\n(4) View statistics" << std::endl;

    while (true) {

        std::cout << std::endl;
        std::pair<int, int> current_pity = default_banner.get_current_pity();
        std::cout << "Pity 5-Star: " << current_pity.first << std::endl;
        std::cout << "Pity 4-Star: " << current_pity.second << std::endl;

        std::cout << "____________________\n" << std::endl;

        bool correct_key = false;

        while (!correct_key) {
            int click = _getch();

            switch (click) {
            case('1'):
                default_banner.single_wish();
                std::cout << std::endl;
                correct_key = true;
                break;

            case('2'):
                default_banner.multiwish(10);
                correct_key = true;
                break;

            case('3'):
                default_banner.get_inventory();
                correct_key = true;
                break;

            case('4'):
                std::cout << "Constellations: " << std::endl;
                default_banner.constellation();
                std::cout << std::endl;

                std::cout << "Statistics: " << std::endl;
                default_banner.get_statistic();
                correct_key = true;
                break;

            case(ESC_KEY): return 0;
                // debug
            case('0'):
                int doubleCheck = _getch();
                if (doubleCheck == '0') {
                    std::cout << "// debug //" << std::endl;
                    std::cout << std::endl;
                    Debug_System init(true);
                    init.start();
                }
                correct_key = true;
                break;
            }
        }
    }
    return 0;
}

int start_banner() {
    std::cout << "\nBANNER SIMULATOR" << std::endl;

    while (true) {
        std::cout << "\n(1) Event Banner\n(2) Default Banner" << std::endl;

        bool correct_key = false;

        while (!correct_key) {
            int click = _getch();

            switch (click) {
            case('1'): start_EventBanner(); correct_key = true; break;
            case('2'): start_DefaultBanner(); correct_key = true; break;
            case(ESC_KEY): return 0;
            }
        }
    }
}

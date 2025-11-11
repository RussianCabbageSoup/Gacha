#pragma once
#include <iostream>
#include <random>
#include <vector>
#include <conio.h>
#include <limits>
#include <iomanip>
#include <cmath>

using namespace std;

class GachaSystem {
private:

	const vector<string> ThreeStarItem = { "Trash" };

	const vector<string> FourStarItem = { "Церемониальный меч", "Меч Фавония", "Церемониальный двуручный меч", "Двуручный меч Фавония",
		"Гроза драконов", "Церемониальный мемуары", "Кодекс Фавония", "Церемониальный лук", "Боевой лук Фавония", "Драконий рык",
		"Меч-флейта", "Дождерез", "Меч-колокол", "Копьё Фавония", "Око сознания", "Песнь Странника", "Ржавый лук", "Бесструнный" };

	const vector<string> FourStarCharacter = {
		"Айно", "Ифа", "Лань Янь", "Качина", "Ка Мин", "Шарлотта", "Линнет", "Мика", "Фарузан", "Кандакия", "Коллеи", "Юнь Цзинь",
		"Сиканоин Хэйдзо", "Горо" , "Тома", "Розария", "Сахароза", "Чун Юнь", "Беннет", "Нин Гуан", "Бэй Доу", "Эмбер", "Кэйа", "Лиза",
		"Далия", "Иансан", "Оророн", "Сетос", "Шеврёз", "Фремине", "Кавех", "Яо Яо", "Лайла", "Дори", "Куки Синобу", "Кирара",
		"Кудзё Сара", "Саю", "Янь Фэй", "Синь Янь", "Диона", "Ноэлль", "Фишль", "Син Цю", "Сян Лин", "Рэйзор", "Барбара" };

	const vector<string> FiveStarCharacter = { "Мидзуки", "Тигнари", "Мона", "Дилюк", "Дэхья", "Кэ Цин", "Ци Ци", "Джинн" };

	const vector<string> FiveStarItem = { "Небесный меч", "Волчья погибель", "Нефритовый Коршун", "Молитва Святым Ветрам", "Лук Амоса",
		"Меч Сокола", "Небесное величие", "Небесная ось", "Небесный атлас", "Небесное крыло" };

	vector <pair<string, int>> FiveStarDrop;
	vector<pair<string, int>> charDrop;
	vector<string> inventory;

	int countFOUR = 0;
	int countFIVE = 0;
	int Rate = 0;

	double RateForFive() {
		if (countFIVE >= 73) {
			return (double)(1 - 1.93 / (2.05 * pow((countFIVE - 72), 0.134)));
		}
		else {
			return 0.006;
		}
	}

	double RateForFour() {
		if (countFOUR >= 9) {
			return 0.7;
		}
		else {
			return 0.051;
		}
	}

	void checkDublicate(string drop) {

		bool dublicate = false;
		size_t index;

		for (size_t i = 0; i < charDrop.size(); i++) {
			if (drop == charDrop[i].first) {
				dublicate = true;
				index = i;
			}
		}
		if (!dublicate) {
			charDrop.push_back({ drop, 0 });
		}
		else {
			if (charDrop[index].second < 6) charDrop[index].second++;
		}
	}

public:

	random_device rd;
	mt19937 gen;
	uniform_real_distribution<> charDist;

	int counter = 0;

	GachaSystem() : gen(rd()), charDist(0.0, 1.0) {}

	void getInvent() {
		if (!inventory.empty()) {
			for (size_t i = 1; i < inventory.size() + 1; i++) {
				cout << setw(30) << inventory[i - 1];
				if (i % 3 == 0) cout << endl;
			}
		}
		else {
			cout << "Ты не получил ни одного предмета" << endl;
		}
		cout << endl;
	}

	void ConstList() {
		if (!charDrop.empty()) {
			sort(charDrop.begin(), charDrop.end(), [](const pair<string, int>& a, const pair<string, int>& b) {
				return a.second > b.second; });

			for (size_t i = 1; i < charDrop.size() + 1; i++) {
				cout << setw(30) << charDrop[i - 1].first << " " << charDrop[i - 1].second;
				if (i != 0 && i % 3 == 0) cout << endl;
			}
		}
		else {
			cout << "У тебя ещё нет ни одного персонажа" << endl;
		}
	}

	void GetStat() {

		double avr = 0;
		vector<int> dist(90, 0);

		if (!FiveStarDrop.empty()) {

			for (size_t i = 1; i < FiveStarDrop.size() + 1; i++) {
				cout << setw(30) << FiveStarDrop[i - 1].first << " - " << FiveStarDrop[i - 1].second;
				if (i != 0 && i % 3 == 0) cout << endl;

				avr += FiveStarDrop[i - 1].second;
			}
			avr /= (double)FiveStarDrop.size();
			cout << endl;

			for (size_t i = 0; i < FiveStarDrop.size(); i++) {
				dist[FiveStarDrop[i].second - 1]++;
			}
		}
		else {
			cout << "Ты ещё не получил ни одного 5-star дропа" << endl;
		}

		cout << endl;
		cout << setw(15) << "Среднее: " << avr << endl;
		cout << setw(15) << "Распределение: " << endl;
		cout << endl;
		for (size_t i = 1; i < dist.size() + 1; i++) {
			cout << setw(8) << i << "-ый: " << setw(5) << dist[i - 1];
			if (i != 0 && i % 6 == 0) cout << endl;
		}
	}

	void SingleWish() {

		counter++;
		countFIVE++;
		countFOUR++;
		Rate++;

		double chance = charDist(gen);

		if (chance < RateForFive() || countFIVE == 90) {
			if (charDist(gen) < 0.5) {
				uniform_int_distribution<> dis(0, FiveStarCharacter.size() - 1);
				string drop = FiveStarCharacter[dis(gen)];
				cout << "5-Star " << drop;

				checkDublicate(drop);

				FiveStarDrop.push_back({ drop, Rate });

				countFIVE = 0;
				Rate = 0;
			}
			else {
				uniform_int_distribution<> dis(0, FiveStarItem.size() - 1);
				string drop = FiveStarItem[dis(gen)];
				cout << "5-Star " << drop;

				FiveStarDrop.push_back({ drop, Rate });
				inventory.push_back(drop);
				countFIVE = 0;
				Rate = 0;
			}

		}
		else if (chance < RateForFour() || countFOUR == 10) {
			if (charDist(gen) < 0.5) {
				uniform_int_distribution<> dis(0, FourStarCharacter.size() - 1);
				string drop = FourStarCharacter[dis(gen)];
				cout << "4-Star " << drop;

				checkDublicate(drop);

			}
			else {
				uniform_int_distribution<> dis(0, FourStarItem.size() - 1);
				string drop = FourStarItem[dis(gen)];
				cout << "4-Star " << drop;

				inventory.push_back(drop);
			}

			countFOUR = 0;
		}
		else {
			cout << ThreeStarItem[0];
		}
	}

	void multiWish(long n) {
		for (int i = 0; i < n; i++) {
			SingleWish();
			cout << endl;
		}
	}
};
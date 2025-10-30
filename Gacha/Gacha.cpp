#include <iostream>
#include <random>
#include <vector>
#include <conio.h>
#include <limits>
#include <iomanip>
#include <numeric> 

using namespace std;

class GachaSystem {
private:

	vector<string> ThreeStarItem = { "Trash" };

	vector<string> FourStarItem = { "Церемониальный меч", "Меч Фавония", "Церемониальный двуручный меч", "Двуручный меч Фавония",
		"Гроза драконов", "Церемониальный мемуары", "Кодекс Фавония", "Церемониальный лук", "Боевой лук Фавония", "Драконий рык", 
		"Меч-флейта", "Дождерез", "Меч-колокол", "Копьё Фавония", "Око сознания", "Песнь Странника", "Ржавый лук", "Бесструнный"};

	vector<string> FourStarCharacter = { 
		"Айно", "Ифа", "Лань Янь", "Качина", "Ка Мин", "Шарлотта", "Линнет", "Мика", "Фарузан", "Кандакия", "Коллеи", "Юнь Цзинь",
		"Сиканоин Хэйдзо", "Горо" , "Тома", "Розария", "Сахароза", "Чун Юнь", "Беннет", "Нин Гуан", "Бэй Доу", "Эмбер", "Кэйа", "Лиза",
		"Далия", "Иансан", "Оророн", "Сетос", "Шеврёз", "Фремине", "Кавех", "Яо Яо", "Лайла", "Дори", "Куки Синобу", "Кирара",
		"Кудзё Сара", "Саю", "Янь Фэй", "Синь Янь", "Диона", "Ноэлль", "Фишль", "Син Цю", "Сян Лин", "Рэйзор", "Барбара" };

	vector<string> FiveStarCharacter = { "Мидзуки", "Тигнари", "Мона", "Дилюк", "Дэхья", "Кэ Цин", "Ци Ци", "Джинн"};

	vector<string> FiveStarItem = { "Небесный меч", "Волчья погибель", "Нефритовый Коршун", "Молитва Святым Ветрам", "Лук Амоса", 
		"Меч Сокола", "Небесное величие", "Небесная ось", "Небесный атлас", "Небесное крыло" };

	vector<int> FiveStarScore;
	vector <string> FiveStarDrop;

	vector<string> charDrop;

	vector<short> constList;

	int countFOUR = 0;
	int countFIVE = 0;
	int Rate = 0;

	double RateForFive() {
		if (countFIVE >= 80) {
			return 0.25;
		}
		else if (countFIVE >= 75) {
			return 0.12;
		}
		else if (countFIVE >= 70) {
			return 0.066;
		}
		else {
			return 1.0;
		}
	}

	double RateForFour() {
		if (countFOUR >= 8) {
			return 0.25;
		}
		else if (countFOUR >= 6) {
			return 0.11;
		}
		else {
			return 0.051;
		}
	}

	void checkDublicate(string drop) {

		bool dublicate = false;
		size_t index;
		
		for (size_t i = 0; i < charDrop.size(); i++) {
			if (drop == charDrop[i]) {
				dublicate = true;
				index = i;
			}
		}
		if (!dublicate) {
			charDrop.push_back(drop);
			constList.push_back(0);
		}
		else {
			if (constList[index] < 6) constList[index]++;
		}
	}
	
public:

	random_device rd;
	mt19937 gen;
	uniform_real_distribution<> charDist;

	int counter = 0;

	GachaSystem(): gen(rd()), charDist(0.0, 1.0) {}

	void ConstList() {
		if (!charDrop.empty()) {

			vector<size_t> indices(charDrop.size());
			iota(indices.begin(), indices.end(), 0);

			sort(indices.begin(), indices.end(), [&](size_t i1, size_t i2) {
				return constList[i1] > constList[i2];
				});

			for (size_t i : indices) {
				cout << setw(21) << charDrop[i] << " (" << constList[i] << ")" << endl;
			}
		}
		else {
			cout << "У тебя ещё нет ни одного персонажа" << endl;
		}
	}

	void GetStat() {
		if (!FiveStarDrop.empty()) {
			for (size_t i = 0; i < FiveStarScore.size(); i++) {
				cout << setw(21) << FiveStarDrop[i] << " - " << FiveStarScore[i] << endl;
			}
		}
		else {
			cout << "Ты ещё не получил ни одного 5-star дропа" << endl;
		}
	}

	void SingleWish() {

		counter++;
		countFIVE++;
		countFOUR++;
		Rate++;

		double chance = charDist(gen);

		if (chance < RateForFive() || countFIVE == 90) {
			if (charDist(gen) < 1.0) {
				uniform_int_distribution<> dis(0, FiveStarCharacter.size() - 1);
				string drop = FiveStarCharacter[dis(gen)];
				cout << "5-Star " << drop;

				checkDublicate(drop);

				FiveStarDrop.push_back(drop);
				FiveStarScore.push_back(Rate);

				countFIVE = 0;
				Rate = 0;
			}
			else {
				uniform_int_distribution<> dis(0, FiveStarItem.size() - 1);
				string drop = FiveStarItem[dis(gen)];
				cout << "5-Star " << drop;

				FiveStarDrop.push_back(drop);
				FiveStarScore.push_back(Rate);
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
				cout << "4-Star	" << FourStarItem[dis(gen)];
			}

			countFOUR = 0;
		}
		else {
			cout << ThreeStarItem[0];
		}
	}

	void multiWish(int n) {
		for (int i = 0; i < n; i++) {
			SingleWish();
			cout << endl;
		}
	}
};

class Character {
private:
protected:
public:
};

int main() {

	setlocale(LC_ALL, "Ru");
	cout << "SIMULATOR" << endl;
	cout << endl;
	GachaSystem Simulate;

	cout << "(1), чтобы Помолится 1 раз\n(2), чтобы Помолится 10 раз\n(3), чтобы Помолится 100 раз\n(4), чтобы посмотреть статистику" << endl;

	while (true) {

		cout << endl;
		cout << "Всего скучено: " << Simulate.counter << " (" << Simulate.counter * 160 << " Примогемов)" << endl;
		
		cout << "____________________" << endl;

		int type = _getch();
		cout << endl;

		if (type == '1') {
			Simulate.SingleWish();
			cout << endl;
		}
		else if (type == '2') {
			Simulate.multiWish(10);
			cout << endl;
		}
		else if (type == '3') {
			Simulate.multiWish(100);
			cout << endl;
		}
		else if (type == '4') {
			cout << "Консты: " << endl;
			Simulate.ConstList();

			cout << endl;

			cout << "Статистика: " << endl;
			Simulate.GetStat();
		}
	}

	return 0;
}
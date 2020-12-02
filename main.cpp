#include <clocale>
//#include <vld.h>
#include"ReadJSON.h"

using namespace std;

bool compareTextbyvowincrease(EncryptedText* ptr1, EncryptedText* ptr2) {
	return ptr1->getText().size() > ptr2->getText().size();
}

bool compareTextbyvowdecrease(EncryptedText* ptr1, EncryptedText* ptr2) {
	return ptr1->getText().size() < ptr2->getText().size();
}

bool compareVowels(EncryptedText* ptr1) {
	return ptr1->getVowels() == 0;
}

bool compareTypeVigEnc(EncryptedText* ptr1) {
	return dynamic_cast<VigenereEncText*>(ptr1);
}

bool compareTypeCycEnc(EncryptedText* ptr1) {
	return dynamic_cast<CyclicalShiftEncText*>(ptr1);
}

bool compareTypeCharEnc(EncryptedText* ptr1) {
	return dynamic_cast<CharSubstitutionEncText*>(ptr1);
}

void Swichsort(List<EncryptedText*>& enctexts, int sw = 0) {
	cout << "Выберите функцию:" << endl;
	cout << "1. Сортировка по возрастанию количества гласных" << endl;
	cout << "2. Сортировка по убыванию количества гласных" << endl;
	if (sw==0)
	cin >> sw;
	switch (sw)
	{
	case 1:
		enctexts.sort(compareTextbyvowincrease);
		break;
	case 2:
		enctexts.sort(compareTextbyvowdecrease);
		break;
	default:
		break;
	}
	enctexts.display();
}

void Swichdelete(List<EncryptedText*>& enctexts, int sw = 0) {
	cout << "Выберите функцию:" << endl;
	cout << "1. Удаление текстов с шифром Виженера" << endl;
	cout << "2. Удаление текстов с шифром Циклического сдвига" << endl;
	cout << "3. Удаление текстов с шифром Замены символов" << endl;
	cout << "4. Удаление текстов количество глассных в которых равно 0" << endl;
	if (sw==0)
		cin >> sw;
	switch (sw)
	{
	case 1:
		enctexts.remove(compareTypeVigEnc);
		break;
	case 2:
		enctexts.remove(compareTypeCycEnc);
		break;
	case 3:
		enctexts.remove(compareTypeCharEnc);
		break;
	case 4:
		enctexts.remove(compareVowels);
		break;
	default:
		break;
	}
	enctexts.display();
}

int main(int argc, char* argv[])
{
	cout << "Start"<<endl;
	if (argc < 3 || argc > 5) {  
		cout << "End " << argc << endl;
		return 0; 
	}
	string pathin = argv[1];
	string pathout = argv[2];
	setlocale(LC_ALL, "rus");
	//string path = "D:\\test\\Oppolab1\\Oppolab1\\Тестовые наборы данных\\входные и выходные файлы\\in_13.txt";
	ReadJSON json(pathin);
	List<EncryptedText*> &enctexts  = json.getListTexts();
	int sw=0, sw2=0;
	enctexts.display();
	cout << "Выберите функцию:"<<endl;
	cout << "1. Простой вывод"<<endl;
	cout << "2. Отсортировать"<<endl;
	cout << "3. Удаление элементов" << endl;
	if (argc == 3)
		cin >> sw;
	else {
		stringstream convert1(argv[3]);
		if (!(convert1 >> sw)) 
		sw = 1;
		cout<<"Function "<<sw<<endl;
		if (argc == 5){
				stringstream convert2(argv[4]);
				if (!(convert2 >> sw2)) 
				sw2 = 0;
				cout<<"Type function "<<sw2<<endl;
			}
	}
	switch (sw)
	{
	case 1:
		break;
	case 2:
		Swichsort(enctexts,sw2);
		break;
	case 3:
		Swichdelete(enctexts,sw2);
		break;
	default:
		break;
	}
	//ofstream out("D:\\test\\Oppolab1\\Oppolab1\\Тестовые наборы данных\\входные и выходные файлы\\ooout.txt");
	if (!(pathout.empty())) {
		ofstream out(pathout);
		out << enctexts;
	}
	//_CrtDumpMemoryLeaks();
	return 0;
}

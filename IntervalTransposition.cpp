
#include <iostream>;
#include <fstream>;

using namespace std;

void getNotesAndIntervals();
void addInterval(int intrvl, int oIndx, int length);

char note = 0;
int octave = 0;


int main() 
{
	getNotesAndIntervals();
}

void getNotesAndIntervals() {

	ifstream inputFile;
	inputFile.open("NoteIntervals.txt");
	char scale[] = { 'C', 'D', 'E', 'F', 'G', 'A', 'B' };
	int l = 7;

	note = inputFile.get();

	while (!inputFile.fail()) {

		//Records the initial note and its octave
		octave = inputFile.get() - 48;
		cout << note << "" << octave << " ";
		inputFile.get();

		while (!inputFile.fail()) {

			//Searches for the index of note, stored in oIndx
			int oIndx = -1;
			int indx = 0;
			for (int j = 0; j < 7; j++) {
				if (note == scale[j])
					oIndx = indx;
				indx++;
			}

			auto interval_or_note = 0;
			int interval = 0;

			interval_or_note = inputFile.get();
			if (48 <= interval_or_note && interval_or_note <= 57)
				interval = interval_or_note - 48;
			else if (interval_or_note == 45)
				interval = -(inputFile.get() - 48);
			else {
				note = interval_or_note;
				cout << "\n";
				break;
			}

			addInterval(interval, oIndx, l);
			cout << note << "" << octave << " ";
			inputFile.get();

		}
	}
}

/**
* Simply adds the interval to the note and formats accordingly
* Accounts for octave changes
*
* @param intrvl    the interval to be added to note
* @param oIndx     the initial index of the current note
* @param length    the length of scale array
*/
void addInterval(int intrvl, int oIndx, int length) {

	//Adds the interval to note, and tests if note is in a new octave
	if (intrvl != 0) {
		if (intrvl > 0) {
			note += intrvl - 1;
			if (oIndx + intrvl > length)
				octave++;
		}
		else {
			note += intrvl + 1;
			if (oIndx + intrvl + 1 < 0)
				octave--;
		}

		//Simply assures that note is an actual note character
		if (note < 'A')
			note = ('G' + 1) - ('A' - note);
		else if (note > 'G')
			note = ('A' - 1) + (note - 'G');
	}
}

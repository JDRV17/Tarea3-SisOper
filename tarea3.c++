#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <iterator>

using namespace std;

/*la estructura de las entradas es la siguiente:
la primera letra corresponde con el algoritmo que se va a ejecutar, si es S, se ejecutará Scan, si es C, se ejecutará C-Scan
el primer número corresponde con la cantidad de discos que hay
el segundo número corresponde con la entrada leída directamente anterior (se usa para determinar la dirección de los algoritmos, es decir, si van en incremento o decremento)
el tercer número corresponde con el cabezal del brazo de disco, es decir, desde donde se empieza
la lista de números siguientes corresponde con las solicitudes de disco
y el número del final corresponde con el tiempo en µs que tarda una búsqueda por disco*/

int scan(int direction, int head, vector<int> seq, int time)
{
    vector<int> track, seqmM, seqMm;
    int total;
    if (direction)
    {
        while(seq.size() != 0)
        {
            auto min = min_element(seq.begin(), seq.end());
            seqmM.push_back(*min);
            seq.erase(min);
        }

        auto it = seqmM.begin();

        while(*it < head)
        {
            it = next(it, 1);
        }
        auto start = it;
        while(it < seqmM.end())
        {
            track.push_back(*it);
            it = next(it, 1);
        }

        it = start;

        while(it > seqmM.begin())
        {
            it = prev(it, 1);
            track.push_back(*it);
        }

        track.push_back(0);

        cout << endl;
        cout << "El recorrido es el siguiente: ";

        for (const auto& disk : track) 
        {
            cout << disk << " ";
        }
        cout << endl;

        total = track[0] - head;
        for(int i = 1; i < track.size(); i++)
        {
            if (track[i] > track[i-1])
            {
                total += track[i] - track[i-1];
            }
            else
            {
                total += track[i-1] - track[i];
            }
        }
        cout << "El tiempo que tarda es de: " << total*time << " µs." << endl;
    }
    else
    {
        
        while(seq.size() != 0)
        {
            auto max = max_element(seq.begin(), seq.end());
            seqMm.push_back(*max);
            seq.erase(max);
        }

        auto it = seqMm.begin();

        while(*it > head)
        {
            it = next(it, 1);
        }
        auto start = it;
        while(it < seqMm.end())
        {
            track.push_back(*it);
            it = next(it, 1);
        }

        it = start;
        track.push_back(0);

        while(it > seqMm.begin())
        {
            it = prev(it, 1);
            track.push_back(*it);
        }

        cout << endl;
        cout << "El recorrido es el siguiente: ";

        for (const auto& disk : track) 
        {
            cout << disk << " ";
        }
        cout << endl;

        total = head - track[0];
        for(int i = 1; i < track.size(); i++)
        {
            if (track[i] > track[i-1])
            {
                total += track[i] - track[i-1];
            }
            else
            {
                total += track[i-1] - track[i];
            }
        }
        cout << "El tiempo que tarda es de: " << total*time << " µs." << endl;
    }
}

int c_scan(int direction, int head, vector<int> seq, int time)
{
    vector<int> track, seqmM, seqMm;
    int total;
    if (direction)
    {
        while(seq.size() != 0)
        {
            auto min = min_element(seq.begin(), seq.end());
            seqmM.push_back(*min);
            seq.erase(min);
        }

        auto it = seqmM.begin();

        while(*it < head)
        {
            it = next(it, 1);
        }
        auto start = it;
        while(it < seqmM.end())
        {
            track.push_back(*it);
            it = next(it, 1);
        }

        it = seqmM.begin();
        track.push_back(0);

        while(it < start)
        {
            track.push_back(*it);
            it = next(it, 1);
        }

        cout << endl;
        cout << "El recorrido es el siguiente: ";

        for (const auto& disk : track) 
        {
            cout << disk << " ";
        }
        cout << endl;

        total = track[0] - head;
        for(int i = 1; i < track.size(); i++)
        {
            if (track[i] > track[i-1])
            {
                total += track[i] - track[i-1];
            }
            else
            {
                total += track[i-1] - track[i];
            }
        }
        cout << "El tiempo que tarda es de: " << total*time << " µs." << endl;
    }
    else
    {
        while(seq.size() != 0)
        {
            auto max = max_element(seq.begin(), seq.end());
            seqMm.push_back(*max);
            seq.erase(max);
        }

        auto it = seqMm.begin();

        while(*it > head)
        {
            it = next(it, 1);
        }
        auto start = it;
        while(it < seqMm.end())
        {
            track.push_back(*it);
            it = next(it, 1);
        }

        it = seqMm.begin();
        track.push_back(0);

        while(it < start)
        {
            track.push_back(*it);
            it = next(it, 1);
        }

        cout << endl;
        cout << "El recorrido es el siguiente: ";

        for (const auto& disk : track) 
        {
            cout << disk << " ";
        }
        cout << endl;

        total = head - track[0];
        for(int i = 1; i < track.size(); i++)
        {
            if (track[i] > track[i-1])
            {
                total += track[i] - track[i-1];
            }
            else
            {
                total += track[i-1] - track[i];
            }
        }
        cout << "El tiempo que tarda es de: " << total*time << " µs." << endl;
    }
}

int main()
{
    string mode;
    int direction;
    int head;
    int time;
    ifstream file ("solicitudes.txt");
    string line;

    if (file.is_open()) {
        while (getline(file, line)) { 
            istringstream stream(line);
            string word;
            vector<string> words;
            vector<int> seq;

            while (stream >> word) { 
                words.push_back(word);
            }

            mode = words[0];
            int inicio = 0;
            int fin = words[4].find(',');

            while (fin != string::npos) {
                seq.push_back(stoi(words[4].substr(inicio, fin - inicio)));
                inicio = fin + 1; 
                fin = words[4].find(',', inicio); 
            }

            if (find(seq.begin(), seq.end(), stoi(words[1])) == seq.end() && stoi(words[1]) != stoi(words[4].substr(inicio)))
            {
                seq.push_back(stoi(words[1]));
            }
            
            seq.push_back(stoi(words[4].substr(inicio)));
            head = stoi(words[3]);
            direction = stoi(words[2]) < head;
            time = stoi(words[5]);

            if(mode == "S")
            {
                scan(direction, head, seq, time);
            }
            else if (mode == "C")
            {
                c_scan(direction, head, seq, time);
            }
        }
        file.close();
    } else {
        cerr << "No existe un archivo con tal nombre." << endl;
    }
}
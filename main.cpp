#include <iostream>
#include <iomanip>
#include <sstream>
#include "Selection.h"
#include "Bubble.h"
#include "Cocktail.h"
#include "Shuffle.h"
#include "Insertion.h"
#include "Shell.h"
#include "Merge.h"
using namespace std;

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
using namespace sf;

const int SCREEN_BASE = 1000, NUM_ITEMS = 100, LOW = 5, NUM_SORTS = 5, NUM_OCT = 3,
        UNIT = SCREEN_BASE / NUM_ITEMS, SCREEN_SIZE = (UNIT * NUM_ITEMS), RAD = SCREEN_SIZE / 2.5;
const string thousand = "C:\\Users\\Ophiuchus\\Desktop\\C++\\gram\\1000.ogg",
        bass = "C:\\Users\\Ophiuchus\\Desktop\\C++\\gram\\171490__xicecoffeex__savannah-rack-tom-2.wav",
        snare = "C:\\Users\\Ophiuchus\\Desktop\\C++\\gram\\171491__xicecoffeex__savannah-snare.wav";
const float VOLUME = 30, PI = 3.141592;
const Color BASE(Color::Red), LOOK(Color::Green), SWAP(Color::Red), SWAP_LINE(Color::White),
        DONE(Color::White), FINISHING(Color::Green);
int  FRAME = 3, sortType = 4, tone = 0, MAX_TONE = 1;
vector<Music*> tones;
vector<Music*> snares;
vector<Music*> basses;

bool play = true, r = false, m = false;

void Play(int n, float f) {
    if (!m) {
        tone++;
        tone %= MAX_TONE;
        f *= -1;
        f += (1 / (float) LOW);
        float pitch = 1;
//        int octave = (int) pow(2, (int) (LOW * NUM_OCT * f));
//        cout << f << " " << 1 / f << " " << tones[tone]->Playing << endl;
//        pitch = (f);
//        switch ((int) (NUM_ITEMS * f) % 5) {
//            case 0:
//                pitch = (octave / (float) LOW);
//                break;
//            case 1:
//                pitch = ((octave * 32) / (float) (27 * LOW));
//                break;
//            case 2:
//                pitch = ((octave * 4) / (float) (3 * LOW));
//                break;
//            case 3:
//                pitch = ((octave * 3) / (float) (2 * LOW));
//                break;
//            case 4:
//                pitch = ((octave * 16) / (float) (9 * LOW));
//                break;
//        }

        tones[tone]->play();
        if (abs(tones[tone]->getPitch() - pitch) > .001) {
            tones[tone]->setPitch(pitch);
        }
        if (!tones[tone]->Playing || !tones[tone]->Paused) {
        }
    }
}

void Play(int n) {
    if (!m) {
        float pitch = n / (float) NUM_ITEMS;
        pitch /= 1.5;
        pitch += .2;
        tone++;
        tone %= MAX_TONE;
        tones[tone]->play();
        if (abs(tones[tone]->getPitch() - pitch) > .001) {
            tones[tone]->pause();
            tones[tone]->setPitch(pitch);
            tones[tone]->play();

        }
        if (!tones[tone]->Playing || !tones[tone]->Paused) {
        }
    }
}

void Pause(int max) {
    for (int i = max; i < tones.size(); i++) {
        tones[i]->pause();
    }
}

void Mute() {
    for (int i = 0; i < MAX_TONE; i++) {
        if (!m) tones[i]->setVolume(VOLUME);
        else tones[i]->setVolume(0);
    }
}

void Stop() {
    for (Music* s : tones) {
        delete s;
    }
}

bool vFind(vector<int> v, int n) {
    for (int i : v) {
        if (i == n) return true;
    }
    return false;
}

bool within(vector<int> bounds, int target) {
    if (bounds.size() == 1) return target > bounds[0];
    for (int i = 0; i < bounds.size(); i += 2) {
        if (bounds[i] < target && target < bounds[i + 1]) return true;
    }
    return false;
}

template <typename T>
void showSortStarsAndBars(T* s, RenderWindow &window, vector<int> &save) {
    Font arial;
    arial.loadFromFile("C:\\Users\\Ophiuchus\\Desktop\\C++\\sort\\data\\arial.ttf");

    int comp = 0, swap = 0, swing;

    Text name;
    name.setFont(arial);
    name.setCharacterSize(40);
    name.setFillColor(Color::White);
    name.setPosition(20, SCREEN_SIZE);
    name.setString(String(typeid(s).name()).substring(2));
    window.setTitle(String(typeid(s).name()).substring(2));
    Text stats;
    stats.setFont(arial);
    stats.setCharacterSize(40);
    stats.setFillColor(Color::White);
    stats.setPosition(200, SCREEN_SIZE);
    stringstream ss;
    ss << "Comparisons: " << comp << "  Swaps: " << swap;
    stats.setString(ss.str());


    while (window.isOpen()) {
        swing++;
        swing %= 3;
        if (play) {
            vector<int> cont = s->contents();
            vector<vector<int>> v(s->step());
            if (v.size() == 0) {
                save = s->contents();
                return;
            }
            int size = v[0].size();
            for (int i = 0; i < v[0].size(); i++) {
//                Play(i, (float) ((NUM_ITEMS - cont[v[0][i]]) / (float) (NUM_ITEMS * LOW)));
                Play(cont[v[0][i]]);
            }
            if (v.size() > 1) {
                for (int i = 0; i < v[1].size(); i++) {
//                    Play(i + v[0].size(),
//                         (float) ((NUM_ITEMS - cont[v[1][i]]) / (float) (NUM_ITEMS * LOW)));
                    Play(cont[v[1][i]]);
                    size += v[1].size();
                }
            }
            Pause(size);

            window.clear(Color::Black);

            window.draw(name);

            VertexArray vert(LinesStrip, 2);
            bool done = false;

            for (int i = 0; i < cont.size(); i++) {
                RectangleShape rect;
                rect.setPosition(i * UNIT, SCREEN_SIZE - (cont[i] * UNIT));
                int sub = 0;
                if (NUM_ITEMS < SCREEN_SIZE / 2) {
                    rect.setSize(Vector2f(UNIT - 1, cont[i] * UNIT));
                } else rect.setSize(Vector2f(2, 1));
                if (v.size() > 1) {
                    if (vFind(v[0], i)) {rect.setFillColor(LOOK); comp++;}
                    else if (vFind(v[1], i)) {
                        rect.setFillColor(SWAP);
                        if (done) {swap++; comp++;}
                        vert[done].position = rect.getPosition();
                        vert[done].color = SWAP_LINE;
                        done = true;
                    }
                    else {
                        rect.setFillColor(BASE);
                        if (within(v[2], i)) rect.setFillColor(DONE);
                    }
                } else {
                    rect.setFillColor(FINISHING);
                    if (i > v[0][0]) rect.setFillColor(BASE);
                }
                window.draw(rect);
            }
            if (done) window.draw(vert);
            stringstream ss;
            ss << "Comparisons: " << comp << "  Swaps: " << swap << "  " << setprecision(2) << 100 * swap / (float)comp << "%";
            stats.setString(ss.str());
            window.draw(stats);

            window.display();
        }



        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();
            } else if (event.type == Event::KeyPressed) {
                switch (event.key.code) {
                    case Keyboard::Escape:
                        window.close();
                        break;
                    case Keyboard::Q:
                        save = s->contents();
                        return;
                    case Keyboard::Space:
                        play = !play;
                        break;
                    case Keyboard::R:
                        r = !r;
                        break;
                    case Keyboard::Up:
                    case Keyboard::W:
                        sortType++;
                        sortType %= NUM_SORTS;
                        break;
                    case Keyboard::Down:
                    case Keyboard::S:
                        sortType += NUM_SORTS - 1;
                        sortType %= NUM_SORTS;
                        break;
                    case Keyboard::Add:
                        FRAME++;
                        window.setFramerateLimit(FRAME);
                        break;
                    case Keyboard::Subtract:
                        FRAME--;
                        window.setFramerateLimit(FRAME);
                        break;
                    case Keyboard::M:
                        m = !m;
                        Mute();
                        break;
                }
            }
        }
    }
}

template <typename T>
void showSortCircleDots(T* s, RenderWindow &window, vector<int> &save) {
    Font arial;
    arial.loadFromFile("C:\\Users\\Ophiuchus\\Desktop\\C++\\sort\\data\\arial.ttf");

    int comp = 0, swap = 0, swing = 0;

    Text name;
    name.setFont(arial);
    name.setCharacterSize(40);
    name.setFillColor(Color::White);
    name.setPosition(20, SCREEN_SIZE);
    name.setString(String(typeid(s).name()).substring(2));
    window.setTitle(String(typeid(s).name()).substring(2));
    Text stats;
    stats.setFont(arial);
    stats.setCharacterSize(40);
    stats.setFillColor(Color::White);
    stats.setPosition(200, SCREEN_SIZE);
    stringstream ss;
    ss << "Comparisons: " << comp << "  Swaps: " << swap;
    stats.setString(ss.str());


    while (window.isOpen()) {
        swing++;
        swing %= 3;
        if (play) {
            vector<int> cont = s->contents();
            vector<vector<int>> v(s->step());
            if (v.size() == 0) {
                save = s->contents();
                return;
            }
            int size = v[0].size();
            for (int i = 0; i < v[0].size(); i++) {
                Play(cont[v[0][i]]);
            }
            if (v.size() > 1) {
                for (int i = 0; i < v[1].size(); i++) {
                    Play(cont[v[1][i]]);
//                    Play(i + v[0].size(),
//                         (float) ((NUM_ITEMS - cont[v[1][i]]) / (float) (NUM_ITEMS * LOW)));
                    size += v[1].size();
                }
            }
            Pause(size);

            window.clear(Color::Black);

            window.draw(name);

            VertexArray vert(LinesStrip, 2);
            bool done = false;

            for (int i = 0; i < cont.size(); i++) {
                RectangleShape rect;
                float ph =  (cont[i] / (float)NUM_ITEMS) * RAD;
                rect.setPosition((SCREEN_SIZE / 2) + (ph * cos(2 * PI * (i / (float)NUM_ITEMS))), (SCREEN_SIZE / 2) + (ph * sin(2 * PI * (i / (float)NUM_ITEMS))));
//                cout << rect.getPosition().x << " " << rect.getPosition().y << endl;
                int sub = 0;
                rect.setSize(Vector2f(1, 1));
                if (v.size() > 1) {
                    if (vFind(v[0], i)) {rect.setFillColor(LOOK); comp++;}
                    else if (vFind(v[1], i)) {
                        rect.setFillColor(SWAP);
                        if (done) {swap++; comp++;}
                        vert[done].position = rect.getPosition();
                        vert[done].color = SWAP_LINE;
                        done = true;
                    }
                    else {
                        rect.setFillColor(BASE);
                        if (within(v[2], i)) rect.setFillColor(DONE);
                    }
                } else {
                    rect.setFillColor(FINISHING);
                    if (i > v[0][0]) rect.setFillColor(BASE);
                }
                window.draw(rect);
            }
            if (done) window.draw(vert);
            stringstream ss;
            ss << "Comparisons: " << comp << "  Swaps: " << swap << "  " << setprecision(2) << 100 * swap / (float)comp << "%";
            stats.setString(ss.str());
            window.draw(stats);

            window.display();
        }



        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();
            } else if (event.type == Event::KeyPressed) {
                switch (event.key.code) {
                    case Keyboard::Escape:
                        window.close();
                        break;
                    case Keyboard::Q:
                        save = s->contents();
                        return;
                    case Keyboard::Space:
                        play = !play;
                        break;
                    case Keyboard::R:
                        r = !r;
                        break;
                    case Keyboard::Up:
                    case Keyboard::W:
                        sortType++;
                        sortType %= NUM_SORTS;
                        break;
                    case Keyboard::Down:
                    case Keyboard::S:
                        sortType += NUM_SORTS - 1;
                        sortType %= NUM_SORTS;
                        break;
                    case Keyboard::Add:
                        FRAME++;
                        window.setFramerateLimit(FRAME);
                        break;
                    case Keyboard::Subtract:
                        FRAME--;
                        window.setFramerateLimit(FRAME);
                        break;
                    case Keyboard::M:
                        m = !m;
                        Mute();
                        break;
                }
            }
        }
    }
}

int main() {
    srand(time(NULL));

    RenderWindow window(VideoMode(SCREEN_SIZE, SCREEN_SIZE + 50), "You shouldn't be seeing this");
    window.requestFocus();
    window.setMouseCursorVisible(false);
    window.setFramerateLimit(FRAME);

    for (int i = 0; i < 200; i++) {
        Music* m = new Music;
        m->openFromFile(thousand);
        m->setVolume(VOLUME);
        tones.push_back(m);
    }
//    for (int i = 0; i < 200; i++) {
//        Music* m = new Music;
//        m->openFromFile(bass);
//        m->setVolume(VOLUME);
//        basses.push_back(m);
//    }
//    for (int i = 0; i < 200; i++) {
//        Music* m = new Music;
//        m->openFromFile(snare);
//        m->setVolume(VOLUME);
//        snares.push_back(m);
//    }

    vector<int> v;

    showSortCircleDots(new Shuffle(v), window, v);
    showSortCircleDots(new Insertion(NUM_ITEMS), window, v);
    while (window.isOpen()) {
//        if (r) sortType = rand() % 4;
//        switch (sortType) {
//            case 0:
//                showSort(new Insertion(v), window, v);
//                break;
//            case 1:
//                showSort(new Selection(v), window, v);
//                break;
//            case 2:
//                showSort(new Bubble(v), window, v);
//                break;
//            case 3:
//                showSort(new Cocktail(v), window, v);
//                break;
//            case 4:
//                showSort(new Shell(v), window, v);
//                break;
//        }
//        if (rand() % 2) showSortCircleDots(new Insertion(v), window, v);
//        else showSortCircleDots(new Shell(v), window, v);
        showSortCircleDots(new Shuffle(v), window, v);
        showSortCircleDots(new Shell(v), window, v);


    }
    Stop();

    return 0;
}
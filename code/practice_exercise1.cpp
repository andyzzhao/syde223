// Andrew Zhao 20785698
// Jeffery Ng 20762964

#include <iostream>
#include <vector>
#include <random>
#include <ctime>
#include <cstdlib>

using namespace std;


class Music{
    string artist_name;
    unsigned int year_made;
    string id;

public:
    Music() : year_made(0){   
    }

    Music(string artist_name, unsigned int year_made, string id){
        artist_name = artist_name;
        year_made = year_made;
        id = id;
    }

    string get_artist(){
        return artist_name;
    }

    bool operator ==(Music &rhs){
        if (artist_name == rhs.artist_name && year_made == rhs.year_made && id == rhs.id){
            return true;
        }
        else{
            return false;
        }
    }       
};


class Song : public Music {
    unsigned int song_length;
    string genre;
    string song_name;

public:
    Song() : song_length(0){}

    Song(unsigned int song_length, string genre, string song_name){
        song_length = song_length;
        genre = genre; 
        song_name = song_name; 
    }

    bool operator ==(Song &rhs){
        if (song_length == rhs.song_length && genre == rhs.genre && song_name == rhs.song_name){
            return true;
        }
        else{
            return false;
        }
    }  

    string get_song_name () {
        return song_name;
    }
};

class Playlist{
    vector<Song> my_playlist;
public: 
    Playlist(){}

    bool insert_song(Song &song_info){
        int counter = 0; 
        for (int i=0; i < my_playlist.size(); i++){
            if(song_info.get_artist()== my_playlist.at(i).get_artist()){
                counter++;
            }

            if(song_info == my_playlist.at(i) || counter >= 3){
                return false; 
            }
        }
        my_playlist.push_back(song_info);
        cout << "Adding song" << endl;
        return true; 
    }

    Playlist shuffle_song(){
        Playlist my_new_playlist;
        int vector_size = my_playlist.size();

        // my_new_playlist.my_playlist = my_playlist;
        vector<Song> copied_playlist = my_playlist;
        vector<Song> shuffled_playlist;

        while (copied_playlist.size() > 0) 
        {
            int random = (int)(rand() % vector_size - 1);
            shuffled_playlist.push_back(copied_playlist.at(random));
            
            for (int i = 0; i < shuffled_playlist.size(); i++) {
                cout << shuffled_playlist.at(i).get_song_name() << endl;
            }
            copied_playlist.erase(copied_playlist.begin() + random);
        }
        return my_new_playlist; 
    }

    friend Playlist operator+(const Playlist& target1, const Playlist& target2){
        Playlist new_playlist;
        new_playlist.my_playlist.insert(my_playlist.end(), target1.my_playlist.begin(), target1.my_playlist.end());
        new_playlist.my_playlist.insert(my_playlist.end(), target2.my_playlist.begin(), target2.my_playlist.end());
        return new_playlist;
    }
};

void test_insert_songs() {
    Playlist my_new_playlist;
    Song first_song = Song(10, "rock", "we will rock you");
    Song second_song = Song(10, "rock", "we will rock you");
    
    my_new_playlist.insert_song(first_song);
    //test duplicate songs
    my_new_playlist.insert_song(second_song);
    
    //test 4 songs
}

void test_shuffle_songs(Playlist my_new_playlist) {
    my_new_playlist.shuffle_song();
}

int main(){
    srand(time(0));
    test_insert_songs();
    return 0;
}
// Andrew Zhao 20785698
// Jeffery Ng 20762964

#include <iostream>
#include <vector>
#include <random>
#include <ctime>
#include <cstdlib>
#include <cassert>

using namespace std;

// PURPOSE: Models music with artist name, year made and id 
class Music{
    string artist_name;
    unsigned int year_made;
    string id;
public:
    // CONSTRUCTORS
    // Default/empty constuctors for Music
    Music() : year_made(0){   
    }

    //Parametric constructors for Music
    Music(string new_artist_name, unsigned int new_year_made, string new_id){
        artist_name = new_artist_name;
        year_made = new_year_made;
        id = new_id;
    }

    // SERVICE FUNCTIONS
    // PURPOSE: gets artist_name
    // INPUTS: None
    // RETURNS: artist_name
    string get_artist(){
        return artist_name;
    }

    // PURPOSE: compares two pieces of music
    // INPUTS: rhs - Music instance that is being compared 
    // RETURNS: true if the two instances are the same, false otherwise
    bool operator ==(Music &rhs){
        if (artist_name == rhs.artist_name && year_made == rhs.year_made && id == rhs.id){
            return true;
        }
        else{
            return false;
        }
    }       
};

// Models a completed piece of music as a song, inherites attributes from Music class 
class Song : public Music {
    unsigned int song_length;
    string genre;
    string song_name;

public:
    // CONSTRUCTORS
    // Default/empty constructors for Song
    Song() : song_length(0){}

    // Parametric constructor for Song without Music instance 
    Song(unsigned int new_song_length, string new_genre, string new_song_name){
        song_length = new_song_length;
        genre = new_genre; 
        song_name = new_song_name; 
    }

    // Parametric constructor for Song
    Song(unsigned int new_song_length, string new_genre, string new_song_name, Music new_music) : 
        Music(new_music), song_length(new_song_length), genre(new_genre), song_name(new_song_name){}

    // SERVICE FUNCTIONS
    // PURPOSE: compares two songs
    // INPUTS: rhs - song instance that is being compared
    // RETURNS: true if the two instances are the same, false otherwise 
    bool operator == (Song &rhs){
        if (song_length == rhs.song_length && genre == rhs.genre && song_name == rhs.song_name){
            return true;
        }
        else{
            return false;
        }
    }  

    // PURPOSE: gets song_name
    // INPUTS: None
    // RETURNS: song_name
    string get_song_name () {
        return song_name;
    }
};

// PURPOSE: Models a playlist, a collection of songs 
class Playlist{
    vector<Song> my_playlist;
public: 
    // CONSTRUCTORS
    // Default/empty constructors for Playlist
    Playlist(){}

    // PURPOSE: adds a song to the playlist, duplicates not allowed
    // INPUTS: song_info - Song instance 
    // RETURNS: true if the song is added, false otherwise
    bool insert_song(Song &song_info){
        int counter = 0; // number of times the song's artist already appears in the playlist
        for(int i=0; i < my_playlist.size(); i++){
            if(song_info.get_artist() == my_playlist.at(i).get_artist()){
                counter++;
            }

            if(song_info == my_playlist.at(i) || counter >= 3){
                return false; 
            }
        }
        my_playlist.push_back(song_info);
        return true; 
    }

    // PURPOSE: getter method for the playlist
    // INPUTS: none
    // RETURNS: vector of playlist
    vector<Song> get_playlist() {
        return my_playlist;
    }

    // PURPOSE: setter method for the playlist
    // INPUTS: new_playlist
    // RETURNS: none
    void set_playlist(vector<Song> new_playlist) {
        my_playlist = new_playlist;
    }

    // PURPOSE: shuffles songs in a playlist
    // INPUTS: None
    // RETURNS: new playlist with the songs rearranged 
    Playlist shuffle_song(){
        Playlist my_new_playlist;

        vector<Song> shuffled_playlist;
        vector<Song> copied_playlist = my_playlist;

        do {
            shuffled_playlist.clear();
            while (copied_playlist.size() > 0) {
                int vector_size = copied_playlist.size();
                int random = (int)(rand() % vector_size);

                shuffled_playlist.push_back(copied_playlist.at(random));

                copied_playlist.erase(copied_playlist.begin() + random);
            }
            copied_playlist = my_playlist;
        } while (check_two_song_vectors(my_playlist, shuffled_playlist));

        my_new_playlist.set_playlist(shuffled_playlist);
        
        return my_new_playlist; 
    }
    
    // HELPER FUNCTION
    // PURPOSE: checks if two song vectors are the same
    // INPUTS: two song vectors that are compared
    // RETURNS: true if vectors are the same
    bool check_two_song_vectors(vector<Song> vector1, vector<Song> vector2) {
        for (int i = 0; i < vector1.size(); i++) {
            if (!(vector1.at(i) == vector2.at(i))){
                return false;
            }
        }
        return true;
    }
    
    // PURPOSE: compares two playlist objects
    // INPUTS: target_playlist - playlist that is being compared
    // RETURNS: true if playlist are the same
    bool operator == (Playlist& target_playlist) {
        return check_two_song_vectors(target_playlist.my_playlist, my_playlist);
    }    

    // PURPOSE: combines two playlist together 
    // INPUTS: target1 - Playlist instance
    //         target2 - Playlist instance
    // RETURNS: a Playlist with songs from target1 and target2
    friend Playlist operator+(const Playlist& target1, const Playlist& target2);
};

Playlist operator+(const Playlist& target1, const Playlist& target2){
    Playlist new_playlist;
    new_playlist.my_playlist.insert(new_playlist.my_playlist.end(), target1.my_playlist.begin(), target1.my_playlist.end());
    new_playlist.my_playlist.insert(new_playlist.my_playlist.end(), target2.my_playlist.begin(), target2.my_playlist.end());
    return new_playlist;
}

// driver function, used to test song insertion 
Playlist test_insert_songs(){
    Playlist my_new_playlist;
    
    Music lover_album = Music("Taylor Swift", 2019, "01"); 

    // duplicate songs
    Song first_song = Song(245, "Rock", "We will rock you");
    Song second_song = Song(245, "Rock", "We will rock you");

    // four songs by Taylor Swift
    Song third_song = Song(210, "Pop", "Afterglow", lover_album);
    Song fouth_song = Song(220, "Pop", "Lover", lover_album);
    Song fith_song = Song(235, "Pop", "Daylight", lover_album);
    Song sixth_song = Song(215, "Pop", "The Man", lover_album);
   
    //test duplicate songs
    my_new_playlist.insert_song(first_song);
    my_new_playlist.insert_song(second_song); // this won't work
    
    //test 4 songs with the same artist
    my_new_playlist.insert_song(third_song);
    my_new_playlist.insert_song(fouth_song);
    my_new_playlist.insert_song(fith_song);
    my_new_playlist.insert_song(sixth_song); // this won't work
    
    return my_new_playlist;
}

// driver function, used to test if the playlist has been shuffled
void test_shuffle_songs(Playlist my_new_playlist){

    Playlist playlist_copy = my_new_playlist;
    my_new_playlist = my_new_playlist.shuffle_song();

    if (playlist_copy == my_new_playlist) {
        cout << "true" << endl;
    } else {
        cout << "false" << endl;
    }
    
    assert(!(playlist_copy == my_new_playlist));
}

// driver function, used to test adding two playlist together
void add_two_playlists() {
    Playlist my_playlist_1;
    
    Music lover_album = Music("Taylor Swift", 2019, "01"); 

    // duplicate songs
    Song first_song = Song(245, "Rock", "We will rock you");
    Song second_song = Song(245, "Rock", "We will rock you");

    // four songs by Taylor Swift
    Song third_song = Song(210, "Pop", "Afterglow", lover_album);
    Song fouth_song = Song(220, "Pop", "Lover", lover_album);
    Song fith_song = Song(235, "Pop", "Daylight", lover_album);
    Song sixth_song = Song(215, "Pop", "The Man", lover_album);
   
    //test duplicate songs
    my_playlist_1.insert_song(first_song);
    
    //test 4 songs with the same artist
    my_playlist_1.insert_song(third_song);
    my_playlist_1.insert_song(fouth_song);
    my_playlist_1.insert_song(fith_song);

    Playlist my_playlist_2 = my_playlist_1;

    Playlist my_playlist_3 = my_playlist_1 + my_playlist_2;
    vector<Song> playlist3_vector = my_playlist_3.get_playlist();
    
    for(int i = 0; i < playlist3_vector.size(); i++) {
        cout << playlist3_vector.at(i).get_song_name() << endl;
    }
}

int main(){
    srand(time(0));
    Playlist my_playlist_1 = test_insert_songs();
    test_shuffle_songs(my_playlist_1);

    add_two_playlists();
    
    return 0;
}
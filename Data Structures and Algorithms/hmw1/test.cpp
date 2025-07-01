#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

struct MusicTrack {
    std::string title;
    // Add more track information if needed
};

struct Playlist {
    std::vector<MusicTrack> tracks;
};

// Function to add a music track to a playlist
void addTrackToPlaylist(Playlist& playlist, const MusicTrack& newTrack) {
    playlist.tracks.push_back(newTrack);
}

// Function to remove a music track from a playlist
void removeTrackFromPlaylist(Playlist& playlist, const std::string& trackTitle) {
    playlist.tracks.erase(std::remove_if(playlist.tracks.begin(), playlist.tracks.end(),
                                         [trackTitle](const MusicTrack& track) {
                                             return track.title == trackTitle;
                                         }),
                          playlist.tracks.end());
}

// Function to move a music track to a new position on the playlist
void moveTrackInPlaylist(Playlist& playlist, const std::string& trackTitle, int newPosition) {
    auto it = std::find_if(playlist.tracks.begin(), playlist.tracks.end(),
                           [trackTitle](const MusicTrack& track) {
                               return track.title == trackTitle;
                           });

    if (it != playlist.tracks.end()) {
        // Adjust position (1-based to 0-based)
        newPosition--;

        // Move the track to the specified position
        std::rotate(it, it + (newPosition - std::distance(playlist.tracks.begin(), it)), it + 1);
    }
}

// Function to print playlist content
void printPlaylist(const Playlist& playlist) {
    for (const auto& track : playlist.tracks) {
        std::cout << track.title << std::endl;
    }
}

int main() {
    // Example playlists and tracks
    Playlist myPlaylist;
    std::vector<MusicTrack> allTracks = {{"Track1"}, {"Track2"}, {"Track3"}};

    // Command 1: Add a music track to a playlist
    addTrackToPlaylist(myPlaylist, {"NewTrack"});
    printPlaylist(myPlaylist);

    // Command 2: Remove a music track from a playlist
    removeTrackFromPlaylist(myPlaylist, "Track2");
    printPlaylist(myPlaylist);

    // Command 3: Move a music track to a new position on the playlist
    moveTrackInPlaylist(myPlaylist, "NewTrack", 2);
    printPlaylist(myPlaylist);

    return 0;
}
